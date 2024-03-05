cmake_minimum_required(VERSION 3.10)
project(Homework05)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Find Eigen package
find_package(Eigen3 REQUIRED)

# Add executable
add_executable(homework05 homework05.cpp)

# Include directories for Eigen
target_include_directories(homework05 PRIVATE ${EIGEN3_INCLUDE_DIRS})

# Link OpenCV
target_link_libraries(homework05 PRIVATE ${OpenCV_LIBS})
