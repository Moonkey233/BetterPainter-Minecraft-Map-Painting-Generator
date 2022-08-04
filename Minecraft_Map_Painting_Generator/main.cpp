#include "mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Minecraft Map Painting Generator designed by Moonkey_ 2022");
    w.show();
    return a.exec();
}
