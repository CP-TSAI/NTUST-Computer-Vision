## Using Homography Translation to Obtain a Better View Images 

#### ABSTRACT
- In this project, we want to use the **Homography Translation** to perform mapping between planes.

- Two images are given, as the following shows. A man is standing in fornt of the camera, blocked the partial view of the blackboard. 

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/1.JPG" width="45%" height="45%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/2.JPG" width="45%" height="45%"> 

- What we need to do is to calculate **homography mapping matrix between two images**, and get the image information for the blocked region from another image, then convert it into a front-view image.

#### Introduction of Homography

- The following shows the transformation between two rectangles.

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/homography.png" width="45%" height="45%"> 

- To compute the Homography Matrix H, we can first pick 4 corresponding image points. 

- Please manually pickup at least 4 corresponding coordinates on both images by using any Image Viewer Tool.

- Store these correspondences, then compute their homography matrix. (Hint: all points on this projection-screen are co-planar.)

- Please manually define the pixel-region of the obstacle, as a mask. Then draw the regions by the pixels from other view according to homography transformation. 

- Finally convert it into front view image. 

## Results:
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/隨班附讀-蔡金博.jpg" width="50%" height="50%"> 

