#ifndef MSETTINGDIALOG_H
#define MSETTINGDIALOG_H

#include <QDialog>
#include "mpainting.h"
#include <QColorDialog>

namespace Ui {
class MSettingDialog;
}

class MSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MSettingDialog(MPainting *paint, QWidget *parent = nullptr);
    void setUi();
    ~MSettingDialog();

private slots:
    void submit();
    void autoSet();
    void planeSet();
    void cubeSet();
    void reHeight();
    void reM1();
    void reM2();
    void reX();
    void reZ();
    void selectColor();

private:
    MPainting *painting;
    Ui::MSettingDialog *ui;
};

#endif // MSETTINGDIALOG_H
