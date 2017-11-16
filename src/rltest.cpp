#include "ros/ros.h"
#include "std_msgs/String.h"

#include "realsense_camera/r200_nodelet.h"
#include "realsense_camera/r200_paramsConfig.h"
#include "librealsense/rs.hpp"
#include "librealsense/rscore.hpp"
#include "librealsense/rs.h"
#include "librealsense/rsutil.h"

#include <opencv2/opencv.hpp>
#include "GLFW/glfw3.h"


using namespace std;
using namespace cv;
using namespace rs;

int main(int argc, char **argv)
{
  rs::context ctx;
  rs::device *dev = ctx.get_device(0);

  dev->enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 60);
  dev->start();
  for(int i=0;i<30;i++)
  {
    dev->wait_for_frames();
  }

  glfwInit();
  GLFWwindow * win = glfwCreateWindow(640, 480, "depth raw", nullptr, nullptr);
  glfwMakeContextCurrent(win);

   while(!glfwWindowShouldClose(win))
   {

     glfwPollEvents();
     dev->wait_for_frames();
     glClear(GL_COLOR_BUFFER_BIT);


     glPixelTransferf(GL_RED_SCALE, 0xFFFF * dev->get_depth_scale() / 2.0f);
     glDrawPixels(640, 480, GL_RED, GL_UNSIGNED_SHORT, dev->get_frame_data(rs::stream::depth));
     glPixelTransferf(GL_RED_SCALE, 1.0f);


     glfwSwapBuffers(win);
   }

  return 0;
}
