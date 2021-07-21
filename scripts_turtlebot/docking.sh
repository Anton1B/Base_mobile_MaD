#!/bin/bash

# Lancement du master ROS
gnome-terminal -x roscore &

sleep 5

# les ssh sur la Pi pour la caméra et Lidar+core
gnome-terminal -x sshpass -p 'turtlebot' ssh -t pi@192.168.1.128 "cd catkin_ws;
source /opt/ros/kinetic/setup.bash;
export ROS_MASTER_URI=http://192.168.1.122:11311;
export ROS_HOSTNAME=192.168.1.128;
source devel/setup.bash;
roslaunch turtlebot3_bringup turtlebot3_robot.launch;
" &

sleep 5

gnome-terminal -x sshpass -p 'turtlebot' ssh -t pi@192.168.1.128  "cd catkin_ws;
source /opt/ros/kinetic/setup.bash;
export ROS_MASTER_URI=http://192.168.1.122:11311;
export ROS_HOSTNAME=192.168.1.128;
source devel/setup.bash;
roslaunch turtlebot3_bringup turtlebot3_rpicamera.launch;
" &

sleep 20

#Raspberry pi package will publish compressed type image for fast communication. However, what will be needed in image rectification in image_proc node is raw type image. Hence, compressed image should be transform to raw image.

gnome-terminal -x rosrun image_transport republish compressed in:=raspicam_node/image raw out:=raspicam_node/image &

# utilisation de image_proc pour avoir la version rectifiée afin d'utiliser la lecture de marqueurs pour le dock

ROS_NAMESPACE=raspicam_node rosrun image_proc image_proc image_raw:=image _approximate_s=true _queue_size:=20 &


gnome-terminal -x roslaunch turtlebot3_automatic_parking_vision turtlebot3_automatic_parking_vision.launch &

sleep 5

exit 0


