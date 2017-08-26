// homework01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h> 
#include "opencv/opencv2/opencv.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <conio.h> 
#include <Eigen/Dense>  

#ifdef ___WIN_X64_LIB___
#pragma comment(lib, "../../lib/x64/opencv_world320.lib")
#endif

#ifdef ___WIN_X86_LIB___
#pragma comment(lib, "../../lib/x86/opencv_world320.lib")
#endif

using namespace cv;
using namespace Eigen;
using namespace std;


// describe the coordination on an image
class Coordination
{
private:
	double x = 0;
	double y = 0;
public:
	Coordination(int a, int b) // constructor
	{
		x = a;
		y = b;
	}
	double getx() { return x; }
	double gety() { return y; }
	
};

// normalize the 3x1 matrix
MatrixXd normalized_3x1(MatrixXd& mat)
{
	mat(0, 0) = mat(0, 0) / mat(2, 0);
	mat(1, 0) = mat(1, 0) / mat(2, 0);
	mat(2, 0) = 1;
	return mat;
}


int main()
{
	// read image 
	cv::Mat myJPG_001 = cv::imread("1.JPG");  // Read the 001 file
	cv::Mat myJPG_002 = cv::imread("2.JPG");  // Read the 002 file
	if (!myJPG_001.data || !myJPG_002.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	
	// initialize the boundary point
	Coordination p1_1(437, 205);  // point on 1.jpg => 1
	Coordination p1_2(1979, 351);  // point on 1.jpg => 2
	Coordination p1_3(1977, 1469);  // point on 1.jpg => 3
	Coordination p1_4(433, 1563);  // point on 1.jpg => 4

	Coordination p2_1(505, 317);  // point on 2.jpg => 1
	Coordination p2_2(1883, 607);  // point on 2.jpg => 2
	Coordination p2_3(1893, 1679);  // point on 2.jpg => 3
	Coordination p2_4(477, 1755);  // point on 2.jpg => 4

	// calculate the Homography matrix
	MatrixXd HomoMat(8, 8);
	HomoMat <<
		p2_1.getx(), p2_1.gety(), 1, 0, 0, 0, -p1_1.getx()*p2_1.getx(), -p1_1.getx()*p2_1.gety(),
		0, 0, 0, p2_1.getx(), p2_1.gety(), 1, -p1_1.gety()*p2_1.getx(), -p1_1.gety()*p2_1.gety(),
		p2_2.getx(), p2_2.gety(), 1, 0, 0, 0, -p1_2.getx()*p2_2.getx(), -p1_2.getx()*p2_2.gety(),
		0, 0, 0, p2_2.getx(), p2_2.gety(), 1, -p1_2.gety()*p2_2.getx(), -p1_2.gety()*p2_2.gety(),
		p2_3.getx(), p2_3.gety(), 1, 0, 0, 0, -p1_3.getx()*p2_3.getx(), -p1_3.getx()*p2_3.gety(),
		0, 0, 0, p2_3.getx(), p2_3.gety(), 1, -p1_3.gety()*p2_3.getx(), -p1_3.gety()*p2_3.gety(),
		p2_4.getx(), p2_4.gety(), 1, 0, 0, 0, -p1_4.getx()*p2_4.getx(), -p1_4.getx()*p2_4.gety(),
		0, 0, 0, p2_4.getx(), p2_4.gety(), 1, -p1_4.gety()*p2_4.getx(), -p1_4.gety()*p2_4.gety();
	
	MatrixXd proj_point(8, 1);
	proj_point << p1_1.getx(), p1_1.gety(), p1_2.getx(), p1_2.gety(), p1_3.getx(), p1_3.gety(), p1_4.getx(), p1_4.gety();

	MatrixXd h_coefficient(8, 1); 
	h_coefficient = HomoMat.inverse()*proj_point;

	// build the 3x3 Homography matrix
	Matrix3d H;
	H <<
		h_coefficient(0, 0), h_coefficient(1, 0), h_coefficient(2, 0),
		h_coefficient(3, 0), h_coefficient(4, 0), h_coefficient(5, 0),
		h_coefficient(6, 0), h_coefficient(7, 0), 1;

	// the obstacle coordination on the picture 2
	MatrixXd obstacle21(3, 1);
	obstacle21 << 1313, 645, 1;
	MatrixXd obstacle22(3, 1);
	obstacle22 << 1887, 645, 1;
	MatrixXd obstacle23(3, 1);
	obstacle23 << 1887, 1703, 1;
	MatrixXd obstacle24(3, 1);
	obstacle24 << 1313, 1703, 1;

	MatrixXd obstacle21_projected = H * obstacle21;
	obstacle21_projected = normalized_3x1(obstacle21_projected);
	MatrixXd obstacle22_projected = H * obstacle22;
	obstacle22_projected = normalized_3x1(obstacle22_projected);
	MatrixXd obstacle23_projected = H * obstacle23;
	obstacle23_projected = normalized_3x1(obstacle23_projected);
	MatrixXd obstacle24_projected = H * obstacle24;
	obstacle24_projected = normalized_3x1(obstacle24_projected);
	
	cv::Mat myJPG_no_Obstacle = myJPG_002;  // Read the 002 file
	
	// fill the obstacle by the data point from 1.jpg
	MatrixXd temp(3, 1); // 3x1 temp point
	MatrixXd temp_projected(3, 1); // 3x1 temp point
	for (int i = obstacle21(0,0); i < obstacle22(0,0); i++) // x
	{
		for (int j = obstacle21(1,0); j < obstacle24(1,0); j++) // y
		{
			temp << i, j, 1;
			temp_projected = H * temp;
			temp_projected = normalized_3x1(temp_projected);

			myJPG_no_Obstacle.at<Vec3b>(Point(i, j))[0] = myJPG_001.at<Vec3b>(temp_projected(1, 0), temp_projected(0, 0))[0];
			myJPG_no_Obstacle.at<Vec3b>(Point(i, j))[1] = myJPG_001.at<Vec3b>(temp_projected(1, 0), temp_projected(0, 0))[1];
			myJPG_no_Obstacle.at<Vec3b>(Point(i, j))[2] = myJPG_001.at<Vec3b>(temp_projected(1, 0), temp_projected(0, 0))[2];
		}
	}
	//imwrite("myJPG_no_Obstacle.jpg", myJPG_no_Obstacle); // save as the myJPG_withoutObstacle.jpg


	// the coordination on the target image 
	Coordination p_Final_1(0, 0);  
	Coordination p_Final_2(3000, 0);  
	Coordination p_Final_3(3000, 2000);  
	Coordination p_Final_4(0, 2000);  

	// calculate the Homography matrix
	MatrixXd HomoMat2(8, 8);
	HomoMat2 <<
		p2_1.getx(), p2_1.gety(), 1, 0, 0, 0, -p_Final_1.getx()*p2_1.getx(), -p_Final_1.getx()*p2_1.gety(),
		0, 0, 0, p2_1.getx(), p2_1.gety(), 1, -p_Final_1.gety()*p2_1.getx(), -p_Final_1.gety()*p2_1.gety(),
		p2_2.getx(), p2_2.gety(), 1, 0, 0, 0, -p_Final_2.getx()*p2_2.getx(), -p_Final_2.getx()*p2_2.gety(),
		0, 0, 0, p2_2.getx(), p2_2.gety(), 1, -p_Final_2.gety()*p2_2.getx(), -p_Final_2.gety()*p2_2.gety(),
		p2_3.getx(), p2_3.gety(), 1, 0, 0, 0, -p_Final_3.getx()*p2_3.getx(), -p_Final_3.getx()*p2_3.gety(),
		0, 0, 0, p2_3.getx(), p2_3.gety(), 1, -p_Final_3.gety()*p2_3.getx(), -p_Final_3.gety()*p2_3.gety(),
		p2_4.getx(), p2_4.gety(), 1, 0, 0, 0, -p_Final_4.getx()*p2_4.getx(), -p_Final_4.getx()*p2_4.gety(),
		0, 0, 0, p2_4.getx(), p2_4.gety(), 1, -p_Final_4.gety()*p2_4.getx(), -p_Final_4.gety()*p2_4.gety();

	MatrixXd proj_point2(8, 1);
	proj_point2 << 0, 0, 3000, 0, 3000, 2000, 0, 2000;

	MatrixXd h_coefficient2(8, 1);
	h_coefficient2 = HomoMat2.inverse()*proj_point2;

	// build the 3x3 Homography matrix
	Matrix3d H2;
	H2 <<
		h_coefficient2(0, 0), h_coefficient2(1, 0), h_coefficient2(2, 0),
		h_coefficient2(3, 0), h_coefficient2(4, 0), h_coefficient2(5, 0),
		h_coefficient2(6, 0), h_coefficient2(7, 0), 1;


	// build a blank image as the following spec ...
	//Width: 3000 pixels ; Height : 2000 pixels
	//Each pixel value(intensity) is 0 ~255 : an 8 - bit unsigned integer
	//Supports all RGB colors : 3 channels
	//Initial color : black = (B, G, R) = (0, 0, 0)
	cv::Mat result_image(2000, 3000, CV_8UC3, Scalar(0, 0, 0));


	// start projection
	MatrixXd temp2(3, 1); // 3x1 temp point
	MatrixXd temp_projected2(3, 1); // 3x1 temp point
	MatrixXd H2_inv = H2.inverse();
	for (int i = 0; i < 3000; i++) // x
	{
		for (int j = 0; j < 2000; j++) // y
		{
			temp2 << i, j, 1;
			temp_projected2 = H2_inv * temp2;
			temp_projected2 = normalized_3x1(temp_projected2);

			result_image.at<Vec3b>(Point(i, j))[0] = myJPG_no_Obstacle.at<Vec3b>(temp_projected2(1, 0), temp_projected2(0, 0))[0];
			result_image.at<Vec3b>(Point(i, j))[1] = myJPG_no_Obstacle.at<Vec3b>(temp_projected2(1, 0), temp_projected2(0, 0))[1];
			result_image.at<Vec3b>(Point(i, j))[2] = myJPG_no_Obstacle.at<Vec3b>(temp_projected2(1, 0), temp_projected2(0, 0))[2];
		}
	}

	// save the image
	//imwrite("result_image.jpg", result_image);
	imwrite("ÀH¯ZªþÅª-½²ª÷³Õ.jpg", result_image);
					
	//system("pause");
	return 0;
}
