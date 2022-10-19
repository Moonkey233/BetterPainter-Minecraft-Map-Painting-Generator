#include "mfinishform.h"
#include "ui_mfinishform.h"

MFinishForm::MFinishForm(MPainting *paint, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MFinishForm)
{
    painting = paint;
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(saveExit()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(edit()));
    connect(ui->beginButton, SIGNAL(clicked()), this, SLOT(begin()));
    connect(ui->githubButton, SIGNAL(clicked()), this, SLOT(github()));
    connect(ui->bilibiliButton, SIGNAL(clicked()), this, SLOT(bilibili()));
    connect(ui->fileButton, SIGNAL(clicked()), this, SLOT(file()));
}

MFinishForm::~MFinishForm()
{
    delete ui;
}

void MFinishForm::saveExit(){
    exit(0);
}

void MFinishForm::edit(){
    emit setIndex(1);
}

void MFinishForm::begin(){
    emit setIndex(0);
}

void MFinishForm::github(){
    QDesktopServices::openUrl(QUrl("https://github.com/Moonkey233/Minecraft-Map-Painting-Generator", QUrl::TolerantMode));
}

void MFinishForm::bilibili(){
    QDesktopServices::openUrl(QUrl("https://space.bilibili.com/215177187", QUrl::TolerantMode));
}

void MFinishForm::file(){
    QDesktopServices::openUrl("file:" + painting->setting.savePath);
}
