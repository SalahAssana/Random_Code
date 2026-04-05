import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

class ImageSegmentation:
    def __init__(self, image_path, num_clusters):
        self.image_path = image_path
        self.num_clusters = num_clusters

    def load_image(self):
        from PIL import Image
        img = Image.open(self.image_path).convert('RGB')
        return np.array(img)

    def segment_image(self):
        image = self.load_image()
        kmeans = KMeans(n_clusters=self.num_clusters)
        pixel_values = image.reshape((-1, 3))
        labels = kmeans.fit_predict(pixel_values)
        segmented_image = labels.reshape(image.shape[:2] + (self.num_clusters,))
        return segmented_image

    def display_segmented_image(self, segmented_image):
        plt.imshow(segmented_image.astype('uint8'))
        plt.show()

if __name__ == '__main__':
    segmentation = ImageSegmentation('image.jpg', 4)
    segmented_image = segmentation.segment_image()
    segmentation.display_segmented_image(segmented_image)