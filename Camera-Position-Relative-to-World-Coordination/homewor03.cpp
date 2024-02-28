// homework01.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <windows.h> 
// #include "opencv/opencv2/opencv.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <conio.h> 
#include <Eigen/Dense>  

// #ifdef ___WIN_X64_LIB___
// #pragma comment(lib, "../../lib/x64/opencv_world320.lib")
// #endif

// #ifdef ___WIN_X86_LIB___
// #pragma comment(lib, "../../lib/x86/opencv_world320.lib")
// #endif

// using namespace cv;
// using namespace Eigen;
using namespace std;

// normalize the 3x1 matrix
void normalized_3x1(Eigen::MatrixXd& mat)
{
	mat(0, 0) = mat(0, 0) / mat(2, 0);
	mat(1, 0) = mat(1, 0) / mat(2, 0);
	mat(2, 0) = 1;
	//return mat;
}

int main()
{
	// // coordination on image
	// MatrixXd A1(3, 1);	A1 << 217, 135, 1;
	// MatrixXd A2(3, 1);	A2 << 248, 311, 1;
	// MatrixXd A3(3, 1);	A3 << 370, 262, 1;
	// MatrixXd A4(3, 1);	A4 << 365, 117, 1;
	// MatrixXd B1(3, 1);	B1 << 440, 117, 1;
	// MatrixXd B2(3, 1);	B2 << 434, 262, 1;
	// MatrixXd B3(3, 1);	B3 << 562, 307, 1;
	// MatrixXd B4(3, 1);	B4 << 594, 134, 1;
	// MatrixXd C1(3, 1);	C1 << 401, 289, 1;
	// MatrixXd C2(3, 1);	C2 << 300, 337, 1;
	// MatrixXd C3(3, 1);	C3 << 409, 404, 1;
	// MatrixXd C4(3, 1);	C4 << 508, 334, 1;

	// // calculate the Homography matrix
	// MatrixXd unit1(3, 1);	unit1 << 0, 0, 1;
	// MatrixXd unit2(3, 1);	unit2 << 0, 30, 1;
	// MatrixXd unit3(3, 1);	unit3 << 30, 30, 1;
	// MatrixXd unit4(3, 1);	unit4 << 30, 0, 1;

	// MatrixXd unit1_c(3, 1);	unit1_c << 0, 0, 1;
	// MatrixXd unit2_c(3, 1);	unit2_c <<  30, 0, 1;
	// MatrixXd unit3_c(3, 1);	unit3_c << 30, 30, 1;
	// MatrixXd unit4_c(3, 1);	unit4_c << 0, 30, 1;



	// MatrixXd A_unit_to_square(12, 9);
	// A_unit_to_square <<
	// 	0, 0, 0, -1 * A1(2, 0)*unit1(0, 0), -1 * A1(2, 0)*unit1(1, 0), -1 * A1(2, 0)*unit1(2, 0), A1(1, 0)*unit1(0, 0), A1(1, 0)*unit1(1, 0), A1(1, 0)*unit1(2, 0),
	// 	A1(2, 0)*unit1(0, 0), A1(2, 0)*unit1(1, 0), A1(2, 0)*unit1(2, 0), 0, 0, 0, -1 * A1(0, 0)*unit1(0, 0), -1 * A1(0, 0)*unit1(1, 0), -1 * A1(0, 0)*unit1(2, 0),
	// 	0, 0, 0, -1 * A2(2, 0)*unit2(0, 0), -1 * A2(2, 0)*unit2(1, 0), -1 * A2(2, 0)*unit2(2, 0), A2(1, 0)*unit2(0, 0), A2(1, 0)*unit2(1, 0), A2(1, 0)*unit2(2, 0),
	// 	A2(2, 0)*unit2(0, 0), A2(2, 0)*unit2(1, 0), A2(2, 0)*unit2(2, 0), 0, 0, 0, -1 * A2(0, 0)*unit2(0, 0), -1 * A2(0, 0)*unit2(1, 0), -1 * A2(0, 0)*unit2(2, 0),
	// 	0, 0, 0, -1 * A3(2, 0)*unit3(0, 0), -1 * A3(2, 0)*unit3(1, 0), -1 * A3(2, 0)*unit3(2, 0), A3(1, 0)*unit3(0, 0), A3(1, 0)*unit3(1, 0), A3(1, 0)*unit3(2, 0),
	// 	A3(2, 0)*unit3(0, 0), A3(2, 0)*unit3(1, 0), A3(2, 0)*unit3(2, 0), 0, 0, 0, -1 * A3(0, 0)*unit3(0, 0), -1 * A3(0, 0)*unit3(1, 0), -1 * A3(0, 0)*unit3(2, 0),
	// 	0, 0, 0, -1 * A4(2, 0)*unit4(0, 0), -1 * A4(2, 0)*unit4(1, 0), -1 * A4(2, 0)*unit4(2, 0), A4(1, 0)*unit4(0, 0), A4(1, 0)*unit4(1, 0), A4(1, 0)*unit4(2, 0),
	// 	A4(2, 0)*unit4(0, 0), A4(2, 0)*unit4(1, 0), A4(2, 0)*unit4(2, 0), 0, 0, 0, -1 * A4(0, 0)*unit4(0, 0), -1 * A4(0, 0)*unit4(1, 0), -1 * A4(0, 0)*unit4(2, 0);

	// MatrixXd B_unit_to_square(12, 9);
	// B_unit_to_square <<
	// 	0, 0, 0, -1 * B1(2, 0)*unit1(0, 0), -1 * B1(2, 0)*unit1(1, 0), -1 * B1(2, 0)*unit1(2, 0), B1(1, 0)*unit1(0, 0), B1(1, 0)*unit1(1, 0), B1(1, 0)*unit1(2, 0),
	// 	B1(2, 0)*unit1(0, 0), B1(2, 0)*unit1(1, 0), B1(2, 0)*unit1(2, 0), 0, 0, 0, -1 * B1(0, 0)*unit1(0, 0), -1 * B1(0, 0)*unit1(1, 0), -1 * B1(0, 0)*unit1(2, 0),
	// 	0, 0, 0, -1 * B2(2, 0)*unit2(0, 0), -1 * B2(2, 0)*unit2(1, 0), -1 * B2(2, 0)*unit2(2, 0), B2(1, 0)*unit2(0, 0), B2(1, 0)*unit2(1, 0), B2(1, 0)*unit2(2, 0),
	// 	B2(2, 0)*unit2(0, 0), B2(2, 0)*unit2(1, 0), B2(2, 0)*unit2(2, 0), 0, 0, 0, -1 * B2(0, 0)*unit2(0, 0), -1 * B2(0, 0)*unit2(1, 0), -1 * B2(0, 0)*unit2(2, 0),
	// 	0, 0, 0, -1 * B3(2, 0)*unit3(0, 0), -1 * B3(2, 0)*unit3(1, 0), -1 * B3(2, 0)*unit3(2, 0), B3(1, 0)*unit3(0, 0), B3(1, 0)*unit3(1, 0), B3(1, 0)*unit3(2, 0),
	// 	B3(2, 0)*unit3(0, 0), B3(2, 0)*unit3(1, 0), B3(2, 0)*unit3(2, 0), 0, 0, 0, -1 * B3(0, 0)*unit3(0, 0), -1 * B3(0, 0)*unit3(1, 0), -1 * B3(0, 0)*unit3(2, 0),
	// 	0, 0, 0, -1 * B4(2, 0)*unit4(0, 0), -1 * B4(2, 0)*unit4(1, 0), -1 * B4(2, 0)*unit4(2, 0), B4(1, 0)*unit4(0, 0), B4(1, 0)*unit4(1, 0), B4(1, 0)*unit4(2, 0),
	// 	B4(2, 0)*unit4(0, 0), B4(2, 0)*unit4(1, 0), B4(2, 0)*unit4(2, 0), 0, 0, 0, -1 * B4(0, 0)*unit4(0, 0), -1 * B4(0, 0)*unit4(1, 0), -1 * B4(0, 0)*unit4(2, 0);

	// MatrixXd C_unit_to_square(12, 9);
	// C_unit_to_square <<
	// 	0, 0, 0, -1 * C1(2, 0)*unit1_c(0, 0), -1 * C1(2, 0)*unit1_c(1, 0), -1 * C1(2, 0)*unit1_c(2, 0), C1(1, 0)*unit1_c(0, 0), C1(1, 0)*unit1_c(1, 0), C1(1, 0)*unit1_c(2, 0),
	// 	C1(2, 0)*unit1_c(0, 0), C1(2, 0)*unit1_c(1, 0), C1(2, 0)*unit1_c(2, 0), 0, 0, 0, -1 * C1(0, 0)*unit1_c(0, 0), -1 * C1(0, 0)*unit1_c(1, 0), -1 * C1(0, 0)*unit1_c(2, 0),
	// 	0, 0, 0, -1 * C2(2, 0)*unit2_c(0, 0), -1 * C2(2, 0)*unit2_c(1, 0), -1 * C2(2, 0)*unit2_c(2, 0), C2(1, 0)*unit2_c(0, 0), C2(1, 0)*unit2_c(1, 0), C2(1, 0)*unit2_c(2, 0),
	// 	C2(2, 0)*unit2_c(0, 0), C2(2, 0)*unit2_c(1, 0), C2(2, 0)*unit2_c(2, 0), 0, 0, 0, -1 * C2(0, 0)*unit2_c(0, 0), -1 * C2(0, 0)*unit2_c(1, 0), -1 * C2(0, 0)*unit2_c(2, 0),
	// 	0, 0, 0, -1 * C3(2, 0)*unit3_c(0, 0), -1 * C3(2, 0)*unit3_c(1, 0), -1 * C3(2, 0)*unit3_c(2, 0), C3(1, 0)*unit3_c(0, 0), C3(1, 0)*unit3_c(1, 0), C3(1, 0)*unit3_c(2, 0),
	// 	C3(2, 0)*unit3_c(0, 0), C3(2, 0)*unit3_c(1, 0), C3(2, 0)*unit3_c(2, 0), 0, 0, 0, -1 * C3(0, 0)*unit3_c(0, 0), -1 * C3(0, 0)*unit3_c(1, 0), -1 * C3(0, 0)*unit3_c(2, 0),
	// 	0, 0, 0, -1 * C4(2, 0)*unit4_c(0, 0), -1 * C4(2, 0)*unit4_c(1, 0), -1 * C4(2, 0)*unit4_c(2, 0), C4(1, 0)*unit4_c(0, 0), C4(1, 0)*unit4_c(1, 0), C4(1, 0)*unit4_c(2, 0),
	// 	C4(2, 0)*unit4_c(0, 0), C4(2, 0)*unit4_c(1, 0), C4(2, 0)*unit4_c(2, 0), 0, 0, 0, -1 * C4(0, 0)*unit4_c(0, 0), -1 * C4(0, 0)*unit4_c(1, 0), -1 * C4(0, 0)*unit4_c(2, 0);

	// // using SVD to make the rank of Fundamental_matrix to be 2
	// JacobiSVD<MatrixXd> svd_A(A_unit_to_square, ComputeFullV | ComputeFullU);
	// //MatrixXd U = svd.matrixU();
	// //MatrixXd S = svd.singularValues().asDiagonal();
	// MatrixXd V_A = svd_A.matrixV();

	// JacobiSVD<MatrixXd> svd_B(B_unit_to_square, ComputeFullV | ComputeFullU);
	// MatrixXd V_B = svd_B.matrixV();

	// JacobiSVD<MatrixXd> svd_C(C_unit_to_square, ComputeFullV | ComputeFullU);
	// MatrixXd V_C = svd_C.matrixV();

	// MatrixXd H_A(3, 3);
	// H_A << V_A(0, 8), V_A(1, 8), V_A(2, 8),
	// 	   V_A(3, 8), V_A(4, 8), V_A(5, 8),
	// 	   V_A(6, 8), V_A(7, 8), V_A(8, 8);

	// MatrixXd H_B(3, 3);
	// H_B << V_B(0, 8), V_B(1, 8), V_B(2, 8),
	// 	   V_B(3, 8), V_B(4, 8), V_B(5, 8),
	// 	   V_B(6, 8), V_B(7, 8), V_B(8, 8);

	// MatrixXd H_C(3, 3);
	// H_C << V_C(0, 8), V_C(1, 8), V_C(2, 8),
	// 	   V_C(3, 8), V_C(4, 8), V_C(5, 8),
	// 	   V_C(6, 8), V_C(7, 8), V_C(8, 8);
	
	// // normalize
	// for (int i = 0; i < 3; i++) {
	// 	for (int j = 0; j < 3; j++) {
	// 		H_A(i, j) = H_A(i, j) / V_A(8, 8);
	// 		H_B(i, j) = H_B(i, j) / V_B(8, 8);
	// 		H_C(i, j) = H_C(i, j) / V_C(8, 8);
	// 	}
	// }
	
	// //MatrixXd pp1(3, 1);
	// //pp1 = H_A * unit1;
	// //normalized_3x1(pp1);
	// //cout << "pp1 = \n " << pp1 << endl;


	// MatrixXd H_A_1(3, 1);
	// H_A_1 << H_A(0, 0), H_A(1, 0), H_A(2, 0);
	// MatrixXd H_A_2(3, 1);
	// H_A_2 << H_A(0, 1), H_A(1, 1), H_A(2, 1);
	// MatrixXd H_A_3(3, 1);
	// H_A_3 << H_A(0, 2), H_A(1, 2), H_A(2, 2);

	// MatrixXd H_B_1(3, 1);
	// H_B_1 << H_B(0, 0), H_B(1, 0), H_B(2, 0);
	// MatrixXd H_B_2(3, 1);
	// H_B_2 << H_B(0, 1), H_B(1, 1), H_B(2, 1);
	// MatrixXd H_B_3(3, 1);
	// H_B_3 << H_B(0, 2), H_B(1, 2), H_B(2, 2);

	// MatrixXd H_C_1(3, 1);
	// H_C_1 << H_C(0, 0), H_C(1, 0), H_C(2, 0);
	// MatrixXd H_C_2(3, 1);
	// H_C_2 << H_C(0, 1), H_C(1, 1), H_C(2, 1);
	// MatrixXd H_C_3(3, 1);
	// H_C_3 << H_C(0, 2), H_C(1, 2), H_C(2, 2);



	
	// MatrixXd H_matrix(6, 6);
	// H_matrix <<
	// 	H_A_1(0, 0)*H_A_2(0, 0), H_A_1(0, 0)*H_A_2(1, 0) + H_A_1(1, 0)*H_A_2(0, 0), H_A_1(0, 0)*H_A_2(2, 0) + H_A_1(2, 0)*H_A_2(0, 0), H_A_1(1, 0)*H_A_2(1, 0), H_A_1(1, 0)*H_A_2(2, 0) + H_A_1(2, 0)*H_A_2(1, 0), H_A_1(2, 0)*H_A_2(2, 0),
	// 	H_A_1(0, 0)*H_A_1(0, 0) - H_A_2(0, 0)*H_A_2(0, 0), 2 * (H_A_1(0, 0)*H_A_1(1, 0) - H_A_2(0, 0)*H_A_2(1, 0)), 2 * (H_A_1(0, 0)*H_A_1(2, 0) - H_A_2(0, 0)*H_A_2(2, 0)), H_A_1(1, 0)*H_A_1(1, 0) - H_A_2(1, 0)*H_A_2(1, 0), 2 * (H_A_1(1, 0)*H_A_1(2, 0) - H_A_2(1, 0)*H_A_2(2, 0)), H_A_1(2, 0)*H_A_1(2, 0) - H_A_2(2, 0)*H_A_2(2, 0),
	// 	H_B_1(0, 0)*H_B_2(0, 0), H_B_1(0, 0)*H_B_2(1, 0) + H_B_1(1, 0)*H_B_2(0, 0), H_B_1(0, 0)*H_B_2(2, 0) + H_B_1(2, 0)*H_B_2(0, 0), H_B_1(1, 0)*H_B_2(1, 0), H_B_1(1, 0)*H_B_2(2, 0) + H_B_1(2, 0)*H_B_2(1, 0), H_B_1(2, 0)*H_B_2(2, 0),
	// 	H_B_1(0, 0)*H_B_1(0, 0) - H_B_2(0, 0)*H_B_2(0, 0), 2 * (H_B_1(0, 0)*H_B_1(1, 0) - H_B_2(0, 0)*H_B_2(1, 0)), 2 * (H_B_1(0, 0)*H_B_1(2, 0) - H_B_2(0, 0)*H_B_2(2, 0)), H_B_1(1, 0)*H_B_1(1, 0) - H_B_2(1, 0)*H_B_2(1, 0), 2 * (H_B_1(1, 0)*H_B_1(2, 0) - H_B_2(1, 0)*H_B_2(2, 0)), H_B_1(2, 0)*H_B_1(2, 0) - H_B_2(2, 0)*H_B_2(2, 0),
	// 	H_C_1(0, 0)*H_C_2(0, 0), H_C_1(0, 0)*H_C_2(1, 0) + H_C_1(1, 0)*H_C_2(0, 0), H_C_1(0, 0)*H_C_2(2, 0) + H_C_1(2, 0)*H_C_2(0, 0), H_C_1(1, 0)*H_C_2(1, 0), H_C_1(1, 0)*H_C_2(2, 0) + H_C_1(2, 0)*H_C_2(1, 0), H_C_1(2, 0)*H_C_2(2, 0),
	// 	H_C_1(0, 0)*H_C_1(0, 0) - H_C_2(0, 0)*H_C_2(0, 0), 2 * (H_C_1(0, 0)*H_C_1(1, 0) - H_C_2(0, 0)*H_C_2(1, 0)), 2 * (H_C_1(0, 0)*H_C_1(2, 0) - H_C_2(0, 0)*H_C_2(2, 0)), H_C_1(1, 0)*H_C_1(1, 0) - H_C_2(1, 0)*H_C_2(1, 0), 2 * (H_C_1(1, 0)*H_C_1(2, 0) - H_C_2(1, 0)*H_C_2(2, 0)), H_C_1(2, 0)*H_C_1(2, 0) - H_C_2(2, 0)*H_C_2(2, 0);

	// JacobiSVD<MatrixXd> svd_H_matrix(H_matrix, ComputeFullV | ComputeFullU);
	// MatrixXd V_H_matrix = svd_H_matrix.matrixV();

	// MatrixXd omega(3, 3);
	// omega << V_H_matrix(0, 5), V_H_matrix(1, 5), V_H_matrix(2, 5),
	// 		 V_H_matrix(1, 5), V_H_matrix(3, 5), V_H_matrix(4, 5),
	// 		 V_H_matrix(2, 5), V_H_matrix(4, 5), V_H_matrix(5, 5);

	// //cout << "omega = \n" << omega << endl << endl;

	// MatrixXd omega_inv(3, 3);
	// omega_inv = omega.inverse();
	// //cout << "omega_inv = \n" << omega_inv << endl << endl;

	// // normalize
	// double normalizer = omega_inv(2, 2);
	// for (int i = 0; i < 3; i++)
	// 	for (int j = 0; j < 3; j++)
	// 		omega_inv(i,j) = omega_inv(i,j) / normalizer;
	// //cout << "after normalized, omega_inv = \n " << omega_inv << endl;

	// MatrixXd K(3, 3);
	// double c = omega_inv(0, 2);
	// double e = omega_inv(1, 2);
	// double d = sqrt(omega_inv(1, 1) - e*e);
	// double b = (omega_inv(0, 1) - c*e) / d;
	// double a = sqrt(omega_inv(0, 0) - b*b - c*c);
	// K << a, b, c,
	// 	 0, d, e,
	// 	 0, 0, 1;
	// //cout << "K = \n " << K << endl;





	// //MatrixXd ra(3, 3);
	// //ra = K.inverse()*H_A;
	// //cout << "ra = \n " << ra << endl;

	// MatrixXd rc(3, 3);
	// rc = K.inverse()*H_C;
	// //cout << "ra = \n " << ra << endl;


	// //double length_a = sqrt(ra(0, 0)*ra(0, 0) + ra(1, 0)*ra(1, 0) + ra(2, 0)*ra(2, 0));
	// ////cout << "length = " << length << endl;
	// //Vector3d ra_1(ra(0, 0) / length_a, ra(1, 0) / length_a, ra(2, 0) / length_a);
	// //Vector3d ra_2(ra(0, 1) / length_a, ra(1, 1) / length_a, ra(2, 1) / length_a);
	// //Vector3d ra_3 = ra_1.cross(ra_2);
	// //ra_3.normalized();
	// //ra_2 = ra_3.cross(ra_1);
	// //cout << "ra_1 = \n " << ra_1 << ", ra_1.norm() = " << ra_1.norm() << endl;


	// double length_c = sqrt(rc(0, 0)*rc(0, 0) + rc(1, 0)*rc(1, 0) + rc(2, 0)*rc(2, 0));
	// //cout << "length = " << length << endl;
	// Vector3d rc_1(rc(0, 0) / length_c, rc(1, 0) / length_c, rc(2, 0) / length_c);
	// Vector3d rc_2(rc(0, 1) / length_c, rc(1, 1) / length_c, rc(2, 1) / length_c);
	// Vector3d rc_3 = rc_1.cross(rc_2);
	// rc_3.normalized();
	// rc_2 = rc_3.cross(rc_1);
	
	// //MatrixXd t_a(3, 1);
	// //t_a = K.inverse() * H_A_3 / length_a;

	// MatrixXd t_c(3, 1);
	// t_c = K.inverse() * H_C_3 / length_c;


	// //MatrixXd Rt_a(3, 4);
	// //Rt_a <<
	// //	ra_1(0), ra_2(0), ra_3(0), t_a(0,0),
	// //	ra_1(1), ra_2(1), ra_3(1), t_a(1,0),
	// //	ra_1(2), ra_2(2), ra_3(2), t_a(2,0);
	// //cout << "Rt_a = \n " << Rt_a << endl;

	// MatrixXd Rt_c(3, 4);
	// Rt_c <<
	// 	rc_1(0), rc_2(0), rc_3(0), t_c(0, 0),
	// 	rc_1(1), rc_2(1), rc_3(1), t_c(1, 0),
	// 	rc_1(2), rc_2(2), rc_3(2), t_c(2, 0);
	// //cout << "Rt_c = \n " << Rt_c << endl;

	// //MatrixXd Rt_a_extend(4, 4);
	// //Rt_a_extend <<
	// //	ra_1(0), ra_2(0), ra_3(0), t_a(0, 0),
	// //	ra_1(1), ra_2(1), ra_3(1), t_a(1, 0),
	// //	ra_1(2), ra_2(2), ra_3(2), t_a(2, 0),
	// //		  0,	   0,	    0,		 1;

	// MatrixXd Rt_c_extend(4, 4);
	// Rt_c_extend <<
	// 	rc_1(0), rc_2(0), rc_3(0), t_c(0, 0),
	// 	rc_1(1), rc_2(1), rc_3(1), t_c(1, 0),
	// 	rc_1(2), rc_2(2), rc_3(2), t_c(2, 0),
	// 	0, 0, 0, 1;

	// MatrixXd Rt_c_extend_inverse(4, 4);
	// Rt_c_extend_inverse = Rt_c_extend.inverse();

	// //cout << "Rt_c_extend_inverse = \n " << Rt_c_extend_inverse << endl;


	// char filename[] = "coordination_of_camera.txt";
	// fstream fp;
	// fp.open(filename, ios::out);
	// if (!fp) {
	// 	cout << "Fail to open file: " << filename << endl;
	// }
	// fp << "the coordination of camera is" << endl << Rt_c_extend_inverse(0, 3) << endl << Rt_c_extend_inverse(1, 3) << endl << Rt_c_extend_inverse(2, 3);
	// fp.close();

					
	// //system("pause");
	// return 0;
}
