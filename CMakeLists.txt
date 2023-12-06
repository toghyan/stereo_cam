cmake_minimum_required(VERSION 3.0)
project(CaptureImages)

find_package(OpenCV REQUIRED)

add_executable(capture_images capture_images.cpp)

target_link_libraries(capture_images PRIVATE ${OpenCV_LIBS})
