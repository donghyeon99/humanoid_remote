/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/humanoid_remote/main_window.hpp"
#include "geometry_msgs/TwistStamped.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace humanoid_remote
{
    extern bool isRecv;

    using namespace Qt;

    /*****************************************************************************
    ** Implementation [MainWindow]
    *****************************************************************************/

    MainWindow::MainWindow(int argc, char **argv, QWidget *parent)
        : QMainWindow(parent), qnode(argc, argv)
    {
        ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

        QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
        qnode.init();

        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(timerLoop()));
        m_timer->start(20);
    }
 
    MainWindow::~MainWindow() {}

    void MainWindow::timerLoop()
    {
        geometry_msgs::TwistStamped data;
        data.twist.linear.x = mStateHu1.x;
        data.twist.linear.y = mStateHu1.y;
        data.twist.linear.z = mStateHu1.yaw;
        data.twist.angular.x = mStateHu2.x;
        data.twist.angular.y = mStateHu2.y;
        data.twist.angular.z = mStateHu2.yaw;
        qnode.pub.publish(data);
    }

    void MainWindow::keyPressEvent(QKeyEvent *e)
    {
        if (e->key() == Qt::Key_W) // hu1
        {
            ui.textEdit->append("W");
            mStateHu1.x = 1;
        }
        else if (e->key() == Qt::Key_A)
        {
            ui.textEdit->append("A");
            mStateHu1.y = 1;
        }
        else if (e->key() == Qt::Key_S)
        {
            ui.textEdit->append("S");
            DIR3 clear;
            mStateHu1 = clear;
        }
        else if (e->key() == Qt::Key_D)
        {
            ui.textEdit->append("D");
            mStateHu1.y = -1;
        }
        else if (e->key() == Qt::Key_X)
        {
            mStateHu1.x = -1;
        }
        else if (e->key() == Qt::Key_E)
        {
            mStateHu1.yaw = 1;
        }
        else if (e->key() == Qt::Key_Q)
        {
            mStateHu1.yaw = -1;
        }

        // ################# hu2 #################
        else if (e->key() == Qt::Key_I) 
        {
            ui.textEdit->append("I");
            mStateHu2.x = 1;
        }
        else if (e->key() == Qt::Key_J)
        {
            ui.textEdit->append("J");
            mStateHu2.y = 1;
        }
        else if (e->key() == Qt::Key_K)
        {
            ui.textEdit->append("K");
            DIR3 clear;
            mStateHu2 = clear;
        }
        else if (e->key() == Qt::Key_L)
        {
            ui.textEdit->append("L");
            mStateHu2.y = -1;
        }
        else if (e->key() == Qt::Key_M)
        {
            ui.textEdit->append("M");
            mStateHu2.x = -1;
        }
        else if (e->key() == Qt::Key_O)
        {
            ui.textEdit->append("O");
            mStateHu2.yaw = 1;
        }
        else if (e->key() == Qt::Key_U)
        {
            ui.textEdit->append("U");
            mStateHu2.yaw = -1;
        }

        else if (e->key() == Qt::Key_C)
        {
            ui.pushButton_clear->clicked();
        }

    }

    void MainWindow::closeEvent(QCloseEvent *event)
    {
        QMainWindow::closeEvent(event);
    }

} // namespace humanoid_remote
