## HW1: 3D reconstruction from silhouette method

### ABSTRACT
- There are 4 data sets (“Eagle”, “Bunny”, “Teapot”, and “Venus”), each set has 8 silhouette images.
(Take the “Eagle” for example.)

<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/pic.jpg" width="75%" height="75%"> 

<!--
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/001.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/002.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/003.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/004.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/005.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/006.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/007.bmp" width="25%" height="25%"> <img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/008.bmp" width="25%" height="25%"> 
-->

- Calculated the camera parameter (Intrinsic Parameter & Extrinsic Parameter)
- Projected test points inside the workspace, if the projected point is inside the white space, then keep it. 
- After 8 runs, the remained points can be the 3D space reconstruction.




## Results:
<img src="https://github.com/CP-TSAI/Computer-Vision/raw/master/cv_pic/recon.png" width="25%" height="25%"> 

