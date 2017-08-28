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

#ifdef ___WIN_X64_LIB___
#pragma comment(lib, "../../lib/x64/opencv_world320.lib")
#endif

#ifdef ___WIN_X86_LIB___
#pragma comment(lib, "../../lib/x86/opencv_world320.lib")
#endif

using namespace cv;
using namespace std;


// ********* Eagle *********
vector< vector<double> > exstrinsic1 = { {  0.866849, -0.493982, -0.067491, 5.680202 },{ -0.033026, 0.078177, -0.996382, 40.192253 } ,{  0.497476, 0.865950, 0.051456, 131.575211 } };

vector< vector<double> > exstrinsic2 = { {  0.691898,  0.718699, -0.068914,   3.033622 } ,
										 { -0.018523, -0.077748, -0.996791,  40.538036 } ,
										 { -0.721758,  0.690961, -0.040479, 132.814957 } };

vector< vector<double> > exstrinsic3 = { { -0.708825,  0.705031, -0.022315,   2.710659 } ,
										 { -0.023775, -0.055497, -0.998163,  40.025272 } ,
										 { -0.704984, -0.707001, -0.056103, 131.650055 } };

vector< vector<double> > exstrinsic4 = { { -0.990984, -0.131983, -0.023039,  -1.359515 } ,
										 {  0.033893, -0.080598, -0.996156,  40.564919 } ,
										 {  0.129620, -0.987970,  0.084348, 126.794678 } };

vector< vector<double> > exstrinsic5 = { { -0.071742, -0.997325,  0.014031,  10.313296 } ,
										 { -0.040528, -0.011141, -0.999102,  40.912224 } ,
										 {  0.996600, -0.072247, -0.039619, 127.704018 } };

vector< vector<double> > exstrinsic6 = { { -0.946351, -0.190357,  0.261120, -10.116337 } ,
										 { -0.241168,  0.953881, -0.178661,   7.099833 } ,
										 { -0.215071, -0.232055, -0.948628, 156.788635 } };

vector< vector<double> > exstrinsic7 = { { -0.280008,  0.952858,  0.116867,  -2.020520 } ,
										 { -0.725914, -0.130496, -0.675269,  28.864723 } ,
										 { -0.628193, -0.273920,  0.728245, 106.115578 } };

vector< vector<double> > exstrinsic8 = { { 0.897493, -0.360072, -0.254667,   8.695093 } ,
										 { 0.088773,  0.713100, -0.695396,  31.042011 } ,
										 { 0.432002,  0.601513,  0.671979, 125.422333 } };




// ********* Bunny *********
//vector< vector<double> > exstrinsic1 = { {  0.866849, -0.493982, -0.067491,   5.680202 } ,
//										 { -0.033026,  0.078177, -0.996382,  40.192253 } ,
//										 {  0.497476,  0.865950,  0.051456, 131.575211 } };
//
//vector< vector<double> > exstrinsic2 = { {  0.691898,  0.718699,  -0.068914,   3.033622 } ,
//										 { -0.018523, -0.077748,  -0.996791,  40.538036 } ,
//										 { -0.721758,  0.690961,  -0.040479, 132.814957 } };
//
//vector< vector<double> > exstrinsic3 = { { -0.708825,  0.705031, -0.022315,   2.710659 } ,
//										 { -0.023775, -0.055497, -0.998163,  40.025272 } ,
//										 { -0.704984,  0.707001,  0.056103, 131.650055 } };
//
//vector< vector<double> > exstrinsic4 = { { -0.990984, -0.131983, -0.023039,  -1.359515 } ,
//										 {  0.033893, -0.080598, -0.996156,  40.564919 } ,
//										 {  0.129620, -0.987970,  0.084348, 126.794678 } };
//
//vector< vector<double> > exstrinsic5 = { { -0.071742, -0.997325,  0.014031,  10.313296 } ,
//										 { -0.040528, -0.011141, -0.999102,  40.912224 } ,
//										 {  0.996600, -0.072247, -0.039619, 127.704018 } };
//
//vector< vector<double> > exstrinsic6 = { { -0.946351, -0.190357,  0.261120, -10.116337 } ,
//										 { -0.241168,  0.953881, -0.178661,   7.099833 } ,
//										 { -0.215071, -0.232055, -0.948628, 156.788635 } };
//
//vector< vector<double> > exstrinsic7 = { { -0.280008,  0.952858,  0.116867,  -2.020520 } ,
//										 { -0.725914, -0.130496, -0.675269,  28.864723 } ,
//										 { -0.628193, -0.273920,  0.728245, 106.115578 } };
//
//vector< vector<double> > exstrinsic8 = { { 0.897493, -0.360072, -0.254667,   8.695093 } ,
//										 { 0.088773,  0.713100, -0.695396,  31.042011 } ,
//										 { 0.432002,  0.601513,  0.671979, 125.422333 } };


