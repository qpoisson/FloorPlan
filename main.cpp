#include "XyzToPCD.h"

int main() {
    XyzToPCD xyzToPCD("file.xyz", "file.pcd");
    xyzToPCD.convert();
}