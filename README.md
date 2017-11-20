# Intel Realsense camera C++ application for ROS.

This package have been tested in ROS kinetic only and no guarantee for other ROS versions.

## Device support

Intel realsense camera family:

 * R200
 * SR300

## Pre-install & Requirements
Note that all packages should be installed in path /opt/... or the catkin tool cant find them!

 1. [ROS install](http://wiki.ros.org/kinetic/Installation/Ubuntu)

 2. [Ubuntu kernel >= 4.4](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation.md#make-ubuntu-up-to-date)
  
   ```
   sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist-upgrade
   sudo apt-get install --install-recommends linux-generic-lts-xenial xserver-xorg-core-lts-xenial xserver-xorg-lts-xenial xserver-xorg-video-all-lts-xenial xserver-xorg-input-all-lts-xenial libwayland-egl1-mesa-lts-xenial
   ```
	
   run `sudo update-grub && sudo reboot`

   In GRUB mode , Selecting the kernel version correctly.

   Check Ubuntu kernel version `uname -r` . The Kernel version should be greater than 4.4 !
	
 3. [librealsense](https://github.com/IntelRealSense/realsense_samples_ros#installation-instructions)

 ```
 sudo apt-key adv --keyserver keys.gnupg.net --recv-key D6FB2970
 sudo sh -c 'echo "deb http://realsense-alm-public.s3.amazonaws.com/apt-repo xenial main" > /etc/apt/sources.list.d/realsense-latest.list'
 sudo apt update
 sudo apt install -y librealsense-object-recognition-dev librealsense-persontracking-dev librealsense-slam-dev 
 ```
 4. [realsense-camera](http://wiki.ros.org/realsense_camera)
	
  ```
  sudo apt-get install ros-kinetic-realsense-camera
  ```	
 5. OpenCV greater than 3.2.0 version

## How to use this package?

Assume that you alredy have a catkin-workspace (`catkin_ws`) in your root directory.
```
cd ~/catkin_ws/src
git clone https://github.com/EdXian/ROS-R200.git
cd ..
catkin_make

```
```
rosrun cv_tutorial tutorial_1
```
## Reference and Cookbook
 * [OpenCV3.2 tutorial](https://docs.opencv.org/3.2.0/d9/d97/tutorial_table_of_content_features2d.html)
 * [Stream Format](https://github.com/IntelRealSense/librealsense/blob/legacy/doc/supported_video_formats.pdf)
 * [Step by Step](https://software.intel.com/en-us/articles/using-librealsense-and-opencv-to-stream-rgb-and-depth-data#_Toc462147826)
 * [Developer's Guide](https://software.intel.com/sites/products/realsense/camera/developer_guide.html)

## TODO List
 * Object-tracking in real-time.
 * SLAM (Simultaneous localiztion and mapping)

