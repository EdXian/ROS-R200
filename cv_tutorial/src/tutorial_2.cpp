#include <ros/ros.h>
#include "librealsense/rs.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/text/ocr.hpp"
using namespace std;
using namespace cv;
using namespace rs;

cv::Mat rgb_erode;
cv::Mat rgb_dilate;


int main()
{
  rs::context ctx;
  rs::device& camera=*ctx.get_device(0);
  intrinsics color_intrin;

  camera.enable_stream(rs::stream::color,320,240,rs::format::rgb8,60);
  cv::namedWindow("rgb_color",cv::WINDOW_AUTOSIZE);
  camera.start();

  Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));


  while(true)
  {
    if(camera.is_streaming())
    {
       camera.wait_for_frames();
    }
    color_intrin =camera.get_stream_intrinsics(rs::stream::color);
    cv::Mat color(color_intrin.height,color_intrin.width,CV_8UC3,(uchar*)camera.get_frame_data(rs::stream::color));
    cv::cvtColor(color,color,cv::COLOR_BGR2RGB);

    cv::imshow("rgb_color",color);
    cv::erode(color,rgb_erode,element);
    cv::imshow("erode",rgb_erode);
    cv::dilate(color,rgb_dilate,element);
    cv::imshow("dilate",rgb_dilate);
    std::cout<<"acess to an element in Mat :"<<color.at<short>(160,120)<<std::endl;

     cvWaitKey(1);
  }

}
