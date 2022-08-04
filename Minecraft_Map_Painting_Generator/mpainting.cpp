#include "mpainting.h"

MPainting::MPainting(){
    picNum = 0;
    setting.isPlane = false;
    setting.isDither = true;
    setting.colorType = 0;
    setting.isBedrock = true;
    setting.colorSpace = 1;
    setting.fileName = "MyPicture";
    setting.isImage = true;
    setting.isFunction = false;
    setting.isSchematic = false;
    setting.maxHeight = 319;
    setting.minHeight = -60;
    setting.beginX = -64;
    setting.beginZ = -64;
    setting.edition = 0;
    setting.savePath = QString("output\\");
    setting.bgColor = {255, 255, 255};
}

MPainting::~MPainting(){

}

void MPainting::readFile(){
//    picNum = 1;
//    picList = new QString [picNum];
//    picList[0] = {QString("pictures/test.png")};
//    //picList[1] = {QString("pictures/test.png")};
}

void MPainting::generator(QProgressBar *bar){
    float value = 0;
    if(setting.maxHeight - setting.minHeight < 4)
        setting.isPlane = true;
    width = new int [picNum];
    height = new int [picNum];
    ans = new short** [picNum];
    for(int i = 0; i < picNum; i++){
        if(i > 0){
            for(int j = 0; j < height[i-1]; j++) //清除堆内存
                delete [] xyz[j];
            delete [] xyz;
            delete currentPicture;
        }
        currentPicture = new MPicture(picList[i]);
        xyz = currentPicture->getColor(setting.bgColor);
        width[i] = currentPicture->getWidth();
        height[i] = currentPicture->getHeight();
        ans[i] = new short* [height[i]];
        for(int j = 0; j < height[i]; j++){
            ans[i][j] = new short [width[i]];
            value = i * 1000 / picNum + j * 1000 / (height[i] - 1) / picNum;
            bar->setValue(value);
            bar->setFormat(QString::fromLocal8Bit("%1%").arg(QString::number(value / 10, 'f', 1)));
            for(int k = 0; k < width[i]; k++){
                QApplication::processEvents();
                this->correct(j, k);
                ans[i][j][k] = xyz[j][k].minDist(setting.isBedrock, setting.isPlane, blockData, setting.colorSpace, setting.colorType);
                if(setting.isDither){
                    floydDither(ans[i][j][k], width[i], height[i], j, k);
                }
            }
        }
    }
    //qDebug()<<"generate success";
}

void MPainting::writeFile(QProgressBar *bar){
    progressBar = bar;
    int type = 1;
    totalPix = 0;
    value = 0;
    for(int i = 0; i < picNum; i++){
        totalPix += width[i] * height[i];
    }
    if(setting.isImage)
        type++;
    if(setting.isSchematic)
        type++;
    totalPix *= type;
    progressBar->setRange(0, totalPix);
    QDir *dir = new QDir(setting.savePath);
    if(!dir->exists())
        dir->mkpath(setting.savePath);
    writeFunction();
    if(setting.isImage)
        writeImage();
    if(setting.isSchematic)
        writeSchematic();
}

void MPainting::floydDither(short pos, int w, int h, int x, int y){
    MBasicColor newXyz;
    if(setting.isBedrock)
        newXyz = blockData[pos / 3].beRgbColor[pos % 3];
    else
        newXyz = blockData[pos / 3].jeRgbColor[pos % 3];
    float dr = xyz[x][y].color.x - newXyz.x; //记录偏色误差
    float dg = xyz[x][y].color.y - newXyz.y;
    float db = xyz[x][y].color.z - newXyz.z;
    if(y + 1 < w){ //抖动纠正
        xyz[x][y+1].color.x += 7.0f/16.0f*dr;
        xyz[x][y+1].color.y += 7.0f/16.0f*dg;
        xyz[x][y+1].color.z += 7.0f/16.0f*db;
    }
    if(y + 1 < w && x + 1 < h){
        xyz[x+1][y+1].color.x += 1.0f/16.0f*dr;
        xyz[x+1][y+1].color.y += 1.0f/16.0f*dg;
        xyz[x+1][y+1].color.z += 1.0f/16.0f*db;
    }
    if(x + 1 < h){
        xyz[x+1][y].color.x += 5.0f/16.0f*dr;
        xyz[x+1][y].color.y += 5.0f/16.0f*dg;
        xyz[x+1][y].color.z += 5.0f/16.0f*db;
    }
    if(y > 0 && x + 1 < h){
        xyz[x+1][y-1].color.x += 3.0f/16.0f*dr;
        xyz[x+1][y-1].color.y += 3.0f/16.0f*dg;
        xyz[x+1][y-1].color.z += 3.0f/16.0f*db;
    }
}

