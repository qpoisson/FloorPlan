#include <iostream>

#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

#ifndef FLOORPLAN_VIEW_H
#define FLOORPLAN_VIEW_H


class View {
public:

    View() {
        show();
    }

    boost::shared_ptr<pcl::visualization::PCLVisualizer> loadFromFile() {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::io::loadPCDFile("file.pcd", *cloud);
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
        viewer->setBackgroundColor(0, 0, 0);
        viewer->addPointCloud<pcl::PointXYZ>(cloud, "loaded cloud");
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
        viewer->addCoordinateSystem(1.0);
        viewer->initCameraParameters();
        return (viewer);
    }

// --------------
// -----Main-----
// --------------
    int
    show() {
        // ------------------------------------
        // -----Create example point cloud-----
        // ------------------------------------
        pcl::PointCloud<pcl::PointXYZ>::Ptr basic_cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_from_pcd(new pcl::PointCloud<pcl::PointXYZ>);
        std::cout << "Genarating example point clouds.\n\n";
        // We're going to make an ellipse extruded along the z-axis. The colour for
        // the XYZRGB cloud will gradually go from red to green to blue.
        uint8_t r(255), g(15), b(15);
        for (float z(-1.0); z <= 1.0; z += 0.05) {
            for (float angle(0.0); angle <= 360.0; angle += 5.0) {
                pcl::PointXYZ basic_point;
                basic_point.x = 0.5 * cosf(pcl::deg2rad(angle));
                basic_point.y = sinf(pcl::deg2rad(angle));
                basic_point.z = z;
                basic_cloud_ptr->points.push_back(basic_point);

                pcl::PointXYZRGB point;
                point.x = basic_point.x;
                point.y = basic_point.y;
                point.z = basic_point.z;
                uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
                                static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
                point.rgb = *reinterpret_cast<float *>(&rgb);
                point_cloud_ptr->points.push_back(point);
            }
            if (z < 0.0) {
                r -= 12;
                g += 12;
            }
            else {
                g -= 12;
                b += 12;
            }
        }
        basic_cloud_ptr->width = (int) basic_cloud_ptr->points.size();
        basic_cloud_ptr->height = 1;
        point_cloud_ptr->width = (int) point_cloud_ptr->points.size();
        point_cloud_ptr->height = 1;

        // ----------------------------------------------------------------
        // -----Calculate surface normals with a search radius of 0.05-----
        // ----------------------------------------------------------------
        pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> ne;
        ne.setInputCloud(point_cloud_ptr);
        pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>());
        ne.setSearchMethod(tree);
        pcl::PointCloud<pcl::Normal>::Ptr cloud_normals1(new pcl::PointCloud<pcl::Normal>);
        ne.setRadiusSearch(0.05);
        ne.compute(*cloud_normals1);

        // ---------------------------------------------------------------
        // -----Calculate surface normals with a search radius of 0.1-----
        // ---------------------------------------------------------------
        pcl::PointCloud<pcl::Normal>::Ptr cloud_normals2(new pcl::PointCloud<pcl::Normal>);
        ne.setRadiusSearch(0.1);
        ne.compute(*cloud_normals2);

        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

        viewer = loadFromFile();


        //--------------------
        // -----Main loop-----
        //--------------------
        while (!viewer->wasStopped()) {
            viewer->spinOnce(100);
            boost::this_thread::sleep(boost::posix_time::microseconds(100000));
        }
    };
};


#endif //FLOORPLAN_VIEW_H
