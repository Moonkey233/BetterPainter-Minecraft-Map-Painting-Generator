#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    MPainting *painting = new MPainting;
    beginWindow = new MBeginForm(painting);
    editWindow = new MEditForm(painting);
    finishWindow = new MFinishForm(painting);
    stackWidget = new QStackedWidget;
    stackWidget->addWidget(beginWindow);
    stackWidget->addWidget(editWindow);
    stackWidget->addWidget(finishWindow);
    this->setCentralWidget(stackWidget);
    stackWidget->setCurrentIndex(0);

    connect(beginWindow, &MBeginForm::setIndex, [this](int n){
       stackWidget->setCurrentIndex(n);
       editWindow->setInfo();
    });
    connect(editWindow, &MEditForm::setIndex, [this](int n){
       stackWidget->setCurrentIndex(n);
    });
    connect(finishWindow, &MFinishForm::setIndex, [this](int n){
       stackWidget->setCurrentIndex(n);
    });
}

MainWindow::~MainWindow(){
    delete ui;
}
