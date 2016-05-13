
#include <iostream>

#include "../copySegment.h"
#include "../spatialTraits.h"
#include "../type_name.h"

template <class Box>
void cudaUtils::copySegment(SegmentDesc<Box> const& /*src*/, SegmentDesc<Box>& /*dst*/, int /*sizeofType*/) {
    using std::cout;
    using std::endl;

//    Box const& box = src.boundBox;
    cout << "function: copySegment" << endl;
    cout << type_name<Box>() << endl;
}


template <class Point>
void cudaUtils::_dm(Point const& p) {
    using std::cout;
    using std::endl;

    cout << "*: " << type_name<Point>() << " " << p.getX() << endl;
    cout << "*: " << type_name<Point>() << " " << traits::point::get<0>(p) << endl;
}