## HW1: 3D reconstruction from silhouette method

- 4 data sets (“Eagle”, “Bunny”, “Teapot”, and “Venus”), Each set has 8 silhouette images.

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/001.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/002.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/003.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/004.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/005.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/006.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/007.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/008.bmp" width="25%" height="25%"> 

- “white” pixels indicate “foreground”, and “black” pixels mean “background”.

- Given the same intrinsic parameter and respective extrinsic parameter.

- The workspace in world coordinate is around (-50,-50,-10) to (50,50,90). The voxel is a cube with 1 x 1 x 1 in dimensions. So, there are 1.0 million candidate voxels should be processed. 

- hint: if a voxel is projected on the background of one image of them, it should be removed. The remained voxels indicate the final shape.

## Results:
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/recon.png" width="25%" height="25%"> 

