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
//    foutHu1.open("foutHu1.txt");
//    foutHu2.open("foutHu2.txt");
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerLoop()));
    m_timer->start(100);
}

MainWindow::~MainWindow()
{
    foutHu1.close();
    foutHu2.close();
}

void MainWindow::timerLoop()
{
    static int i = 0;
    geometry_msgs::TwistStamped data;
    if(Recflag == true)
    {
        data.twist.linear.x = mRecotdHu1[i].x;
        data.twist.linear.y = mRecotdHu1[i].y;
        data.twist.linear.z = mRecotdHu1[i].yaw;
        data.twist.angular.x = mRecotdHu2[i].x;
        data.twist.angular.y = mRecotdHu2[i].y;
        data.twist.angular.z = mRecotdHu2[i].yaw;
        i++;
        if(i >= mRecotdHu1.size())
            i=0;
    }
    else
    {
        i=0;
        data.twist.linear.x = mStateHu1.x;
        data.twist.linear.y = mStateHu1.y;
        data.twist.linear.z = mStateHu1.yaw;
        data.twist.angular.x = mStateHu2.x;
        data.twist.angular.y = mStateHu2.y;
        data.twist.angular.z = mStateHu2.yaw;
    }
    qnode.pub.publish(data);
}

void MainWindow::readRecordHu1()
{
    fstream fs;
    string str_buf;
    mRecotdHu1.clear();
    fs.open("foutHu11.txt",ios::in);
    int cnt = 0;
    DIR3 hu1;
    vector<int> data;
    while(!fs.eof()){
        getline(fs, str_buf,',');
        if(atoi(str_buf.c_str()) != 0 || str_buf == "0")
        {
            data.push_back(stoi(str_buf));
            cnt++;
            if(cnt == 3)
            {
                data.clear();
                hu1.x = data[0];
                hu1.y = data[1];
                hu1.yaw = data[2];
                mRecotdHu1.push_back(hu1);
                cnt = 0;
            }
        }
    }
    fs.close();
    cout<<"mRecotdHu1.size(): "<<mRecotdHu1.size()<<endl;
}
void MainWindow::readRecordHu2()
{
    fstream fs;
    string str_buf;
    mRecotdHu2.clear();
    fs.open("foutHu22.txt",ios::in);
    int cnt = 0;
    DIR3 hu1;
    vector<int> data;
    while(!fs.eof()){
        getline(fs, str_buf,',');
        if(atoi(str_buf.c_str()) != 0 || str_buf == "0")
        {
            data.push_back(stoi(str_buf));
            cnt++;
            if(cnt == 3)
            {
                data.clear();
                hu1.x = data[0];
                hu1.y = data[1];
                hu1.yaw = data[2];
                mRecotdHu2.push_back(hu1);
                cnt = 0;
            }
        }
    }
    fs.close();
    cout<<"mRecotdHu2.size(): "<<mRecotdHu2.size()<<endl;
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
        ui.textEdit->append("X");
        mStateHu1.x = -1;
    }
    else if (e->key() == Qt::Key_E)
    {
        ui.textEdit->append("E");

        mStateHu1.yaw = 1;
    }
    else if (e->key() == Qt::Key_Q)
    {
        ui.textEdit->append("Q");
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
    foutHu1.close();
    foutHu2.close();
    QMainWindow::closeEvent(event);
}


void MainWindow::on_pushButton_start_clicked()
{
    Recflag = true;
    ui.lineEdit_record->setStyleSheet("QLineEdit {background-color: blue;}");
}
void MainWindow::on_pushButton_reset_clicked()
{
    Recflag = false;
    ui.lineEdit_record->setStyleSheet("QLineEdit {background-color: white;}");
}


void MainWindow::on_pushButton_read_clicked()
{
    readRecordHu1();
    readRecordHu2();
    ui.textEdit_record->append("read data");
}

void MainWindow::recordLoop()
{
    foutHu1 << ","<<mStateHu1.x <<","<<mStateHu1.y<<","<<mStateHu1.yaw<<","<<endl;
    foutHu2 << ","<<mStateHu2.x <<","<<mStateHu2.y<<","<<mStateHu2.yaw<<","<<endl;
}

void MainWindow::on_pushButton_record_clicked()
{
    ui.lineEdit_recording->setStyleSheet("QLineEdit {background-color: red;}");

    m_REC = new QTimer(this);
    connect(m_REC, SIGNAL(timeout()), this, SLOT(recordLoop()));
    foutHu1.open("foutHu11.txt");
    foutHu2.open("foutHu22.txt");
    m_REC->start(100);
}
void MainWindow::on_pushButton_stop_clicked()
{
    ui.lineEdit_recording->setStyleSheet("QLineEdit {background-color: white;}");

    foutHu1.close();
    foutHu2.close();
    m_REC->stop();
}


} // namespace humanoid_remote
