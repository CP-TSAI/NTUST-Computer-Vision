## HW1: 3D Reconstruction from Silhouette Method

#### ABSTRACT
- In this project, we use the concept of **"Voxel-based Extraction"** to recontruct the 3D object from 2D images.
- 8 images for each object are given, as the following shows. (It is the silhouette of an eagle.)

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/eagle8.png" width="75%" height="75%"> 

- The **Extrinsic Matrix** (i.e The relative position between camera and object) and **Intrinsic Matrix** (i.e: The parameters of the camera) is given, therefore we get the projection matrix from 3D object to 2D image.


#### Method

- Firstly, we assume the 3D object is located in the workspace: 
**-50 < x < 50**; 
**-50 < y < 50**; 
**-10 < z < 90**;

- Secondly, we can use the properties of the *binary image*: **pixel 0 is black, pixel 256 is white**. 

- Third, **we project each point in the 3D workspace to 2D images, if a point can be projected in the white region for all 8 images, then it's the target point**. 

- Finally, output all the target point set, and print them out, we can have the 3D model!

- The result is shown as followings.
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/recon.png" width="25%" height="25%"> 



#### How to execute

- cd to `Shape from Silhouette`

- mkdir build

- cd build

- cmake ..

- make

- ./homework01

- meshlab 3D_point.xyz (<---- check the result)


