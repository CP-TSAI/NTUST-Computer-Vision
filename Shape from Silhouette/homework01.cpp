#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include "opencv2/opencv.hpp"
using namespace std;

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

void read_files(
	string object_name,
	std::vector<std::vector<double>>& intrinsic_parameters,
	std::vector<std::vector<std::vector<double>>>& extrinsic_parameters)
{
	std::ifstream input_file("../imgs/" + object_name + "/camera_parameter.txt");

    if (!input_file.is_open())
	{
        std::cerr << "Error opening file!" << std::endl;
    }


    std::string line;
	int img_num = 0;
    while (std::getline(input_file, line)) {
        std::istringstream iss(line);

		// extrinsic parameters
		if (line.size() > 2 && line[1] == 'E')
		{
			string img_num_str = line.substr(line.size()-8);
			img_num = img_num_str[2] - '0';
		}

        // Skip comments and empty lines
        if (line.size() <= 1 || line[0] == '#' || line[0] == 'F')
		{
            continue;
        }
		// std::cout << "line: " << line << std::endl;
		// std::cout << "line.size: " << line.size() << std::endl;

		
        // Read values and store in appropriate vectors
        double value;
        std::vector<double> parameters;

        while (iss >> value)
		{
            parameters.push_back(value);
        }

		// Intrinsic parameter
        if (parameters.size() == 3)
		{
            intrinsic_parameters.push_back(parameters);
        }
		// Extrinsic parameter for one image
		else if (parameters.size() == 4)
		{
			// std::cout << "img_num: " << img_num << std::endl;
            extrinsic_parameters[img_num-1].push_back(parameters);
        }
    }

    // Print the extracted parameters for verification
    // std::cout << "Intrinsic Parameters:\n";
    // for (const auto &param : intrinsic_parameters) {
    //     for (const auto &value : param) {
    //         std::cout << value << " ";
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << "\nExtrinsic Parameters for Image 1:\n";
    // for (int i = 0; i < extrinsic_parameters.size(); i++)
	// {
	// 	std::cout << "--- extrinsic matrix: " << i << std::endl;
	// 	for (int j = 0; j < extrinsic_parameters[i].size(); j++)
	// 	{
	// 		for (int k = 0; k < extrinsic_parameters[i][j].size(); k++)
	// 		{
	// 			std::cout << extrinsic_parameters[i][j][k] << " ";
	// 		}
	// 		std::cout << std::endl;
	// 	}
	// }
}

string choice_to_object_name(int choice)
{
	if (choice == 1) return "Bunny";
	else if (choice == 2) return "Eagle";
	else if (choice == 3) return "Teapot";
	else if (choice == 4) return "Venus";
	else return "PLEASE MAKE A MEANINGFUL CHOICE";
}



void get_projection_matrix(
	std::vector<std::vector<double>>& intrinsic_parameters, 
	std::vector<std::vector<std::vector<double>>>& extrinsic_parameters, 
	std::vector<std::vector<std::vector<double>>>& projections)
{
	// init projection to have the same dimension as extrinsic_parameters
	projections = extrinsic_parameters;

	// make every value in the projection matrix 0
	for (int i = 0; i < projections.size(); i++)
	{
		for (int j = 0; j < projections[i].size(); j++)
		{
			for (int k = 0; k < projections[i][j].size(); k++)
			{
				projections[i][j][k] = 0;
			}
		}
	}

	for (int matrix_idx = 0; matrix_idx < extrinsic_parameters.size(); matrix_idx++)
	{

		// use 3 for loops for the regular matrix calculation
		// projection matrix = K * [R|t] (K: 3x3, [R|t]: 3x4)
		for (unsigned i = 0; i < intrinsic_parameters.size(); i++)
			for (unsigned j = 0; j < extrinsic_parameters[matrix_idx][i].size(); j++)
				for (unsigned k = 0; k < intrinsic_parameters[i].size(); k++)
					projections[matrix_idx][i][j] += intrinsic_parameters[i][k] * extrinsic_parameters[matrix_idx][k][j];
	
	}
}

Point_on_2D get_projection_and_normalized_result(vector<vector<double>>& projection, Point_on_3D& pt_3d)
{
	Point_on_2D pt_2d;
	// projection
	pt_2d.x_2d = projection[0][0] * pt_3d.x_3d + projection[0][1] * pt_3d.y_3d + projection[0][2] * pt_3d.z_3d + projection[0][3] * pt_3d.w_3d;
	pt_2d.y_2d = projection[1][0] * pt_3d.x_3d + projection[1][1] * pt_3d.y_3d + projection[1][2] * pt_3d.z_3d + projection[1][3] * pt_3d.w_3d;
	pt_2d.w_2d = projection[2][0] * pt_3d.x_3d + projection[2][1] * pt_3d.y_3d + projection[2][2] * pt_3d.z_3d + projection[2][3] * pt_3d.w_3d;

	// normalize
	pt_2d.x_2d = pt_2d.x_2d / pt_2d.w_2d;
	pt_2d.y_2d = pt_2d.y_2d / pt_2d.w_2d;
	pt_2d.w_2d = pt_2d.w_2d / pt_2d.w_2d;

	return pt_2d;
}

