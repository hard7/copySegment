#ifndef COPYSEGMENT_MYPOINT_H
#define COPYSEGMENT_MYPOINT_H


namespace scope {

    class MyPoint {
    public:
        typedef int type;

        int getX() const { return x; }
        int getY() const { return y; }
        int getZ() const { return z; }

        void setX(int value) { x = value; }
        void setY(int value) { y = value; }
        void setZ(int value) { z = value; }

        MyPoint(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}

    private:
        int x, y, z;
    };

}

#endif //COPYSEGMENT_MYPOINT_H
