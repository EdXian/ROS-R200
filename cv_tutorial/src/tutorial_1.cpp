#include "ros/ros.h"
#include <librealsense/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace rs;
using namespace std;


int main()
{

  rs::context ctx;
  rs::device& rs_camera = *ctx.get_device(0);
  intrinsics depth_intrin;


  //enable data streaming
  //see realsense format data table
  rs_camera.enable_stream(rs::stream::depth,320,240,rs::format::z16,60);
  rs_camera.start();
  //set cv window
  cv::namedWindow("tutorial_1",cv::WINDOW_AUTOSIZE);


  while(true)
  {
    if(rs_camera.is_streaming())
    {
      rs_camera.wait_for_frames();
    }
    depth_intrin = rs_camera.get_stream_intrinsics(rs::stream::depth);

    cv::Mat depth16(depth_intrin.height,depth_intrin.width,CV_16U,(uchar *)rs_camera.get_frame_data(rs::stream::depth));
    cv::Mat depth8u = depth16;
    depth8u.convertTo(depth8u,CV_8UC1,255.0/1000.0);
    cv::imshow("tutorial_1",depth8u);
    cvWaitKey(1);

  }

}