// ********* Teapot *********
//vector< vector<double> > exstrinsic1 = { {  0.866849, -0.493982, -0.067491,   5.680202 } ,
//										 { -0.033026,  0.078177, -0.996382,  40.192253 } ,
//										 {  0.497476,  0.865950,  0.051456, 131.575211 } };
//
//vector< vector<double> > exstrinsic2 = { {  0.691898,  0.718699, -0.068914,   3.033622 } ,
//										 { -0.018523, -0.077748, -0.996791,  40.538036 } ,
//										 { -0.721758,  0.690961, -0.040479, 132.814957 } };
//
//vector< vector<double> > exstrinsic3 = { { -0.708825,  0.705031,  0.022315,   2.710659 } ,
//										 { -0.023775, -0.055497, -0.998163,  40.025272 } ,
//										 { -0.704984, -0.707001,  0.056103, 131.650055 } };
//
//vector< vector<double> > exstrinsic4 = { { -0.990984, -0.131983, -0.023039,  -1.359515 } ,
//										 {  0.033893, -0.080598, -0.996156,  40.564919 } ,
//										 {  0.129620, -0.987970,  0.084348, 126.794678 } };
//
//vector< vector<double> > exstrinsic5 = { { -0.071742, -0.997325,  0.014031,  10.313296 } ,
//										 { -0.040528, -0.011141, -0.999102,  40.912224 } ,
//										 {  0.996600, -0.072247, -0.039619, 127.704018 } };
//
//vector< vector<double> > exstrinsic6 = { { -0.946351, -0.190357,  0.261120, -10.116337 } ,
//										 { -0.241168,  0.953881, -0.178661,   7.099833 } ,
//										 { -0.215071, -0.232055, -0.948628, 156.788635 } };
//
//vector< vector<double> > exstrinsic7 = { { -0.280008,  0.952858,  0.116867,  -2.020520 } ,
//										 { -0.725914, -0.130496, -0.675269,  28.864723 } ,
//										 { -0.628193, -0.273920,  0.728245, 106.115578 } };
//
//vector< vector<double> > exstrinsic8 = { { 0.897493, -0.360072, -0.254667,   8.695093 } ,
//										 { 0.088773,  0.713100, -0.695396,  31.042011 } ,
//										 { 0.432002,  0.601513,  0.671979, 125.422333 } };


