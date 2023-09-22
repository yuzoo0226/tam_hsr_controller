#include <rviz/panel.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <pluginlib/class_list_macros.h>
#include <tmc_msgs/Voice.h>
#include <tam_hsr_controller/hsr_launcher.h>


namespace tam_hsr_controller{
  HSRLauncher::HSRLauncher(QWidget* parent) : rviz::Panel(parent)
  {
    // bringup
    button_bring_up_ = new QPushButton("Start Bringup", this);
    connect(button_bring_up_, SIGNAL(clicked()), this, SLOT(startBringUp()));

    // slam
    button_slam_ = new QPushButton("Start SLAM", this);
    connect(button_slam_, SIGNAL(clicked()), this, SLOT(startSlam()));

    // パネルにウィジェットを追加
    layout = new QVBoxLayout;
    layout->addWidget(button_bring_up_);
    layout->addWidget(button_slam_);

    setLayout(layout);
  }

  HSRLauncher::~HSRLauncher() = default;

  void HSRLauncher::onInitialize()
  {
    std::cout << "initialize" << std::endl;
  }

  void HSRLauncher::startBringUp(){
    // roslaunchコマンドを呼び出してlaunchファイルを実行
    ROS_INFO("start bring_up.launch.");

    QProcess process_bring_up;
    process_bring_up.start("roslaunch tam_hsr_utils bring_up.launch ");
    sleep(1);  // 起動安定化のために一定秒sleep
    process_bring_up.kill();

  }

  void HSRLauncher::startSlam(){
    // roslaunchコマンドを呼び出してlaunchファイルを実行
    ROS_INFO("start map.launch.");

    QProcess process_slam;
    process_slam.start("roslaunch tam_slam map.launch map_name:=hma_room05");
    sleep(1);  // 起動安定化のために一定秒sleep
    process_slam.kill();

  }

}

PLUGINLIB_EXPORT_CLASS(tam_hsr_controller::HSRLauncher, rviz::Panel)