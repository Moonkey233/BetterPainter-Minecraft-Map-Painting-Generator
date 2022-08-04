#ifndef MFINISHFORM_H
#define MFINISHFORM_H

#include <QWidget>
#include <QFileDialog>
#include <mpainting.h>
#include <QDesktopServices>

namespace Ui {
class MFinishForm;
}

class MFinishForm : public QWidget
{
    Q_OBJECT

public:
    explicit MFinishForm(MPainting *paint, QWidget *parent = nullptr);
    ~MFinishForm();

signals:
    void setIndex(int);

private slots:
    void saveExit();
    void edit();
    void begin();
    void bilibili();
    void github();
    void file();

private:
    MPainting *painting;
    Ui::MFinishForm *ui;
};

#endif // MFINISHFORM_H
