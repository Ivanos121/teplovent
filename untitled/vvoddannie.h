#ifndef VVODDANNIE_H
#define VVODDANNIE_H

#include <QWidget>

namespace Ui {
class vvoddannie;
}

class vvoddannie : public QWidget
{
    Q_OBJECT

public:
    explicit vvoddannie(QWidget *parent = nullptr);
    ~vvoddannie();
    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::vvoddannie *ui;
};

#endif // VVODDANNIE_H
