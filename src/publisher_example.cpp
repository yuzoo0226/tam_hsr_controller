#include <rviz/panel.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <pluginlib/class_list_macros.h>
#include <tam_hsr_controller/publisher_example.h>

namespace tam_hsr_controller{
  MyRvizPanel::MyRvizPanel(QWidget* parent) : rviz::Panel(parent)
  {
    // Create a QPushButton
    publish_button_ = new QPushButton("Publish Message", this);

    // Create a ROS publisher
    pub_ = nh_.advertise<std_msgs::String>("/publish/example/message", 1);

    // Connect the button click event to the publishMessage slot
    connect(publish_button_, SIGNAL(clicked()), this, SLOT(publishMessage()));
  }

  MyRvizPanel::~MyRvizPanel() = default;

  void MyRvizPanel::onInitialize()
  {
    std::cout << "initialize" << std::endl;
  }

  void MyRvizPanel::onEnable()
  {
    std::cout << "onEnable" << std::endl;
    // show();
    // parentWidget()->show();
  }

  void MyRvizPanel::onDisable()
  {
    std::cout << "onDisable" << std::endl;
    // hide();
    // parentWidget()->hide();
  }


  void MyRvizPanel::publishMessage()
  {
    std_msgs::String msg;
    msg.data = "Hello, RViz!";
    pub_.publish(msg);
  }
}

PLUGINLIB_EXPORT_CLASS(tam_hsr_controller::MyRvizPanel, rviz::Panel)