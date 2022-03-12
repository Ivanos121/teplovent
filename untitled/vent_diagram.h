#ifndef VENT_DIAGRAM_H
#define VENT_DIAGRAM_H

#include <QWidget>

namespace Ui {
class vent_diagram;
}

class vent_diagram : public QWidget
{
    Q_OBJECT

public:
    explicit vent_diagram(QWidget *parent = nullptr);
    ~vent_diagram();

private:
    Ui::vent_diagram *ui;
};

#endif // VENT_DIAGRAM_H
