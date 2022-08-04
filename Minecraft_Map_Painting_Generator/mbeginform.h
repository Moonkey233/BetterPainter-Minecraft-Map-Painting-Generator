#ifndef MBEGINFORM_H
#define MBEGINFORM_H

#include <QWidget>
#include "mpainting.h"
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MBeginForm;
}

class MBeginForm : public QWidget
{
    Q_OBJECT

public:
    explicit MBeginForm(MPainting *paint, QWidget *parent = nullptr);
    ~MBeginForm();

signals:
    void setIndex(int);

private slots:
    void beginEdit();
    void inputFiles();

private:
    MPainting *painting;
    Ui::MBeginForm *ui;
};

#endif // MBEGINFORM_H