void MPainting::correct(int j, int k){
    xyz[j][k].color.x = xyz[j][k].color.x > 255 ? 255 : xyz[j][k].color.x;
    xyz[j][k].color.y = xyz[j][k].color.y > 255 ? 255 : xyz[j][k].color.y;
    xyz[j][k].color.z = xyz[j][k].color.z > 255 ? 255 : xyz[j][k].color.z;
    xyz[j][k].color.x = xyz[j][k].color.x < 0 ? 0 : xyz[j][k].color.x;
    xyz[j][k].color.y = xyz[j][k].color.y < 0 ? 0 : xyz[j][k].color.y;
    xyz[j][k].color.z = xyz[j][k].color.z < 0 ? 0 : xyz[j][k].color.z;
}

void MPainting::newFile(int i){
    sum++;
    if(sum >= 10000){
        file1.close();
        file2.close();
        total++;
        sum -= 10000;
        file1.setFileName(setting.savePath + setting.fileName + "_" + QString::number(i + 1) + "_" + QString::number(total + 1) + ".mcfunction");
        file2.setFileName(setting.savePath + setting.fileName + "_" + QString::number(i + 1) + "_" + QString::number(total + 1) + "_clear" + ".mcfunction");
        file1.open(QIODevice::WriteOnly | QIODevice::Text);
        file2.open(QIODevice::WriteOnly | QIODevice::Text);
    }
}

void MPainting::writeImage(){
    short pos;
    for(int k = 0; k < picNum; k++){
        QImage image(width[k], height[k], QImage::Format_ARGB32);
        for(int i = 0; i < height[k]; i++){
            progressBar->setValue(value);
            progressBar->setFormat(QString::fromLocal8Bit("%1%").arg(QString::number(value * 100 / totalPix, 'f', 1)));
            for(int j = 0; j < width[k]; j++){
                value++;
                QApplication::processEvents();
                pos = ans[k][i][j];
                image.setPixel(j,i,qRgb((int)(blockData[pos/3].beRgbColor[pos%3].x),(int)(blockData[pos/3].beRgbColor[pos%3].y),(int)(blockData[pos/3].beRgbColor[pos%3].z)));
            }
        }
        image.save(setting.savePath + setting.fileName + "_" + QString::number(k + 1) + ".jpg");
    }
}

