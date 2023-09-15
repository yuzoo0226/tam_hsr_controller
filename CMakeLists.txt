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
  Qt5Widgets
  class_loader
  pluginlib
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES tam_hsr_controller
  CATKIN_DEPENDS roscpp rospy rviz class_loader pluginlib
#   DEPENDS system_lib
)

#############
## Library ##
#############
# Qt settings #
add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)


###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
link_directories(${catkin_LIBRARY_DIRS})

set(HEADERS
  include/tam_hsr_controller/publisher_example.h
)

add_library(publisher_example_lib SHARED src/publisher_example.cpp ${HEADERS})
set_target_properties(publisher_example_lib PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_include_directories(publisher_example_lib PRIVATE "${OGRE_PREFIX_DIR}/include")

target_link_libraries(publisher_example_lib ${catkin_LIBRARIES})

#############
## Install ##
#############

install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
# install(DIRECTORY icons DESTINATION share/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(TARGETS publisher_example_lib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
