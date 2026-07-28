cmake_minimum_required(VERSION 3.8)
project(pointcloud_conversions)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(yaml_cpp_vendor REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(PCL REQUIRED COMPONENTS common io)

include_directories(include)
include_directories(${PCL_INCLUDE_DIRS})

set(transframer_deps
  ${rclcpp_TARGETS}
  ${tf2_TARGETS}
  ${tf2_ros_TARGETS}
  ${tf2_geometry_msgs_TARGETS}
  ${sensor_msgs_TARGETS}
  ${std_srvs_TARGETS}
  yaml-cpp::yaml-cpp
  ${PCL_LIBRARIES}
)

# --- ply_to_xyz_transframer (C++) ---
add_library(ply_to_xyz_transframer_lib
  src/ply_to_xyz_transframer/ply_to_xyz_transframer_interface.cpp
  src/ply_to_xyz_transframer/ply_to_xyz_transframer.cpp
)
target_link_libraries(ply_to_xyz_transframer_lib ${transframer_deps})

add_executable(ply_to_xyz_transframer_interface_node
  src/ply_to_xyz_transframer/ply_to_xyz_transframer_interface_node.cpp)
target_link_libraries(ply_to_xyz_transframer_interface_node
  ply_to_xyz_transframer_lib
  ${transframer_deps}
)

# --- xyz_to_ply_transframer (C++) ---
add_library(xyz_to_ply_transframer_lib
  src/xyz_to_ply_transframer/xyz_to_ply_transframer_interface.cpp
  src/xyz_to_ply_transframer/xyz_to_ply_transframer.cpp
)
target_link_libraries(xyz_to_ply_transframer_lib ${transframer_deps})

add_executable(xyz_to_ply_transframer_interface_node
  src/xyz_to_ply_transframer/xyz_to_ply_transframer_interface_node.cpp)
target_link_libraries(xyz_to_ply_transframer_interface_node
  xyz_to_ply_transframer_lib
  ${transframer_deps}
)

# --- pointcloud_to_ply (Python) ---
ament_python_install_package(pointcloud_to_ply)
install(PROGRAMS
  pointcloud_to_ply/pointcloud_to_ply_node.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME pointcloud_to_ply_node
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  ply_to_xyz_transframer_lib
  ply_to_xyz_transframer_interface_node
  xyz_to_ply_transframer_lib
  xyz_to_ply_transframer_interface_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include/
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
