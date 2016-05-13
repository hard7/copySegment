#include <iostream>
#include "copySegment.h"

#include "detail/copySegment.hh"        // Warning
#include "detail/myPoint.h"

#include <vector>

using namespace std;

struct Point {int x ,y, z; };
struct Box {Point lo, hi; };



int main() {

    Box srcBoundBox = {{1, 2, 3}, {4, 5, 6}};
    Box srcSegmentBox = {{1, 2, 3}, {4, 3, 4}};
    cudaUtils::SegmentDesc<Box> src(nullptr, srcBoundBox, srcSegmentBox);


    Box dstBoundBox = {{10, 20, 30}, {40, 50, 60}};
    Box dstSegmentBox = {{10, 20, 30}, {13, 50, 60}};
    cudaUtils::SegmentDesc<Box> dst(nullptr, dstBoundBox, dstSegmentBox);

    using cudaUtils::makeSegmentDesc;

//    cudaUtils::copySegment(src, dst, 4);

    scope::MyPoint p = {42, 2, 3};
    cudaUtils::_dm(p);

    cout << "Hello, World!" << endl;
    return 0;
}