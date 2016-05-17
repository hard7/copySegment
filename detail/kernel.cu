
#include "cuda_types.h"


__device__ long cudaTreadIndex() {}

extern "C"
__global__ void copySegment(char* srcPtr, cudaType::Point srcWidth, cudaType::Box srcSegment,
                            char* dstPtr, cudaType::Point dstWidth, cudaType::Box dstSegment, int sizeofType) {

    long tid = cudaTreadIndex();
    int xS = srcSegment.lo.x + (tid % srcSegment.width.x);
    int yS = srcSegment.lo.y + (tid / srcSegment.width.x % srcSegment.width.y);
    int zS = srcSegment.lo.z + (tid / srcSegment.width.x / srcSegment.width.y % srcSegment.width.z);

    int xD = dstSegment.lo.x + (tid % dstSegment.width.x);
    int yD = dstSegment.lo.y + (tid / dstSegment.width.x % dstSegment.width.y);
    int zD = dstSegment.lo.z + (tid / dstSegment.width.x / dstSegment.width.y % dstSegment.width.z);

    long offsetSrc = sizeofType * ( (long) srcWidth.y * srcWidth.x * zS + srcWidth.x * yS + xS);
    long offsetDst = sizeofType * ( (long) dstWidth.y * dstWidth.x * zD + dstWidth.x * yD + xD);


}




extern "C" __global__ void setup() {}