void MPainting::writeFunction(){
    int high, mid = 128;
    int upCount = 0, downCount = 0;
    mid = (setting.maxHeight + setting.minHeight) / 2;
    for(int i = 0; i < picNum; i++){
        QString line = "";
        if(setting.isFunction){
            file1.setFileName(setting.savePath + setting.fileName + "_" + QString::number(i + 1) + "_" + QString::number(total + 1) + ".mcfunction");
            file2.setFileName(setting.savePath + setting.fileName + "_" + QString::number(i + 1) + "_" + QString::number(total + 1) + "_clear" + ".mcfunction");
            file1.open(QIODevice::WriteOnly | QIODevice::Text);
            file2.open(QIODevice::WriteOnly | QIODevice::Text);
        }
        for(int y = 0; y < width[i]; y++){
            //progressBar->setValue();
            downCount = 0;
            upCount = 0;
            if(setting.isFunction) newFile(i);
            if(ans[i][0][y] % 3 == 0){
                high = setting.minHeight - 1;
                upCount = 1;
            }
            else if(ans[i][0][y] % 3 == 2){
                high = setting.maxHeight + 2;
                downCount = 1;
            }
            else
                high = mid;
            progressBar->setValue(value);
            progressBar->setFormat(QString::fromLocal8Bit("%1%").arg(QString::number(value * 100 / totalPix, 'f', 1)));
            for(int x = 0; x < height[i]; x++){
                value++;
                QApplication::processEvents();
                short pos = ans[i][x][y];
                if(pos % 3 == 0){ //上升
                    if((high < mid && upCount == 0) || high >= setting.maxHeight - 1){
                        if(high >= setting.maxHeight - 1){
                            ans[i][x][y] += 2;
                            if(upCount > 0)
                                high = setting.minHeight;
                            else
                                high = mid;
                        }else
                            high = mid;
                    }else
                        high += 2;
                    upCount++;
                    downCount = 0;
                }else if(pos % 3 == 2){
                    if((high > mid && downCount == 0) || high <= setting.minHeight + 1){
                        if(high <= setting.minHeight + 1){
                            ans[i][x][y] -= 2;
                            if(downCount > 0)
                                high = setting.maxHeight;
                            else
                                high = mid;
                        }else
                            high = mid;
                    }else
                        high -= 2;
                    downCount++;
                    upCount = 0;
                }
                if(setting.isFunction){
                    QString b;
                    if(setting.isBedrock)
                        b = blockData[pos / 3].beName;
                    else
                        b = blockData[pos / 3].jeName;
                    if(b == "water" || b == "kelp"){
                        newFile(i);
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high - 1) + " " + QString::number(x + setting.beginZ) + " glass 0\r\n";
                        file1.write(line.toUtf8());
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high - 1) + " " + QString::number(x + setting.beginZ) + " air\r\n";
                        file2.write(line.toUtf8());
                        newFile(i);
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high + 1) + " " + QString::number(x + setting.beginZ) + " glass 0\r\n";
                        file1.write(line.toUtf8());
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high + 1) + " " + QString::number(x + setting.beginZ) + " air\r\n";
                        file2.write(line.toUtf8());
                        newFile(i);
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ + 1) + " glass 0\r\n";
                        file1.write(line.toUtf8());
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ) + " air\r\n";
                        file2.write(line.toUtf8());
                        newFile(i);
                        line = "setblock " + QString::number(y + setting.beginX + 1) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ) + " glass 0\r\n";
                        file1.write(line.toUtf8());
                        line = "setblock " + QString::number(y + setting.beginX + 1) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ) + " air\r\n";
                        file2.write(line.toUtf8());
                        newFile(i);
                        line = "fill " + QString::number(y + setting.beginX - 1) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ) + " " + QString::number(y - 65) + " " + QString::number(high) + " " + QString::number(x - 64) + " glass 0 replace air\r\n";
                        file1.write(line.toUtf8());
                        line = "setblock " + QString::number(y + setting.beginX - 1) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ) + " air\r\n";
                        file2.write(line.toUtf8());
                        newFile(i);
                        line = "fill " + QString::number(y + setting.beginX) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ - 1) + " " + QString::number(y - 64) + " " + QString::number(high) + " " + QString::number(x - 65) + " glass 0 replace air\r\n";
                        file1.write(line.toUtf8());
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ - 1) + " air\r\n";
                        file2.write(line.toUtf8());
                    }
                    newFile(i);
                    if(setting.isBedrock)
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ) + " " + b + " " + QString::number(blockData[pos / 3].beData) + "\r\n";
                    else
                        line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high) + " " + QString::number(x+ setting.beginZ) + " " + b + " " + QString::number(blockData[pos / 3].jeData) + "\r\n";
                    file1.write(line.toUtf8());
                    line = "setblock " + QString::number(y + setting.beginX) + " " + QString::number(high) + " " + QString::number(x + setting.beginZ) + " air\r\n";
                    file2.write(line.toUtf8());
                }
            }
        }
        if(setting.isFunction){
            file1.close();
            file2.close();
        }
    }
}

void MPainting::writeSchematic(){

}
