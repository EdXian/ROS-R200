#include "ros/ros.h"
#include "std_msgs/String.h"

#include "realsense_camera/r200_nodelet.h"
#include "realsense_camera/r200_paramsConfig.h"
#include "librealsense/rs.hpp"
#include <opencv2/opencv.hpp>
#include "GLFW/glfw3.h"

using namespace std;
using namespace cv;

int main() //try
{
    // Create a context object. This object owns the handles to all connected realsense devices.
    rs::context ctx;
    printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
    if(ctx.get_device_count() == 0) return EXIT_FAILURE;

    // This tutorial will access only a single device, but it is trivial to extend to multiple devices
    rs::device * dev = ctx.get_device(0);
    printf("\nUsing device 0, an %s\n", dev->get_name());
    printf("    Serial number: %s\n", dev->get_serial());
    printf("    Firmware version: %s\n", dev->get_firmware_version());

    // Configure all streams to run at VGA resolution at 60 frames per second
    dev->enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 60);
    dev->enable_stream(rs::stream::color, 640, 480, rs::format::rgb8, 60);
    dev->enable_stream(rs::stream::infrared, 640, 480, rs::format::y8, 60);
    try { dev->enable_stream(rs::stream::infrared2, 640, 480, rs::format::y8, 60); }
    catch(...) { printf("Device does not provide infrared2 stream.\n"); }
    dev->start();

    // Open a GLFW window to display our output
    glfwInit();
    GLFWwindow * win = glfwCreateWindow(1280, 960, "librealsense tutorial #2", nullptr, nullptr);
    glfwMakeContextCurrent(win);
    while(!glfwWindowShouldClose(win))
    {
        // Wait for new frame data
        glfwPollEvents();
        dev->wait_for_frames();

        glClear(GL_COLOR_BUFFER_BIT);
        glPixelZoom(1, -1);

        // Display depth data by linearly mapping depth between 0 and 2 meters to the red channel
        glRasterPos2f(-1, 1);
        glPixelTransferf(GL_RED_SCALE, 0xFFFF * dev->get_depth_scale() / 2.0f);
        glDrawPixels(640, 480, GL_RED, GL_UNSIGNED_SHORT, dev->get_frame_data(rs::stream::depth));
        glPixelTransferf(GL_RED_SCALE, 1.0f);

        // Display color image as RGB triples
        glRasterPos2f(0, 1);
        glDrawPixels(640, 480, GL_RGB, GL_UNSIGNED_BYTE, dev->get_frame_data(rs::stream::color));

        // Display infrared image by mapping IR intensity to visible luminance
        glRasterPos2f(-1, 0);
        glDrawPixels(640, 480, GL_LUMINANCE, GL_UNSIGNED_BYTE, dev->get_frame_data(rs::stream::infrared));

        // Display second infrared image by mapping IR intensity to visible luminance
        if(dev->is_stream_enabled(rs::stream::infrared2))
        {
            glRasterPos2f(0, 0);
            glDrawPixels(640, 480, GL_LUMINANCE, GL_UNSIGNED_BYTE, dev->get_frame_data(rs::stream::infrared2));
        }

        glfwSwapBuffers(win);
    }

    return EXIT_SUCCESS;
}

