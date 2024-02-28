cmake_minimum_required(VERSION 3.10)
project(Homework02)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Find Eigen package
find_package(Eigen3 REQUIRED)

# Add executable
add_executable(homework02 homework02.cpp)

# Include directories for Eigen
target_include_directories(homework02 PRIVATE ${EIGEN3_INCLUDE_DIRS})

# Link OpenCV
target_link_libraries(homework02 PRIVATE ${OpenCV_LIBS})
