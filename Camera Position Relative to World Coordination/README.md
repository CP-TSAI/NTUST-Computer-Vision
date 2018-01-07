## Determine Camera Position Relative to World Coordinate 


#### ABSTRACT
- In this project, we are going to **calculate the camera position from ONE given image and a known structure**.

- During the process, we need to calculate the **Intrinsic and Extrinsic matrix of the camera by ourselves**.

- The image is shown as followings: There is a cube with 50 cm in length, width and height. The world coordinate is on a corner and its x, y and z axes are on the edges.

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/Calibration.png" width="40%" height="40%"> 


#### METHOD

- To get the camera position relative to world coordination, we need to use the **camera model** as shown below.

```math # camera model
x = PX,  P = k[R|t]
```

- *x* means the 2D point on images, and *X* means the 3D point in spaces. With **projection matrix** *P*, we can project the 3D point on the images. 

- The projection matrix P is built by both the **Intrinsic Matrix K** and **Extrinsic Matrix [R|t]**.

- Using the **Camera Calibration Method** mentioned in *Multi View Geometry, by Richard Hartley* we can first calculate 3 different **Homography Matrix** from a unit rectangle to 3 different rectangles A, B, C as shown below. 

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/CalibrationIMG 修正v4.bmp" width="41%" height="41%">

- With the 3 Homography Matrix, we can then calculate the **OMEGA parameter** by the equation below. 

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/h_function.png" width="41%" height="41%">

- The relation between OMEGA and Intrinsic Matrix K is described below. 

```math # camera model
w = (K*K^{T})^{-1}
```

[A flexible new technique for camera calibration](http://ieeexplore.ieee.org/document/888718/)

- Please manually select 3 squares, as well as known shapes, (please show me in another figure), then determine their homography from a unit square. Based on Zhang’s method (or IAC), please 
calculate the intrinsic parameter of the camera.

- Finally, try to find out the camera position relative to World coordinate. 

- there is NO need to read this image or detect features in your program. Using an image tool (ex. photoshop) for picking out the pixel coordinate is recommended. 

## Results:
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/camera_relative.png" width="40%" height="40%"> 

- The coordination of camera is (74.8452, 71.3981, 52.4693)

