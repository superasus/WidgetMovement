#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);
    m_timer = new QTimer();
    m_timer->setInterval(QRandomGenerator::global()->bounded(100, 1000));
    connect(m_timer, &QTimer::timeout,
            [wnd = this]{
                auto pb = new QPushButton("*", wnd);
                pb->setStyleSheet("QPushButton{"
                                  "background-color: aliceblue;"
                                  "border: 1px solid gray;"
                                  "border-radius: 3px;} "
                                  "QPushButton:hover {"
                                  "background-color: powderblue;} ");
                int buttonWidth = 20;
                pb->setGeometry(QRandomGenerator::global()->bounded(wnd->width() - buttonWidth),
                    QRandomGenerator::global()->bounded(100),
                    buttonWidth, buttonWidth);
                pb->show();
                auto moveTimer = new QTimer(pb);
                moveTimer->setInterval(QRandomGenerator::global()->bounded(70, 250));
                connect(moveTimer, &QTimer::timeout,
                        [pb, wnd]{
                            int posShift = 3;
                            if(pb->underMouse()) {
                                posShift *= 2;
                            }
                            pb->move(pb->pos() + QPoint(0, posShift));
                            if(pb->pos().y() > wnd->height() - pb->height()) {
                                wnd->setStyleSheet("background-color: red;");
                                wnd->setWindowTitle("YOU LOSE!");
                                pb->deleteLater();
                            }
                        });
                connect(pb, &QPushButton::clicked,
                        [pb]{
                            pb->deleteLater();
                        });
                moveTimer->start();
                wnd->m_timer->setInterval(QRandomGenerator::global()->bounded(100, 1000));
            });
    m_timer->start();
}

MainWindow::~MainWindow()
{
    delete m_timer;
}
