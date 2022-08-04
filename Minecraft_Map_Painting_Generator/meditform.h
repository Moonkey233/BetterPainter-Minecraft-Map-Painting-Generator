#ifndef MEDITFORM_H
#define MEDITFORM_H

#include <QWidget>
#include "mpainting.h"
#include "msettingdialog.h"
#include "moutputdialog.h"

namespace Ui {
class MEditForm;
}

class MEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit MEditForm(MPainting *paint, QWidget *parent = nullptr);
    ~MEditForm();
    void setInfo();

signals:
    void setIndex(int);

private slots:
    void reSelect();
    void generate();
    void setting();
    void output();

private:
    Ui::MEditForm *ui;
    MSettingDialog *settingWindow;
    MOutputDialog *outputWindow;
    MPainting *painting;
};

#endif // MEDITFORM_H
