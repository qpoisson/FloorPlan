#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/io/pcd_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

#ifndef FLOORPLAN_XYZTOPCD_H
#define FLOORPLAN_XYZTOPCD_H

using namespace std;
using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

class XyzToPCD {
private:
    string fileName_xyz;
    string fileName_pcd;
    PointCloud<PointXYZ> cloud;

public:
    XyzToPCD(string xyz, string pcd);

    int
    readPCD ();

    bool
    loadCloud (const string &filename, PointCloud<PointXYZ> &cloud);

    int convert();
};

#endif //FLOORPLAN_XYZTOPCD_H


