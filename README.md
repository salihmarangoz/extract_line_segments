# LaserScan Line Segment Extraction (ROS)

Line segment extraction from ROS LaserScan using [Douglas-Peucker](http://en.wikipedia.org/wiki/Ramer–Douglas–Peucker_algorithm) algorithm.

- Used [simplify](https://www.boost.org/doc/libs/1_68_0/libs/geometry/doc/html/geometry/reference/algorithms/simplify/simplify_3.html) from Boost library for the Douglas-Peucker algorithm.
- Used [laser_geometry](http://wiki.ros.org/laser_geometry) for converting LaserScan to PointCloud.
- Used [visualization_msgs/Marker](http://wiki.ros.org/rviz/DisplayTypes/Marker) for visualization.

Youtube Link: https://www.youtube.com/watch?v=EF6ovIfM_Ug

[![](https://img.youtube.com/vi/EF6ovIfM_Ug/0.jpg)](https://www.youtube.com/watch?v=EF6ovIfM_Ug)


## Running

```bash
$ roslaunch extract_line_segments start.launch
```

## Parameters

`~douglas_pecker_distance` (`double`, default: 0.1)

​	Distance parameter in the Douglas-Peucker algorithm. Too high values lead to less but inaccurate line segments, too low values lead to many and small line segments.

`~neighbor_distance` (`double`, default: 0.5)

​	Maximum distance constraint in meters to add points into the same cluster.

`~min_cluster_size` (`int`, default: 5)

​	The minimum number of points required to allow for the cluster to be processed.

