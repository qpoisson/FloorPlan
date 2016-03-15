#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/surface/concave_hull.h>
#include "ReadPCD.h"

#ifndef FLOORPLAN_PLANRECOGNITION_H
#define FLOORPLAN_PLANRECOGNITION_H


class PlanRecognition {
private:
    std::string filePCD;
public:
    PlanRecognition(std:: string pcd);

    int takePlan();

    virtual ~PlanRecognition() { }

};


#endif //FLOORPLAN_PLANRECOGNITION_H
