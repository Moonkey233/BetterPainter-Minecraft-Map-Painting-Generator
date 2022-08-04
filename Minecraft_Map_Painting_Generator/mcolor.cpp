#include "mcolor.h"

MColor::MColor(){

}

short MColor::minDist(bool isBe, bool isPlane, MBlock* b, int colorSpace, int colorType){
    short pos = 0;
    double min = INF;
    double dis = 0;
    MBasicColor bc;
    for(int i = 0; i < blockType; i++){
        if(colorType == 1){ //灰度
            if(b[i].beRgbColor[0].x != b[i].beRgbColor[0].y ||
               b[i].beRgbColor[0].y != b[i].beRgbColor[0].z)
                continue;
        }
        if(colorType == 2){ //黑白
            if(i != 7 && i != 28) //白色黑色羊毛
                continue;
        }
        for(int j = 0; j < 3; j++){
            if(isPlane && j != 1)
                continue;
            if(isBe && b[i].isBe){
                switch(colorSpace){
                case 0:
                    bc = b[i].beRgbColor[j];
                    dis = rgbDist(bc, this->color);
                    break;
                case 1:
                    bc = b[i].beRgbColor[j];
                    dis = rgbpDist(bc, this->color);
                    break;
                case 2:
                    bc = b[i].beHsvColor[j];
                    dis = hsvDist(bc, this->toHsv());
                    break;
                case 3:
                    bc = b[i].beLabColor[j];
                    dis = labDist(bc, this->toLab());
                    break;
                case 4:
                    bc = b[i].beLabColor[j];
                    dis = labpDist(bc, this->toLab());
                    break;
                default:
                    bc = b[i].beRgbColor[j];
                    dis = rgbDist(bc, this->color);
                    break;
                }
            }else if(!isBe){
                switch(colorSpace){
                case 0:
                    bc = b[i].jeRgbColor[j];
                    dis = rgbDist(bc, this->color);
                    break;
                case 1:
                    bc = b[i].jeRgbColor[j];
                    dis = rgbpDist(bc, this->color);
                    break;
                case 2:
                    bc = b[i].jeHsvColor[j];
                    dis = hsvDist(bc, this->toHsv());
                    break;
                case 3:
                    bc = b[i].jeLabColor[j];
                    dis = labDist(bc, this->toLab());
                    break;
                case 4:
                    bc = b[i].jeLabColor[j];
                    dis = labpDist(bc, this->toLab());
                    break;
                default:
                    bc = b[i].jeRgbColor[j];
                    dis = rgbDist(bc, this->color);
                    break;
                }
            }
            if(dis < min){
                min = dis;
                pos = i * 3 + j;
            }
        }
    }
    return pos;
}

double MColor::rgbDist(MBasicColor bc, MBasicColor c){
    double r = (c.x + bc.x) / 2.0f;
    return sqrt((2.0f + r / 256.0f) * pow(c.x - bc.x, 2) + 4.0f * pow(c.y - bc.y, 2) + (2.0f + (255.0f - r) / 256.0f) * pow(c.z - bc.z, 2));
}

