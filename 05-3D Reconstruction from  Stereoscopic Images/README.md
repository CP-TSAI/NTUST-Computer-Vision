## Reconstruct 3D from Stereoscopic Images 


#### ABSTRACT

- In this project, we want to **reconstruct 3D Object from Stereoscopic Images that is made by laser scanner**, as the following shows.

- The Intrinsic and Extrinsic Matrix of the camera are given.

- The Fundamental Matrix between two corresponding images is also given.

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/whole.png" width="35%" height="35%">


#### METHOD

- First, we would transform the images to gray scale images, then transform it to the binary images.

- Second, use the fundamental matrix to multiply a point on the left images, the we can get the Epipoline on the right images. 

- Check the points on the Epipoline, if the pixel value is larger than zero (i.e: white points), then we get the corresponding point. The pipeline is shown below. 

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/Fundamental_Trans.png" width="50%" height="50%">

- With the **projection matrix** and the **corresponding datasets**, we can use the **3D Estimation Direct Trianglation Method** mentioned in *Multiple View Geometry in Computer Vision, by Richard Hartley* to calculate their 3D points, then store them as a .xyz file.

#### Results:

- The 3D point is shown below.
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/Reconstruct.png" width="55%" height="55%">




