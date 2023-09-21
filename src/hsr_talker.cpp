#include <rviz/panel.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <pluginlib/class_list_macros.h>
#include <tmc_msgs/Voice.h>
#include <tam_hsr_controller/hsr_talker.h>


namespace tam_hsr_controller{
  HSRTalker::HSRTalker(QWidget* parent) : rviz::Panel(parent)
  {
    // Create a QPushButton
    publish_button_ = new QPushButton("speak", this);
    button_speech_recog_ = new QPushButton("start speech recognition server", this);

    // テキスト入力ボックスを作成
    text_input_ = new QLineEdit(this);
    label_text_input_ = new QLabel("talk txt", this);

    // Create a ROS publisher
    pub_ = nh_.advertise<tmc_msgs::Voice>("/talk_request", 1);

    // Connect the button click event to the publishMessage slot
    connect(publish_button_, SIGNAL(clicked()), this, SLOT(publishMessage()));
    connect(button_speech_recog_, SIGNAL(clicked()), this, SLOT(startSpeechRecogServer()));


    // ラジオボタンを作成
    radio_ja_ = new QRadioButton("Japanese", this);
    radio_en_ = new QRadioButton("English", this);
    QButtonGroup* radio_group = new QButtonGroup(this);
    radio_group->addButton(radio_ja_);
    radio_group->addButton(radio_en_);
    // label_ja; = new QLabel("Japanese", this);
    // label_en; = new QLabel("English", this);

    // パネルにウィジェットを追加
    layout = new QVBoxLayout;
    layout_text_input = new QHBoxLayout;

    layout_text_input->addWidget(label_text_input_);
    layout_text_input->addWidget(text_input_);

    layout->addWidget(radio_ja_);
    layout->addWidget(radio_en_);
    layout->addLayout(layout_text_input);
    layout->addWidget(publish_button_);
    layout->addWidget(button_speech_recog_);
    setLayout(layout);
  }

  HSRTalker::~HSRTalker() = default;

  void HSRTalker::onInitialize()
  {
    std::cout << "initialize" << std::endl;
  }

  void HSRTalker::publishMessage()
  {
    tmc_msgs::Voice msg;

    // 発話内容決定
    msg.sentence = text_input_->text().toStdString();

    // 言語選択
    bool language = (radio_ja_->isChecked());
    if (language){
      msg.language = 0;
    }
    else{
      msg.language = 1;
    }
    pub_.publish(msg);
  }

  void HSRTalker::startSpeechRecogServer(){
    // roslaunchコマンドを呼び出してlaunchファイルを実行
    ROS_INFO("Try to launch file started.");

    QProcess process;
    process.start("roslaunch tam_speech_recog speech_recognition_server.launch ");
    process.start("roslaunch tam_hsr_utils bring_up.launch ");


    if (process.waitForStarted() && process.waitForFinished())
    {
      ROS_INFO("Launch file started successfully.");
    }
    else
    {
      ROS_ERROR("Failed to start launch file.");
    }
  }

}

PLUGINLIB_EXPORT_CLASS(tam_hsr_controller::HSRTalker, rviz::Panel)