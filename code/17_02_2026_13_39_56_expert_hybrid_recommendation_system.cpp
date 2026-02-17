#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <random>

// Hybrid Recommendation System
class HybridRecommender {
public:
    HybridRecommender(const std::vector<std::pair<int, int>>& user_item_interactions) 
        : user_item_interactions_(user_item_interactions), 
          collaborative_filtering_model_(),
          content_based_filtering_model_() {}

    // Collaborative Filtering
    double calculate_similarity(int user_id1, int user_id2) {
        std::vector<int> user_items1, user_items2;
        for (const auto& interaction : user_item_interactions_) {
            if (interaction.first == user_id1 || interaction.first == user_id2) {
                user_items1.push_back(interaction.second);
                if (interaction.first != user_id1) {
                    user_items2.push_back(interaction.second);
                }
            }
        }

        double similarity = 0.0;
        for (const auto& item : user_items1) {
            if (std::count(user_items2.begin(), user_items2.end(), item) > 0) {
                similarity += std::pow(1.0, std::sqrt(std::count(user_items1.begin(), user_items1.end(), item)));
            }
        }

        return similarity;
    }

    // Content-Based Filtering
    double calculate_similarity(int user_id, int item_id) {
        std::map<int, double> user_features, item_features;

        for (const auto& interaction : user_item_interactions_) {
            if (interaction.first == user_id) {
                user_features[interaction.second] = 1.0;
            }
            else if (interaction.second == item_id) {
                item_features[interaction.first] = 1.0;
            }
        }

        double similarity = std::inner_product(user_features.begin(), user_features.end(), item_features.begin(), 0.0);
        return similarity;
    }

    // Hybrid Recommendation
    std::vector<std::pair<int, int>> get_recommendations(int user_id) {
        std::vector<std::pair<int, int>> recommendations;

        // Calculate Collaborative Filtering Similarity
        double max_similarity = -1.0;
        for (const auto& interaction : user_item_interactions_) {
            if (interaction.first != user_id) {
                double similarity = calculate_similarity(user_id, interaction.second);
                if (similarity > max_similarity) {
                    max_similarity = similarity;
                }
            }
        }

        // Calculate Content-Based Filtering Similarity
        std::map<int, double> item_features;
        for (const auto& interaction : user_item_interactions_) {
            if (interaction.first == user_id) {
                item_features[interaction.second] = 1.0;
            }
        }

        // Hybrid Recommendation
        for (int item_id = 1; item_id <= 10; ++item_id) {
            double similarity_cf = 0.0, similarity_cbf = 0.0;

            if (std::count(user_item_interactions_.begin(), user_item_interactions_.end(), std::make_pair(user_id, item_id)) == 0) {
                for (const auto& interaction : user_item_interactions_) {
                    if (interaction.first != user_id && interaction.second == item_id) {
                        similarity_cf += calculate_similarity(user_id, interaction.second);
                    }
                    else if (interaction.second == item_id) {
                        similarity_cbf = calculate_similarity(user_id, item_id);
                    }
                }

                double score = 0.5 * max_similarity + 0.5 * similarity_cbf;
                recommendations.emplace_back(user_id, item_id, score);
            }
        }

        std::sort(recommendations.begin(), recommendations.end(), [](const auto& a, const auto& b) {
            return a.z > b.z;
        });

        return recommendations;
    }

private:
    std::vector<std::pair<int, int>> user_item_interactions_;
};

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    std::vector<std::pair<int, int>> user_item_interactions;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 5; ++j) {
            user_item_interactions.emplace_back(i, dist(gen));
        }
    }

    HybridRecommender recommender(user_item_interactions);

    std::vector<std::pair<int, int>> recommendations = recommender.get_recommendations(1);
    for (const auto& recommendation : recommendations) {
        std::cout << "User 1 recommended item " << recommendation.second << " with score " << recommendation.third << std::endl;
    }

    return 0;
}