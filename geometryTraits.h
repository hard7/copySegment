#ifndef __COPY_SEGMENT__GEOMETRY_TRAITS_H__
#define __COPY_SEGMENT__GEOMETRY_TRAITS_H__


#include <iostream>
#include "type_name.h"
#include "takeTypeDefault.h"


namespace traits {
    namespace point {

        template<class Point>
        struct Type {
            typedef takeTypeDefault<Point, double> type;
        };

        template <class Point> using _t = typename Type<Point>::type;

        template<int N, class Point>
        _t<Point> get(Point const &) {
            std::cout << "Please, make specialization: traits::point::get< ";
            std::cout << type_name<Point>() << ", " << N << " >" << std::endl;
            exit(8);
        }

        template<int N, class Point>
        void set(Point&, _t<Point> /* value */) {
            std::cout << "Please, make specialization: traits::point::set< ";
            std::cout << type_name<Point>() << ", " << N << " >" << std::endl;
            exit(8);
        }

        template<typename Point>
        Point make(_t<Point>, _t<Point>, _t<Point>) {
            std::cout << "Please, make specialization: traits::point::make< ";
            std::cout << type_name<Point>() << " > (..) " << std::endl;
            exit(8);
        }

    }

    namespace box {
        template<class Box> struct DeductPoint {
            typedef typename Box::Point type;
        };

        template <class Box>
        using _p = typename DeductPoint<Box>::type;


    }

}

#endif //__COPY_SEGMENT__GEOMETRY_TRAITS_H__
