# LaserScan Line Segment Extraction (ROS)

Line segment extraction using [Douglas-Peucker](http://en.wikipedia.org/wiki/Ramer–Douglas–Peucker_algorithm) algorithm.

- Used [simplify](https://www.boost.org/doc/libs/1_68_0/libs/geometry/doc/html/geometry/reference/algorithms/simplify/simplify_3.html) from Boost library for the Douglas-Peucker algorithm.
- Used [laser_geometry](http://wiki.ros.org/laser_geometry) for converting LaserScan to PointCloud.
- Used [visualization_msgs/Marker](http://wiki.ros.org/rviz/DisplayTypes/Marker) for visualization.

Youtube Link: https://www.youtube.com/watch?v=EF6ovIfM_Ug

[![](https://img.youtube.com/vi/EF6ovIfM_Ug/0.jpg)](https://www.youtube.com/watch?v=EF6ovIfM_Ug)



## Running

```bash
$ roslaunch extract_line_segments start.launch
```

