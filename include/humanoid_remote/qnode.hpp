    /**
 * @file /include/acsl_drone_ui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef HUMANOID_REMOTE_QNODE_HPP_
#define HUMANOID_REMOTE_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include <fstream>
#include <iostream>

#include <geometry_msgs/TwistStamped.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace humanoid_remote {

/*****************************************************************************
** Class
*****************************************************************************/


class QNode : public QThread {
    Q_OBJECT
public:
    QNode(int argc, char** argv );
    virtual ~QNode();
    bool init();
    void run();

    ros::Publisher pub;
    

Q_SIGNALS:
    void rosShutdown();
private:
    int init_argc;
    char** init_argv;




};

}  // namespace humanoid_remote

#endif /* HUMANOID_REMOTE_QNODE_HPP_ */
