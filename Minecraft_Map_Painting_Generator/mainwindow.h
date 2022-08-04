#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "data.h"
#include "ui_mainwindow.h"
#include "mpainting.h"
#include "mbeginform.h"
#include "meditform.h"
#include "mfinishform.h"
#include "msettingdialog.h"
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MBeginForm *beginWindow;
    MEditForm *editWindow;
    MFinishForm *finishWindow;
    QStackedWidget *stackWidget;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
