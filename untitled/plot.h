#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

namespace Ui {
class Plot;
}

struct DataPoint
{
    DataPoint(double _t, double _U) : t(_t), U(_U) {}

    double t;
    double U;
};

struct DataLine
{
    DataLine(QColor _color, double _lineOffset) : color(_color), lineOffset(_lineOffset) {}

    QColor color;
    double lineOffset;
    std::vector<DataPoint> data;
};

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);
    ~Plot();
    void paintEvent(QPaintEvent *);

    void reset();
    void clear();

    int margin_bottom;
    int margin_left;

    double t_max;
    double U_max;

    double t_max_v;
    double U_max_v;
    double t_offset;
    double U_offset;

    double gridStep;

    void addPoint(size_t lineNumber, double t, double U);
    void addDataLine(QColor color, double lineOffset);

    void setDataLineColor(size_t lineNumber, QColor _color);

private:
    QPoint p1,p2;
    double t_offset_move;
    double U_offset_move;
    bool leftButtonPressed = false;

    void wheelEvent(QWheelEvent *event);

    void drawBackground();
    void drawBorder();
    void drawGrid();
    void drawMainGrid();
    void drawAxisText();

    std::vector<DataLine> dataLines;

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *event);

//    void timerEvent(QTimerEvent *event);
};

#endif // CANVAS_H
