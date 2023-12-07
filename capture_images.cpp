#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

std::string gstreamer_pipeline (int camera_index, int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc sensor_id=" + std::to_string(camera_index) + " ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main() {

    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 30 ;
    int flip_method = 2;

    std::string pipeline_0 = gstreamer_pipeline(0,
	capture_width,
	capture_height,
	display_width,
	display_height,
	framerate,
	flip_method);
    std::string pipeline_1 = gstreamer_pipeline(1,
        capture_width,
        capture_height,
        display_width,
        display_height,
        framerate,
        flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline_0 << "\n";

    cv::VideoCapture cap1(pipeline_0, cv::CAP_GSTREAMER); // Use the appropriate camera index for camera 1
    cv::VideoCapture cap2(pipeline_1, cv::CAP_GSTREAMER); // Use the appropriate camera index for camera 2

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

