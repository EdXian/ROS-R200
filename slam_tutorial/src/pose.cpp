#include <ros/ros.h>
#include "librealsense/rs.hpp"
#include "librealsense/slam/slam.h"
#include "librealsense/slam/slam_core.h"
#include "librealsense/slam/slam_utils.h"
#include "rs_sdk.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <thread>

#include "eigen3/Eigen/Dense"
using namespace std;
using namespace rs::core;
using namespace rs::slam;

class slam_event_handler : public rs::core::video_module_interface::processing_event_handler
{
    shared_ptr<occupancy_map> occ_map;
public:
    void module_output_ready(rs::core::video_module_interface * sender, correlated_sample_set * sample)
    {
        // Get a handle to the slam module
        auto slam = dynamic_cast<rs::slam::slam*>(sender);

        // Create an occupancy map container if we don't already have one.
        if (!occ_map)
        {
            // This will only happen on the first execution of this callback.
            occ_map = slam->create_occupancy_map(50 * 50);
        }

        // Get the camera pose
        PoseMatrix4f pose;
        slam->get_camera_pose(pose);

        // Get the tracking accuracy as a string

        // Get the number of occupancy map tiles that were updated
        slam->get_occupancy_map_update(occ_map);
        int count_updated_tiles = occ_map->get_tile_count(); // This will only be > 0 when the tracking accuracy is > low.

        // Print the camera pose and number of updated occupancy map tiles to the console

        // Get the occupany map (with trajectory) as an image and render it in the map window

    }
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "pose");
  ros::NodeHandle nh;

  rs::context ctx;
  rs::device &camera = *ctx.get_device(0);

  video_module_interface::supported_module_config supported_slam_config;

  rs::slam::PoseMatrix4f pose_matrix;

  camera.set_option(rs::option::fisheye_strobe,1);
  camera.set_option(rs::option::fisheye_external_trigger,1);

  auto &fisheye_stream_config = supported_slam_config[stream_type::fisheye];
  camera.enable_stream(rs::stream::fisheye, fisheye_stream_config.size.width, fisheye_stream_config.size.height, rs::format::raw8, fisheye_stream_config.frame_rate);

  auto &depth_stream_config = supported_slam_config[stream_type::depth];
  camera.enable_stream(rs::stream::depth, depth_stream_config.size.width, depth_stream_config.size.height, rs::format::z16, depth_stream_config.frame_rate);


  //std::unique_ptr<slam> slam(new rs::slam::slam());






}

