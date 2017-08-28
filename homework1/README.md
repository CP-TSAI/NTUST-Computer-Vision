## HW1: 3D reconstruction from silhouette method

### 1. 4 data sets (“Eagle”, “Bunny”, “Teapot”, and “Venus”), Each set has 8 silhouette images.
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/001.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/002.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/003.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/004.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/005.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/006.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/007.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/008.bmp" width="25%" height="25%"> 

## 2. “white” pixels indicate “foreground”, and “black” pixels mean “background”.

## 3. All images are taken with the same intrinsic parameter, and their extrinsic parameters are corresponding to the number in the TXT file. For example, 001.bmp, 002.bmp, 003.bmp et. al. have the extrinsic parameters shown in “camera parameter.txt”

## 4.The workspace in world coordinate is around (-50,-50,-10) to (50,50,90). The voxel is a cube with 1 x 1 x 1 in dimensions. So, there are 1.0 million candidate voxels should be processed. Please project all voxels in each silhouette image, and check their existence. (hint: if a voxel is projected on the background of one image of them, it should be removed. The remained voxels indicate the final shape).

## 5.Please save the voxel file as a .xyz file. It’s simple txt file format for storing (x, y, z) data in every row (as following figure, for example). The professor provides a simple viewer tool for visualizing this kind of data, and you can view files by “meshlab” software as well.
