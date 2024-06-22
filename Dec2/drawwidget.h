#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void SetA(double a);
    void SetS(double s);
    void SetAlp(double alp);
    void MoveS();
    void ResetSquarePosition();
    void SetSystem();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    double _a = 1;
    double _alp = 0;
    double _sqe = 10;
    bool _dirty = true;
    bool _dirtysqe = true;
    int _currentIndex = 0;
    QList<QPointF> _points;
    double _currentPosition = 0.0;
    QPointF _currentPoint;
    bool _sys = true;

signals:
};

#endif // DRAWWIDGET_H
