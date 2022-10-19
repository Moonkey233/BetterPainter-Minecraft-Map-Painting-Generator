#ifndef MOUTPUTDIALOG_H
#define MOUTPUTDIALOG_H

#include <QDialog>
#include "mpainting.h"
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MOutputDialog;
}

class MOutputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MOutputDialog(MPainting *paint, QWidget *parent = nullptr);
    ~MOutputDialog();

signals:
    void setIndex(int);

private slots:
    void output();
    void savePath();

private:
    MPainting *painting;
    Ui::MOutputDialog *ui;
};

#endif // MOUTPUTDIALOG_H
