#include "mpicture.h"

MPicture::MPicture(QString path){
    filePath = path;
}

MColor** MPicture::getColor(MBasicColor bgc){
    img = new QImage;
    img->load(filePath); //加载图片img
    *img = img->convertToFormat(QImage::Format_ARGB32);

    int height = img->height();
    int width = img->width();

    MColor** xyz = new MColor* [height];//动态数组存原图rgba
    for(int i = 0; i < height; i++){
        xyz[i] = new MColor [width];
    }
    for(int x = 0; x < height; x++){
        for(int y = 0; y < width; y++){
            QColor c = img->pixelColor(y, x);
            float a = 1.0;
            a = c.alphaF(); //alpha通道透明度[0 - 1]
            xyz[x][y].color.x = (c.red() + (bgc.x - c.red()) * (1 - a) + 0.5) * 100 / 100; //半透明混合背景色(当前255,255,255白色)四舍五入保留整数
            xyz[x][y].color.y = (c.green() + (bgc.y - c.green()) * (1 - a) + 0.5) * 100 / 100;
            xyz[x][y].color.z = (c.blue() + (bgc.z - c.blue()) * (1 - a) + 0.5) * 100 / 100;
        }
    }
    return xyz;
}

int MPicture::getWidth(){
    return img->width();
}

int MPicture::getHeight(){
    return img->height();
}
