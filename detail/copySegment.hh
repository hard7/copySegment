#ifndef __CUDA_UTILS__COPY_SEGMENT_IMPL_HH__
#define __CUDA_UTILS__COPY_SEGMENT_IMPL_HH__

#include <iostream>

#include "../copySegment.h"
#include "../spatialTraits.h"
#include "../type_name.h"
#include <helper_cuda_drvapi.h>
#include <cassert>

template <class Box> traits::box::_p<Box> getBoxSizes(Box const& box) {
    typedef traits::box::_p<Box> Point;
    using traits::point::get;
    using traits::box::low;
    using traits::box::high;

    return traits::point::make< Point >(
            get<0>(high(box)) - get<0>(low(box)),
            get<1>(high(box)) - get<1>(low(box)),
            get<2>(high(box)) - get<2>(low(box))
    );
}

template <typename T>
struct has_operator_equal {
    template <typename U> static auto test(...) -> std::false_type;
    template <typename U> static auto test(int) -> decltype( std::declval<U>() == std::declval<U>(), std::true_type());

    typedef decltype(test<T>(0)) type;
    static constexpr int value = type::value;

};

template <class Point, class =typename has_operator_equal<Point>::type >
struct PointCompare {
    static bool isEqual(Point const& lhs, Point const& rhs) { return lhs == rhs; }
};

template <class Point>
struct PointCompare <Point, std::false_type> {
    static bool isEqual(Point const& lhs, Point const& rhs) {
        using traits::point::get;
        return get<0>(lhs) == get<0>(rhs) and get<1>(lhs) == get<1>(rhs) and get<2>(lhs) == get<2>(rhs);
    }
};

std::ostream& operator<<(std::ostream& os, scope::MyPoint const& p) {
    os << "{" << p.getX() << ", " << p.getY() << ", " << p.getZ() << "}";
    return os;
}

template <class Box>
void cudaUtils::copySegment(SegmentDesc<Box> const& src, SegmentDesc<Box> const& dst, int sizeofType) {
    using namespace traits;
    using std::cout;
    using std::endl;
    typedef box::_p<Box> Point;
    typedef box::_t<Box> Value;

    Point srcSizes = getBoxSizes(src.segmentBox);
    Point dstSizes = getBoxSizes(dst.segmentBox);

    assert(PointCompare<Point>::isEqual(srcSizes, dstSizes));

    using namespace traits::point;
    using namespace traits::box;
    
    CUDA_MEMCPY3D cp;
    cp.srcXInBytes = point::get<0>(box::low(src.segmentBox)) * sizeofType;
    cp.srcY = point::get<1>(box::low(src.segmentBox));
    cp.srcZ = point::get<2>(box::low(src.segmentBox));
    cp.srcLOD = 0;                                  // let it be
    cp.srcMemoryType = CU_MEMORYTYPE_DEVICE;        // "The owls are not what they seem"
    cp.srcDevice = src.ptr;
    cp.srcPitch = (point::get<0>(box::high(src.boundBox)) - point::get<0>(box::low(src.boundBox))) * sizeofType;
    cp.srcHeight = point::get<1>(box::high(src.boundBox)) - point::get<1>(box::low(src.boundBox));

    cp.dstXInBytes = point::get<0>(box::low(dst.segmentBox)) * sizeofType;
    cp.dstY = point::get<1>(box::low(dst.segmentBox));
    cp.dstZ = point::get<2>(box::low(dst.segmentBox));
    cp.dstLOD = 0;                                  // let it be
    cp.dstMemoryType = CU_MEMORYTYPE_DEVICE;        // "The owls are not what they seem"
    cp.dstDevice = dst.ptr;
    cp.dstPitch = (point::get<0>(box::high(dst.boundBox)) - point::get<0>(box::low(dst.boundBox))) * sizeofType;
    cp.dstHeight = point::get<1>(box::high(dst.boundBox)) - point::get<1>(box::low(dst.boundBox));

    cp.WidthInBytes = (point::get<0>(box::high(src.segmentBox)) - point::get<0>(box::low(src.segmentBox))) * sizeofType;
    cp.Height = point::get<1>(box::high(src.segmentBox)) - point::get<1>(box::low(src.segmentBox));
    cp.Depth = point::get<2>(box::high(src.segmentBox)) - point::get<2>(box::low(src.segmentBox));

    checkCudaErrors( cuMemcpy3D(&cp) );




}

#endif//__CUDA_UTILS__COPY_SEGMENT_IMPL_HH__