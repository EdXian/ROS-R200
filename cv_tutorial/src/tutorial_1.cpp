#include <ros/ros.h>
#include "librealsense/rs.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std ;
using namespace rs;

int const INPUT_WIDTH = 320;
int const INPUT_HEIGHT = 240;
int const FRAMERATE =60;

char* const WINDOW_DEPTH = "Depth Image";
char* const WINDOW_RGB = "RGB Image";

rs::context rs_ctx;
rs::device& rs_camera = *rs_ctx.get_device(0);

intrinsics depth_intrin;
intrinsics color_intrin;
bool loop=true;

bool stream_init()
{
  bool success = false;
  if (rs_ctx.get_device_count()>0)
  {
   // rs_camera.enable_stream(rs::stream::color,INPUT_WIDTH,INPUT_HEIGHT,rs::format::rgb8,FRAMERATE);
    rs_camera.enable_stream(rs::stream::depth,INPUT_WIDTH,INPUT_HEIGHT,rs::format::z16,FRAMERATE);
    rs_camera.start();
    success = true;
  }

  return success;
}

static void onmouse(int event,int x , int y , int ,void* window_name)
{
  if(event==cv::EVENT_LBUTTONDOWN)
  {
    loop = false;
  }
}


void setup_windows()
{
  cv::namedWindow(WINDOW_DEPTH,0);
 // cv::namedWindow(WINDOW_RGB,0);
  cv::setMouseCallback(WINDOW_DEPTH,onmouse,WINDOW_DEPTH);
  //cv::setMouseCallback(WINDOW_RGB,onmouse,WINDOW_RGB);

}

bool show_next_frame()
{
  depth_intrin = rs_camera.get_stream_intrinsics(rs::stream::depth);
  //color_intrin = rs_camera.get_stream_intrinsics(rs::stream::color);

  cv::Mat depth16(depth_intrin.height,depth_intrin.width,CV_16U,
                  (uchar *)rs_camera.get_frame_data(rs::stream::depth));

//  cv::Mat rgb(color_intrin.height,color_intrin.width,CV_8UC3,
//               (uchar *)rs_camera.get_frame_data(rs::stream::color));

  cv::Mat depth8u=depth16;
  depth8u.convertTo(depth8u,CV_8UC1,255.0/1000);
  cv::imshow(WINDOW_DEPTH,depth8u);

  cvWaitKey(1);

//  cv::cvtColor(rgb,rgb,cv::COLOR_BGR2RGB);
//  cv::imshow(WINDOW_RGB,rgb);
  cvWaitKey();
  return true;
}

int main()try
{
  rs::log_to_console(rs::log_severity::warn);

  if(!stream_init())
  {
    std::cout << "No device be found"<<std::endl;

    rs::log_to_console(rs::log_severity::fatal);
    return EXIT_FAILURE;

  }

  setup_windows();

  while(loop)
  {
    if(rs_camera.is_streaming())
    {
      rs_camera.wait_for_frames();
    }
    show_next_frame();
  }

  rs_camera.stop();
  cv::destroyAllWindows();
  return EXIT_SUCCESS;
}
catch(const rs::error & err)
{
  std::cerr << "error return ----->"<<err.get_failed_function()<< "("
            << err.get_failed_args()<<"):\n"<<err.what()<<std::endl;
  return EXIT_FAILURE;

}
