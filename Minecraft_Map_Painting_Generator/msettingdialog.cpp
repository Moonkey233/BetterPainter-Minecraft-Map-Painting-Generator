#include "msettingdialog.h"
#include "ui_msettingdialog.h"

MSettingDialog::MSettingDialog(MPainting *paint, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MSettingDialog)
{
    painting = paint;
    ui->setupUi(this);
    ui->edition->addItem(tr("1.18及之后"));
    //autoSet();
    connect(ui->submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(ui->autoButton, SIGNAL(clicked()), this, SLOT(autoSet()));
    connect(ui->plane, SIGNAL(clicked()), this, SLOT(planeSet()));
    connect(ui->cube, SIGNAL(clicked()), this, SLOT(cubeSet()));
    connect(ui->height, SIGNAL(editingFinished()), this, SLOT(reHeight()));
    connect(ui->mheight1, SIGNAL(editingFinished()), this, SLOT(reM1()));
    connect(ui->mheight2, SIGNAL(editingFinished()), this, SLOT(reM2()));
    connect(ui->beginX, SIGNAL(editingFinished()), this, SLOT(reX()));
    connect(ui->beginZ, SIGNAL(editingFinished()), this, SLOT(reZ()));
    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectColor()));
}

MSettingDialog::~MSettingDialog()
{
    delete ui;
}

void MSettingDialog::submit(){
    reHeight();
    reM1();
    reM2();
    reX();
    reZ();
    if(ui->space0->isChecked()){
        painting->setting.colorSpace = 0;
    }else if(ui->space1->isChecked()){
        painting->setting.colorSpace = 1;
    }else if(ui->space2->isChecked()){
        painting->setting.colorSpace = 2;
    }else if(ui->space3->isChecked()){
        painting->setting.colorSpace = 3;
    }else{
        painting->setting.colorSpace = 4;
    }

    if(ui->type0->isChecked()){
        painting->setting.colorType = 0;
    }else if(ui->type1->isChecked()){
        painting->setting.colorType = 1;
    }else{
        painting->setting.colorType = 2;
    }

    if(ui->dither->isChecked()){
        painting->setting.isDither = true;
    }else{
        painting->setting.isDither = false;
    }

    if(ui->bedrock->isChecked()){
        painting->setting.isBedrock = true;
    }else{
        painting->setting.isBedrock = false;
    }

    if(ui->plane->isChecked()){
        painting->setting.isPlane = true;
        painting->setting.minHeight = ui->height->text().toInt();
        painting->setting.maxHeight = ui->height->text().toInt();
    }else{
        painting->setting.isPlane = false;
        painting->setting.maxHeight = ui->mheight1->text().toInt() >= ui->mheight2->text().toInt() ? ui->mheight1->text().toInt() : ui->mheight2->text().toInt();
        painting->setting.minHeight = ui->mheight1->text().toInt() <= ui->mheight2->text().toInt() ? ui->mheight1->text().toInt() : ui->mheight2->text().toInt();
    }

    painting->setting.beginX = ui->beginX->text().toInt();
    painting->setting.beginZ = ui->beginZ->text().toInt();

    this->accept();
//    qDebug()<<painting->setting.colorSpace
//           <<painting->setting.colorType
//          <<painting->setting.beginX
//         <<painting->setting.beginZ
//        <<painting->setting.isPlane
//       <<painting->setting.isDither
//      <<painting->setting.isBedrock
//     <<painting->setting.maxHeight
//    <<painting->setting.minHeight;
}

