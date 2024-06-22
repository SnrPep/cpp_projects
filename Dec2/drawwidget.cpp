#include "drawwidget.h"

#include <QPainter>
#include <cmath>
#include <iostream>

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget{parent}
{}

void DrawWidget::SetA(double a)
{
    _a = a;
    _dirty = true;
    _dirtysqe = true;
}

void DrawWidget::SetAlp(double alp)
{
    _alp = alp;
    _dirtysqe = true;
    _dirty = true;
}

void DrawWidget::SetS(double s)
{
    _sqe = s;
    _dirtysqe = true;
}

void DrawWidget::MoveS()
{
    double stepSize = 1.0;

    if (_points.isEmpty()) return;

    double distanceToMove = stepSize;

    while (distanceToMove > 0.0)
    {
        if (_currentPosition >= _points.size() - 1)
        {
            _currentPosition = 0;
        }

        int currentIndex = static_cast<int>(_currentPosition);
        double fraction = _currentPosition - currentIndex;

        QPointF start = _points[currentIndex];
        QPointF end = _points[currentIndex + 1];

        double segmentLength = QLineF(start, end).length();
        double remainingDistanceOnSegment = segmentLength * (1.0 - fraction);

        if (distanceToMove < remainingDistanceOnSegment)
        {
            _currentPosition += distanceToMove / segmentLength;
            int newCurrentIndex = static_cast<int>(_currentPosition);
            fraction = _currentPosition - newCurrentIndex;
            start = _points[newCurrentIndex];
            end = _points[newCurrentIndex + 1];
            _currentPoint = start + fraction * (end - start);
            distanceToMove = 0.0;
        }
        else
        {
            distanceToMove -= remainingDistanceOnSegment;
            _currentPosition = currentIndex + 1;
        }
    }

    _dirtysqe = true;
    update();
}

void DrawWidget::ResetSquarePosition()
{
    _currentPosition = 0.0;
    _dirtysqe = true;
    update();
}

void DrawWidget::SetSystem()
{
    _sys = !_sys;
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    //создаем отрисовщик
    QWidget::paintEvent(event);
    QPainter painter(this);

    //белый фон
    painter.fillRect(0, 0, width(), height(), QBrush(QColor(255, 255, 255)));

    //найдем центр
    auto center = QPointF(width() / 2.f, height() / 2.f);

    if (_sys)
    {
        //нарисуем сетку
        {
            painter.setPen(QPen(QBrush(QColor(127, 127, 127)), 1));
            painter.drawLine(center.x(), 0, center.x(), height());
            painter.drawLine(0, center.y(), width(), center.y());

            auto step = 10;
            int boldStep = 5;
            for (int i = 1; i * step < center.x(); i++)
            {
                painter.setPen(QPen(QBrush(QColor(127, 127, 127)), i % boldStep == 0 ? 0.5 : 0.25));
                painter.drawLine(center.x() + i * step, 0, center.x() + i * step, height());
                painter.drawLine(center.x() - i * step, 0, center.x() - i * step, height());
            }

            for (int i = 1; i * step < center.y(); i++)
            {
                painter.setPen(QPen(QBrush(QColor(127, 127, 127)), i % boldStep == 0 ? 0.5 : 0.25));
                painter.drawLine(0, center.y() + i * step, width(), center.y() + i * step);
                painter.drawLine(0, center.y() - i * step, width(), center.y() - i * step);
            }
        }

        // Статичные обозначения
        painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 1));
        painter.drawText(center.x() + 5, 15, "y");
        painter.drawText(width() - 15, center.y() - 5, "x");
        painter.drawText(center.x() + 5, center.y() - 5, "0");

        // Обозначения на осях
        if (_alp != 0)
        {
            int labelStep = 1;
            for (int i = labelStep; i < width() / 2; i += labelStep)
            {
                painter.drawText(center.x() + i * _alp - 5, center.y() - 5, QString::number(round(_alp / _a) * i));
                painter.drawText(center.x() - i * _alp - 5, center.y() - 5, QString::number(-round(_alp / _a) * i));
            }
            for (int i = labelStep; i < height() / 2; i += labelStep)
            {
                painter.drawText(center.x() + 5, center.y() - i * _alp + 5, QString::number(round(_alp / _a) * i));
                painter.drawText(center.x() + 5, center.y() + i * _alp + 5, QString::number(-round(_alp / _a) * i));
            }
        }
    }
    else
    {
        // Круги и обозначения на осях
        {
            int numCircles = 5;
            int radiusStep = width() / (2 * numCircles);

            for (int i = 1; i <= numCircles; ++i)
            {
                int radius = i * radiusStep;
                painter.setPen(QPen(QBrush(QColor(127, 127, 127)), 1, Qt::DashLine));
                painter.drawEllipse(center, radius, radius);

                QString radiusLabel = QString::number(i / _a);
                painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 1));
                painter.drawText(center.x() + radius, center.y(), radiusLabel);
            }

            painter.setPen(QPen(QBrush(QColor(127, 127, 127)), 1));
            for (int i = 0; i < 360; i += 30) {
                double angle = i * M_PI / 180.0;
                double x = center.x() + (width() / 2) * cos(angle);
                double y = center.y() - (width() / 2) * sin(angle);
                painter.drawLine(center.x(), center.y(), x, y);
                QString angleLabel = QString::number(i) + "°";
                painter.drawText(x, y, angleLabel);
            }
        }

        // Статичные обозначения
        painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 1));
        painter.drawText(center.x() + 5, 15, "y");
        painter.drawText(width() - 15, center.y() - 5, "x");
        painter.drawText(center.x() + 5, center.y() - 5, "0");
    }

    // Линия
    if (_alp != 0)
    {
        if (_dirty)
        {
            _dirty = false;
            _points.clear();

            double step = 0.01;

            for (auto t = M_PI_4; ; t += step)
            {
                auto sin = qSin(t);
                auto cos = qCos(t);
                auto r = (3 * _alp * _a * sin * cos) / (sin * sin * sin + cos * cos * cos);

                _points.append(QPointF(r * cos + center.x(), -r * sin + center.y()));
                _points.emplace(0, QPointF(r * qCos(2 * M_PI_4 - t) + center.x(), -r * qSin(2 * M_PI_4 - t) + center.y()));

                if ((abs(r * qCos(2 * M_PI_4 - t)) > center.x() || abs(r * qSin(2 * M_PI_4 - t)) > center.y()) && t > M_PI_2)
                {
                    break;
                }
            }
        }

        painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 3));
        painter.drawPolyline(QPolygonF(_points));
    }

    // Квадрат
    if (_dirtysqe)
    {
        _dirtysqe = false;
        if (!_points.empty())
        {
            double a = _sqe;
            QPointF squareTopLeft = _currentPoint - QPointF(a / 2, a / 2);
            painter.fillRect(squareTopLeft.x(), squareTopLeft.y(), a, a, QBrush(QColor(0, 0, 255)));
        }
    }


    painter.end();
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    _dirtysqe = true;
    _dirty = true;
    QWidget::resizeEvent(event);
}