int main()
{
	// (1) Bunny, (2) Eagle, (3) Teapot, (4) Venus
	int choice = 2;
	string object_name = choice_to_object_name(choice);
	std::cout << "[main] you've chosen " << object_name << std::endl;


	// read camera parameters
    std::vector<std::vector<double>> intrinsic_parameters;
    std::vector<std::vector<std::vector<double>>> extrinsic_parameters(8);
    read_files(object_name, intrinsic_parameters, extrinsic_parameters);


	// calculate projection matrix = intrinsic x extrinsic 
	std::vector<std::vector<std::vector<double>>> projections;
	get_projection_matrix(intrinsic_parameters, extrinsic_parameters, projections);


	// read images
	cv::Mat myBMP_001 = cv::imread("../imgs/" + object_name + "/001.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 001 file
	cv::Mat myBMP_002 = cv::imread("../imgs/" + object_name + "/002.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 002 file
	cv::Mat myBMP_003 = cv::imread("../imgs/" + object_name + "/003.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 003 file
	cv::Mat myBMP_004 = cv::imread("../imgs/" + object_name + "/004.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 004 file
	cv::Mat myBMP_005 = cv::imread("../imgs/" + object_name + "/005.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 005 file
	cv::Mat myBMP_006 = cv::imread("../imgs/" + object_name + "/006.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 006 file
	cv::Mat myBMP_007 = cv::imread("../imgs/" + object_name + "/007.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 007 file
	cv::Mat myBMP_008 = cv::imread("../imgs/" + object_name + "/008.bmp", CV_LOAD_IMAGE_GRAYSCALE);  // Read the 008 file
	if (!myBMP_001.data || !myBMP_002.data || !myBMP_003.data || !myBMP_004.data || !myBMP_005.data || !myBMP_006.data || !myBMP_007.data || !myBMP_008.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}


	
	
	bool checking;
	int pixel_value;

	vector<Point_on_3D> vec_p_on_3d;
	for (double x_workspace = -50; x_workspace <= 50; x_workspace++)
	{
		for (double y_workspace = -50; y_workspace <= 50; y_workspace++)
		{
			for (double z_workspace = -10; z_workspace <= 90; z_workspace++)
			{
				checking = 1; // initialize the bool value

				// project the 3D workspace on to 2D coordination ...
				Point_on_3D p_on_3d_temp;
				p_on_3d_temp.x_3d = x_workspace;
				p_on_3d_temp.y_3d = y_workspace;
				p_on_3d_temp.z_3d = z_workspace;


				// ***** check 001.bmp *****
				Point_on_2D p_on_2d_temp = get_projection_and_normalized_result(projections[0], p_on_3d_temp);

				if (0 <= p_on_2d_temp.x_2d && p_on_2d_temp.x_2d < 800 && 
					0 <= p_on_2d_temp.y_2d && p_on_2d_temp.y_2d < 600) // 0 < x < 800 ; 0 < y <600
				{
					pixel_value = (int)myBMP_001.at<uchar>(p_on_2d_temp.y_2d, p_on_2d_temp.x_2d);
					
					if (pixel_value == 0) { checking = 0; } // GET-OUT!
	
				}
				else
					checking = 0;


				// ***** check 002.bmp *****
				if (checking)
				{
					p_on_2d_temp = get_projection_and_normalized_result(projections[1], p_on_3d_temp);

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
					p_on_2d_temp = get_projection_and_normalized_result(projections[2], p_on_3d_temp);

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
					p_on_2d_temp = get_projection_and_normalized_result(projections[3], p_on_3d_temp);
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
					p_on_2d_temp = get_projection_and_normalized_result(projections[4], p_on_3d_temp);

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
					p_on_2d_temp = get_projection_and_normalized_result(projections[5], p_on_3d_temp);

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
					p_on_2d_temp = get_projection_and_normalized_result(projections[6], p_on_3d_temp);

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
					p_on_2d_temp = get_projection_and_normalized_result(projections[7], p_on_3d_temp);

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
				}
			}
		}
	}

	// output the 3D point ...
	ofstream myfile_xyz;
	string output_file = "3D_point.xyz";
	myfile_xyz.open(output_file);
	for (unsigned i = 0; i < vec_p_on_3d.size(); i++)
	{
		myfile_xyz << vec_p_on_3d[i].x_3d << " " << vec_p_on_3d[i].y_3d << " " << vec_p_on_3d[i].z_3d << endl;
	}
	myfile_xyz.close();
	cout << "[main] succesfully output to file: " << output_file << endl;

	return 0;
}