double MColor::rgbpDist(MBasicColor bc, MBasicColor c){
    float r1 = c.x;
    float g1 = c.y;
    float b1 = c.z;
    float r2 = bc.x;
    float g2 = bc.y;
    float b2 = bc.z;
    if(r1 == r2 && g1 == g2 && b1 == b2)
        return 0;
    if(r1 == 0 && r2 == 0)
        r1 = 0.00001;
    if(g1 == 0 && g2 == 0)
        g1 = 0.00001;
    if(b1 == 0 && b2 == 0)
        b1 = 0.00001;
    if(r1 == 0 && g1 == 0 && b1 == 0){
        r1 = 0.00001;
        g1 = 0.00001;
        b1 = 0.00001;
    }
    if(r2 == 0 && g2 == 0 && b2 == 0){
        r2 = 0.00001;
        g2 = 0.00001;
        b2 = 0.00001;
    }
    int wr = 1, wg = 2, wb = 1;
    float sum = 1.0f / 3.0f * (r1 + r2 + g1 + g2 + b1 + b2);
    float sr = (r1 + r2)/sum < 1 ? (r1 + r2)/sum : 1;
    float sg = (g1 + g2)/sum < 1 ? (g1 + g2)/sum : 1;
    float sb = (b1 + b2)/sum < 1 ? (b1 + b2)/sum : 1;
    float ac = (r1 * r2 + g1 * g2 + b1 * b2) / sqrt((r1 * r1 + g1 * g1 + b1 * b1) * (r2 * r2 + g2 * g2 + b2 * b2));
    ac = ac > 1 ? 1 : ac;
    ac = ac < -1 ? -1 : ac;
    float rad = 2.0f / 3.14159265358f * acos(ac);
    float rr = fabs(r1 - r2) / (r1 + r2);
    float gg = fabs(g1 - g2) / (g1 + g2);
    float bb = fabs(b1 - b2) / (b1 + b2);
    float srr = rr / (rr + gg + bb) * sr * sr;
    float sgg = gg / (rr + gg + bb) * sg * sg;
    float sbb = bb / (rr + gg + bb) * sb * sb;
    float srad = srr + sgg + sbb;
    float sm = myMax(r1, myMax(r2, myMax(g1, myMax(g2, myMax(b1, b2))))) / 255.0f;
    float a1 = sr * sr * wr * (r1 - r2) * (r1 - r2);
    float a2 = sg * sg * wg * (g1 - g2) * (g1 - g2);
    float a3 = sb * sb * wb * (b1 - b2) * (b1 - b2);
    float a4 = (wr + wg + wb) * 255 * 255;
    float a5 = srad * sm * rad * rad;
    float dis = sqrt((a1 + a2 + a3) / a4 + a5);
    if(isnan(dis)){
        qDebug()<<"r1"<<r1<<"g1"<<g1<<"b1"<<b1<<"r2"<<r2<<"g2"<<g2<<"b2"<<b2<<srr<<sgg<<sbb<<rad<<a1<<a2<<a3<<a4<<a5;
        system("pause");
    }
    return  dis;
}

double MColor::hsvDist(MBasicColor bc, MBasicColor c){
    return sqrt(pow((c.x - bc.x), 2) + pow(100 * (c.y - bc.y), 2) + pow(100 * (c.z - bc.z), 2));
}

double MColor::labDist(MBasicColor bc, MBasicColor c){
    return sqrt(pow(c.x - bc.x, 2) + pow(c.y - bc.y, 2) + pow(c.z - bc.z, 2));
}

double MColor::labpDist(MBasicColor bc, MBasicColor c){
    double L2 = bc.x;
    double a2 = bc.y;
    double b2 = bc.z;
    double L1 = c.x;
    double a1 = c.y;
    double b1 = c.z;
    double E00 = 0;
    double LL1, LL2, aa1, aa2, bb1, bb2;
    double delta_LL, delta_CC, delta_hh, delta_HH;
    double kL, kC, kH;
    double RT = 0;
    double G = 0;
    double mean_Cab = 0;
    double SL, SC, SH, T;
    kL = 1;
    kC = 1;
    kH = 1;
    mean_Cab = (dc(a1, b1) + dc(a2, b2)) / 2;
    double mean_Cab_pow7 = pow(mean_Cab, 7);
    G = 0.5*(1 - pow(mean_Cab_pow7 / (mean_Cab_pow7 + pow(25, 7)), 0.5));
    LL1 = L1;
    aa1 = a1 * (1 + G);
    bb1 = b1;
    LL2 = L2;
    aa2 = a2 * (1 + G);
    bb2 = b2;
    double CC1, CC2;
    CC1 = dc(aa1, bb1);
    CC2 = dc(aa2, bb2);
    double hh1, hh2;
    hh1 = rc(aa1, bb1);
    hh2 = rc(aa2, bb2);
    delta_LL = LL1 - LL2;
    delta_CC = CC1 - CC2;
    delta_hh = rc(aa1, bb1) - rc(aa2, bb2);
    delta_HH = 2 * sin(M_PI*delta_hh / 360) * pow(CC1 * CC2, 0.5);
    double mean_LL = (LL1 + LL2) / 2;
    double mean_CC = (CC1 + CC2) / 2;
    double mean_hh = (hh1 + hh2) / 2;
    SL = 1 + 0.015 * pow(mean_LL - 50, 2) / pow(20 + pow(mean_LL - 50, 2), 0.5);
    SC = 1 + 0.045 * mean_CC;
    T = 1 - 0.17 * cos((mean_hh - 30) * M_PI / 180) + 0.24 * cos((2 * mean_hh) * M_PI / 180)
        + 0.32 * cos((3 * mean_hh + 6) * M_PI / 180) - 0.2 * cos((4 * mean_hh - 63) * M_PI / 180);
    SH = 1 + 0.015 * mean_CC * T;
    double mean_CC_pow7 = pow(mean_CC, 7);
    double RC = 2 * pow(mean_CC_pow7 / (mean_CC_pow7 + pow(25, 7)), 0.5);
    double delta_xita = 30 * exp(-pow((mean_hh - 275) / 25, 2));
    RT = -sin((2 * delta_xita) * M_PI / 180) * RC;
    double L_item, C_item, H_item;
    L_item = delta_LL / (kL * SL);
    C_item = delta_CC / (kC * SC);
    H_item = delta_HH / (kH * SH);
    E00 = pow(L_item * L_item + C_item * C_item + H_item * H_item + RT * C_item * H_item, 0.5);
    if(isnan(E00)){
        qDebug()<<H_item<<RT;
        system("pause");
    }
    return E00;
}

