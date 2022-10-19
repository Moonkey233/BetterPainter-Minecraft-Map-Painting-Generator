#include "meditform.h"
#include "ui_meditform.h"

MEditForm::MEditForm(MPainting *paint, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MEditForm)
{
    painting = paint;
    settingWindow = new MSettingDialog(painting);
    outputWindow = new MOutputDialog(painting);
    ui->setupUi(this);
    ui->progressBar->setRange(0, 0);
    //ui->progressBar->setFormat(QString::fromLocal8Bit("%f%").arg(QString::number(value, 'f', f)));
    ui->progressBar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    //ui->progressBar->set
    ui->outputButton->setEnabled(false);
    connect(ui->selectButton, SIGNAL(clicked()), this, SLOT(reSelect()));
    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->settingButton, SIGNAL(clicked()), this, SLOT(setting()));
    connect(ui->outputButton, SIGNAL(clicked()), this, SLOT(output()));
    connect(outputWindow, &MOutputDialog::setIndex, [this](int n){
       emit setIndex(n);
    });
}

MEditForm::~MEditForm()
{
    delete ui;
}

void MEditForm::reSelect(){
    emit setIndex(0);
}

void MEditForm::generate(){
    ui->progressBar->setRange(0,1000);
    ui->progressBar->setValue(0);
    painting->generator(ui->progressBar);
    ui->outputButton->setEnabled(true);
    ui->progressBar->setRange(0,0);
    QMessageBox::information(this, tr("提示"), tr("生成完成！"));
}

void MEditForm::setting(){
    //settingWindow->setModal(true);
    settingWindow->setUi();
    settingWindow->exec();
    setInfo();
}

void MEditForm::output(){
    outputWindow->exec();
}

void MEditForm::setInfo(){
    QString space, type, dither, edition, editionID, mode, high;
    if(painting->setting.colorSpace == 0)
        space = "RGB";
    else if(painting->setting.colorSpace == 1)
        space = "RGB Plus";
    else if(painting->setting.colorSpace == 2)
        space = "HSV";
    else if(painting->setting.colorSpace == 3)
        space = "Lab";
    else
        space = "Lab Plus";

    if(painting->setting.colorType == 0)
        type = tr("彩色");
    else if(painting->setting.colorType == 1)
        type = tr("灰阶");
    else
        type = tr("黑白");

    dither = painting->setting.isDither ? tr("启用") : tr("禁用");

    edition = painting->setting.isBedrock ? tr("基岩版") : tr("Java版");

    if(painting->setting.edition == 0)
        editionID = tr("1.18及之后");
    else
        editionID = tr("1.18之前");

    if(painting->setting.isPlane){
        mode = tr("平面像素画");
        high = QString::number(painting->setting.minHeight);
    }
    else{
        mode = tr("立体像素画");
        high = QString::number(painting->setting.minHeight) + " " + tr("到") + " " + QString::number(painting->setting.maxHeight);
    }

    QString info = "\n" + tr("色差算法：") + space + "      " + tr("颜色模式：") + type + "      " + tr("抖动仿色：") + dither +
            "\n\n" + tr("平台：") + edition + "      " + tr("版本：") + editionID + "      " + tr("立体模式：") + mode +
            "\n\n" + tr("生成高度：") + high + "      " + tr("起始X坐标：") + QString::number(painting->setting.beginX) +
            "      " + tr("起始Z坐标：") + QString::number(painting->setting.beginZ);
    ui->Info->setText(info);
}
