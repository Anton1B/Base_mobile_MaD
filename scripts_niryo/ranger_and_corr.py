#!/usr/bin/env python

# To use the API, copy these 4 lines on each Python file you create
from niryo_one_python_api.niryo_one_api import *
import math
import rospy
import time
import numpy as np
import cv2
import sys
from geometry_msgs.msg import Twist
from std_msgs.msg import Int32


import markers_detection as m
import math_functions as math

memo_pause = 0
memo_action = 0

#workspace_ratio = n.get_workspace_ratio('default_workspace')
workspace_ratio = 1.0
check_workspace = 1
angle = 10

#Ecoute les demandes de mise en pause ou d'arret
class Niryo_Listener:
  def __init__(self):
    self.sub = rospy.Subscriber("interactions_niryo",Int32,self.callback,queue_size=1)
    self.ask = -1
  def callback(self,data):
    #print(data.data)
    self.ask = data.data


#Action si on a demande une pause ou un arret
def pause(n,interaction,rate):
    if interaction.ask == 0:
        print("Action en pause")
        while interaction.ask == 0:
            n.wait(0.5)
	    global memo_pause
	    memo_pause = 1
        print("Reprise de l'action")

    if interaction.ask == 2:
      global memo_action
      memo_action = 2
      n.open_gripper(TOOL_GRIPPER_3_ID, 250)
      n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
      n.close_gripper(TOOL_GRIPPER_3_ID, 250)
      n.activate_learning_mode(True)
      talker(rate)
      return 1
    

#Signale au node de controle que l'action est terminee et publie le message de fin
def talker(rate):
    print("Fin du programme")
    pub = rospy.Publisher('reponse', Int32, queue_size=10)
    pub2 = rospy.Publisher('messages_niryo', String, queue_size=10)
    count = 0
    if memo_action == 10 : 
    	mes = "Le bras a depose l'objet sur la zone de depot"
    if memo_action == 11 : 
    	mes = "Le bras a range l'objet dans le meuble"
    if memo_action == 2 : 
    	mes = "Le bras est au repos, vous pouvez relancer une action"

    fin_action = 1
    while not rospy.is_shutdown():
      if count>10:
        if memo_pause == 1:
          pub2.publish(mes)
        break
        
      pub.publish(fin_action)
      count = count + 1
      rate.sleep()
    return


def f(compressed_image):
    np_arr = np.fromstring(compressed_image, np.uint8)
    img = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
    return img

#Signale au turtlebot qu'il doit tenter de se repositionner
def turn(rate,angle,n):
    vit_rot = 1
    print("Repositionnement du turtlebot")
    pub_cmd_vel = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
    twist = Twist()
    twist.linear.x = 0
    twist.linear.y = 0
    twist.linear.z = 0
    twist.angular.x = 0
    twist.angular.y = 0
    twist.angular.z = -0.2*np.sign(angle)
    pub_cmd_vel.publish(twist)
    
    n.wait(angle/vit_rot) #On attend le repositionnement
    twist.angular.z = 0
    pub_cmd_vel.publish(twist) #Stop
    return
    


rospy.init_node('niryo_one_example_python_api')
print "--- Start"

n = NiryoOne()


# Calibrate robot first
n.calibrate_auto()
print "Calibration finished !"

n.activate_learning_mode(False)

rate = rospy.Rate(10) # 10hz

