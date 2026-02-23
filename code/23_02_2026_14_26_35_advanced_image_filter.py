from PIL import Image, ImageFilter
import numpy as np

class Filter:
    def __init__(self, image):
        self.image = image

    def apply_filter(self, filter_type):
        if filter_type == "grayscale":
            return self.apply_grayscale()
        elif filter_type == "blur":
            return self.apply_blur()
        else:
            raise ValueError("Invalid filter type")

    def apply_grayscale(self):
        filtered_image = Image.fromarray(np.array(self.image).astype('float32') / 255.0)
        filtered_image.putalpha(255) # Preserve alpha channel
        filtered_image = filtered_image.convert('L')
        return filtered_image.filter(ImageFilter.GRAY)

    def apply_blur(self):
        blurred_image = self.image.filter(ImageFilter.BLUR)
        return blurred_image

def main():
    if __name__ == '__main__':
        image_path = "path_to_your_image.jpg"
        original_image = Image.open(image_path)
        filter_instance = Filter(original_image)

        print("Available filters: ")
        print("1. Grayscale")
        print("2. Blur")

        choice = input("Enter the number of your preferred filter (1/2): ")

        if choice == "1":
            filtered_image = filter_instance.apply_filter("grayscale")
        elif choice == "2":
            filtered_image = filter_instance.apply_filter("blur")
        else:
            print("Invalid choice. Exiting.")
            exit()

        filtered_image.save('filtered_image.jpg')

if __name__ == '__main__':
    main()