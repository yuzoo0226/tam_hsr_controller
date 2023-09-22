cmake_minimum_required(VERSION 3.0.2)
project(tam_hsr_controller)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -DEIGEN_RUNTIME_NO_MALLOC")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fno-asm")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

find_package(Qt5 COMPONENTS REQUIRED Core Widgets)
set(QT_LIBRARIES Qt5::Widgets)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  rviz
  tmc_msgs
  Qt5Widgets
  class_loader
  pluginlib
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES tam_hsr_controller
  CATKIN_DEPENDS roscpp rospy rviz class_loader pluginlib tmc_msgs
)

#############################################################
##                         Library                         ##
#############################################################

# Qt settings
add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)


#############################################################
##                          Build                          ##
#############################################################

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
link_directories(${catkin_LIBRARY_DIRS})

#############################################################
##  プラグインを追加するたびに，以下の4行をコピペし，先頭部分を変更  ##
#############################################################

# publishe example
add_library(publisher_example_lib SHARED src/publisher_example.cpp include/tam_hsr_controller/publisher_example.h)
set_target_properties(publisher_example_lib PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_include_directories(publisher_example_lib PRIVATE "${OGRE_PREFIX_DIR}/include")
target_link_libraries(publisher_example_lib ${catkin_LIBRARIES})

# talker
add_library(hsr_talker_lib SHARED src/hsr_talker.cpp include/tam_hsr_controller/hsr_talker.h)
set_target_properties(hsr_talker_lib PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_include_directories(hsr_talker_lib PRIVATE "${OGRE_PREFIX_DIR}/include")
target_link_libraries(hsr_talker_lib ${catkin_LIBRARIES})

# launcher
add_library(hsr_launcher_lib SHARED src/hsr_launcher.cpp include/tam_hsr_controller/hsr_launcher.h)
set_target_properties(hsr_launcher_lib PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_include_directories(hsr_launcher_lib PRIVATE "${OGRE_PREFIX_DIR}/include")
target_link_libraries(hsr_launcher_lib ${catkin_LIBRARIES})

#############################################################
##                         Install                         ##
#############################################################
install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
# install(DIRECTORY icons DESTINATION share/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(TARGETS publisher_example_lib hsr_talker_lib hsr_launcher_lib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
