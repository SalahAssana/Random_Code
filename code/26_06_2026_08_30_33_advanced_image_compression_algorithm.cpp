#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Image {
public:
    vector<vector<int>> pixels;
    int width;
    int height;

    Image(int w, int h) : width(w), height(h) {}

    void addPixel(int x, int y, int val) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = val;
        }
    }

    void compress() {
        vector<vector<int>> compressedPixels(pixels.size(), vector<int>(pixels[0].size()));
        for (int i = 0; i < pixels.size(); i++) {
            for (int j = 0; j < pixels[i].size(); j++) {
                int val = pixels[i][j];
                if (val > 128) {
                    compressedPixels[i][j] = 255;
                } else {
                    compressedPixels[i][j] = 0;
                }
            }
        }
        swap(pixels, compressedPixels);
    }

    void decompress() {
        vector<vector<int>> decompressedPixels(pixels.size(), vector<int>(pixels[0].size()));
        for (int i = 0; i < pixels.size(); i++) {
            for (int j = 0; j < pixels[i].size(); j++) {
                int val = pixels[i][j];
                if (val == 255) {
                    decompressedPixels[i][j] = 128 + (rand() % 127);
                } else {
                    decompressedPixels[i][j] = 0;
                }
            }
        }
        swap(pixels, decompressedPixels);
    }

    void printImage() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << pixels[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Image img(10, 10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int val = rand() % 256;
            img.addPixel(j, i, val);
        }
    }
    cout << "Original Image:" << endl;
    img.printImage();
    img.compress();
    cout << "Compressed Image:" << endl;
    img.printImage();
    img.decompress();
    cout << "Decompressed Image:" << endl;
    img.printImage();
    return 0;
}