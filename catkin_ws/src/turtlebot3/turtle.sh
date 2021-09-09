#!/bin/bash

# heure = `date +'%H'`
printf -v heure '%(%H)T' -1
echo "Il est actuellement plus de : $heure h"

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

sleep 20

gnome-terminal -x sshpass -p 'turtlebot' ssh -t pi@192.168.1.128  "cd catkin_ws;
source /opt/ros/kinetic/setup.bash;
export ROS_MASTER_URI=http://192.168.1.122:11311;
export ROS_HOSTNAME=192.168.1.128;
source devel/setup.bash;
roslaunch turtlebot3_bringup turtlebot3_rpicamera.launch;
" &

sleep 20

gnome-terminal -x sshpass -p 'robotics' ssh -t niryo@192.168.1.130 "cd catkin_ws;
source /opt/ros/kinetic/setup.bash;
export ROS_MASTER_URI=http://192.168.1.122:11311;
export ROS_HOSTNAME=192.168.1.130;
source devel/setup.bash;
roslaunch niryo_one_bringup rpi_setup.launch;
" &

sleep 70


# on publie l'image_raw de la camera (de base on a seulement la version compressée disponible)
gnome-terminal -x rosrun image_transport republish compressed in:=raspicam_node/image raw out:=raspicam_node/image &

sleep 5

# utilisation de image_proc pour avoir la version rectifiée afin d'utiliser la lecture de marqueurs pour le dock

ROS_NAMESPACE=raspicam_node rosrun image_proc image_proc image_raw:=image _approximate_s=true _queue_size:=20 &

sleep 5

# démarrage de la navigation stack
gnome-terminal -x roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=/home/chaire/chaire_mad.yaml &

sleep 5

# démarage du noeud de gestion de la batterie
gnome-terminal -x rosrun battery_monitoring battery_monitoring &
gnome-terminal -x rosrun niryo_control niryo_control_v2 &
gnome-terminal -x rosrun simple_navigation_goals simple_navigation_goals &
gnome-terminal -x rosrun web_video_server web_video_server &
gnome-terminal -x roslaunch rosbridge_server rosbridge_websocket.launch &
gnome-terminal -x roslaunch niryo_control actions_niryo_final.launch &

sleep 5

if [[ $heure -gt 19 ]]
then
    gnome-terminal --working-directory=/home/chaire/catkin_ws/src/turtlebot3/Web_App_dark/ -x live-server . --port=5500 --no-browser & # --no-browser
else
    gnome-terminal --working-directory=/home/chaire/catkin_ws/src/turtlebot3/Web_App/ -x live-server . --port=5500 --no-browser & # --no-browser
fi
exit 0
