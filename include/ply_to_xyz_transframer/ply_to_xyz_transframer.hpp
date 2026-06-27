// Copyright 2026 Alexandros Filotheou
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "geometry_msgs/msg/point_stamped.hpp"
#include "pcl/io/ply_io.h"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "yaml-cpp/yaml.h"

class Transframer
{
public:
  explicit Transframer(std::shared_ptr<rclcpp::Node> node);
  void run();

private:
  std::shared_ptr<rclcpp::Node> node_;
  std::string input_directory_;
  std::string output_directory_;
  std::string input_file_prefix_;
  std::string input_file_pattern_;
  std::string output_name_pattern_;
  std::string source_frame_;
  std::string target_frame_;
  std::string input_file_id_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  std::vector<std::string> find_matching_files() const;
  std::string generate_output_filename(const std::string & input_path) const;
  void load_params(std::shared_ptr<rclcpp::Node> node);
  pcl::PointCloud<pcl::PointXYZ>::Ptr load_ply(const std::string & file);
  pcl::PointCloud<pcl::PointXYZ>::Ptr transform_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
  void save_xyz(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const std::string & file);
  std::string transform_filename(const std::string & input_filename) const;
};
