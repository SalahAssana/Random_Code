import cv2
import numpy as np

def apply_filter(image, kernel):
    """
    Apply a convolutional filter to an image.
    
    Args:
        image (numpy array): The input image.
        kernel (numpy array): The convolutional filter.
        
    Returns:
        A new image with the filter applied.
    """
    return cv2.filter2D(image, -1, kernel)

def apply_thresholding(image):
    """
    Apply thresholding to an edge detected image.
    
    Args:
        image (numpy array): The input image.
        
    Returns:
        A new image with the threshold applied.
    """
    _, thresh = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
    return thresh

def detect_edges(image):
    """
    Detect edges in an image using convolution and thresholding.
    
    Args:
        image (numpy array): The input image.
        
    Returns:
        A new image with the detected edges.
    """
    # Define the Sobel operator kernel
    sobel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    sobel_y = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])

    # Apply the Sobel operator to detect edges
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gradient_x = apply_filter(gray, sobel_x)
    gradient_y = apply_filter(gray, sobel_y)
    gradient = np.sqrt(gradient_x**2 + gradient_y**2)

    # Apply thresholding to the edge detected image
    return apply_thresholding(gradient)

def main():
    """
    Main function.
    
    Returns:
        None.
    """
    # Load an example image
    image_path = 'image.jpg'
    image = cv2.imread(image_path)

    # Detect edges in the image
    edged_image = detect_edges(image)

    # Display the original and edge detected images
    cv2.imshow('Original', image)
    cv2.imshow('Edged', edged_image)

    # Wait for a key press before closing all windows
    cv2.waitKey(0)

    # Close all windows
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()