#ifndef __CUDA_UTILS__COPY_SEGMENT_IMPL_HH__
#define __CUDA_UTILS__COPY_SEGMENT_IMPL_HH__

#include <iostream>

#include "../copySegment.h"
#include "../spatialTraits.h"
#include "../type_name.h"

template <class Box>
void cudaUtils::copySegment(SegmentDesc<Box> const& src, SegmentDesc<Box>& /*dst*/, int /*sizeofType*/) {
    using namespace traits;
    using std::cout;
    using std::endl;
    typedef box::_p<Box> Point;
    typedef box::_t<Box> Value;



    cout << "function: copySegment" << endl;
    cout << point::get<0>(box::low(src.boundBox)) << endl;
}

#endif//__CUDA_UTILS__COPY_SEGMENT_IMPL_HH__