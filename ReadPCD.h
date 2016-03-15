#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/io/pcd_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

#ifndef FLOORPLAN_READPCD_H
#define FLOORPLAN_READPCD_H

using namespace std;
using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

class ReadPCD {
private:
    string pcdFile;

public:
    ReadPCD(string fileName);

    PointCloud<pcl::PointXYZ>::Ptr read();
};


#endif //FLOORPLAN_READPCD_H
