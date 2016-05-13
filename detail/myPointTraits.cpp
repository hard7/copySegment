#include "myPoint.h"
#include "../geometryTraits.h"


typedef scope::MyPoint Point;

namespace traits {
    namespace point {
        template<> _t<Point> get<0>(Point const& p) { return p.getX(); }
        template<> _t<Point> get<1>(Point const& p) { return p.getY(); }
        template<> _t<Point> get<2>(Point const& p) { return p.getZ(); }

        template<> void set<0>(Point& p, _t<Point> value) { p.setX(value); }
        template<> void set<1>(Point& p, _t<Point> value) { p.setY(value); }
        template<> void set<2>(Point& p, _t<Point> value) { p.setZ(value); }

        template<> Point make<Point>(_t<Point> x, _t<Point> y, _t<Point> z) {
            return Point(x, y, z);
        }
    } // namespace point
} // namespace traits