void MSettingDialog::autoSet(){
    painting->setting.isPlane = false;
    //painting->setting.isDither = true;
    painting->setting.colorType = 0;
    painting->setting.isBedrock = true;
    painting->setting.colorSpace = 1;
    painting->setting.maxHeight = 319;
    painting->setting.minHeight = -60;
    painting->setting.beginX = -64;
    painting->setting.beginZ = -64;
    painting->setting.edition = 0;
    painting->setting.savePath = QString("output/");
    painting->setting.bgColor = {255, 255, 255};
    ui->edition->setCurrentIndex(0);
    ui->space1->setChecked(true);
    ui->type0->setChecked(true);
    ui->bedrock->setChecked(true);
    ui->cube->setChecked(true);
    ui->mheight1->setText("-60");
    ui->mheight2->setText("319");
    ui->beginX->setText("-64");
    ui->beginZ->setText("-64");
    cubeSet();
    QImage img;
    img.load(painting->picList[0]);
    if(img.width() * img.height() > 20000 || img.width() * img.height() < 0){
        painting->setting.isDither = true;
        ui->dither->setChecked(true);
    }else{
        painting->setting.isDither = false;
        ui->dither->setChecked(false);
    }
}

void MSettingDialog::planeSet(){
    ui->mheight1->setEnabled(false);
    ui->mheight2->setEnabled(false);
    ui->height->setEnabled(true);
}

void MSettingDialog::cubeSet(){
    ui->mheight1->setEnabled(true);
    ui->mheight2->setEnabled(true);
    ui->height->setEnabled(false);
}

void MSettingDialog::reHeight(){
    bool ok;
    ui->height->text().toInt(&ok);
    if(ok == false){
        ui->height->setText("0");
    }
}

void MSettingDialog::reM1(){
    bool ok;
    ui->mheight1->text().toInt(&ok);
    if(ok == false){
        ui->mheight1->setText("-60");
    }
}

void MSettingDialog::reM2(){
    bool ok;
    ui->mheight2->text().toInt(&ok);
    if(ok == false){
        ui->mheight2->setText("319");
    }
}

void MSettingDialog::reX(){
    bool ok;
    ui->beginX->text().toInt(&ok);
    if(ok == false){
        ui->beginX->setText("-64");
    }
}

void MSettingDialog::reZ(){
    bool ok;
    ui->beginZ->text().toInt(&ok);
    if(ok == false){
        ui->beginZ->setText("-64");
    }
}

void MSettingDialog::setUi(){
    if(painting->setting.colorSpace == 0)
        ui->space0->setChecked(true);
    else if(painting->setting.colorSpace == 1)
        ui->space1->setChecked(true);
    else if(painting->setting.colorSpace == 2)
        ui->space2->setChecked(true);
    else if(painting->setting.colorSpace == 3)
        ui->space3->setChecked(true);
    else
        ui->space4->setChecked(true);

    if(painting->setting.colorType == 0)
        ui->type0->setChecked(true);
    else if(painting->setting.colorType == 1)
        ui->type1->setChecked(true);
    else
        ui->type2->setChecked(true);

    if(painting->setting.isDither)
        ui->dither->setChecked(true);
    else
        ui->dither->setChecked(true);

    if(painting->setting.isBedrock)
        ui->bedrock->setChecked(true);
    else
        ui->java->setChecked(true);

    if(painting->setting.isPlane){
        ui->plane->setChecked(true);
        planeSet();
        ui->height->setText(QString::number(painting->setting.minHeight));
    }else{
        ui->cube->setChecked(true);
        cubeSet();
        ui->mheight1->setText(QString::number(painting->setting.minHeight));
        ui->mheight2->setText(QString::number(painting->setting.maxHeight));
    }

    ui->beginX->setText(QString::number(painting->setting.beginX));
    ui->beginZ->setText(QString::number(painting->setting.beginZ));

    if(painting->setting.edition == 0)
        ui->edition->setCurrentIndex(0);
    else
        ui->edition->setCurrentIndex(0); //
}

void MSettingDialog::selectColor(){
    QColor bc;
    bc.setRed(painting->setting.bgColor.x);
    bc.setGreen(painting->setting.bgColor.y);
    bc.setBlue(painting->setting.bgColor.z);

    QColor c = QColorDialog::getColor(bc);
    painting->setting.bgColor.x = c.red();
    painting->setting.bgColor.y = c.green();
    painting->setting.bgColor.z = c.blue();
}
