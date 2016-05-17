#ifndef __COPY_SEGMENT__MY_SPATIAL_H__
#define __COPY_SEGMENT__MY_SPATIAL_H__

namespace scope {

    typedef int VarT;

    class MyPoint {
    public:
        typedef int _tp;

        _tp getX() const { return x; }
        _tp getY() const { return y; }
        _tp getZ() const { return z; }

        void setX(_tp value) { x = value; }
        void setY(_tp value) { y = value; }
        void setZ(_tp value) { z = value; }

        MyPoint(_tp x_, _tp y_, _tp z_) : x(x_), y(y_), z(z_) {}

    private:
        int x, y, z;
    };

    struct Box { MyPoint lo, hi; };
}

#endif //__COPY_SEGMENT__MY_SPATIAL_H__
