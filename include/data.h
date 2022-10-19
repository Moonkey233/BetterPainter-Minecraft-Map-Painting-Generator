#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <math.h>
#include <QImage>
#include <QDebug>
#include <QString>
#include <QMainWindow>
#include <QApplication>
#include <QDir>
#include <QUrl>

const int blockType = 52;
const double INF = 999999999;

struct MBasicColor{
    float x;
    float y;
    float z;
};

struct MBlock{
    bool isBe;
    int beData;
    int jeData;
    int index;
    QString beName;
    QString jeName;
    MBasicColor beRgbColor[3];
    MBasicColor beHsvColor[3];
    MBasicColor beLabColor[3];
    MBasicColor jeRgbColor[3];
    MBasicColor jeHsvColor[3];
    MBasicColor jeLabColor[3];
};

struct MSetting{
    bool isPlane;
    bool isBedrock;
    bool isDither;
    int colorSpace; //0rgb 1rgbp 2hsv 3lab 4labp
    int colorType; //0彩色 1灰度 2黑白
    int maxHeight;
    int minHeight;
    int beginX;
    int beginZ;
    int edition;
    double scale;
    QString fileName;
    QString savePath;
    bool isImage;
    bool isFunction;
    bool isSchematic;
    MBasicColor bgColor;
};

#endif // DATA_H
