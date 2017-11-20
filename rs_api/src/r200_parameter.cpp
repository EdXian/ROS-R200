#include <ros/ros.h>
#include "librealsense/rs.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

double option_max ,option_min ,option_step,option_default;
rs::context ctx;
rs::device  *camera;
rs::option option;
int main(int argc, char **argv)
{
  ros::init(argc, argv, "r200_parameter");
  ros::NodeHandle nh;
  camera = ctx.get_device(0);

  option = rs::option::color_saturation;
  camera->get_option_range(option,option_min,option_max,option_step,option_default);
  std::cout <<"******"<< option<<"******"<<std::endl;
  std::cout<<"min : "<<option_min<<std::endl;
  std::cout<<"max : "<<option_max<<std::endl;
  std::cout<<"step : "<<option_step<<std::endl;
  std::cout<<"default : "<<option_default<<std::endl;
  std::cout<<"-------------------------------" <<std::endl;

  option =rs::option::color_brightness;
  camera->get_option_range(option,option_min,option_max,option_step,option_default);
  std::cout <<"******"<< option<<"******"<<std::endl;
  std::cout<<"min : "<<option_min<<std::endl;
  std::cout<<"max : "<<option_max<<std::endl;
  std::cout<<"step : "<<option_step<<std::endl;
  std::cout<<"default : "<<option_default<<std::endl;
  std::cout<<"-------------------------------" <<std::endl;

  option =rs::option::color_contrast;
  camera->get_option_range(option,option_min,option_max,option_step,option_default);
  std::cout <<"******"<< option<<"******"<<std::endl;
  std::cout<<"min : "<<option_min<<std::endl;
  std::cout<<"max : "<<option_max<<std::endl;
  std::cout<<"step : "<<option_step<<std::endl;
  std::cout<<"default : "<<option_default<<std::endl;
  std::cout<<"-------------------------------" <<std::endl;

  option =rs::option::color_enable_auto_exposure;
  camera->get_option_range(option,option_min,option_max,option_step,option_default);
  std::cout <<"******"<< option<<"******"<<std::endl;
  std::cout<<"min : "<<option_min<<std::endl;
  std::cout<<"max : "<<option_max<<std::endl;
  std::cout<<"step : "<<option_step<<std::endl;
  std::cout<<"default : "<<option_default<<std::endl;
  std::cout<<"-------------------------------" <<std::endl;


  option =rs::option::r200_depth_units;
  camera->get_option_range(option,option_min,option_max,option_step,option_default);
  std::cout <<"******"<< option<<"******"<<std::endl;
  std::cout<<"min : "<<option_min<<std::endl;
  std::cout<<"max : "<<option_max<<std::endl;
  std::cout<<"step : "<<option_step<<std::endl;
  std::cout<<"default : "<<option_default<<std::endl;
  std::cout<<"-------------------------------" <<std::endl;

  option =rs::option::r200_emitter_enabled;
  camera->get_option_range(option,option_min,option_max,option_step,option_default);
  std::cout <<"******"<< option<<"******"<<std::endl;
  std::cout<<"min : "<<option_min<<std::endl;
  std::cout<<"max : "<<option_max<<std::endl;
  std::cout<<"step : "<<option_step<<std::endl;
  std::cout<<"default : "<<option_default<<std::endl;
  std::cout<<"-------------------------------" <<std::endl;






}
