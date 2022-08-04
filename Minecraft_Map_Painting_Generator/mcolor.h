#ifndef MCOLOR_H
#define MCOLOR_H

#include "data.h"

class MColor{
public:
    MColor();
    short minDist(bool isBe, bool isPlane, MBlock* b, int colorSpace, int colorType);
    double rgbDist(MBasicColor bc, MBasicColor c);
    double rgbpDist(MBasicColor bc, MBasicColor c);
    double hsvDist(MBasicColor bc, MBasicColor c);
    double labDist(MBasicColor bc, MBasicColor c);
    double labpDist(MBasicColor bc, MBasicColor c);
    double myMax(double a, double b);
    double myMin(double a, double b);
    double dc(double a, double b);
    double rc(double a, double b);
    MBasicColor toHsv();
    MBasicColor toLab();
    MBasicColor color;
private:
};

#endif // MCOLOR_H
