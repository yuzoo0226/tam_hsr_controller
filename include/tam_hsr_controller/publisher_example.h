#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <rviz/panel.h>
#endif

#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>


namespace tam_hsr_controller{
  class PublisherExample : public rviz::Panel
  {
    Q_OBJECT
  public:
    PublisherExample(QWidget* parent = 0);
    ~PublisherExample() override;

    void onInitialize() override;
    // void onEnable();
    // void onDisable();

  public Q_SLOTS:
    void publishMessage();

  private:
    QPushButton* publish_button_;
    QLineEdit* text_input_;
    ros::NodeHandle nh_;  // ノードハンドルを追加
    ros::Publisher pub_;
  };
}