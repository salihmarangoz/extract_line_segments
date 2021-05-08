#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <laser_geometry/laser_geometry.h>
#include <visualization_msgs/Marker.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/assign.hpp>

ros::Publisher marker_pub;
ros::Subscriber laser_sub;

double douglas_pecker_distance;
double neighbor_distance;
int min_cluster_size;

typedef boost::geometry::model::d2::point_xy<double> xy;
laser_geometry::LaserProjection lp;


void laser_cb(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    // Create marker for rviz
    visualization_msgs::Marker line_segments;
    line_segments.header.frame_id = msg->header.frame_id;
    line_segments.header.stamp = msg->header.stamp;
    line_segments.ns = "line_segments";
    line_segments.action = visualization_msgs::Marker::ADD;
    line_segments.type = visualization_msgs::Marker::LINE_LIST;
    line_segments.pose.orientation.w = 1.0;
    line_segments.id = 42;
    line_segments.scale.x = 0.1;
    line_segments.color.r = 1.0;
    line_segments.color.a = 1.0;


    // Convert laser data from polar to cartesian coordinate system
    sensor_msgs::PointCloud cloud;
    lp.projectLaser(*msg, cloud);


    // Cluster the point cloud
    boost::geometry::model::linestring<xy> cluster;
    for (int i=0; i<cloud.points.size(); i++)
    {
        boost::geometry::append(cluster, xy(cloud.points[i].x, cloud.points[i].y));
        bool is_cluster_ready = false;

        // If this is the last point, don't check the next one and complete the cluster
        if (i == cloud.points.size())
        {
            is_cluster_ready = true;
        }
        else
        {
            // Find if the point is in the cluster using euclidian distance
            double x1, y1, x2, y2;
            x1 = cloud.points[i].x;
            y1 = cloud.points[i].y;
            x2 = cloud.points[i+1].x;
            y2 = cloud.points[i+1].y;
            is_cluster_ready = ( pow(x1-x2, 2)+pow(y1-y2, 2) > pow(neighbor_distance, 2) );
        }

        if (is_cluster_ready)
        {
            if (cluster.size() >= min_cluster_size)
            {
                // simplify process
                boost::geometry::model::linestring<xy> simplified;
                boost::geometry::simplify(cluster, simplified, douglas_pecker_distance); // Using Douglas-Peucker algorithm

                // Parse results from "simplified" for visualization purposes
                for (int j=0; j<simplified.size()-1; j++)
                {
                    geometry_msgs::Point p1, p2;
                    p1.x = simplified[j].x();
                    p1.y = simplified[j].y();
                    p2.x = simplified[j+1].x();
                    p2.y = simplified[j+1].y();

                    line_segments.points.push_back(p1);
                    line_segments.points.push_back(p2);
                }
                cluster.clear();
            }
            else
            {
                cluster.clear();
            }
        }
    }

    marker_pub.publish(line_segments);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "extract_line_segments_node");
    ros::NodeHandle nh;
    ros::NodeHandle priv_nh("~");

    priv_nh.param("douglas_pecker_distance", douglas_pecker_distance, 0.1);
    priv_nh.param("neighbor_distance", neighbor_distance, 0.5);
    priv_nh.param("min_cluster_size", min_cluster_size, 5);

    marker_pub = nh.advertise<visualization_msgs::Marker>("line_segments", 2);
    laser_sub = nh.subscribe("scan", 2, laser_cb);

    ros::spin();
    return 0;
}