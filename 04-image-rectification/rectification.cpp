// #include "opencv/opencv2/opencv.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <Eigen/Dense>  
#include <math.h>  
#include <chrono>
#include <iostream>
#include "opencv2/opencv.hpp"

#define PI 3.14159265
using namespace std;

// describe the coordination on an image
class Coordination_3x1
{
private:
	double x = 0;
	double y = 0;
	double z = 1;
public:
	Coordination_3x1(int a, int b) // constructor
	{
		x = a;
		y = b;
	}
	double getx() { return x; }
	double gety() { return y; }
};

// normalize the 3x1 matrix
Eigen::MatrixXd normalized_3x1(Eigen::MatrixXd& mat)
{
	mat(0, 0) = mat(0, 0) / mat(2, 0);
	mat(1, 0) = mat(1, 0) / mat(2, 0);
	mat(2, 0) = 1;
	return mat;
}

Eigen::Matrix3d get_fundamental_matrix(
	Eigen::MatrixXd p1, Eigen::MatrixXd p2, Eigen::MatrixXd p3, Eigen::MatrixXd p4, Eigen::MatrixXd p5, Eigen::MatrixXd p6, Eigen::MatrixXd p7, Eigen::MatrixXd p8,
	Eigen::MatrixXd pp1, Eigen::MatrixXd pp2, Eigen::MatrixXd pp3, Eigen::MatrixXd pp4, Eigen::MatrixXd pp5, Eigen::MatrixXd pp6, Eigen::MatrixXd pp7, Eigen::MatrixXd pp8)
{
	/******************* Calculate the Fundamental Matrix *******************/

	Eigen::MatrixXd A(8, 8);
	A <<
		pp1(0, 0) * p1(0, 0), pp1(0, 0) * p1(1, 0), pp1(0, 0), p1(0, 0) * pp1(1, 0), p1(1, 0) * pp1(1, 0), pp1(1, 0), p1(0, 0), p1(1, 0),
		pp2(0, 0) * p2(0, 0), pp2(0, 0) * p2(1, 0), pp2(0, 0), p2(0, 0) * pp2(1, 0), p2(1, 0) * pp2(1, 0), pp2(1, 0), p2(0, 0), p2(1, 0),
		pp3(0, 0) * p3(0, 0), pp3(0, 0) * p3(1, 0), pp3(0, 0), p3(0, 0) * pp3(1, 0), p3(1, 0) * pp3(1, 0), pp3(1, 0), p3(0, 0), p3(1, 0),
		pp4(0, 0) * p4(0, 0), pp4(0, 0) * p4(1, 0), pp4(0, 0), p4(0, 0) * pp4(1, 0), p4(1, 0) * pp4(1, 0), pp4(1, 0), p4(0, 0), p4(1, 0),
		pp5(0, 0) * p5(0, 0), pp5(0, 0) * p5(1, 0), pp5(0, 0), p5(0, 0) * pp5(1, 0), p5(1, 0) * pp5(1, 0), pp5(1, 0), p5(0, 0), p5(1, 0),
		pp6(0, 0) * p6(0, 0), pp6(0, 0) * p6(1, 0), pp6(0, 0), p6(0, 0) * pp6(1, 0), p6(1, 0) * pp6(1, 0), pp6(1, 0), p6(0, 0), p6(1, 0),
		pp7(0, 0) * p7(0, 0), pp7(0, 0) * p7(1, 0), pp7(0, 0), p7(0, 0) * pp7(1, 0), p7(1, 0) * pp7(1, 0), pp7(1, 0), p7(0, 0), p7(1, 0),
		pp8(0, 0) * p8(0, 0), pp8(0, 0) * p8(1, 0), pp8(0, 0), p8(0, 0) * pp8(1, 0), p8(1, 0) * pp8(1, 0), pp8(1, 0), p8(0, 0), p8(1, 0);


	Eigen::MatrixXd minus1(8, 1);
	minus1 << -1, -1, -1, -1, -1, -1, -1, -1;

	// build the 3 x 3 Fundamental matrix
	Eigen::MatrixXd F(8, 1);
	F = A.inverse() * minus1;
	Eigen::Matrix3d Fundamental_matrix;
	Fundamental_matrix <<
		F(0, 0), F(1, 0), F(2, 0),
		F(3, 0), F(4, 0), F(5, 0),
		F(6, 0), F(7, 0),		1;


	// using SVD to make the rank of Fundamental_matrix to be 2
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(Fundamental_matrix, Eigen::ComputeFullV | Eigen::ComputeFullU);
	Eigen::MatrixXd U = svd.matrixU();
	Eigen::MatrixXd S = svd.singularValues().asDiagonal();
	Eigen::MatrixXd V_T = svd.matrixV().transpose();
	S(2, 2) = 0; // enforcing singularity

	// the final answer of FUNDAMENTAL MATRIX
	Eigen::MatrixXd Fundamental_Matrix_SVD = U * S * V_T;

	std::cout << "Fundamental_Matrix_SVD ... = \n" << Fundamental_Matrix_SVD << std::endl;
	
	return Fundamental_Matrix_SVD;
}


