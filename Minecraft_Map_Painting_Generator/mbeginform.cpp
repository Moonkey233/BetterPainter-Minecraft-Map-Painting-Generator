#include "mbeginform.h"
#include "ui_mbeginform.h"

MBeginForm::MBeginForm(MPainting *paint, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MBeginForm)
{
    painting = paint;
    ui->setupUi(this);
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(beginEdit()));
    connect(ui->beginButton, SIGNAL(clicked()), this, SLOT(inputFiles()));
}

MBeginForm::~MBeginForm()
{
    delete ui;
}

void MBeginForm::beginEdit(){
    if(painting->picNum == 0){
        //ui->editButton->setText(tr("请先导入图片"));
        QMessageBox::critical(this, tr("提示"), tr("请先导入图片！"));
    }else{
        emit setIndex(1);
    }
}

void MBeginForm::inputFiles(){
    QStringList list = QFileDialog::getOpenFileNames(
        this, "选择要生成像素画的图片",
        "/",
        "图片文件 (*.jpg *.jpeg *.png *.bmp *.tif *.tiff)");
    //qDebug()<<list;
    if(list.size() != 0){
        painting->picNum = list.size();
        painting->picList = new QString [painting->picNum];
        for(int i = 0; i < painting->picNum; i++){
            painting->picList[i] = list[i];
        }
    }
    ui->num->setText(QString::number(painting->picNum));
    ui->editButton->setText(tr("开始编辑"));
}
