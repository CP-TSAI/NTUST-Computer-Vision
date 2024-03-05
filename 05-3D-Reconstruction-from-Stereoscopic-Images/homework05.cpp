#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>  
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;

// void normalized_3x1(MatrixXd& mat)
// {
// 	mat(0, 0) = mat(0, 0) / mat(2, 0);
// 	mat(1, 0) = mat(1, 0) / mat(2, 0);
// 	mat(2, 0) = 1;
// }
// void normalized_4x1(MatrixXd& mat)
// {
// 	mat(0, 0) = mat(0, 0) / mat(3, 0);
// 	mat(1, 0) = mat(1, 0) / mat(3, 0);
// 	mat(2, 0) = mat(2, 0) / mat(3, 0);
// 	mat(3, 0) = 1;
// }

// struct point_2D
// {
// public:
// 	int x = 0;
// 	int y = 0;
// 	int w = 1;
// };
// struct point_3D
// {
// public:
// 	int x = 0;
// 	int y = 0;
// 	int z = 0;
// 	int w = 1;
// };

// vector<point_2D> L_point;
// vector<point_2D> R_point;
//vector<point_3D> space_point_3D;


int main()
{

	Eigen::MatrixXd L_Camera_K(3, 3);
	L_Camera_K <<
		1031.107181256652, 0.000000000000, 300.315754576448,
		0.000000000000, 1031.922726531495, 596.128631557107,
		0.000000000000, 0.000000000000, 1.000000000000;


	Eigen::MatrixXd L_Camera_RT(3, 4);
	L_Camera_RT <<
		1.000000000000, 0.000000000000, 0.000000000000, 0.000000000000,
		0.000000000000, 1.000000000000, 0.000000000000, 0.000000000000,
		0.000000000000, 0.000000000000, 1.000000000000, 0.000000000000;

	Eigen::MatrixXd R_Camera_K(3, 3);
	R_Camera_K <<
		1034.184348727144, 0.000000000000, 417.455360200033,
		0.000000000000, 1034.889311554467, 615.052068517334,
		0.000000000000, 0.000000000000, 1.000000000000;


	Eigen::MatrixXd R_Camera_RT(3, 4);
	R_Camera_RT <<
		0.960420625577, 0.010140226529, 0.278369175326, -70.168656978049,
		-0.009291786823, 0.999947294142, -0.004367108410, -0.002608446641,
		-0.278398787108, 0.001607713956, 0.960464226607, 13.498989529018;

	Eigen::MatrixXd Fundamental_Matrix(3, 3);
	Fundamental_Matrix <<
		-0.000000050362, 0.000002369273, -0.001301863689,
		0.000000811157, -0.000000004467, -0.011984436200,
		-0.000689813339, 0.010646819054, 1.000000000000;

	Eigen::MatrixXd L_Project_Matrix(3, 4);
	L_Project_Matrix = L_Camera_K * L_Camera_RT;
	//cout << "L_Project_Matrix = \n" << L_Project_Matrix << endl;

	Eigen::MatrixXd R_Project_Matrix(3, 4);
	R_Project_Matrix = R_Camera_K * R_Camera_RT;
	//cout << "R_Project_Matrix = \n" << R_Project_Matrix << endl;


	// ---------------------------------------------------------------------------

	ofstream myfile_xyz;
	myfile_xyz.open("xyz_file.xyz");

	// read image file
	string L_imageName = "../L/";
	string R_imageName = "../R/";
	
	// for (int imgName = 0; imgName <= 363; imgName++)
	// {
	// 	string L_whole_name = "";
	// 	string R_whole_name = "";
	// 	if (imgName >= 0 && imgName <= 9)
	// 	{
	// 		L_whole_name = L_imageName + "000" + to_string(imgName) + ".jpg"; // ex: "../L/0001.jpg"
	// 		R_whole_name = R_imageName + "000" + to_string(imgName) + ".jpg"; // ex: "../R/0001.jpg"
	// 	}
	// 	else if (imgName >= 10 && imgName <= 99)
	// 	{
	// 		L_whole_name = L_imageName + "00" + to_string(imgName) + ".jpg"; // ex: "../L/0011"
	// 		R_whole_name = R_imageName + "00" + to_string(imgName) + ".jpg"; // ex: "../R/0011"
	// 	}
	// 	else // imgName >= 100 || imgName <= 363
	// 	{
	// 		L_whole_name = L_imageName + "0" + to_string(imgName) + ".jpg"; // ex: "../L/0111"
	// 		R_whole_name = R_imageName + "0" + to_string(imgName) + ".jpg"; // ex: "../R/0111"
	// 	}

	// 	cv::Mat img_L = cv::imread(L_whole_name, CV_LOAD_IMAGE_COLOR);
	// 	cv::Mat img_R = cv::imread(R_whole_name, CV_LOAD_IMAGE_COLOR);
	// 	if (!img_L.data || !img_R.data) // Check for invalid input
	// 	{
	// 		cout << "Could not open or find the image" << std::endl;
	// 		return -1;
	// 	}

	// 	//Grayscale matrix
	// 	cv::Mat gray_L(img_L.size(), CV_8U);
	// 	cv::Mat gray_R(img_L.size(), CV_8U);
	// 	//Convert BGR to Gray
	// 	cv::cvtColor(img_L, gray_L, CV_BGR2GRAY);
	// 	cv::cvtColor(img_R, gray_R, CV_BGR2GRAY);

	// 	// preprocess, 
	// 	for (int y = 0; y < gray_L.rows; y++) // y = 1280 in this case
	// 	{
	// 		for (int x = 0; x < gray_L.cols; x++)
	// 		{
	// 			if (gray_L.at<uchar>(y, x) < 40 )
	// 			{
	// 				gray_L.at<uchar>(y, x) = 0;
	// 			}
	// 			if (gray_R.at<uchar>(y, x) < 40)
	// 			{
	// 				gray_R.at<uchar>(y, x) = 0;
	// 			}
	// 		}
	// 	}

	// 	// check the pixel
	// 	point_2D L_p_2d;
	// 	point_2D R_p_2d;
	// 	for (int y = 0; y < gray_L.rows; y++) // y = 1280 in this case
	// 	{
	// 		for (int x = 0; x < gray_L.cols; x++) // x = 720 in this case
	// 		{
	// 			if (gray_L.at<uchar>(y, x) != 0)
	// 			{
	// 				if (gray_L.at<uchar>(y, x) > gray_L.at<uchar>(L_p_2d.y, L_p_2d.x))
	// 				{
	// 					L_p_2d.x = x;
	// 					L_p_2d.y = y;
	// 				}
	// 			}
	// 		}
	// 		//myfile_L << L_p_2d.x << "; " << L_p_2d.y << "; 0" << endl;
	// 		L_point.push_back(L_p_2d);
			
	// 		// calculate the coresponding point on R image
	// 		MatrixXd point(3, 1);
	// 		point << L_p_2d.x, L_p_2d.y, 1;

	// 		MatrixXd epipoline(3, 1);
	// 		epipoline = Fundamental_Matrix.transpose() * point;
	// 		//epipoline = Fundamental_Matrix * point;
	// 		//cout << "epipoline = \n" << epipoline << endl;

	// 		for (int x_point = 0; x_point < 720; x_point++) // find the corresponding point by Fundamental_Matrix
	// 		{
	// 			int y_point = (-epipoline(2, 0) - epipoline(0, 0) * x_point) / epipoline(1, 0);
	// 			//cout << "y_point = " << y_point << endl;
				
	// 			if (y_point > 0 && y_point < 1280)
	// 			{
	// 				if (gray_R.at<uchar>(y_point, x_point) > 0)
	// 				{
	// 					if (gray_R.at<uchar>(y_point, x_point) > gray_R.at<uchar>(R_p_2d.y, R_p_2d.x))
	// 					{
	// 						R_p_2d.x = x_point;
	// 						R_p_2d.y = y_point;
	// 					}
	// 				}
	// 			}
	// 		}
	// 		R_point.push_back(R_p_2d);			
	// 	}
	// }
	
	// //cout << "L_point.size = " << L_point.size() << endl;
	// //cout << "R_point.size = " << R_point.size() << endl;

	// // ---------------------------------------------------------------------------
	
	// // calculate the space point
	// MatrixXd p1(4, 1);
	// p1 << L_Project_Matrix(0, 0), L_Project_Matrix(0, 1), L_Project_Matrix(0, 2), L_Project_Matrix(0, 3);
	// MatrixXd p2(4, 1);
	// p2 << L_Project_Matrix(1, 0), L_Project_Matrix(1, 1), L_Project_Matrix(1, 2), L_Project_Matrix(1, 3);
	// MatrixXd p3(4, 1);
	// p3 << L_Project_Matrix(2, 0), L_Project_Matrix(2, 1), L_Project_Matrix(2, 2), L_Project_Matrix(2, 3);
	

	// MatrixXd pp1(4, 1);
	// pp1 << R_Project_Matrix(0, 0), R_Project_Matrix(0, 1), R_Project_Matrix(0, 2), R_Project_Matrix(0, 3);
	// MatrixXd pp2(4, 1);
	// pp2 << R_Project_Matrix(1, 0), R_Project_Matrix(1, 1), R_Project_Matrix(1, 2), R_Project_Matrix(1, 3);
	// MatrixXd pp3(4, 1);
	// pp3 << R_Project_Matrix(2, 0), R_Project_Matrix(2, 1), R_Project_Matrix(2, 2), R_Project_Matrix(2, 3);
	

	// ofstream xyz_file;
	// xyz_file.open("xyz_file.txt");
	// //int idx = 0;
	// for (unsigned i = 0; i < L_point.size(); i++)
	// {
	// 	MatrixXd x(3, 1);
	// 	x << L_point[i].x, L_point[i].y, L_point[i].w;

	// 	MatrixXd xx(3, 1);
	// 	xx << R_point[i].x, R_point[i].y, R_point[i].w;

	// 	MatrixXd A(4, 4);
	// 	A << 
	// 		x(0, 0)*p3.transpose() - p1.transpose(), 
	// 		x(1, 0)*p3.transpose() - p2.transpose(), 
	// 		xx(0, 0)*pp3.transpose() - pp1.transpose(), 
	// 		xx(1, 0)*pp3.transpose() - pp2.transpose();

	// 	JacobiSVD<MatrixXd> svd(A, ComputeFullV | ComputeFullU);
	// 	MatrixXd V = svd.matrixV();
	// 	MatrixXd X(4, 1);
	// 	X << V(0, 3), V(1, 3), V(2, 3), V(3, 3);
	// 	normalized_4x1(X);

	// 	// projection err detection
	// 	MatrixXd L_point_test(3, 1);
	// 	MatrixXd R_point_test(3, 1);
	// 	L_point_test = L_Project_Matrix * X;
	// 	R_point_test = R_Project_Matrix * X;
	// 	normalized_3x1(L_point_test);
	// 	normalized_3x1(R_point_test);
	// 	double L_diff = sqrt((L_point_test(0, 0) - x(0, 0))*(L_point_test(0, 0) - x(0, 0)) + (L_point_test(1, 0) - x(1, 0))*(L_point_test(1, 0) - x(1, 0)) + (L_point_test(2, 0) - x(2, 0))*(L_point_test(2, 0) - x(2, 0)));
	// 	double R_diff = sqrt((R_point_test(0, 0) - xx(0, 0))*(R_point_test(0, 0) - xx(0, 0)) + (R_point_test(1, 0) - xx(1, 0))*(R_point_test(1, 0) - xx(1, 0)) + (R_point_test(2, 0) - xx(2, 0))*(R_point_test(2, 0) - xx(2, 0)));

	// 	if (L_diff < 40 && R_diff < 40)
	// 	{
	// 		//idx++;
	// 		xyz_file << X(0, 0) << "; " << X(1, 0) << "; " << X(2, 0) << endl;
	// 		myfile_xyz << X(0, 0) << " " << X(1, 0) << " " << X(2, 0) << endl;
	// 	}
	// }
	// //cout << "idx = " << idx << endl;
	// myfile_xyz.close();
					
	// system("pause");
	// return 0;
}
