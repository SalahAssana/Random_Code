#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <algorithm>

using namespace std;
using namespace Eigen;

void load_data(vector<vector<double>>& user_item_matrix, vector<pair<int, int>>& user_item_pairs) {
    // Load synthetic data
    user_item_matrix.resize(5, 10);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            user_item_matrix(i, j) = rand() % 2;
        }
    }

    // Generate synthetic user-item pairs
    user_item_pairs.resize(20);
    int id = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (user_item_matrix(i, j) == 1) {
                user_item_pairs[id] = make_pair(i, j);
                id++;
            }
        }
    }
}

void matrix_factorization(vector<vector<double>>& user_item_matrix, vector<pair<int, int>>& user_item_pairs, MatrixXd& P, MatrixXd& Q, double lambda, double alpha, int iterations) {
    // Initialize matrices
    P.resize(user_item_matrix.rows(), 2);
    Q.resize(2, user_item_matrix.cols());

    // Random initialization of latent factors
    for (int i = 0; i < P.rows(); i++) {
        for (int j = 0; j < P.cols(); j++) {
            P(i, j) = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    for (int i = 0; i < Q.rows(); i++) {
        for (int j = 0; j < Q.cols(); j++) {
            Q(i, j) = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    // Matrix factorization
    for (int iteration = 0; iteration < iterations; iteration++) {
        for (const auto& pair : user_item_pairs) {
            int user_id = pair.first;
            int item_id = pair.second;

            VectorXd u(P.rows());
            VectorXd v(Q.cols());

            // Compute latent factors
            for (int i = 0; i < P.rows(); i++) {
                u(i) = P(i, 0) + P(i, 1);
            }

            for (int j = 0; j < Q.cols(); j++) {
                v(j) = Q(0, j) + Q(1, j);
            }

            // Compute predicted rating
            double prediction = u.dot(v);

            // Update latent factors
            VectorXd error = (prediction - user_item_matrix(user_id, item_id)) * alpha;
            for (int i = 0; i < P.rows(); i++) {
                P(i, 0) += (error(i) + lambda * P(i, 0));
                P(i, 1) += (error(i) + lambda * P(i, 1));
            }

            for (int j = 0; j < Q.cols(); j++) {
                Q(0, j) += (error(j) + lambda * Q(0, j));
                Q(1, j) += (error(j) + lambda * Q(1, j));
            }
        }
    }
}

void generate_recommendations(vector<vector<double>>& user_item_matrix, vector<pair<int, int>>& user_item_pairs, MatrixXd& P, MatrixXd& Q, int num_recommendations) {
    // Generate recommendations for each user
    for (int i = 0; i < user_item_matrix.rows(); i++) {
        VectorXd u(P.rows());
        for (int j = 0; j < P.rows(); j++) {
            u(j) = P(i, 0) + P(i, 1);
        }

        MatrixXd v(Q.cols(), num_recommendations);
        for (int j = 0; j < Q.cols(); j++) {
            for (int k = 0; k < num_recommendations; k++) {
                v(j, k) = Q(0, j) + Q(1, j);
            }
        }

        // Compute dot product of user latent factors and item latent factors
        VectorXd predictions(user_item_matrix.cols());
        for (int j = 0; j < user_item_matrix.cols(); j++) {
            VectorXd prediction(v.col(0));
            for (int k = 1; k < num_recommendations; k++) {
                prediction += v.col(k);
            }

            // Compute top-N recommendations
            int topN_index = 0;
            double max_prediction = -DBL_MAX;
            for (int j = 0; j < user_item_matrix.cols(); j++) {
                double prediction_value = u.dot(v.col(j));
                if (prediction_value > max_prediction) {
                    max_prediction = prediction_value;
                    topN_index = j;
                }
            }

            // Print recommendation
            cout << "User " << i << " recommended item " << topN_index << endl;
        }
    }
}

int main() {
    vector<vector<double>> user_item_matrix;
    vector<pair<int, int>> user_item_pairs;

    load_data(user_item_matrix, user_item_pairs);

    MatrixXd P, Q;

    double lambda = 0.1;
    double alpha = 0.2;
    int iterations = 10;
    int num_recommendations = 5;

    matrix_factorization(user_item_matrix, user_item_pairs, P, Q, lambda, alpha, iterations);
    generate_recommendations(user_item_matrix, user_item_pairs, P, Q, num_recommendations);

    return 0;
}