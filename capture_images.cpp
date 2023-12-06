#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap1(0, cv::CAP_V4L2); // Use the appropriate camera index for camera 1
    cv::VideoCapture cap2(1, cv::CAP_V4L2); // Use the appropriate camera index for camera 2

    if (!cap1.isOpened() || !cap2.isOpened()) {
        std::cerr << "Error: Unable to open one or both cameras." << std::endl;
        return 1;
    }

    cv::Mat frame1, frame2;

    // Grab a single frame from both cameras
    if (cap1.grab() && cap2.grab()) {
        cap1.retrieve(frame1);
        cap2.retrieve(frame2);

        // Save the captured frames as images
        cv::imwrite("image1.jpg", frame1);
        cv::imwrite("image2.jpg", frame2);

        // Release the camera resources
        cap1.release();
        cap2.release();

        return 0;
    } else {
        std::cerr << "Error: Failed to capture frames from one or both cameras." << std::endl;
        return 1;
    }
}

