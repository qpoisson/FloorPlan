#include "XyzToPCD.h"
#include "PlanRecognition.h"
#include "View/View.h"

int main() {
    std::string file_xyz = "file.xyz";
    std::string file_pcd = "file.pcd";
    XyzToPCD xyzToPCD(file_xyz, file_pcd);
    xyzToPCD.convert();
    xyzToPCD.~XyzToPCD();

//    PlanRecognition planRecognition(file_pcd);
//    planRecognition.takePlan();

    View();

}

