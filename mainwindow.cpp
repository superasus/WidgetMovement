#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);
    m_timer = new QTimer(this);
    m_timer->setInterval(QRandomGenerator::global()->bounded(100, 1000));
    connect(m_timer, &QTimer::timeout,
            [this]{
                auto pb = new QPushButton("*", this);
                pb->setStyleSheet("QPushButton{"
                                  "background-color: aliceblue;"
                                  "border: 1px solid gray;"
                                  "border-radius: 3px;} "
                                  "QPushButton:hover {"
                                  "background-color: powderblue;} ");
                constexpr int buttonWidth = 20;
                pb->setGeometry(QRandomGenerator::global()->bounded(width() - buttonWidth),
                    QRandomGenerator::global()->bounded(100),
                    buttonWidth, buttonWidth);
                pb->show();
                auto moveTimer = new QTimer(pb);
                moveTimer->setInterval(QRandomGenerator::global()->bounded(70, 250));
                connect(moveTimer, &QTimer::timeout,
                        [pb, this]{
                            const int posShift = pb->underMouse() ? 6 : 3;
                            pb->move(pb->pos() + QPoint(0, posShift));
                            if(pb->pos().y() > height() - pb->height()) {
                                setStyleSheet("background-color: red;");
                                setWindowTitle("YOU LOSE!");
                                pb->deleteLater();
                            }
                        });
                connect(pb, &QPushButton::clicked, pb, &QPushButton::deleteLater);
                moveTimer->start();
                m_timer->setInterval(QRandomGenerator::global()->bounded(100, 1000));
            });
    m_timer->start();
}

MainWindow::~MainWindow()
{
}
