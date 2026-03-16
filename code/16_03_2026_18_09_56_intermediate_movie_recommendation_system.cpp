#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Movie {
    string title;
    vector<int> ratings;
};

struct User {
    string name;
    map<string, int> ratings;
};

double calculateCosine(Movie& m1, Movie& m2) {
    double dotProduct = 0.0;
    double magnitudeM1 = 0.0;
    double magnitudeM2 = 0.0;

    for (int i = 0; i < m1.ratings.size(); i++) {
        int rating = m1.ratings[i];
        if (m2.ratings.find(m1.title) != m2.ratings.end() && m2.ratings[m1.title] == rating) {
            dotProduct += pow(rating, 2);
        }
    }

    for (int i = 0; i < m1.ratings.size(); i++) {
        int rating = m1.ratings[i];
        magnitudeM1 += pow(rating, 2);
    }

    for (auto& rating : m2.ratings) {
        magnitudeM2 += pow(rating.second, 2);
    }

    double magnitudeM1Sqrt = sqrt(magnitudeM1);
    double magnitudeM2Sqrt = sqrt(magnitudeM2);

    if (magnitudeM1 == 0.0 || magnitudeM2 == 0.0) {
        return 0.0;
    } else {
        return dotProduct / (magnitudeM1 * magnitudeM2);
    }
}

vector<string> getRecommendations(Movie& movie, map<string, User>& users, int k) {
    vector<string> recommendations;

    for (auto& user : users) {
        double cosine = 0.0;
        for (auto& otherMovie : users) {
            if (&otherMovie != &user && otherMovie.second.ratings.find(movie.title) != otherMovie.second.ratings.end()) {
                cosine += calculateCosine(movie, *(&otherMovie));
            }
        }

        int index = static_cast<int>(cosine * 100);
        for (int i = 0; i < k; i++) {
            if (index >= users.size() - 1) {
                break;
            } else {
                recommendations.push_back(users.begin()->first);
                index++;
            }
        }

        if (recommendations.size() == k) {
            break;
        }
    }

    return recommendations;
}

int main() {
    map<string, Movie> movies = {
        {"Movie1", {"Title1", {5, 4, 3}}},
        {"Movie2", {"Title2", {5, 4}}}
    };

    map<string, User> users = {
        {"User1", {"Name1", {{"Movie1": 5}, {"Movie2": 4}}}},
        {"User2", {"Name2", {{"Movie1": 4}, {"Movie2": 5}}}}
    };

    vector<string> recommendations = getRecommendations(*movies.begin()->second, users, 3);

    for (auto& recommendation : recommendations) {
        cout << recommendation << endl;
    }

    return 0;
}