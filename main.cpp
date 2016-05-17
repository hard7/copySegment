#include <iostream>
#include "copySegment.h"
#include "detail/mySpatial.h"
#include "detail/mySpatialType.h"
#include "detail/copySegment.hh"        // Warning

using namespace std;

int main() {

    scope::Box srcBoundBox = {{1, 2, 3}, {4, 5, 6}};
    scope::Box srcSegmentBox = {{1, 2, 3}, {4, 3, 4}};
    cudaUtils::SegmentDesc<scope::Box> src(nullptr, srcBoundBox, srcSegmentBox);


    scope::Box dstBoundBox = {{10, 20, 30}, {40, 50, 60}};
    scope::Box dstSegmentBox = {{10, 20, 30}, {13, 50, 60}};
    cudaUtils::SegmentDesc<scope::Box> dst(nullptr, dstBoundBox, dstSegmentBox);

    using cudaUtils::makeSegmentDesc;

    cudaUtils::copySegment(src, dst, 4);

    return 0;
}