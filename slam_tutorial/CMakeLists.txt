cmake_minimum_required(VERSION 2.8.3)
project(slam_tutorial)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -fmessage-length=0 --std=c++11 -pthread -fPIC -std=c++0x -fexceptions -frtti -ffunction-sections -fdata-sections")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    pcl_conversions
    pcl_ros
    sensor_msgs
    #realsense_camera
   # librealsense
)
find_package(librealsense REQUIRED)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES slam_tutorial
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)
set( PROJECT_LINK_LIBS
    realsense_image
    realsense_lrs_image
    realsense_playback
    realsense
    pthread
    realsense_slam
    SP_Core
    tracker

)

include_directories(

  /usr/lib/libSP_Core.so
  /usr/include
  /usr/include/librealsense
  /usr/include/librealsense/slam
  ${CONSOLE_DISPLAY_DIR}
  ${COMMON_UTILS_DIR}
  ${catkin_INCLUDE_DIRS}
)
link_directories(
    /usr/lib
    /usr/local/lib)

 add_executable(pose src/pose.cpp)

 target_link_libraries(pose
   ${catkin_LIBRARIES}
    ${GTEST_LIBRARIES}
    realsense_image
    realsense_lrs_image
    realsense_playback
    realsense
    pthread
    realsense_slam
    SP_Core
    tracker
  ${PROJECT_LINK_LIBS}
  ${GTEST_LIBRARIES}
 )

