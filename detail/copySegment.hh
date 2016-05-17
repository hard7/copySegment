#ifndef __CUDA_UTILS__COPY_SEGMENT_IMPL_HH__
#define __CUDA_UTILS__COPY_SEGMENT_IMPL_HH__

#include <iostream>

#include "../copySegment.h"
#include "../spatialTraits.h"
#include "../type_name.h"
#include "cassert"

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
void cudaUtils::copySegment(SegmentDesc<Box> const& src, SegmentDesc<Box>& dst, int /*sizeofType*/) {
    using namespace traits;
    using std::cout;
    using std::endl;
    typedef box::_p<Box> Point;
    typedef box::_t<Box> Value;

    Point srcSizes = getBoxSizes(src.segmentBox);
    Point dstSizes = getBoxSizes(dst.segmentBox);

    cout << srcSizes << " " << dstSizes << endl;
    assert(PointCompare<Point>::isEqual(srcSizes, dstSizes));






}

#endif//__CUDA_UTILS__COPY_SEGMENT_IMPL_HH__