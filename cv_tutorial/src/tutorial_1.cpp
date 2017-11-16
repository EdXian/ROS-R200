#include "ros/ros.h"
#include <librealsense/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define RGB_COLOR true
#define DEPTH  true

using namespace std;
using namespace rs;
using namespace std;


int main()
{

  rs::context ctx;
  rs::device& rs_camera = *ctx.get_device(0);
  intrinsics depth_intrin;
  intrinsics color_intrin;

  //enable data streaming
  //see realsense format data table
  if(RGB_COLOR)
  {
    rs_camera.enable_stream(rs::stream::color,320,240,rs::format::rgb8,60);
    cv::namedWindow("tutorial_1_color",cv::WINDOW_AUTOSIZE);

  }

  if(DEPTH)
  {
    rs_camera.enable_stream(rs::stream::depth,320,240,rs::format::z16,60);
    cv::namedWindow("tutorial_1_depth",cv::WINDOW_AUTOSIZE);

  }


  rs_camera.start();
  //set cv window


  while(true)
  {

    if(rs_camera.is_streaming())
    {
      rs_camera.wait_for_frames();
    }

    if(RGB_COLOR)
    {
      color_intrin = rs_camera.get_stream_intrinsics(rs::stream::color);
      cv::Mat color( color_intrin.height,
                                  color_intrin.width,
                                  CV_8UC3,
                                  (uchar *)rs_camera.get_frame_data( rs::stream::color ) );
      cv::cvtColor( color, color, cv::COLOR_BGR2RGB );
      cv::imshow("tutorial_1_color",color);
    }
    cvWaitKey(1);
    if(DEPTH)
    {
      depth_intrin = rs_camera.get_stream_intrinsics(rs::stream::depth);
      cv::Mat depth16(depth_intrin.height,depth_intrin.width,CV_16U,(uchar *)rs_camera.get_frame_data(rs::stream::depth));
      cv::Mat depth8u = depth16;
      depth8u.convertTo(depth8u,CV_8UC1,255.0/1000.0);
      cv::imshow("tutorial_1_depth",depth8u);
    }

    cvWaitKey(1);

  }

}
