## Reconstruct 3D from Stereoscopic Images 


#### ABSTRACT

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/whole.png" width="35%" height="35%">

- In this project, we want to reconstruct 3D Object from images that is made by laser scaner from left and right view, as the above shows.

- The Intrinsic and Extrinsic Matrix of the camera are given.

- The Fundamental Matrix between two corresponding images are also given.


#### METHOD

- First, we would transform the images to gray scale images.

- Second, use the fundamental matrix to multiply a point on the left images, the we can get the Epipoline on the right images. 

- Check the point on the Epipoline, if the pixel value is larger than zero, then we get the corresponding point. The pipeline is shown below. 

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/Fundamental_Trans.png" width="25%" height="25%">

- With the projection matrix and the corresponding datasets, we can use the **3D Estimation Direct Trianglation Method** mentioned in *Multiple View Geometry in Computer Vision, by Richard Hartley* to calculate their 3D points, then store them as a .xyz file.

#### Results:

- The 3D point is shown below.
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/original.png" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/3dd.png" width="30%" height="30%"> 




