#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <rviz/panel.h>
#endif

#include <QPushButton>

namespace tam_hsr_controller{
  class MyRvizPanel : public rviz::Panel
  {
    Q_OBJECT
  public:
    MyRvizPanel(QWidget* parent = 0);
    ~MyRvizPanel() override;

    void onInitialize() override;
    void onEnable();
    void onDisable();

  public Q_SLOTS:
    void publishMessage();

  private:
    QPushButton* publish_button_;
    ros::NodeHandle nh_;  // ノードハンドルを追加
    ros::Publisher pub_;
  };
}