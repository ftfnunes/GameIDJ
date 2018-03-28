#ifndef T1_VECTOR_H
#define T1_VECTOR_H


class Vector {
public:
    int x, y;
    Vector();
    Vector(int x, int y);
    Vector operator+(const Vector v2);
};


#endif //T1_VECTOR_H
