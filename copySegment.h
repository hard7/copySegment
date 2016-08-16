#ifndef __CUDA_UTILS__COPY_SEGMENT_H__
#define __CUDA_UTILS__COPY_SEGMENT_H__

#include "cuda.h" // CUdeviceptr

namespace cudaUtils {

    template <class Box_>
    struct SegmentDesc {
        typedef Box_ Box;
        CUdeviceptr ptr;
        const Box boundBox, segmentBox;

        SegmentDesc(CUdeviceptr ptr_, Box const& boundBox_, Box const& segmentBox_) : ptr(ptr_), boundBox(boundBox_), segmentBox(segmentBox_) {}
    };

    // constructor with template deduction
    template <class Box>
    SegmentDesc<Box> makeSegmentDesc(CUdeviceptr ptr, Box const& boundBox, Box const& segmentBox) {
        return SegmentDesc<Box>(ptr, boundBox, segmentBox);
    }


    /*
     * For data using x-major ordering (elements of the X coordinate are contiguous in memory). Then y, then z.
     *
     */

    template<class Box>
    void copySegment(SegmentDesc<Box> const& src, SegmentDesc<Box> const& dst, int sizeofType);

} // namespace CudaUtils


#endif //__CUDA_UTILS__COPY_SEGMENT_H__
