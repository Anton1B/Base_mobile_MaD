#!/bin/bash

# Lancement du master ROS
#gnome-terminal -x roscore &

#sleep 5

gnome-terminal -x sshpass -p 'robotics' ssh -t niryo@192.168.1.130 "cd catkin_ws;
source /opt/ros/kinetic/setup.bash;
export ROS_MASTER_URI=http://192.168.1.122:11311;
export ROS_HOSTNAME=192.168.1.130;
source devel/setup.bash;
roslaunch niryo_one_bringup rpi_setup.launch;
" &


sleep 80


gnome-terminal -x sshpass -p 'robotics' ssh -t niryo@192.168.1.130  "source /opt/ros/kinetic/setup.bash;
source ~/catkin_ws/devel/setup.bash;
export ROS_MASTER_URI=http://192.168.1.122:11311;
export ROS_HOSTNAME=192.168.1.130;
python catkin_ws/src/niryo_one_python_api/examples/which_hand.py;" &

exit 0


