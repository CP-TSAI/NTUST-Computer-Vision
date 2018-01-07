## Using Homography Translation to Obtain a Better View Images 

#### ABSTRACT
- In this project, we want to use the **Homography Translation** to perform mapping between planes.

- Two images are given, as the following shows. A man is standing in fornt of the camera, blocked the partial view of the blackboard. 

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/1.JPG" width="45%" height="45%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/2.JPG" width="45%" height="45%"> 

- What we need to do is to calculate **homography mapping matrix between two images**, and get the image information for the blocked region from another image, then convert it into a front-view image.

#### Introduction of Homography

- In this section, we would talk the way to obtain the Homography Matrix. 

- If we have **at least 4 corresponding points**, a homography can dominate the transformation between two images, so **we don't have to determine the Intrinsic and Extrinsic matrix for the images**. 

- The following shows the transformation between two rectangles.

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/homography.png" width="45%" height="45%"> 

- To compute the Homography Matrix H, we can first pick **4 corresponding image points**: (x1, y1), (x1', y1'); (x2, y2), (x2', y2'); (x3, y3), (x3', y3'); (x4, y4), (x4', y4')

- We can get a 9x2 matrix for each data set:

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/pi.png" width="45%" height="45%"> 

- With 4 data sets, we can stack them into a matrix P to compute **PH = 0** write a 8x9 matrix:

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/PH.png" width="45%" height="45%"> 

- While adding an extra constraint **|H| = 1** to avoid the obvious solution of H being all zeros. It is easy to use **SVD = (U)(S)(V^t) and select the last singular vector of V as the solution to H**.

- Once we have homography matrix H, you can compute the projected coordinates of any point p(x,y) such as:

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/lambda.png" width="25%" height="25%"> 


#### Method:

- To remove the obstacle (people) out of the image, we would first calculate the Homography Matrix between the two images. 

- Secondly, we would fill the region being blocked by the pixel information from another image. 

- Finally, we would project the cleared image to a front view images. 

#### Results:

- The pipeline of the project is shown as followings. 

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/serial.png" width="65%" height="65%"> 

