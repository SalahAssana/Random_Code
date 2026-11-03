#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Function to extract specific information from HTML
class WebScraper {
public:
    map<string, string> scrape(const string& url) {
        // Initialize a map to store the extracted information
        unordered_map<string, string> result;

        // Open the URL and read its content
        ifstream file(url);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return result;
        }

        // Extract specific information from the HTML content
        string line;
        while (getline(file, line)) {
            size_t pos = line.find("title>");
            if (pos != string::npos) {
                size_t endPos = line.find("</title>");
                if (endPos != string::npos) {
                    result["Title"] = line.substr(pos + 7, endPos - pos - 7);
                }
            }

            pos = line.find("description>");
            if (pos != string::npos) {
                size_t endPos = line.find("</description>");
                if (endPos != string::npos) {
                    result["Description"] = line.substr(pos + 12, endPos - pos - 13);
                }
            }

            // Add more conditions to extract specific information
        }

        return result;
    }
};

int main() {
    WebScraper scraper;

    map<string, string> data1 = scraper.scrape("website1.html");
    cout << "Data from website1: " << endl;
    for (auto& pair : data1) {
        cout << pair.first << ": " << pair.second << endl;
    }

    map<string, string> data2 = scraper.scrape("website2.html");
    cout << "Data from website2: " << endl;
    for (auto& pair : data2) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}