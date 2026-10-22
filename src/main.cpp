
#include <opencv2/opencv.hpp>

#include <chrono>
#include <iostream>

int main() {
    // AVFoundation is macOS's native camera backend.
    cv::VideoCapture camera(0, cv::CAP_AVFOUNDATION);

    if (!camera.isOpened()) {
        std::cerr << "Failed to open camera.\n";
        return 1;
    }

    std::cout << "Camera connected!\n";
    std::cout << "Press Q to quit.\n";

    cv::Mat frame;

    auto lastTime = std::chrono::steady_clock::now();

    while (true) {
        if (!camera.read(frame) || frame.empty()) {
            std::cerr << "Failed to capture frame.\n";
            break;
        }

        // Calculate instantaneous FPS.
        const auto now = std::chrono::steady_clock::now();

        const double elapsed =
            std::chrono::duration<double>(now - lastTime).count();

        lastTime = now;

        const double fps = elapsed > 0.0 ? 1.0 / elapsed : 0.0;

        // Draw the FPS counter on the video.
        cv::putText(
            frame,
            cv::format("FPS: %.1f", fps),
            cv::Point(20, 40),
            cv::FONT_HERSHEY_SIMPLEX,
            1.0,
            cv::Scalar(0, 255, 0),
            2
        );

        cv::imshow("Traffic Monitor", frame);

        const int key = cv::waitKey(1);

        if (key == 'q' || key == 'Q') {
            break;
        }
    }

    camera.release();
    cv::destroyAllWindows();

    return 0;
}
