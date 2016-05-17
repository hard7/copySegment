#include <iostream>
#include "copySegment.h"
#include "detail/mySpatial.h"
#include "detail/mySpatialType.h"
#include "detail/copySegment.hh"        // Warning

using namespace std;

#include <cuda.h>
#include <helper_cuda_drvapi.h>

#define TO_STRING(x) STRINGIFY(x)
#define STRINGIFY(x) #x

const std::string PTX_LOCATE = TO_STRING(PTX_MODULE_LOCATION);

CUfunction getCudaFunction(std::string const& ptxPath, std::string const& funcName, int deviceID =0);
CUfunction getCudaFunction(std::string const& ptxPath, std::string const& funcName, int deviceID /* =0 */) {
    checkCudaErrors(cuInit(0));

    int deviceCount = 0;
    checkCudaErrors(cuDeviceGetCount(&deviceCount));
    assert(deviceID < deviceCount);

    CUdevice cuDevice;
    checkCudaErrors(cuDeviceGet(&cuDevice, deviceID));

    CUcontext cuContext;
    checkCudaErrors(cuCtxCreate(&cuContext, 0, cuDevice));

    CUmodule cuModule;
    checkCudaErrors(cuModuleLoad(&cuModule, ptxPath.c_str()));

    CUfunction cuFunc;
    checkCudaErrors(cuModuleGetFunction(&cuFunc, cuModule, funcName.c_str()));

    return cuFunc;
}


int main() {

    scope::Box srcBoundBox = {{1, 2, 3}, {4, 5, 6}};
    scope::Box srcSegmentBox = {{1, 2, 3}, {4, 3, 4}};
    cudaUtils::SegmentDesc<scope::Box> src(nullptr, srcBoundBox, srcSegmentBox);


    scope::Box dstBoundBox = {{10, 20, 30}, {40, 50, 60}};
    scope::Box dstSegmentBox = {{10, 20, 30}, {13, 21, 31}};
    cudaUtils::SegmentDesc<scope::Box> dst(nullptr, dstBoundBox, dstSegmentBox);

    using cudaUtils::makeSegmentDesc;

    cudaUtils::copySegment(src, dst, 4);


//    checkCudaErrors( cuInit(0) );

    cout << PTX_LOCATE << endl;

    auto cudaFunc = getCudaFunction(PTX_LOCATE, "setup");



    return 0;
}