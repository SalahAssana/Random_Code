import cv2
import numpy as np

class Lane:
    def __init__(self, img):
        self.img = img
        self.left_lines = []
        self.right_lines = []

    def find_lines(self):
        gray = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)
        canny = cv2.Canny(blurred, 50, 150)

        contours, _ = cv2.findContours(canny, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for contour in contours:
            x1, y1, x2, y2 = cv2.boundingRect(contour)
            area = cv2.contourArea(contour)
            if 200 < area < 1000 and 50 < abs(x2 - x1) < 400:
                cv2.rectangle(self.img, (x1, y1), (x2, y2), (255, 0, 0), 3)

        left_lines = []
        right_lines = []

        for contour in contours:
            area = cv2.contourArea(contour)
            if area > 100 and abs(x2 - x1) < 200:
                x1, y1, x2, y2 = cv2.boundingRect(contour)
                slope = (y2 - y1) / (x2 - x1)
                intercept = y1 - slope * x1
                if slope > 0.5 or slope < -0.5:
                    if slope > 0:
                        left_lines.append((slope, intercept))
                    else:
                        right_lines.append((slope, intercept))

        self.left_lines = left_lines
        self.right_lines = right_lines

    def draw_lines(self):
        for line in self.left_lines + self.right_lines:
            slope, intercept = line
            x1 = 0
            y1 = int(slope * x1 + intercept)
            x2 = self.img.shape[1]
            y2 = int(slope * x2 + intercept)
            cv2.line(self.img, (x1, y1), (x2, y2), (0, 255, 0), 3)

    def draw_lanes(self):
        for line in self.left_lines:
            slope, intercept = line
            x1 = 0
            y1 = int(slope * x1 + intercept)
            x2 = self.img.shape[1]
            y2 = int(slope * x2 + intercept)
            cv2.line(self.img, (x1, y1), (x2, y2), (255, 0, 0), 3)

        for line in self.right_lines:
            slope, intercept = line
            x1 = self.img.shape[1]
            y1 = int(slope * x1 + intercept)
            x2 = 0
            y2 = int(slope * x2 + intercept)
            cv2.line(self.img, (x1, y1), (x2, y2), (255, 0, 0), 3)

def main():
    video_capture = cv2.VideoCapture("traffic_video.mp4")

    while True:
        ret, frame = video_capture.read()
        if not ret:
            break

        lane = Lane(frame)
        lane.find_lines()
        lane.draw_lanes()

        cv2.imshow('Traffic Simulation', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    video_capture.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':