// ********* Venus *********
//vector< vector<double> > exstrinsic1 = { {  0.866849, -0.493982, -0.067491,   5.680202 } ,
//										 { -0.033026,  0.078177, -0.996382,  40.192253 } ,
//										 {  0.497476,  0.865950,  0.051456, 131.575211 } };
//
//vector< vector<double> > exstrinsic2 = { {  0.691898,  0.718699, -0.068914,   3.033622 } ,
//										 { -0.018523, -0.077748, -0.996791,  40.538036 } ,
//										 { -0.721758,  0.690961, -0.040479, 132.814957 } };
//
//vector< vector<double> > exstrinsic3 = { { -0.708825,  0.705031, -0.022315,   2.710659 } ,
//										 { -0.023775, -0.055497, -0.998163,  40.025272 } ,
//										 { -0.704984, -0.707001,  0.056103, 131.650055 } };
//
//vector< vector<double> > exstrinsic4 = { { -0.990984, -0.131983, -0.023039,  -1.359515 } ,
//										 {  0.033893, -0.080598, -0.996156,  40.564919 } ,
//										 {  0.129620, -0.987970,  0.084348, 126.794678 } };
//
//vector< vector<double> > exstrinsic5 = { { -0.071742, -0.997325,  0.014031,  10.313296 } ,
//										 { -0.040528, -0.011141, -0.999102,  40.912224 } ,
//										 {  0.996600, -0.072247, -0.039619, 127.704018 } };
//
//vector< vector<double> > exstrinsic6 = { { -0.946351, -0.190357,  0.261120, -10.116337 } ,
//										 { -0.241168,  0.953881, -0.178661,   7.099833 } ,
//										 { -0.215071, -0.232055, -0.948628, 156.788635 } };
//
//vector< vector<double> > exstrinsic7 = { { -0.280008,  0.952858,  0.116867,  -2.020520 } ,
//										 { -0.725914, -0.130496, -0.675269,  28.864723 } ,
//										 { -0.628193, -0.273920,  0.728245, 106.115578 } };
//
//vector< vector<double> > exstrinsic8 = { { 0.897493, -0.360072, -0.254667,   8.695093 } ,
//										 { 0.088773,  0.713100, -0.695396,  31.042011 } ,
//										 { 0.432002,  0.601513,  0.671979, 125.422333 } };




vector< vector<double> > instrinsic_parameter = { { 714.074036,   0.000000, 400.000000 },
												  {   0.000000, 714.073975, 300.000000 },
												  {   0.000000,   0.000000,   1.000000 } };

vector< vector<double> > projection1 = { { 0,0,0,0 },
										 { 0,0,0,0 },
										 { 0,0,0,0 } };

vector< vector<double> > projection2 = projection1;
vector< vector<double> > projection3 = projection1;
vector< vector<double> > projection4 = projection1;
vector< vector<double> > projection5 = projection1;
vector< vector<double> > projection6 = projection1;
vector< vector<double> > projection7 = projection1;
vector< vector<double> > projection8 = projection1;

struct Point_on_2D
{
	double x_2d = 0;
	double y_2d = 0;
	double w_2d = 0;
};

struct Point_on_3D
{
	double x_3d = 0;
	double y_3d = 0;
	double z_3d = 0;
	double w_3d = 1;
};

vector<Point_on_3D> vec_p_on_3d;

