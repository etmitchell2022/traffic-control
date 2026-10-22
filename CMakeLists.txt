
cmake_minimum_required(VERSION 3.20)

project(traffic_monitor
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV 4 REQUIRED COMPONENTS
    core
    imgproc
    highgui
    videoio
)

add_executable(traffic_monitor
    src/main.cpp
)

target_include_directories(traffic_monitor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(traffic_monitor PRIVATE
    ${OpenCV_LIBS}
)

target_compile_options(traffic_monitor PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
