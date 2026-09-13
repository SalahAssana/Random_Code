#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Define a struct to represent a 2D complex number
struct Complex {
    double real;
    double imag;
};

// Define a class for the wavelet transform
class WaveletTransform {
public:
    // Perform the discrete wavelet transform (DWT)
    vector<vector<Complex>> dwt(vector<vector<double>> image) {
        int N = image.size();
        int M = image[0].size();

        vector<vector<Complex>> cwt(N, vector<Complex>(M));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                Complex temp;
                temp.real = 0.5 * image[i][j];
                temp.imag = 0;

                // Calculate the horizontal and vertical wavelet coefficients
                if (i > 0) {
                    temp.real += 0.5 * image[i-1][j];
                }
                if (j > 0) {
                    temp.real += 0.5 * image[i][j-1];
                }
                if (i > 0 && j > 0) {
                    temp.real -= 0.25 * image[i-1][j-1];
                }

                cwt[i][j] = temp;
            }
        }

        return cwt;
    }

    // Perform the inverse discrete wavelet transform (IDWT)
    vector<vector<double>> idwt(vector<vector<Complex>> cwt) {
        int N = cwt.size();
        int M = cwt[0].size();

        vector<vector<double>> image(N, vector<double>(M));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                double temp = 2 * cwt[i][j].real;

                // Calculate the horizontal and vertical wavelet coefficients
                if (i > 0) {
                    temp -= image[i-1][j];
                }
                if (j > 0) {
                    temp -= image[i][j-1];
                }
                if (i > 0 && j > 0) {
                    temp += image[i-1][j-1];
                }

                image[i][j] = temp;
            }
        }

        return image;
    }
};

// Define a class for the Haar wavelet
class HaarWavelet {
public:
    // Perform the Haar wavelet transform on an array of coefficients
    vector<vector<Complex>> haarTransform(vector<double> coeffs) {
        int N = coeffs.size();

        vector<vector<Complex>> hwt(N / 2, vector<Complex>(N / 2));

        for (int i = 0; i < N / 2; i++) {
            for (int j = 0; j < N / 2; j++) {
                Complex temp;
                temp.real = 0.5 * (coeffs[2 * i] + coeffs[2 * i + 1]);
                temp.imag = 0;

                if (i > 0) {
                    temp.real -= 0.25 * (coeffs[2 * i - 1] + coeffs[2 * i]);
                }
                if (j > 0) {
                    temp.real -= 0.25 * (coeffs[2 * i] + coeffs[2 * i + 1]);
                }

                hwt[i][j] = temp;
            }
        }

        return hwt;
    }

    // Perform the inverse Haar wavelet transform on an array of coefficients
    vector<double> haarInverse(vector<vector<Complex>> hwt) {
        int N = hwt.size() * 2;

        vector<double> coeffs(N);

        for (int i = 0; i < hwt.size(); i++) {
            for (int j = 0; j < hwt[0].size(); j++) {
                double temp = 2 * hwt[i][j].real;

                // Calculate the horizontal and vertical wavelet coefficients
                if (i > 0) {
                    temp -= hwt[i-1][j].real;
                }
                if (j > 0) {
                    temp -= hwt[i][j-1].real;
                }
                if (i > 0 && j > 0) {
                    temp += hwt[i-1][j-1].real;
                }

                coeffs[2 * i] = temp;
                coeffs[2 * i + 1] = temp;
            }
        }

        return coeffs;
    }
};

int main() {
    // Load the image
    vector<vector<double>> image = {{0.5, 0.3, 0.7}, {0.8, 0.6, 0.9}, {0.1, 0.4, 0.2}};

    // Perform the wavelet transform
    WaveletTransform wt;
    vector<vector<Complex>> cwt = wt.dwt(image);

    // Apply the Haar wavelet to the coefficients
    HaarWavelet hw;
    vector<double> coeffs(N * M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            coeffs[i * M + j] = cwt[i][j].real;
        }
    }
    vector<vector<Complex>> hwt = hw.haarTransform(coeffs);

    // Perform the inverse Haar wavelet transform
    vector<double> ihwt = hw.haarInverse(hwt);

    // Reconstruct the image using the inverse wavelet transform
    vector<vector<double>> reconstructedImage = wt.idwt(ihwt);

    // Print the reconstructed image
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << reconstructedImage[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}