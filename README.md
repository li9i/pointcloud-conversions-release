### `pointcloud_conversions`: ROS 2 point-cloud conversion & reframing for PLY / XYZ / PointCloud2

<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT"/></a>
  <a href="https://index.ros.org/p/pointcloud_conversions/#humble"><img src="https://img.shields.io/ros/v/humble/pointcloud_conversions" alt="ROS 2 Humble version"/></a>
</p>

A single ROS 2 (Humble) package bundling three utilities:

- **`pointcloud_to_ply`** — Capture a point cloud from a topic and store it in `.ply` or `.obj` format
- **`ply_to_xyz_transframer`** — Transform a `.ply` file expressed in one frame of reference to a `.xyz` file expressed in another
- **`xyz_to_ply_transframer`** — Transform a `.xyz` file expressed in one frame of reference to a `.ply` file expressed in another

## Build

```bash
cd ~/ros2_ws/src
git clone -b humble-devel https://github.com/li9i/ply-utils.git
cd ~/ros2_ws
rosdep install --from-paths src -y --ignore-src
colcon build --packages-select pointcloud_conversions
```

`pointcloud_to_ply` additionally requires [Open3D](https://www.open3d.org/), which has no rosdep key:

```bash
pip3 install open3d
```

## Run

```bash
ros2 launch pointcloud_conversions pointcloud_to_ply.launch.xml
ros2 launch pointcloud_conversions ply_to_xyz_transframer.launch.xml
ros2 launch pointcloud_conversions xyz_to_ply_transframer.launch.xml
```
