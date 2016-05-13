#ifndef __COPY_SEGMENT__SPATIAL_TRAITS_H__
#define __COPY_SEGMENT__SPATIAL_TRAITS_H__


#include <iostream>
#include "type_name.h"
#include "takeTypeDefault.h"
#include "typeDeduct.h"

namespace traits {
    namespace point {

        template<class Point>
        struct TypeDeduct {
            static_assert(not hasType<Point>(),
                        "\n\n\t\t************ "
                        "Error: determine typedef [CustomPoint]::type. "
                        "Or define template specialisation for traits::point::TypeDeduct <[CustomPoint]> "
                        "in all translation units, where it used (including implicitly) in algorithms with custom points."
            );
            typedef typename Point::type type;
        };

        template <class Point> using _t = typename TypeDeduct<Point>::type;

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

    } // namespace point

    namespace box {
        template<class Box> struct DeductPoint {
            typedef typename Box::Point type;
        };

        template <class Box>
        using _p = typename DeductPoint<Box>::type;


    } // namespace box

} // namespace traits

#endif //__COPY_SEGMENT__SPATIAL_TRAITS_H__