double MColor::myMax(double a, double b){
    return a > b ? a : b;
}

double MColor::myMin(double a, double b){
    return a < b ? a : b;
}

double MColor::dc(double a, double b){
    double Cab = 0;
    Cab = pow(a * a + b * b, 0.5);
    return Cab;
}

double MColor::rc(double a, double b){
    if(a == 0){
        if(b > 0)
            return 90;
        else if(b < 0)
            return -90;
        else
            return 0;
    }
    double h = 0;
    double hab = 0;
    h = (180 / M_PI) * atan(b / a);
    if (a > 0 && b > 0)
        hab = h;
    else if (a < 0 && b>0)
        hab = 180 + h;
    else if (a < 0 && b < 0)
        hab = 180 + h;
    else
        hab = 360 + h;
    return hab;
}

MBasicColor MColor::toHsv(){
    float R = color.x / 255.0f;
    float G = color.y / 255.0f;
    float B = color.z / 255.0f;
    float Cmax = myMax(R, myMax(G, B));
    float Cmin = myMin(R, myMin(G, B));
    float delta = Cmax - Cmin;
    float H, S, V;
    if(delta == 0){
        H = 0;
    }else if (Cmax == R){
        H = 60.0f * (G - B) / delta;
    }else if(Cmax == G){
        H = 60.0f * ((B - R) / delta + 2);
    }else{
        H = 60.0f * ((R - G) / delta + 4);
    }
    if(Cmax == 0){
        S = 0;
    }else{
        S = delta / Cmax;
    }
    V = Cmax;
    MBasicColor bc;
    bc.x = H;
    bc.y = S;
    bc.z = V;
    return bc;
}

MBasicColor MColor::toLab(){
    float R = color.x / 255.0f;
    float G = color.y / 255.0f;
    float B = color.z / 255.0f;
    if(R > 0.04045f){
        R = pow((R+0.055f)/1.055f, 2.4f);
    }else{
        R /= 12.92f;
    }
    if(G > 0.04045f){
        G = pow((G+0.055f)/1.055f, 2.4f);
    }else{
        G /= 12.92f;
    }
    if(B > 0.04045f){
        B = pow((B+0.055f)/1.055f, 2.4f);
    }else{
        B /= 12.92f;
    }
    float X = 0.4124564f * R + 0.3575761f * G + 0.1804375f * B;
    float Y = 0.2126729f * R + 0.7151522f * G + 0.0721750f * B;
    float Z = 0.0193339f * R + 0.1191920f * G + 0.9503041f * B;
    float x = X / 0.950456f;
    float y = Y / 1.0f;
    float z = Z / 1.088754f;
    if(x > 0.0088565f){
        x = pow(x, 0.333333f);
    }else{
        x = 7.787037f * x + 0.137931f;
    }
    if(y > 0.0088565f){
        y = pow(y, 0.333333f);
    }else{
        y = 7.787037f * y + 0.137931f;
    }
    if(z > 0.0088565f){
        z = pow(z, 0.333333f);
    }else{
        z = 7.787037f * z + 0.137931f;
    }
    MBasicColor bc;
    bc.x = 116.0f * y - 16.0f;
    bc.x = bc.x > 0.0f ? bc.x : 0.0f;
    bc.y = 500.0f * (x - y);
    bc.z = 200.0f * (y - z);
    return bc;
}
