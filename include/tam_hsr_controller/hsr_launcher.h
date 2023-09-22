#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <rviz/panel.h>
#endif

#include <QPushButton>
#include <QProcess>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <unistd.h>

namespace tam_hsr_controller{
  class HSRLauncher : public rviz::Panel
  {
    Q_OBJECT
  public:
    HSRLauncher(QWidget* parent = 0);
    ~HSRLauncher() override;
    void onInitialize() override;

  public Q_SLOTS:
    void startBringUp();
    void startSlam();

  private:
    // layout
    QVBoxLayout* layout;

    // bringup
    QPushButton* button_bring_up_;

    // slam
    QLabel* label_slam_;
    QPushButton* button_slam_;

    ros::NodeHandle nh_;  // ノードハンドルを追加
    // ros::Publisher pub_;
  };
}