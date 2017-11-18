#include <ros/ros.h>
#include "librealsense/rs.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

int focal_value=1;
rs::context ctx;
rs::device  *camera;
rs::intrinsics color_intrins;
cv::Mat color_rgb;


int main(int argc, char **argv)
{
  ros::init(argc, argv,"option_config");
  ros::NodeHandle nh;
  nh.param("focal_length",focal_value,250);
  camera = ctx.get_device(0);
  camera->set_option(rs::option::color_gamma,focal_value);


  camera->enable_stream(rs::stream::color,320,240,rs::format::bgr8,60);
  camera->start();

  cv::namedWindow("Coniguration",cv::WINDOW_FULLSCREEN);

  while(ros::ok())
  {
    nh.getParam("focal_length",focal_value);
    camera->set_option(rs::option::color_gain,focal_value);
    if(camera->is_streaming())
    {
      camera->wait_for_frames();
    }

    color_intrins = camera->get_stream_intrinsics(rs::stream::color);
    cv::Mat color(color_intrins.height,
                                color_intrins.width,
                                CV_8UC3,
                                (uchar *)camera->get_frame_data( rs::stream::color ) );
    cv::imshow("Coniguration",color);
   cvWaitKey(1);
  }
}



