#include <rviz/panel.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <pluginlib/class_list_macros.h>
#include <tam_hsr_controller/publisher_example.h>

namespace tam_hsr_controller{
  PublisherExample::PublisherExample(QWidget* parent) : rviz::Panel(parent)
  {
    // Create a QPushButton
    publish_button_ = new QPushButton("Publish Message", this);

    // テキスト入力ボックスを作成
    text_input_ = new QLineEdit(this);

    // Create a ROS publisher
    pub_ = nh_.advertise<std_msgs::String>("/publish/example/message", 1);

    // Connect the button click event to the publishMessage slot
    connect(publish_button_, SIGNAL(clicked()), this, SLOT(publishMessage()));

    // パネルにウィジェットを追加
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(text_input_);
    layout->addWidget(publish_button_);
    setLayout(layout);
  }

  PublisherExample::~PublisherExample() = default;

  void PublisherExample::onInitialize()
  {
    std::cout << "initialize" << std::endl;
  }

  void PublisherExample::publishMessage()
  {
    std_msgs::String msg;
    msg.data = text_input_->text().toStdString();
    pub_.publish(msg);
  }
}

PLUGINLIB_EXPORT_CLASS(tam_hsr_controller::PublisherExample, rviz::Panel)