int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();

	/************************ read image  ************************/
	cv::Mat myJPG_001 = cv::imread("../DSC_1365.JPG");  // Read the 001 file
	cv::Mat myJPG_002 = cv::imread("../DSC_1370.JPG");  // Read the 002 file
	if (!myJPG_001.data || !myJPG_002.data){
		cout << "COULD NOT OPEN or find the image" << std::endl;
		return -1;
	}

	// point on 001.jpg
	Eigen::MatrixXd p1(3, 1);	p1 << 570, 917, 1;
	Eigen::MatrixXd p2(3, 1);	p2 << 594, 727, 1;
	Eigen::MatrixXd p3(3, 1);	p3 << 781, 776, 1;
	Eigen::MatrixXd p4(3, 1);	p4 << 1490, 846, 1;
	Eigen::MatrixXd p5(3, 1);	p5 << 1492, 848, 1;
	Eigen::MatrixXd p6(3, 1);	p6 << 1521, 581, 1;
	Eigen::MatrixXd p7(3, 1);	p7 << 1730, 474, 1;
	Eigen::MatrixXd p8(3, 1);	p8 << 2377, 1041, 1;
	Eigen::MatrixXd p9(3, 1);	p9 << 686, 858, 1;
	Eigen::MatrixXd p10(3, 1);	p10 << 651, 750, 1;

	// point on 002.jpg
	Eigen::MatrixXd pp1(3, 1);	pp1 << 792, 996, 1;
	Eigen::MatrixXd pp2(3, 1);	pp2 << 872, 818, 1;
	Eigen::MatrixXd pp3(3, 1);	pp3 << 1426, 829, 1;
	Eigen::MatrixXd pp4(3, 1);	pp4 << 1503, 878, 1;
	Eigen::MatrixXd pp5(3, 1);	pp5 << 681, 907, 1;
	Eigen::MatrixXd pp6(3, 1);	pp6 << 2175, 550, 1;
	Eigen::MatrixXd pp7(3, 1);	pp7 << 1797, 452, 1;
	Eigen::MatrixXd pp8(3, 1);	pp8 << 1846, 987, 1;
	Eigen::MatrixXd pp9(3, 1);	pp9 << 1347, 910, 1;
	Eigen::MatrixXd pp10(3, 1); pp10 << 939, 833, 1;


	Eigen::Matrix3d Fundamental_matrix = get_fundamental_matrix(p1, p2, p3, p4, p5, p6, p7, p8,
																pp1, pp2, pp3, pp4, pp5, pp6, pp7, pp8);
	std::cout << "Fundamental matrix ... = \n" << Fundamental_matrix << std::endl;

	// /**************** calculate the epipoline & epipole ****************/

	Eigen::MatrixXd epipoline_1(3, 1); // p1 -> epipoline_1 (on img2)
	epipoline_1 = Fundamental_matrix * p1;
	// std::cout << "epipoline_1 = \n" << epipoline_1 << std::endl;
	// Eigen::MatrixXd check1 = epipoline_1.transpose() * pp1;
	// std::cout << "check1 = \n" << check1 << std::endl;

	Eigen::MatrixXd epipoline_2(3, 1); // p2 -> epipoline_2 (on img2)
	epipoline_2 = Fundamental_matrix * p2;
	// std::coutcout << "epipoline_2 = \n" << epipoline_2 << std::coutendl;
	// MatrixXd check2 = epipoline_2.transpose() * pp2;
	// std::coutcout << "check2 = \n" << check2 << std::coutendl;

	Eigen::MatrixXd epipoline_3(3, 1);	// p3 -> epipoline_3 (on img2)
	epipoline_3 = Fundamental_matrix * p3;
	// cout << "epipoline_3 = \n" << epipoline_3 << endl;
	// MatrixXd check3 = epipoline_3.transpose() * pp3;
	// cout << "check3 = \n" << check3 << endl;

	Eigen::MatrixXd epipoline_4(3, 1);	// p4 -> epipoline_4 (on img2)
	epipoline_4 = Fundamental_matrix * p4;
	// cout << "epipoline_4 = \n" << epipoline_4 << endl;
	// MatrixXd check4 = epipoline_4.transpose() * pp4;
	// cout << "check4 = \n" << check4 << endl;

	Eigen::MatrixXd epipoline_5(3, 1);	// p5 -> epipoline_5 (on img2)
	epipoline_5 = Fundamental_matrix * p5;
	// cout << "epipoline_5 = \n" << epipoline_5 << endl;
	// MatrixXd check5 = epipoline_5.transpose() * pp5;
	// cout << "check5 = \n" << check5 << endl;

	Eigen::MatrixXd epipoline_6(3, 1);	// p6 -> epipoline_6 (on img2)
	epipoline_6 = Fundamental_matrix * p6;
	// cout << "epipoline_6 = \n" << epipoline_6 << endl;
	// MatrixXd check6 = epipoline_6.transpose() * pp6;
	// cout << "check6 = \n" << check6 << endl;

	Eigen::MatrixXd epipoline_7(3, 1);	// p7 -> epipoline_7 (on img2)
	epipoline_7 = Fundamental_matrix * p7;
	// cout << "epipoline_7 = \n" << epipoline_7 << endl;
	// MatrixXd check7 = epipoline_7.transpose() * pp7;
	// cout << "check7 = \n" << check7 << endl;

	Eigen::MatrixXd epipoline_8(3, 1);	// p8 -> epipoline_8 (on img2)
	epipoline_8 = Fundamental_matrix * p8;
	// cout << "epipoline_8 = \n" << epipoline_8 << endl;
	// MatrixXd check8 = epipoline_8.transpose() * pp8;
	// cout << "check8 = \n" << check8 << endl;

	
	Eigen::MatrixXd epipole(3, 1); // the intersection point of epipoline_1 & epipoline_2
	// doing the cross product to get the intersection point (i.e : epipole)
	epipole(0, 0) = epipoline_1(1, 0) * epipoline_2(2, 0) - epipoline_1(2, 0) * epipoline_2(1, 0);
	epipole(1, 0) = epipoline_1(2, 0) * epipoline_2(0, 0) - epipoline_1(0, 0) * epipoline_2(2, 0);
	epipole(2, 0) = epipoline_1(0, 0) * epipoline_2(1, 0) - epipoline_1(1, 0) * epipoline_2(0, 0);
	epipole = normalized_3x1(epipole);
	std::cout << "after normalized, epipole = \n" << epipole << std::endl << endl;

	// Eigen::MatrixXd if_online1 = epipoline_1.transpose() * epipole;
	// cout << "if_online1 = \n" << if_online1 << endl;
	// Eigen::MatrixXd if_online2 = epipoline_2.transpose() * epipole;
	// cout << "if_online2 = \n" << if_online2 << endl;
	// Eigen::MatrixXd if_online3 = epipoline_3.transpose() * epipole;
	// cout << "if_online3 = \n" << if_online3 << endl;
	// Eigen::MatrixXd if_online4 = epipoline_4.transpose() * epipole;
	// cout << "if_online4 = \n" << if_online4 << endl;
	// Eigen::MatrixXd if_online5 = epipoline_5.transpose() * epipole;
	// cout << "if_online5 = \n" << if_online5 << endl;
	// Eigen::MatrixXd if_online6 = epipoline_6.transpose() * epipole;
	// cout << "if_online6 = \n" << if_online6 << endl;
	// Eigen::MatrixXd if_online7 = epipoline_7.transpose() * epipole;
	// cout << "if_online7 = \n" << if_online7 << endl;
	// Eigen::MatrixXd if_online8 = epipoline_8.transpose() * epipole;
	// cout << "if_online8 = \n" << if_online8 << endl;



	Eigen::MatrixXd epipoline_p1(3, 1); // pp1 -> epipoline_p1 (on img1)
	epipoline_p1 = Fundamental_matrix.transpose() * pp1;
	// cout << "epipoline_p1 = \n" << epipoline_p1 << endl;
	// MatrixXd check_p1 = epipoline_p1.transpose() * p1;
	// cout << "check_p1 = \n" << check_p1 << endl;

	Eigen::MatrixXd epipoline_p2(3, 1); // pp2 -> epipoline_p2 (on img1)
	epipoline_p2 = Fundamental_matrix.transpose() * pp2;
	// cout << "epipoline_p2 = \n" << epipoline_p2 << endl;
	// MatrixXd check_p2 = epipoline_p2.transpose() * p2;
	// cout << "check_p2 = \n" << check_p2 << endl;

	Eigen::MatrixXd epipoline_p3(3, 1); // pp3 -> epipoline_p3 (on img1)
	epipoline_p3 = Fundamental_matrix.transpose() * pp3;
	// cout << "epipoline_p3 = \n" << epipoline_p3 << endl;
	// MatrixXd check_p3 = epipoline_p3.transpose() * p3;
	// cout << "check_p3 = \n" << check_p3 << endl;

	Eigen::MatrixXd epipoline_p4(3, 1); // pp4 -> epipoline_p4 (on img1)
	epipoline_p4 = Fundamental_matrix.transpose() * pp4;
	// cout << "epipoline_p4 = \n" << epipoline_p4 << endl;
	// MatrixXd check_p4 = epipoline_p4.transpose() * p4;
	// cout << "check_p4 = \n" << check_p4 << endl;

	Eigen::MatrixXd epipoline_p5(3, 1); // pp5 -> epipoline_p5 (on img1)
	epipoline_p5 = Fundamental_matrix.transpose() * pp5;
	// cout << "epipoline_p5 = \n" << epipoline_p5 << endl;
	// MatrixXd check_p5 = epipoline_p5.transpose() * p5;
	// cout << "check_p5 = \n" << check_p5 << endl;

	Eigen::MatrixXd epipoline_p6(3, 1); // pp6 -> epipoline_p6 (on img1)
	epipoline_p6 = Fundamental_matrix.transpose() * pp6;
	// cout << "epipoline_p6 = \n" << epipoline_p6 << endl;
	// MatrixXd check_p6 = epipoline_p6.transpose() * p6;
	// cout << "check_p6 = \n" << check_p6 << endl;

	Eigen::MatrixXd epipoline_p7(3, 1); // pp7 -> epipoline_p7 (on img1)
	epipoline_p7 = Fundamental_matrix.transpose() * pp7;
	// cout << "epipoline_p7 = \n" << epipoline_p7 << endl;
	// MatrixXd check_p7 = epipoline_p7.transpose() * p7;
	// cout << "check_p7 = \n" << check_p7 << endl;

	Eigen::MatrixXd epipoline_p8(3, 1); // pp8 -> epipoline_p8 (on img1)
	epipoline_p8 = Fundamental_matrix.transpose() * pp8;
	// cout << "epipoline_p8 = \n" << epipoline_p8 << endl;
	// MatrixXd check_p8 = epipoline_p8.transpose() * p8;
	// cout << "check_p8 = \n" << check_p8 << endl;
	
	Eigen::MatrixXd epipole_p(3, 1); // the intersection point of epipoline_p1 & epipoline_p2
	// doing the cross product
	epipole_p(0, 0) = epipoline_p1(1, 0) * epipoline_p2(2, 0) - epipoline_p1(2, 0) * epipoline_p2(1, 0);
	epipole_p(1, 0) = epipoline_p1(2, 0) * epipoline_p2(0, 0) - epipoline_p1(0, 0) * epipoline_p2(2, 0);
	epipole_p(2, 0) = epipoline_p1(0, 0) * epipoline_p2(1, 0) - epipoline_p1(1, 0) * epipoline_p2(0, 0);
	epipole_p = normalized_3x1(epipole_p);
	//cout << "after normalized, epipole_p = \n" << epipole_p << endl << endl;


	//////// ************************ translate the image center ************************

	int offsetx = -1496; 
	int offsety = -1000; 
	cv::Mat trans_mat = (cv::Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
	
	//warpAffine(myJPG_001, myJPG_001, trans_mat, myJPG_001.size());

	Eigen::MatrixXd translation_matrix(3, 3);
	translation_matrix << 
		trans_mat.at<double>(0, 0), trans_mat.at<double>(0, 1), trans_mat.at<double>(0, 2),
		trans_mat.at<double>(1, 0), trans_mat.at<double>(1, 1), trans_mat.at<double>(1, 2),
								 0,							 0,							 1;
	//cout << "translation_matrix = \n" << translation_matrix << endl;


	epipole = translation_matrix * epipole;
	epipole_p = translation_matrix * epipole_p;


	// ************************ rotate the image center ************************

	cv::Point2f center(0, 0); // decide the coordination of rotate center

	// decide the degree between epipole and x axis
	double param1 = epipole(1, 0) / epipole(0, 0); // degree = arctan (y / x)
	double degree1 = atan(param1) * 180 / PI;
	//cout << "degree1 = " << degree1 << endl;

	double param2 = epipole_p(1, 0) / epipole_p(0, 0); // degree = arctan (y / x)
	double degree2 = atan(param2) * 180 / PI;
	//cout << "degree2 = " << degree2 << endl;

	cv::Mat rot_mat1 = cv::getRotationMatrix2D(center, degree1, 1.0);
	//cv::warpAffine(myJPG_001, myJPG_001, rot_mat1, myJPG_001.size());
	Eigen::MatrixXd rotation_matrix1(3, 3);
	rotation_matrix1 <<
		rot_mat1.at<double>(0, 0), rot_mat1.at<double>(0, 1), rot_mat1.at<double>(0, 2),
		rot_mat1.at<double>(1, 0), rot_mat1.at<double>(1, 1), rot_mat1.at<double>(1, 2),
								0,						   0,				    	  1;

	cv::Mat rot_mat2 = cv::getRotationMatrix2D(center, degree2, 1.0);
	//cv::warpAffine(myJPG_002, myJPG_002, rot_mat2, myJPG_002.size());
	Eigen::MatrixXd rotation_matrix2(3, 3);
	rotation_matrix2 <<
		rot_mat2.at<double>(0, 0), rot_mat2.at<double>(0, 1), rot_mat2.at<double>(0, 2),
		rot_mat2.at<double>(1, 0), rot_mat2.at<double>(1, 1), rot_mat2.at<double>(1, 2),
								0,						   0,						  1;

	
	//cout << "rot_mat1 = \n" << rot_mat1 << endl;
	//cout << "rotation_matrix1 = \n" << rotation_matrix1 << endl;

	epipole = rotation_matrix1 * epipole;
	//cout << "after rotation, epipole = \n" << epipole << endl;

	epipole_p = rotation_matrix2 * epipole_p;
	//cout << "after rotation, epipole_p = \n" << epipole_p << endl;


	
	// ************************  project the eipole to infinity ************************
	Eigen::Matrix3d e_infinity1;
	e_infinity1 <<
						 1, 0, 0,
						 0, 1, 0,
		-1 / epipole(0, 0),	0, 1;
	//cout << "e_infinity1 ... = \n" << e_infinity1 << endl;
	epipole = e_infinity1 * epipole;
	epipole = normalized_3x1(epipole);
	//cout << "after projecting to infinity = \n" << epipole << endl;

	Eigen::Matrix3d e_infinity2;
	e_infinity2 <<
						   1, 0, 0,
						   0, 1, 0,
		-1 / epipole_p(0, 0), 0, 1;
	//cout << "e_infinity2 ... = \n" << e_infinity2 << endl;
	epipole_p = e_infinity2 * epipole_p;
	epipole_p = normalized_3x1(epipole_p);
	//cout << "after projecting to infinity = \n" << epipole_p << endl;


	// ************************  calculate H = GRT ************************

	Eigen::MatrixXd H_GRT1(3, 3); 
	H_GRT1 = e_infinity1 * rotation_matrix1 * translation_matrix;
	//cout << "H_GRT1 = \n" << H_GRT1 << endl;
	
	Eigen::MatrixXd H_GRT2(3, 3);
	H_GRT2 = e_infinity2 * rotation_matrix2 * translation_matrix;
	//cout << "H_GRT2 = \n" << H_GRT2 << endl;

	
	

	// **************  find the homography matrix to make 2 image co-plane **************
	// **************  minimize the horizontal disparity **************
	// **************  Ha = [a, b, c; 0, 1, 0; 0, 0, 1]  **************
	
	


	Eigen::MatrixXd abc_minimize(3, 1);
	Eigen::MatrixXd temp1(3, 3);
	Eigen::MatrixXd temp2(3, 1);

	// version 1
	p1 = H_GRT1 * p1;
	p1 = normalized_3x1(p1);
	//cout << "after ..., p1 = \n" << p1 << endl;
	p2 = H_GRT1 * p2;
	p2 = normalized_3x1(p2);
	p3 = H_GRT1 * p3;
	p3 = normalized_3x1(p3);
	p4 = H_GRT1 * p4;
	p4 = normalized_3x1(p4);
	p5 = H_GRT1 * p5;
	p5 = normalized_3x1(p5);
	p6 = H_GRT1 * p6;
	p6 = normalized_3x1(p6);
	p7 = H_GRT1 * p7;
	p7 = normalized_3x1(p7);
	p8 = H_GRT1 * p8;
	p8 = normalized_3x1(p8);

	pp1 = H_GRT2 * pp1;
	pp1 = normalized_3x1(pp1);
	pp2 = H_GRT2 * pp2;
	pp2 = normalized_3x1(pp2);
	pp3 = H_GRT2 * pp3;
	pp3 = normalized_3x1(pp3);
	pp4 = H_GRT2 * pp4;
	pp4 = normalized_3x1(pp4);
	pp5 = H_GRT2 * pp5;
	pp5 = normalized_3x1(pp5);
	pp6 = H_GRT2 * pp6;
	pp6 = normalized_3x1(pp6);
	pp7 = H_GRT2 * pp7;
	pp7 = normalized_3x1(pp7);
	pp8 = H_GRT2 * pp8;
	pp8 = normalized_3x1(pp8);
	temp1(0, 0) = p1(0, 0) * p1(0, 0) + p2(0, 0) * p2(0, 0) + p3(0, 0) * p3(0, 0) + p4(0, 0) * p4(0, 0) +
				  p5(0, 0) * p5(0, 0) + p6(0, 0) * p6(0, 0) + p7(0, 0) * p7(0, 0) + p8(0, 0) * p8(0, 0);
	temp1(0, 1) = p1(0, 0) * p1(1, 0) + p2(0, 0) * p2(1, 0) + p3(0, 0) * p3(1, 0) + p4(0, 0) * p4(1, 0) + 
				  p5(0, 0) * p5(1, 0) + p6(0, 0) * p6(1, 0) + p7(0, 0) * p7(1, 0) + p8(0, 0) * p8(1, 0);
	temp1(0, 2) = p1(0, 0) + p2(0, 0) + p3(0, 0) + p4(0, 0) + p5(0, 0) + p6(0, 0) + p7(0, 0) + p8(0, 0);
	temp1(1, 0) = temp1(0, 1);
	temp1(1, 1) = p1(1, 0) * p1(1, 0) + p2(1, 0) * p2(1, 0) + p3(1, 0) * p3(1, 0) + p4(1, 0) * p4(1, 0) +
				  p5(1, 0) * p5(1, 0) + p6(1, 0) * p6(1, 0) + p7(1, 0) * p7(1, 0) + p8(1, 0) * p8(1, 0);
	temp1(1, 2) = p1(1, 0) + p2(1, 0) + p3(1, 0) + p4(1, 0) + p5(1, 0) + p6(1, 0) + p7(1, 0) + p8(1, 0);
	temp1(2, 0) = temp1(0, 2);
	temp1(2, 1) = temp1(1, 2);
	temp1(2, 2) = 8;

	temp2(0, 0) = p1(0, 0) * pp1(0, 0) + p2(0, 0) * pp2(0, 0) + p3(0, 0) * pp3(0, 0) + p4(0, 0) * pp4(0, 0) + 
				  p5(0, 0) * pp5(0, 0) + p6(0, 0) * pp6(0, 0) + p7(0, 0) * pp7(0, 0) + p8(0, 0) * pp8(0, 0);
	temp2(1, 0) = p1(1, 0) * pp1(0, 0) + p2(1, 0) * pp2(0, 0) + p3(1, 0) * pp3(0, 0) + p4(1, 0) * pp4(0, 0) + 
				  p5(1, 0) * pp5(0, 0) + p6(1, 0) * pp6(0, 0) + p7(1, 0) * pp7(0, 0) + p8(1, 0) * pp8(0, 0);
	temp2(2, 0) = pp1(0, 0) + pp2(0, 0) + pp3(0, 0) + pp4(0, 0) + pp5(0, 0) + pp6(0, 0) + pp7(0, 0) + pp8(0, 0);


	// version 2
	/*MatrixXd v1(3, 1);
	v1 << 738, 123, 1;
	MatrixXd vv1(3, 1);
	vv1 << 328, 49, 1;

	MatrixXd v2(3, 1);
	v2 << 747, 562, 1;
	MatrixXd vv2(3, 1);
	vv2 << 529, 688, 1;

	MatrixXd v3(3, 1);
	v3 << 295, 201, 1;
	MatrixXd vv3(3, 1);
	vv3 << 291, 150, 1;

	MatrixXd v4(3, 1);
	v4 << 431, 666, 1;
	MatrixXd vv4(3, 1);
	vv4 << 510, 589, 1;

	MatrixXd v5(3, 1);
	v5 << 782, 165, 1;
	MatrixXd vv5(3, 1);
	vv5 << 397, 84, 1;

	MatrixXd v6(3, 1);
	v6 << 331, 251, 1;
	MatrixXd vv6(3, 1);
	vv6 << 316, 201, 1;

	MatrixXd v7(3, 1);
	v7 << 333, 295, 1;
	MatrixXd vv7(3, 1);
	vv7 << 329, 242, 1;

	MatrixXd v8(3, 1);
	v8 << 725, 218, 1;
	MatrixXd vv8(3, 1);
	vv8 << 336, 155, 1;

	temp1(0, 0) = v1(0, 0) * v1(0, 0) + v2(0, 0) * v2(0, 0) + v3(0, 0) * v3(0, 0) + v4(0, 0) * v4(0, 0) +
				  v5(0, 0) * v5(0, 0) + v6(0, 0) * v6(0, 0) + v7(0, 0) * v7(0, 0) + v8(0, 0) * v8(0, 0);
	temp1(0, 1) = v1(0, 0) * v1(1, 0) + v2(0, 0) * v2(1, 0) + v3(0, 0) * v3(1, 0) + v4(0, 0) * v4(1, 0) +
				  v5(0, 0) * v5(1, 0) + v6(0, 0) * v6(1, 0) + v7(0, 0) * v7(1, 0) + v8(0, 0) * v8(1, 0);
	temp1(0, 2) = v1(0, 0) + v2(0, 0) + v3(0, 0) + v4(0, 0) + v5(0, 0) + v6(0, 0) + v7(0, 0) + v8(0, 0);
	temp1(1, 0) = temp1(0, 1);
	temp1(1, 1) = v1(1, 0) * v1(1, 0) + v2(1, 0) * v2(1, 0) + v3(1, 0) * v3(1, 0) + v4(1, 0) * v4(1, 0) +
				  v5(1, 0) * v5(1, 0) + v6(1, 0) * v6(1, 0) + v7(1, 0) * v7(1, 0) + v8(1, 0) * v8(1, 0);
	temp1(1, 2) = v1(1, 0) + v2(1, 0) + v3(1, 0) + v4(1, 0) + v5(1, 0) + v6(1, 0) + v7(1, 0) + v8(1, 0);
	temp1(2, 0) = temp1(0, 2);
	temp1(2, 1) = temp1(1, 2);
	temp1(2, 2) = 8;

	temp2(0, 0) = v1(0, 0) * vv1(0, 0) + v2(0, 0) * vv2(0, 0) + v3(0, 0) * vv3(0, 0) + v4(0, 0) * vv4(0, 0) +
				  v5(0, 0) * vv5(0, 0) + v6(0, 0) * vv6(0, 0) + v7(0, 0) * vv7(0, 0) + v8(0, 0) * vv8(0, 0);
	temp2(1, 0) = v1(1, 0) * vv1(0, 0) + v2(1, 0) * vv2(0, 0) + v3(1, 0) * vv3(0, 0) + v4(1, 0) * vv4(0, 0) +
				  v5(1, 0) * vv5(0, 0) + v6(1, 0) * vv6(0, 0) + v7(1, 0) * vv7(0, 0) + v8(1, 0) * vv8(0, 0);
	temp2(2, 0) = vv1(0, 0) + vv2(0, 0) + vv3(0, 0) + vv4(0, 0) + vv5(0, 0) + vv6(0, 0) + vv7(0, 0) + vv8(0, 0);*/


	abc_minimize = temp1.inverse() * temp2;

	/*cout << "abc_minimize = \n" << abc_minimize << endl;*/

	Eigen::MatrixXd H_A(3, 3);
	H_A << abc_minimize(0, 0), abc_minimize(1, 0), abc_minimize(2, 0),
						    0,					1,					0,
							0,					0,					1;
	//cout << "H_A1 = \n" << H_A << endl;


	// ******************  translate the image to original position *******************

	int offsetx_back = 1496;
	int offsety_back = 1000;
	cv::Mat trans_mat_back = (cv::Mat_<double>(2, 3) << 1, 0, offsetx_back, 
												0, 1, offsety_back);

	//warpAffine(myJPG_001, myJPG_001, trans_mat_back, myJPG_001.size());
	//warpAffine(myJPG_002, myJPG_002, trans_mat_back, myJPG_002.size());
	
	Eigen::MatrixXd translation_matrix_back(3, 3);
	translation_matrix_back <<
		trans_mat_back.at<double>(0, 0), trans_mat_back.at<double>(0, 1), trans_mat_back.at<double>(0, 2),
		trans_mat_back.at<double>(1, 0), trans_mat_back.at<double>(1, 1), trans_mat_back.at<double>(1, 2),
									  0,							   0,							    1;

	//cout << "translation_matrix_back = \n" << translation_matrix_back << endl;





	// ****************** TEST *******************

	Eigen::MatrixXd H_final_1(3, 3);
	H_final_1 = translation_matrix_back * H_A * H_GRT1;
	//H_final_1 = translation_matrix_back * H_GRT1;

	Eigen::MatrixXd H_final_2(3, 3);
	H_final_2 = translation_matrix_back * H_GRT2;


	cv::Mat myJPG_001_rectified(2000, 2992, CV_8UC3, cv::Scalar(0, 0, 0)); // build a 2992 * 2000 black image ...
	Eigen::MatrixXd tmp1(3, 1); // 3x1 temp point
	Eigen::MatrixXd temp_projected1(3, 1); // 3x1 temp point
	for (int i = 0; i < 2992; i++) // x
	{
		for (int j = 0; j < 2000; j++) // y
		{
			tmp1 << i, j, 1;
			temp_projected1 = H_final_1.inverse() * tmp1;
			temp_projected1 = normalized_3x1(temp_projected1);

			if (temp_projected1(0, 0) < 2992 && temp_projected1(0, 0) > 0 && temp_projected1(1, 0) < 2000 && temp_projected1(1, 0) > 0)
			{
				myJPG_001_rectified.at<cv::Vec3b>(cv::Point(i, j))[0] = myJPG_001.at<cv::Vec3b>(temp_projected1(1, 0), temp_projected1(0, 0))[0];
				myJPG_001_rectified.at<cv::Vec3b>(cv::Point(i, j))[1] = myJPG_001.at<cv::Vec3b>(temp_projected1(1, 0), temp_projected1(0, 0))[1];
				myJPG_001_rectified.at<cv::Vec3b>(cv::Point(i, j))[2] = myJPG_001.at<cv::Vec3b>(temp_projected1(1, 0), temp_projected1(0, 0))[2];
			}
			
		}
	}


	cv::Mat myJPG_002_rectified(2000, 2992, CV_8UC3, cv::Scalar(0, 0, 0)); // build a 2992 * 2000 black image ...
	Eigen::MatrixXd tmp2(3, 1); // 3x1 temp point
	Eigen::MatrixXd temp_projected2(3, 1); // 3x1 temp point
	for (int i2 = 0; i2 < 2992; i2++) // x
	{
		for (int j2 = 0; j2 < 2000; j2++) // y
		{
			tmp2 << i2, j2, 1;
			temp_projected2 = H_final_2.inverse() * tmp2;
			temp_projected2 = normalized_3x1(temp_projected2);

			if (temp_projected2(0, 0) < 2992 && temp_projected2(0, 0) > 0 && temp_projected2(1, 0) < 2000 && temp_projected2(1, 0) > 0)
			{
				myJPG_002_rectified.at<cv::Vec3b>(cv::Point(i2, j2))[0] = myJPG_002.at<cv::Vec3b>(temp_projected2(1, 0), temp_projected2(0, 0))[0];
				myJPG_002_rectified.at<cv::Vec3b>(cv::Point(i2, j2))[1] = myJPG_002.at<cv::Vec3b>(temp_projected2(1, 0), temp_projected2(0, 0))[1];
				myJPG_002_rectified.at<cv::Vec3b>(cv::Point(i2, j2))[2] = myJPG_002.at<cv::Vec3b>(temp_projected2(1, 0), temp_projected2(0, 0))[2];
			}

		}
	}

	// ****************** print the rectify image *******************

	//const int kNewWidth = 900;
	//const int kNewHeight = 600;
	//
	//cv::Mat resize_myJPG_001;
	//resize(myJPG_001_rectified, resize_myJPG_001, cvSize(kNewWidth, kNewHeight));
	//imshow("resize result1", resize_myJPG_001);
	//waitKey(0);

	imwrite("result_image1.jpg", myJPG_001_rectified);
	imwrite("result_image2.jpg", myJPG_002_rectified);

	auto current_time = std::chrono::high_resolution_clock::now();
	std::cout << "Done. Program has been running for " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() << " seconds" << std::endl;
					
	return 0;
}