while abs(angle) > 0.3 :
  
  print "Go to observation position"
  n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])

  n.wait(1)
  img = n.get_compressed_image()
  img = f(img)

  filename = '/home/niryo/catkin_ws/src/niryo_one_python_api/examples/testImage.jpg'
  cv2.imwrite(filename, img)

  n.activate_learning_mode(True)

  #################################################################################################

  # path 
  path = r'/home/niryo/catkin_ws/src/niryo_one_python_api/examples/testImage.jpg'

  # Reading an image in default mode
  img = cv2.imread(path)

  gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

  img_thresh = cv2.adaptiveThreshold(gray, maxValue=255, adaptiveMethod=cv2.ADAPTIVE_THRESH_MEAN_C,
                          thresholdType=cv2.THRESH_BINARY, blockSize=15, C=25)

  list_good_candidates = m.find_markers_from_img_thresh(img_thresh)


  if not list_good_candidates or len(list_good_candidates) > 6:
      check_workspace = 0

  if len(list_good_candidates) == 4:
      list_good_candidates = m.sort_markers_detection(list_good_candidates)
  else:
      list_good_candidates = m.complicated_sort_markers(list_good_candidates, workspace_ratio=workspace_ratio)
      if list_good_candidates is None:
          check_workspace = 0

  #print(list_good_candidates)

  print("Les marqueurs sont presents : ",check_workspace)

  # temoin1_x = 218
  # temoin1_y = 52

  # temoin2_x = 411
  # temoin2_y = 56

  # temoin3_x = 415
  # temoin3_y = 252

  # temoin4_x = 200
  # temoin4_y = 245

  temoin = [[218,52],[411,56],[415,252],[200,245]]

  test = []

  for i in range (4) :
    test.append([list_good_candidates[i].cx , list_good_candidates[i].cy]) #liste des centres des marqueurs      

  print("-----------------------------")   
  for i in range (4) :
    print(test[i])

  lx = 0
  ly = 0

  print("-----------------------------")
  for i in range (0,4) :
    lx += temoin[i][0]-test[i][0]
    ly += temoin[i][1]-test[i][1]
    print(temoin[i][0]-test[i][0],temoin[i][1]-test[i][1])

  lx = lx/4.0
  ly = ly/4.0
    

  print("-----------------------------")
  print("translation en px",lx,ly)

  mm = 172.0/215.0/1.5 #Il y a 172mm entre le centre de deux marqueurs

  tx = mm*lx
  ty = mm*ly

  print("-----------------------------")
  print("translation en mm",tx,ty)


  v_ws = [test[2][0]-test[3][0], test[2][1]-test[3][1]] #vecteur des deux marqueurs gauche du workspace

  # angle = atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x) --> angle entre le cote du bas du workspace et l'arrete basse de la camera
  angle = np.arctan2(v_ws[1],v_ws[0]) - np.arctan2(0,100)  

  if angle > np.pi  :
    angle -= 2*np.pi

  if angle <= -np.pi :
    angle += 2*np.pi
      
  print("-----------------------------")
  print(angle)
  
  n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
  
  turn(rate,angle,n)
  n.activate_learning_mode(True)
  n.wait(1)
  


n.activate_learning_mode(False)

#On ecoute les demandes de pause
interaction = Niryo_Listener() 

n.change_tool(TOOL_GRIPPER_3_ID)

pause(n,interaction,rate)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction,rate) 
n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
pause(n,interaction,rate)

#Deplacement a la position d'observation:
n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
pause(n,interaction,rate)

test_vision = False
workspace = 'default_workspace'

#Boucle en attendant la detection d'un objet:
while not (test_vision):
    test_vision,rel_pose,obj_shape,obj_color = n.detect_object(workspace, "CIRCLE", "BLUE")
    n.wait(1)
    pause(n,interaction,rate)

rel_pose.x -= tx/100.0
rel_pose.y -= ty/100.0

#Parametres du vision pick
height_offset = -0.002
pick_pose = n.get_target_pose_from_rel(workspace, height_offset, rel_pose.x, rel_pose.y, rel_pose.yaw)
approach_pose = n.get_target_pose_from_rel(workspace, height_offset + 0.05, rel_pose.x, rel_pose.y, rel_pose.yaw)

#Si l'objet a ete repere, faire :
n.move_pose(*n.robot_state_msg_to_list(approach_pose))
pause(n,interaction,rate)  

n.open_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction,rate)

n.move_pose(*n.robot_state_msg_to_list(pick_pose))
pause(n,interaction,rate)

n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction,rate)   

n.move_pose(*n.robot_state_msg_to_list(approach_pose))
pause(n,interaction,rate)

n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
pause(n,interaction,rate)

n.move_joints([1.74, -0.444, -0.788, 0.361, -0.028, 0.633])
pause(n,interaction,rate)   

n.move_joints([1.74, -0.52, -0.788, 0.361, -0.028, 0.633])
pause(n,interaction,rate)

n.open_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction,rate)

n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
pause(n,interaction,rate)

n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
pause(n,interaction,rate)

n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction,rate)

n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])

#Fin du programme
n.activate_learning_mode(True)

talker(rate)

n.wait(5)



#os.system('rm /home/niryo/catkin_ws/src/niryo_one_python_api/examples/testImage.jpg')
