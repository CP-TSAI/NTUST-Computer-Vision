cmake_minimum_required(VERSION 3.10)
project(Rectification)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Find Eigen package
find_package(Eigen3 REQUIRED)

# Add executable
add_executable(rectification rectification.cpp)

# Include directories for Eigen
target_include_directories(rectification PRIVATE ${EIGEN3_INCLUDE_DIRS})

# Link OpenCV
target_link_libraries(rectification PRIVATE ${OpenCV_LIBS})
