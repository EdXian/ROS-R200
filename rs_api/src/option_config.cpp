#include <ros/ros.h>
#include "librealsense/rs.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

int color_saturation=1;
double color_saturation_max ,color_saturation_min ,color_saturation_step,color_saturation_default;
rs::context ctx;
rs::device  *camera;
rs::intrinsics color_intrins;
cv::Mat color_rgb;


int main(int argc, char **argv)
{
  ros::init(argc, argv,"option_config");
  ros::NodeHandle nh;
  const char * get_description;
  nh.param("color_saturation",color_saturation,250);
  camera = ctx.get_device(0);


  get_description= camera->get_option_description(rs::option::color_saturation);
  camera->get_option_range(rs::option::color_saturation,color_saturation_min,color_saturation_max,color_saturation_step,color_saturation_default);

  std::cout<<"saturation_description :"<<get_description<<std::endl;
  std::cout<<"color_saturation_min : "<<color_saturation_min<<std::endl;
  std::cout<<"color_saturation_max : "<<color_saturation_max<<std::endl;
  std::cout<<"color_saturation_step : "<<color_saturation_step<<std::endl;
  std::cout<<"color_saturation_default : "<<color_saturation_default<<std::endl;

  camera->enable_stream(rs::stream::color,320,240,rs::format::bgr8,60);
  camera->start();

  cv::namedWindow("Coniguration",cv::WINDOW_FULLSCREEN);

  while(ros::ok())
  {
    nh.getParam("color_saturation",color_saturation);
    camera->set_option(rs::option::color_saturation,color_saturation);
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



