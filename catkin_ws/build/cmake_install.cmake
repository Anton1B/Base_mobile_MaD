# Install script for directory: /home/chaire/catkin_ws/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/chaire/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/chaire/catkin_ws/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/chaire/catkin_ws/install" TYPE PROGRAM FILES "/home/chaire/catkin_ws/build/catkin_generated/installspace/_setup_util.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/chaire/catkin_ws/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/chaire/catkin_ws/install" TYPE PROGRAM FILES "/home/chaire/catkin_ws/build/catkin_generated/installspace/env.sh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/chaire/catkin_ws/install/setup.bash;/home/chaire/catkin_ws/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/chaire/catkin_ws/install" TYPE FILE FILES
    "/home/chaire/catkin_ws/build/catkin_generated/installspace/setup.bash"
    "/home/chaire/catkin_ws/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/chaire/catkin_ws/install/setup.sh;/home/chaire/catkin_ws/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/chaire/catkin_ws/install" TYPE FILE FILES
    "/home/chaire/catkin_ws/build/catkin_generated/installspace/setup.sh"
    "/home/chaire/catkin_ws/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/chaire/catkin_ws/install/setup.zsh;/home/chaire/catkin_ws/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/chaire/catkin_ws/install" TYPE FILE FILES
    "/home/chaire/catkin_ws/build/catkin_generated/installspace/setup.zsh"
    "/home/chaire/catkin_ws/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/chaire/catkin_ws/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/chaire/catkin_ws/install" TYPE FILE FILES "/home/chaire/catkin_ws/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/chaire/catkin_ws/build/gtest/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_bringup/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_description/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_moveit_config/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3_applications/turtlebot3_applications/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3_applications/turtlebot3_follow_filter/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3_msgs/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3_navigation/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/dynamixel_sdk/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/emergency_stop/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/emergency_stop_for_tests/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/mcp_can_rpi/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_control/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/battery_monitoring/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_camera/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_msgs/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_camera_jevois/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_debug/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_modbus/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_rpi/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_tools/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/simple_navigation_goals/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_commander/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_pose_converter/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_python_api/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_tcp_server/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_user_interface/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3_applications_msgs/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3_applications/turtlebot3_automatic_parking/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3_applications/turtlebot3_automatic_parking_vision/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3_bringup/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3_example/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3_applications/turtlebot3_follower/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3_applications/turtlebot3_panorama/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3_slam/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3_teleop/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_driver/cmake_install.cmake")
  include("/home/chaire/catkin_ws/build/turtlebot3/turtlebot3_description/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/chaire/catkin_ws/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
