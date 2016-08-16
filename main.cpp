#include <iostream>
#include "copySegment.h"
#include "detail/mySpatial.h"
#include "detail/mySpatialType.h"
#include "detail/copySegment.hh"        // Warning
#include <vector>
#include <algorithm>

#include <boost/geometry/geometries/point.hpp>

using namespace std;

#include <cuda.h>
#include <cuda_runtime.h>
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


static int volume(scope::Box const& b) {
    return (b.hi.getX() - b.lo.getX()) * (b.hi.getY() - b.lo.getY()) * (b.hi.getZ() - b.lo.getZ());
}


#include <iostream>
#include <vector>
template <typename T>
inline std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec) {
    for(T const& item : vec) os << item << " ";
    return os;
}


struct _A {
    virtual void foo() =0;
};

void _A::foo() { std::cout << "_A" << std::endl; }

struct _B : _A {
};


int main() {
    _B b;

    checkCudaErrors(cuInit(0));


    scope::MyPoint boxSize(3, 3, 3);
    scope::Box srcBoundBox = {{0, 0, 0}, {3, 3, 3}};
    scope::Box seg = {{1, 1, 1}, {2, 2, 3}};

//    scope::Box dstBoundBox = srcBoundBox;
//    scope::Box dstSegmentBox = srcSegmentBox;

    typedef float Value;
    std::size_t itemCount = static_cast<std::size_t> ( volume(srcBoundBox) );
    std::vector<Value> hostArrayFrom(itemCount), hostArrayTo(itemCount);
    for(std::size_t i=0; i<itemCount; ++i) {
        hostArrayFrom[i] = i;
        hostArrayTo[i] = 0;
    }

    CUdevice device[2];
    checkCudaErrors( cuDeviceGet(&device[0], 0) );
    checkCudaErrors( cuDeviceGet(&device[1], 1) );

    CUcontext context[2];
    checkCudaErrors( cuCtxCreate(&context[0], 0, device[0]) );
    checkCudaErrors( cuCtxCreate(&context[1], 0, device[1]) );

    CUdeviceptr devArrayFrom = 0;
    checkCudaErrors( cuCtxPushCurrent(context[0]) );

    checkCudaErrors( cuMemAlloc(&devArrayFrom, itemCount * sizeof(Value)) );
    checkCudaErrors( cuMemcpyHtoD(devArrayFrom, hostArrayFrom.data(), itemCount * sizeof(Value)) );

    CUdeviceptr devArrayTo = 0;
    checkCudaErrors( cuCtxPushCurrent(context[1]) );
    checkCudaErrors( cuMemAlloc(&devArrayTo, itemCount * sizeof(Value)) );
    checkCudaErrors( cuMemcpyHtoD(devArrayTo, hostArrayTo.data(), itemCount * sizeof(Value)) );

    using cudaUtils::makeSegmentDesc;
    cudaUtils::copySegment(makeSegmentDesc(devArrayFrom, srcBoundBox, seg), makeSegmentDesc(devArrayTo, srcBoundBox, {{0,0,0}, {1,1,2}}), sizeof(Value));
    checkCudaErrors( cuMemcpyDtoH(hostArrayTo.data(), devArrayTo, itemCount * sizeof(Value)) );
    cout << hostArrayTo << endl;

    cuCtxDestroy(context[0]);
    cuCtxDestroy(context[1]);


    return 0;
}