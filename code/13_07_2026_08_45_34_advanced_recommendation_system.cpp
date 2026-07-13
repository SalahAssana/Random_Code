#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

// Define a struct to represent a product
struct Product {
    string name;
    int rating;
};

// Define a struct to represent user preferences
struct Preferences {
    map<string, int> ratings; // ratings for each product
    vector<Product> likedProducts; // products the user likes
};

// Define a class to represent the recommendation system
class RecommendationSystem {
public:
    // Constructor to initialize the system with data
    RecommendationSystem(const vector<Product>& products) : products_(products), preferences_() {}

    // Function to add user preferences
    void addUserPreferences(const string& username, const map<string, int>& ratings) {
        preferences_[username] = Preferences();
        for (const auto& productRating : ratings) {
            if (productRating.second > 0) {
                preferences_[username].ratings[productRating.first] = productRating.second;
            }
        }
    }

    // Function to recommend products based on user preferences
    vector<Product> recommendProducts(const string& username, int numRecommendations) {
        auto userPreferences = preferences_.find(username);
        if (userPreferences == preferences_.end()) {
            return {}; // no recommendations for this user
        }

        vector<Product> recommendedProducts;
        for (const auto& product : products_) {
            if (product.rating > 0 && userPreferences->ratings.find(product.name) == userPreferences->ratings.end() ||
                userPreferences->ratings[product.name] < product.rating) {
                // recommend the product if it's not rated or if the rating is below average
                recommendedProducts.push_back(product);
            }
        }

        // sort recommendations by average rating in descending order
        sort(recommendedProducts.begin(), recommendedProducts.end(),
             [this](const Product& a, const Product& b) {
                 int avgRatingA = getAverageRating(a.name);
                 int avgRatingB = getAverageRating(b.name);
                 return avgRatingA > avgRatingB;
             });

        // limit the number of recommendations
        if (recommendedProducts.size() > numRecommendations) {
            recommendedProducts.resize(numRecommendations);
        }

        return recommendedProducts;
    }

private:
    map<string, int> getAverageRatings(const vector<Product>& products) {
        map<string, int> averageRatings;
        for (const auto& product : products) {
            if (!product.rating) { // ignore unrated products
                continue;
            }
            averageRatings[product.name] = product.rating / 2; // assume the rating is an average of two ratings
        }
        return averageRatings;
    }

    vector<Product> products_;
    map<string, Preferences> preferences_;
};

int main() {
    vector<Product> products = {
        {"Product A", 4},
        {"Product B", 3},
        {"Product C", 5},
        {"Product D", 2},
        {"Product E", 4}
    };

    RecommendationSystem system(products);

    // add user preferences
    system.addUserPreferences("user1", {{"Product A", 5}, {"Product C", 4}});
    system.addUserPreferences("user2", {{"Product B", 3}, {"Product D", 1}});

    // recommend products
    vector<Product> recommendations = system.recommendProducts("user1", 3);
    for (const auto& product : recommendations) {
        cout << "Recommended product: " << product.name << endl;
    }

    return 0;
}