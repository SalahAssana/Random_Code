import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from PIL import Image

class ImageSegmentation:
    def __init__(self, image_path):
        self.image = np.array(Image.open(image_path))
        self.n_clusters = 5

    def kmeans_segmentation(self):
        flattened_image = self.image.reshape((-1, 3))
        kmeans = KMeans(n_clusters=self.n_clusters)
        kmeans.fit(flattened_image)
        labels = kmeans.labels_
        return labels

    def segment_image(self, labels):
        segmented_image = np.zeros((self.image.shape[0], self.image.shape[1], 3))
        for i in range(self.image.shape[0]):
            for j in range(self.image.shape[1]):
                pixel_value = self.image[i][j]
                cluster_id = labels[np.where((flattened_image == pixel_value).all(axis=1))[0][0]]
                segmented_image[i][j] = np.mean(kmeans.cluster_centers_[cluster_id], axis=0)
        return segmented_image

    def visualize_results(self, segmented_image):
        plt.figure(figsize=(10, 5))
        plt.subplot(121)
        plt.imshow(self.image)
        plt.title('Original Image')
        plt.subplot(122)
        plt.imshow(segmented_image)
        plt.title('Segmented Image')
        plt.show()

if __name__ == '__main__':
    image_segmentation = ImageSegmentation('image.jpg')
    labels = image_segmentation.kmeans_segmentation()
    segmented_image = image_segmentation.segment_image(labels)
    image_segmentation.visualize_results(segmented_image)