int main()
{
	// projection matrix = intrinsic x extrinsic 
	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic1[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection1[i][j] += instrinsic_parameter[i][k] * exstrinsic1[k][j];

	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic2[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection2[i][j] += instrinsic_parameter[i][k] * exstrinsic2[k][j];
		
	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic3[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection3[i][j] += instrinsic_parameter[i][k] * exstrinsic3[k][j];

	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic4[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection4[i][j] += instrinsic_parameter[i][k] * exstrinsic4[k][j];

	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic5[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection5[i][j] += instrinsic_parameter[i][k] * exstrinsic5[k][j];

	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic6[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection6[i][j] += instrinsic_parameter[i][k] * exstrinsic6[k][j];

	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic7[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection7[i][j] += instrinsic_parameter[i][k] * exstrinsic7[k][j];

	for (unsigned i = 0; i < instrinsic_parameter.size(); i++)
		for (unsigned j = 0; j < exstrinsic8[i].size(); j++)
			for (unsigned k = 0; k < instrinsic_parameter[i].size(); k++)
				projection8[i][j] += instrinsic_parameter[i][k] * exstrinsic8[k][j];


	// ********* read image *********
	cv::Mat myBMP_001 = cv::imread("001.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 001 file
	cv::Mat myBMP_002 = cv::imread("002.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 002 file
	cv::Mat myBMP_003 = cv::imread("003.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 003 file
	cv::Mat myBMP_004 = cv::imread("004.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 004 file
	cv::Mat myBMP_005 = cv::imread("005.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 005 file
	cv::Mat myBMP_006 = cv::imread("006.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 006 file
	cv::Mat myBMP_007 = cv::imread("007.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 007 file
	cv::Mat myBMP_008 = cv::imread("008.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 008 file
	if (!myBMP_001.data || !myBMP_002.data || !myBMP_003.data || !myBMP_004.data || !myBMP_005.data || !myBMP_006.data || !myBMP_007.data || !myBMP_008.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	
	// project the 3D workspace on to 2D coordination ...
	Point_on_3D p_on_3d_temp;
	Point_on_2D p_on_2d_temp;
	bool checking;
	int pixel_value;


	for (double x_workspace = -50; x_workspace <= 50; x_workspace++)
	{
		for (double y_workspace = -50; y_workspace <= 50; y_workspace++)
		{
			for (double z_workspace = -10; z_workspace <= 90; z_workspace++)
			{
				checking = 1; // initialize the bool value

				// ***** check 001.bmp *****
				p_on_3d_temp.x_3d = x_workspace;
				p_on_3d_temp.y_3d = y_workspace;
				p_on_3d_temp.z_3d = z_workspace;

				// projection
				p_on_2d_temp.x_2d = projection1[0][0] * p_on_3d_temp.x_3d + projection1[0][1] * p_on_3d_temp.y_3d + projection1[0][2] * p_on_3d_temp.z_3d + projection1[0][3] * p_on_3d_temp.w_3d;
				p_on_2d_temp.y_2d = projection1[1][0] * p_on_3d_temp.x_3d + projection1[1][1] * p_on_3d_temp.y_3d + projection1[1][2] * p_on_3d_temp.z_3d + projection1[1][3] * p_on_3d_temp.w_3d;
				p_on_2d_temp.w_2d = projection1[2][0] * p_on_3d_temp.x_3d + projection1[2][1] * p_on_3d_temp.y_3d + projection1[2][2] * p_on_3d_temp.z_3d + projection1[2][3] * p_on_3d_temp.w_3d;


				// normalize
				p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
				p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
				p_on_2d_temp.w_2d = p_on_2d_temp.w_2d / p_on_2d_temp.w_2d;


				if (p_on_2d_temp.x_2d >= 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d >= 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
				{
					pixel_value = (int)myBMP_001.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
					
					if (pixel_value == 0) { checking = 0; } // GET-OUT!
	
				}
				else
					checking = 0;


				// ***** check 002.bmp *****
				if (checking)
				{
					p_on_2d_temp.x_2d = projection2[0][0] * p_on_3d_temp.x_3d + projection2[0][1] * p_on_3d_temp.y_3d + projection2[0][2] * p_on_3d_temp.z_3d + projection2[0][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.y_2d = projection2[1][0] * p_on_3d_temp.x_3d + projection2[1][1] * p_on_3d_temp.y_3d + projection2[1][2] * p_on_3d_temp.z_3d + projection2[1][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.w_2d = projection2[2][0] * p_on_3d_temp.x_3d + projection2[2][1] * p_on_3d_temp.y_3d + projection2[2][2] * p_on_3d_temp.z_3d + projection2[2][3] * p_on_3d_temp.w_3d;

					// normalize
					p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.w_2d = 1;

					if (p_on_2d_temp.x_2d > 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d > 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
					{ 
						pixel_value = (int)myBMP_002.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
						if (pixel_value == 0) { checking = 0; } // GET-OUT!
					}
					else
						checking = 0;
				}

				// ***** check 003.bmp *****
				if (checking)
				{
					p_on_2d_temp.x_2d = projection3[0][0] * p_on_3d_temp.x_3d + projection3[0][1] * p_on_3d_temp.y_3d + projection3[0][2] * p_on_3d_temp.z_3d + projection3[0][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.y_2d = projection3[1][0] * p_on_3d_temp.x_3d + projection3[1][1] * p_on_3d_temp.y_3d + projection3[1][2] * p_on_3d_temp.z_3d + projection3[1][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.w_2d = projection3[2][0] * p_on_3d_temp.x_3d + projection3[2][1] * p_on_3d_temp.y_3d + projection3[2][2] * p_on_3d_temp.z_3d + projection3[2][3] * p_on_3d_temp.w_3d;

					// normalize
					p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.w_2d = 1;

					if (p_on_2d_temp.x_2d > 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d > 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
					{
						pixel_value = (int)myBMP_003.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
						if (pixel_value == 0) { checking = 0; } // GET-OUT!
					}
					else
						checking = 0;
				}

				// ***** check 004.bmp *****
				if (checking)
				{
					p_on_2d_temp.x_2d = projection4[0][0] * p_on_3d_temp.x_3d + projection4[0][1] * p_on_3d_temp.y_3d + projection4[0][2] * p_on_3d_temp.z_3d + projection4[0][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.y_2d = projection4[1][0] * p_on_3d_temp.x_3d + projection4[1][1] * p_on_3d_temp.y_3d + projection4[1][2] * p_on_3d_temp.z_3d + projection4[1][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.w_2d = projection4[2][0] * p_on_3d_temp.x_3d + projection4[2][1] * p_on_3d_temp.y_3d + projection4[2][2] * p_on_3d_temp.z_3d + projection4[2][3] * p_on_3d_temp.w_3d;

					// normalize
					p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.w_2d = 1;

					if (p_on_2d_temp.x_2d > 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d > 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
					{
						pixel_value = (int)myBMP_004.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
						if (pixel_value == 0) { checking = 0; } // GET-OUT!
					}
					else
						checking = 0;
				}

				// ***** check 005.bmp *****
				if (checking)
				{
					p_on_2d_temp.x_2d = projection5[0][0] * p_on_3d_temp.x_3d + projection5[0][1] * p_on_3d_temp.y_3d + projection5[0][2] * p_on_3d_temp.z_3d + projection5[0][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.y_2d = projection5[1][0] * p_on_3d_temp.x_3d + projection5[1][1] * p_on_3d_temp.y_3d + projection5[1][2] * p_on_3d_temp.z_3d + projection5[1][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.w_2d = projection5[2][0] * p_on_3d_temp.x_3d + projection5[2][1] * p_on_3d_temp.y_3d + projection5[2][2] * p_on_3d_temp.z_3d + projection5[2][3] * p_on_3d_temp.w_3d;

					// normalize
					p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.w_2d = 1;

					if (p_on_2d_temp.x_2d > 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d > 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
					{
						pixel_value = (int)myBMP_005.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
						if (pixel_value == 0) { checking = 0; } // GET-OUT!
					}
					else
						checking = 0;
				}

				// ***** check 006.bmp *****
				if (checking)
				{
					p_on_2d_temp.x_2d = projection6[0][0] * p_on_3d_temp.x_3d + projection6[0][1] * p_on_3d_temp.y_3d + projection6[0][2] * p_on_3d_temp.z_3d + projection6[0][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.y_2d = projection6[1][0] * p_on_3d_temp.x_3d + projection6[1][1] * p_on_3d_temp.y_3d + projection6[1][2] * p_on_3d_temp.z_3d + projection6[1][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.w_2d = projection6[2][0] * p_on_3d_temp.x_3d + projection6[2][1] * p_on_3d_temp.y_3d + projection6[2][2] * p_on_3d_temp.z_3d + projection6[2][3] * p_on_3d_temp.w_3d;

					// normalize
					p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.w_2d = 1;

					if (p_on_2d_temp.x_2d > 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d > 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
					{
						pixel_value = (int)myBMP_006.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
						if (pixel_value == 0) { checking = 0; } // GET-OUT!
					}
					else
						checking = 0;
				}

				// ***** check 007.bmp *****
				if (checking)
				{
					p_on_2d_temp.x_2d = projection7[0][0] * p_on_3d_temp.x_3d + projection7[0][1] * p_on_3d_temp.y_3d + projection7[0][2] * p_on_3d_temp.z_3d + projection7[0][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.y_2d = projection7[1][0] * p_on_3d_temp.x_3d + projection7[1][1] * p_on_3d_temp.y_3d + projection7[1][2] * p_on_3d_temp.z_3d + projection7[1][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.w_2d = projection7[2][0] * p_on_3d_temp.x_3d + projection7[2][1] * p_on_3d_temp.y_3d + projection7[2][2] * p_on_3d_temp.z_3d + projection7[2][3] * p_on_3d_temp.w_3d;

					// normalize
					p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.w_2d = 1;

					if (p_on_2d_temp.x_2d > 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d > 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
					{
						pixel_value = (int)myBMP_007.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
						if (pixel_value == 0) { checking = 0; } // GET-OUT!
					}
					else
						checking = 0;
				}

				// ***** check 008.bmp *****
				if (checking)
				{
					p_on_2d_temp.x_2d = projection8[0][0] * p_on_3d_temp.x_3d + projection8[0][1] * p_on_3d_temp.y_3d + projection8[0][2] * p_on_3d_temp.z_3d + projection8[0][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.y_2d = projection8[1][0] * p_on_3d_temp.x_3d + projection8[1][1] * p_on_3d_temp.y_3d + projection8[1][2] * p_on_3d_temp.z_3d + projection8[1][3] * p_on_3d_temp.w_3d;
					p_on_2d_temp.w_2d = projection8[2][0] * p_on_3d_temp.x_3d + projection8[2][1] * p_on_3d_temp.y_3d + projection8[2][2] * p_on_3d_temp.z_3d + projection8[2][3] * p_on_3d_temp.w_3d;

					// normalize
					p_on_2d_temp.x_2d = p_on_2d_temp.x_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.y_2d = p_on_2d_temp.y_2d / p_on_2d_temp.w_2d;
					p_on_2d_temp.w_2d = 1;

					if (p_on_2d_temp.x_2d > 0 && p_on_2d_temp.x_2d < 800 && p_on_2d_temp.y_2d > 0 && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
					{
						pixel_value = (int)myBMP_008.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
						if (pixel_value == 0) { checking = 0; } // GET-OUT!
					}
					else
						checking = 0;
				}

				// ALL PASS, you're the right point!
				if (checking)
				{
					vec_p_on_3d.push_back(p_on_3d_temp);
					//cout << "saved!" << endl;
					//getchar();
				}
			}
		}
	}

	// output the 3D point ...
	/*ofstream myfile_txt;
	myfile_txt.open("3D_point.txt");
	for (unsigned i = 0; i < vec_p_on_3d.size(); i++)
	{
		myfile_txt << vec_p_on_3d[i].x_3d << " " << vec_p_on_3d[i].y_3d << " " << vec_p_on_3d[i].z_3d << endl;
	}
	myfile_txt.close();*/

	ofstream myfile_xyz;
	myfile_xyz.open("3D_point.xyz");
	for (unsigned i = 0; i < vec_p_on_3d.size(); i++)
	{
		myfile_xyz << vec_p_on_3d[i].x_3d << " " << vec_p_on_3d[i].y_3d << " " << vec_p_on_3d[i].z_3d << endl;
	}
	myfile_xyz.close();

	//cout << vec_p_on_3d.size() << endl;
	//cout << "succesfully output to file ... " << endl;

	//system("pause");
	return 0;
}

/*imshow("Gray image", myBMP_008);
waitKey(0);*/

/*cout << "Width : " << myBMP_001.cols << endl;
cout << "Height: " << myBMP_001.rows << endl;*/

