#ifndef MPICTURE_H
#define MPICTURE_H

#include "data.h"
#include "mcolor.h"

class MPicture{
public:
    MPicture(QString path);
    MColor** getColor(MBasicColor bgc);
    MColor toHsv(int x, int y);
    MColor toLab(int x, int y);
    int getWidth();
    int getHeight();
private:
    QImage* img;
    QString filePath;
};

#endif // MPICTURE_H
