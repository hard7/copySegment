#ifndef COPYSEGMENT_MY_POINT_TYPE_H
#define COPYSEGMENT_MY_POINT_TYPE_H


#include "../spatialTraits.h"
#include "myPoint.h"

namespace traits {
    namespace point {

        template<> struct TypeDeduct< ::scope::MyPoint > {
            typedef typename ::scope::MyPoint::_tp type;
        };
    }
}


#endif //COPYSEGMENT_MY_POINT_TYPE_H
