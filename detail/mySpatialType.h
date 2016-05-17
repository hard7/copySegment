#ifndef COPYSEGMENT_MY_POINT_TYPE_H
#define COPYSEGMENT_MY_POINT_TYPE_H


#include "../spatialTraits.h"
#include "mySpatial.h"

namespace traits {
    namespace point {
        template<> struct TypeDeduct< ::scope::MyPoint > {
            typedef typename ::scope::MyPoint::_tp type;
        };
    }

    namespace box {
        template<> struct PointDeduct< ::scope::Box > {
            typedef ::scope::MyPoint type;
        };
    }
}


#endif //COPYSEGMENT_MY_POINT_TYPE_H
