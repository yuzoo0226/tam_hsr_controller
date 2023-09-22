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
  class HSRTalker : public rviz::Panel
  {
    Q_OBJECT
  public:
    HSRTalker(QWidget* parent = 0);
    ~HSRTalker() override;
    void onInitialize() override;

  public Q_SLOTS:
    void publishMessage();
    void startSpeechRecogServer();


  private:
    // 送信ボタン
    QPushButton* publish_button_;

    // 発話内容入力エディタ
    QLineEdit* text_input_;
    QLabel* label_text_input_;
    QHBoxLayout* layout_text_input;

    // 言語選択ラジオボタン
    QRadioButton* radio_en_;
    QRadioButton* radio_ja_;
    // QLabel* label_ja;
    // QLabel* label_en;

    // layout
    QVBoxLayout* layout;

    // speech recog server
    QPushButton* button_speech_recog_;

    ros::NodeHandle nh_;  // ノードハンドルを追加
    ros::Publisher pub_;
  };
}