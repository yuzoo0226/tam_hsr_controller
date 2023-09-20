# TAM_HSR_CONTROLLER

- GUIプラグイン

## Rvizのプラグインを追加

- このパッケージをbuildすることで，rvizに複数のプラグインが追加されます．

## How to setup

- 仮想環境はhsr_environmentsを参照
  - いくつか追加でインストールする必要がある

```bash
singularity shell --nv --fakeroot --writable env/sandbox_hsrb
apt update
apt install qt5-default
```

## プラグインの追加方法

### CMakeLists

- 必要な手順は2つ

- 以下の行を参考に，`publisher_example_lib`の部分を作成したプログラム名に変更
  - `作成したプログラム名_lib`となる．（ビルド後の名前として定義するためっぽい？）
  - headerファイルも追記する必要があることに注意

```cmake
# publishe example
add_library(publisher_example_lib SHARED src/publisher_example.cpp include/tam_hsr_controller/publisher_example.h)
set_target_properties(publisher_example_lib PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_include_directories(publisher_example_lib PRIVATE "${OGRE_PREFIX_DIR}/include")
target_link_libraries(publisher_example_lib ${catkin_LIBRARIES})
```

- headerファイルを追記

```cmake
# ヘッダーファイルを追記
set(HEADERS
  include/tam_hsr_controller/publisher_example.h
)
```

### Plugin.xml

- プログラム名に応じて変更

```xml
<library path="libpublisher_example_lib">
    <class name="tam_hsr_controller/PublisherExample" type="tam_hsr_controller::PublisherExample" base_class_type="rviz::Panel">
        <description>
            A custom RViz panel for publishing messages to a topic.
        </description>
    </class>
</library>
```
