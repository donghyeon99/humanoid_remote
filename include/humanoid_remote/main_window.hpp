/**
 * @file /include/acsl_drone_ui/main_window.hpp
 *
 * @brief Qt based gui for acsl_drone_ui.
 *
 * @date November 2010
 **/
#ifndef HUMANOID_REMOTE_MAIN_WINDOW_H
#define HUMANOID_REMOTE_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <QKeyEvent>
#include <string>

/*****************************************************************************
** Namespace
*****************************************************************************/
using namespace std;
using namespace cv;
namespace humanoid_remote {


/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */

typedef struct _DirectionXYYaw
{
    double x = 0;
    double y = 0;
    double yaw = 0;

    _DirectionXYYaw operator = (_DirectionXYYaw& p) {
         x = p.x;
         y = p.y;
         yaw  = p.yaw;

         return *this;
     }
}DIR3;


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event); // Overloaded function

public Q_SLOTS:
    void keyPressEvent(QKeyEvent *e);

    void timerLoop();

private:
    Ui::MainWindowDesign ui;
    QNode qnode;
    int m_cnt;
    DIR3 mStateHu1;
    DIR3 mStateHu2;

    QTimer *m_timer;

};

}  // namespace humanoid_remote

#endif // HUMANOID_REMOTE_MAIN_WINDOW_H
