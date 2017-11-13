#include "ros/ros.h"
#include "std_msgs/String.h"

#include "realsense_camera/r200_nodelet.h"
#include "realsense_camera/r200_paramsConfig.h"
#include "librealsense/rs.hpp"
#include <opencv2/opencv.hpp>
#include "GLFW/glfw3.h"

using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
  rs::context ctx;
  rs::device *dev = ctx.get_device(0);
  dev->enable_stream(rs::stream::color,1920,1080,rs::format::bgr8,30);

  dev->start();

  for(int i=0;i<30;i++)
  {
    dev->wait_for_frames();
  }

    Mat color(Size(1920,1080),CV_8UC3,(void*)dev->get_frame_data(rs::stream::color),Mat::AUTO_STEP);
    namedWindow("rl_test",WINDOW_GUI_EXPANDED);
    imshow("test",color);



  waitKey(0);
  return 0;
}
