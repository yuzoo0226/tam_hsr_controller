# よくあるissue

- 以下のエラーが出た場合
  - headerファイルのインポートで足りないものがある？
    - headerファイルのインポートの中で，足りないものがあれば自動でインポート先を決定するコードを書いているが，Rvizで読み込む際はそれがうまく機能していない
    - ビルドではエラーが出ず，実行中にのみ出るので，注意が必要

```bash
[ERROR] [1695199729.485754610]: PluginlibFactory: The plugin for class 'tam_hsr_controller/HSRTalker' failed to load.  Error: Failed to load library /home/yuga/ros_ws/hsrc_ws/devel/lib/libhsr_talker_lib.so. Make sure that you are calling the PLUGINLIB_EXPORT_CLASS macro in the library code, and that names are consistent between this macro and your XML. Error string: Could not load library (Poco exception = /home/yuga/ros_ws/hsrc_ws/devel/lib/libhsr_talker_lib.so: undefined symbol: _ZN18tam_hsr_controller16PublisherExampleD1Ev)
```
