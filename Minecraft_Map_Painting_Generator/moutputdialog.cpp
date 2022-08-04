#include "moutputdialog.h"
#include "ui_moutputdialog.h"

MOutputDialog::MOutputDialog(MPainting *paint, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MOutputDialog)
{
    ui->setupUi(this);
    painting = paint;
    ui->path->setText(painting->setting.savePath);
    ui->progressBar->setRange(0,0);
    ui->progressBar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->nameEdit->setText("MyPicture");
    //connect(ui->nameEdit, SIGNAL(editingFinished()), this, SLOT(reName()));
    connect(ui->output, SIGNAL(clicked()), this, SLOT(output()));
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(savePath()));
}

MOutputDialog::~MOutputDialog()
{
    delete ui;
}

void MOutputDialog::output(){
    bool isOk = false;
    painting->setting.fileName = ui->nameEdit->text();
    if(ui->image->isChecked()){
        painting->setting.isImage = true;
        isOk = true;
    }else{
        painting->setting.isImage = false;
    }

    if(ui->function->isChecked()){
        painting->setting.isFunction = true;
        isOk = true;
    }else{
        painting->setting.isFunction = false;
    }

    if(ui->schematic->isChecked()){
        painting->setting.isSchematic = true;
        isOk = true;
    }else{
        painting->setting.isSchematic = false;
    }

    if(isOk){
        ui->progressBar->setRange(0,1000);
        ui->progressBar->setValue(0);
        painting->writeFile(ui->progressBar);
        this->accept();
        QMessageBox::information(this, tr("提示"), tr("导出完成！"));
        emit setIndex(2);
    }else{
        QMessageBox::critical(this, tr("提示"), tr("请至少选择一种导出格式！"));
    }
}

void MOutputDialog::savePath(){
    QString path = QFileDialog::getExistingDirectory(this, "选择保存路径", QCoreApplication::applicationDirPath());
    if(path != ""){
        path += "/";
        painting->setting.savePath = path;
        ui->path->setText(path);
    }
}
