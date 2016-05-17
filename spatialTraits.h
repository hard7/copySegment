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
            static_assert(not deduct::has_type<Point>(),
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
        Point make(_t<Point> x, _t<Point> y, _t<Point> z) {
            return Point(x, y, z);
        }

    } // namespace point

    namespace box {
        template<class Box> struct PointDeduct {
//            typedef deduct::rm_const<Box> Box_;
            static_assert(not deduct::has_PointType<Box>(),
                          "\n\n\t\t************ "
                          "Error: determine typedef [CustomBox]::PointType. "
                          "Or define template specialisation for traits::box::PointDeduct <[CustomBox]> "
                          "in all translation units, where it used (including implicitly) in algorithms with custom box."
            );
            typedef typename Box::PointType type;
        };

        template<class Box> struct PointDeduct <const Box> : PointDeduct<Box> { };      // it's fun, but it's work ;)



        template<class Box> struct TypeDeduct {
            typedef typename ::traits::point::TypeDeduct<
                    typename PointDeduct<Box>::type
            >::type type;
        };


        template<class Box> using _t = typename TypeDeduct<Box>::type;
        template<class Box> using _p = typename PointDeduct<Box>::type;

        template<class Box> _p<Box>& low(Box& /* box */);
        template<class Box> _p<Box>& high(Box& /* box */);

        template<class Box> _p<Box> const& low(Box const& /* box */);
        template<class Box> _p<Box> const& high(Box const& /* box */);

        template<typename Box>
        Box make(_p<Box> const& lo, _p<Box> const& hi) {
            return Box(lo, hi);
        }

    } // namespace box

} // namespace traits

#endif //__COPY_SEGMENT__SPATIAL_TRAITS_H__
