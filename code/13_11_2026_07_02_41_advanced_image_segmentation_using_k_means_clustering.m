% Image Segmentation using K-Means Clustering
%
% This script demonstrates the use of K-means clustering to segment an image into
% different clusters based on color.

% Import necessary libraries
import java.awt.image.BufferedImage;
import javax.swing.*;
import java.io.*;

class ImageSegmentation {
    public static void main(String[] args) throws Exception {

        // Load the image
        BufferedImage img = ImageIO.read(new File("image.jpg"));

        // Convert the image to a matrix of pixel values
        int[][] pixels = new int[img.getHeight()][img.getWidth()];
        for (int i = 0; i < img.getHeight(); i++) {
            for (int j = 0; j < img.getWidth(); j++) {
                pixels[i][j] = img.getRGB(j, i);
            }
        }

        // Define the number of clusters
        int K = 5;

        // Perform k-means clustering
        double[][] centroids = kMeans(pixels, K);

        // Segment the image into different clusters
        for (int i = 0; i < img.getHeight(); i++) {
            for (int j = 0; j < img.getWidth(); j++) {
                int pixelValue = pixels[i][j];
                double minDistance = Double.MAX_VALUE;
                for (int k = 0; k < K; k++) {
                    double distance = euclideanDistance(pixelValue, centroids[k]);
                    if (distance < minDistance) {
                        minDistance = distance;
                        img.setRGB(j, i, getClusterColor(k));
                    }
                }
            }
        }

        // Display the segmented image
        JFrame frame = new JFrame("Image Segmentation");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel label = new JLabel(new ImageIcon(img));
        frame.getContentPane().add(label);
        frame.pack();
        frame.setVisible(true);

    }

    // Function to perform k-means clustering
    public static double[][] kMeans(int[][] pixels, int K) {
        Random rand = new Random();

        // Initialize the centroids randomly
        double[][] centroids = new double[K][3];
        for (int i = 0; i < K; i++) {
            int[] pixelValue = new int[3];
            for (int j = 0; j < 3; j++) {
                pixelValue[j] = rand.nextInt(256);
            }
            centroids[i] = pixelValue;
        }

        // Perform k-means clustering
        double[][] clusters = new double[pixels.length][3];
        int[] labels = new int[pixels.length];

        for (int i = 0; i < pixels.length; i++) {
            double minDistance = Double.MAX_VALUE;
            int clusterIndex = -1;
            for (int j = 0; j < K; j++) {
                double distance = euclideanDistance(pixels[i][j], centroids[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    clusterIndex = j;
                }
            }
            clusters[i] = pixels[i];
            labels[i] = clusterIndex;
        }

        // Update the centroids
        for (int i = 0; i < K; i++) {
            double[] sum = new double[3];
            int count = 0;
            for (int j = 0; j < pixels.length; j++) {
                if (labels[j] == i) {
                    for (int k = 0; k < 3; k++) {
                        sum[k] += clusters[j][k];
                    }
                    count++;
                }
            }
            for (int k = 0; k < 3; k++) {
                centroids[i][k] = sum[k] / count;
            }
        }

        return centroids;
    }

    // Function to calculate the Euclidean distance between two points
    public static double euclideanDistance(int a, int b) {
        return Math.sqrt(Math.pow((a - (b >> 8)) / 255.0, 2) + Math.pow(((a & 0xFF) - (b & 0xFF)) / 255.0, 2));
    }

    // Function to get the color of a cluster
    public static int getClusterColor(int clusterIndex) {
        Random rand = new Random();
        return (rand.nextInt(256) << 8) | rand.nextInt(256);
    }
}