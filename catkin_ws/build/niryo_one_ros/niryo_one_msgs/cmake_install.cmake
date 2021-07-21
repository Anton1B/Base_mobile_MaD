# Install script for directory: /home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/msg" TYPE FILE FILES
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/RPY.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/ShiftPose.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/RobotState.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/RobotMoveCommand.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/ToolCommand.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/ProcessState.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/HardwareStatus.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/LogStatus.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/DigitalIOState.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/SoftwareVersion.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/Sequence.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/SequenceAutorunStatus.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/TrajectoryPlan.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/MatlabMoveResult.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/Position.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/Trajectory.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/ObjectPose.msg"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg/ConveyorFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/srv" TYPE FILE FILES
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ChangeHardwareVersion.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ChangeMotorConfig.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ControlConveyor.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/CloseGripper.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/DebugColorDetection.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/DebugMarkers.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/EditGrip.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/EditWorkspace.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetCalibrationCam.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetDigitalIO.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetInt.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetPositionList.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetSequenceList.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetTargetPose.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetTrajectoryList.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetWorkspaceList.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetWorkspaceRatio.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/GetWorkspaceRobotPoses.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ObjDetection.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ManagePosition.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ManageProcess.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ManageSequence.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/ManageTrajectory.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/OpenGripper.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/PingDxlTool.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/PullAirVacuumPump.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/PushAirVacuumPump.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/RobotMove.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SendCustomDxlValue.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetBool.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetCalibrationCam.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetConveyor.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetDigitalIO.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetInt.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetLeds.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetSequenceAutorun.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/SetString.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/TakePicture.srv"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/srv/UpdateConveyorId.srv"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/action" TYPE FILE FILES
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/action/JoystickJoints.action"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/action/RobotMove.action"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/action/Tool.action"
    "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/action/Sequence.action"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/msg" TYPE FILE FILES
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/JoystickJointsAction.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/JoystickJointsActionGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/JoystickJointsActionResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/JoystickJointsActionFeedback.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/JoystickJointsGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/JoystickJointsResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/JoystickJointsFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/msg" TYPE FILE FILES
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/RobotMoveAction.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/RobotMoveActionGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/RobotMoveActionResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/RobotMoveActionFeedback.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/RobotMoveGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/RobotMoveResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/RobotMoveFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/msg" TYPE FILE FILES
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/ToolAction.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/ToolActionGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/ToolActionResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/ToolActionFeedback.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/ToolGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/ToolResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/ToolFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/msg" TYPE FILE FILES
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/SequenceAction.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/SequenceActionGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/SequenceActionResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/SequenceActionFeedback.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/SequenceGoal.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/SequenceResult.msg"
    "/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg/SequenceFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/cmake" TYPE FILE FILES "/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_msgs/catkin_generated/installspace/niryo_one_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/chaire/catkin_ws/devel/include/niryo_one_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/chaire/catkin_ws/devel/share/roseus/ros/niryo_one_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/chaire/catkin_ws/devel/share/common-lisp/ros/niryo_one_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/chaire/catkin_ws/devel/share/gennodejs/ros/niryo_one_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/chaire/catkin_ws/devel/lib/python2.7/dist-packages/niryo_one_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/chaire/catkin_ws/devel/lib/python2.7/dist-packages/niryo_one_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_msgs/catkin_generated/installspace/niryo_one_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/cmake" TYPE FILE FILES "/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_msgs/catkin_generated/installspace/niryo_one_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs/cmake" TYPE FILE FILES
    "/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_msgs/catkin_generated/installspace/niryo_one_msgsConfig.cmake"
    "/home/chaire/catkin_ws/build/niryo_one_ros/niryo_one_msgs/catkin_generated/installspace/niryo_one_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/niryo_one_msgs" TYPE FILE FILES "/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/package.xml")
endif()

