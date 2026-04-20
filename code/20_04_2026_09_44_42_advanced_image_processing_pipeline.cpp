#include <iostream>
#include <fstream>
#include <vector>
#include "filter.h"
#include "resize.h"

using namespace std;

int main() {
    // Read image from file
    ifstream imageFile("input.png", ios::binary);
    vector<vector<uchar>> image;
    imageFile.seekg(0, ios::beg);
    imageFile.read(reinterpret_cast<char*>(image.data()), 1024 * 1024); // assuming 1MB image

    // Apply filters in a pipeline
    FilterChain chain;

    // Add filters to the chain
    chain.add(new SharpenFilter());
    chain.add(new BlurFilter());
    chain.add(new ThresholdFilter(128));

    // Resize the image
    Resizer resizer(0.5);
    Image resizedImage = resizer.resize(chain.apply(image));

    // Save the processed image
    ofstream output("output.png", ios::binary);
    output.write(reinterpret_cast<char*>(resizedImage.data()), 1024 * 512); // assuming 512KB output

    return 0;
}

// Filter interface
class Filter {
public:
    virtual ~Filter() {}
    virtual vector<vector<uchar>> apply(vector<vector<uchar>> image) = 0;
};

// Concrete filter classes
class SharpenFilter : public Filter {
public:
    vector<vector<uchar>> apply(vector<vector<uchar>> image) override {
        // implement sharpening algorithm here
        return image;
    }
};

class BlurFilter : public Filter {
public:
    vector<vector<uchar>> apply(vector<vector<uchar>> image) override {
        // implement blurring algorithm here
        return image;
    }
};

class ThresholdFilter : public Filter {
public:
    int threshold;

    ThresholdFilter(int t) : threshold(t) {}

    vector<vector<uchar>> apply(vector<vector<uchar>> image) override {
        for (int i = 0; i < image.size(); ++i) {
            for (int j = 0; j < image[0].size(); ++j) {
                if (image[i][j] > threshold) {
                    image[i][j] = 255;
                } else {
                    image[i][j] = 0;
                }
            }
        }
        return image;
    }
};

// Filter chain class
class FilterChain {
public:
    void add(Filter* filter) {
        filters_.push_back(filter);
    }

    vector<vector<uchar>> apply(vector<vector<uchar>> image) {
        for (auto& filter : filters_) {
            image = filter->apply(image);
        }
        return image;
    }

private:
    vector<Filter*> filters_;
};