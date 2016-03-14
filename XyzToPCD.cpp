#include "XyzToPCD.h"
#include <iostream>

using namespace std;

XyzToPCD::XyzToPCD(string xyz, string pcd)  : fileName_xyz(xyz), fileName_pcd(pcd) { }

int XyzToPCD::readPCD() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile<pcl::PointXYZ> ("points.xyz", *cloud) == -1) //* load the file
    {
        PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
        return (-1);
    }
    std::cout << "Loaded "
    << cloud->width * cloud->height
    << " data points from test_pcd.pcd with the following fields: "
    << std::endl;
    for (size_t i = 0; i < cloud->points.size (); ++i)
        std::cout << "    " << cloud->points[i].x
        << " "    << cloud->points[i].y
        << " "    << cloud->points[i].z << std::endl;

    return (0);
}

bool XyzToPCD::loadCloud(const string &filename, PointCloud<PointXYZ> &cloud) {
    ifstream fs;
    fs.open (filename.c_str (), ios::binary);
    if (!fs.is_open () || fs.fail ())
    {
        PCL_ERROR ("Could not open file '%s'! Error : %s\n", filename.c_str (), strerror (errno));
        fs.close ();
        return (false);
    }

    string line;
    vector<string> st;

    while (!fs.eof ())
    {
        getline (fs, line);
        // Ignore empty lines
        if (line == "")
            continue;

        // Tokenize the line
        boost::trim (line);
        boost::split (st, line, boost::is_any_of ("\t\r "), boost::token_compress_on);

        if (st.size () != 3)
            continue;

        cloud.push_back (PointXYZ (float (atof (st[0].c_str ())), float (atof (st[1].c_str ())), float (atof (st[2].c_str ()))));
    }
    fs.close ();

    cloud.width = uint32_t (cloud.size ()); cloud.height = 1; cloud.is_dense = true;
    return (true);
}

int XyzToPCD::convert() {
    if (!loadCloud (fileName_xyz, cloud))
        return (-1);
    cout << "file " << fileName_xyz << " was loaded" << endl;

    // Convert to PCD and save
    PCDWriter w;
    w.writeBinaryCompressed (fileName_pcd, cloud);
    cout << "file " << fileName_pcd << " was saved" << endl;
    return 0;
}