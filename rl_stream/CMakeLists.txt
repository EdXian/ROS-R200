cmake_minimum_required(VERSION 2.8.3)
project(rl_stream)

 add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  realsense_camera


  #cv_bridge

)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

catkin_package(
 # INCLUDE_DIRS include

#  LIBRARIES rl_cv
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
# include
 ${OpenCV_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/rl_cv.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide

add_executable(rl_stream src/rl_stream.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against


target_link_libraries(rl_stream
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
  ${OPENGL_gl_LIBRARY}
  glfw
)


