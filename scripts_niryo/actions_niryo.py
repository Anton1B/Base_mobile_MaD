#!/usr/bin/env python

from niryo_one_python_api.niryo_one_api import *
import rospy
import random
import logging
import threading
import sys
import time
from std_msgs.msg import String
from std_msgs.msg import Int32

memo_pause = 0
memo_action = 0

#Variable de fin de l'action
terminaison = None 

#############################################################################

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

#############################################################################

def servir(n,interaction,rate):
  print("service de l'objet")
  check_end = 0
  n.change_tool(TOOL_GRIPPER_3_ID)

  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.close_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 
  n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 
  n.open_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([1.74, -0.444, -0.788, 0.361, -0.028, 0.633])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([1.74, -0.52, -0.788, 0.361, -0.028, 0.633])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.close_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.move_joints([0.012, -0.597, -0.15, 0.035, -0.788, -2.556])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.move_joints([0.012, -0.65, -0.15, 0.035, -0.788, -2.556])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.open_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.move_joints([0.012, -0.5, -0.15, 0.035, -0.788, -2.556])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.close_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return  
  n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])

  #Fin du programme
  n.activate_learning_mode(True)

  talker(rate)

  #Fin de l'action
  return

#############################################################################


def ranger(n,interaction,rate):
  print("Rangement de l'objet")
  check_end = 0
  n.change_tool(TOOL_GRIPPER_3_ID)

  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 
  n.close_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return   
  n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 

  #Deplacement a la position d'observation:
  n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 

  test_vision = False
  workspace = 'default_workspace'

  #Boucle en attendant la detection d'un objet:
  while not (test_vision):
    test_vision,rel_pose,obj_shape,obj_color = n.detect_object(workspace, "CIRCLE", "BLUE")
    n.wait(1)
    check_end = pause(n,interaction,rate)
    if check_end == 1:
      return 

  rel_pose.x += 0.3
  rel_pose.y += 0.3
  #Parametres du vision pick
  height_offset = 0
  pick_pose = n.get_target_pose_from_rel(workspace, height_offset, rel_pose.x, rel_pose.y, rel_pose.yaw)
  approach_pose = n.get_target_pose_from_rel(workspace, height_offset + 0.05, rel_pose.x, rel_pose.y, rel_pose.yaw)

  #Si l'objet a ete repere, faire :
  n.move_pose(*n.robot_state_msg_to_list(approach_pose))
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 
  n.open_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 
  n.move_pose(*n.robot_state_msg_to_list(pick_pose))
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 
  n.close_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 
  n.move_pose(*n.robot_state_msg_to_list(approach_pose))
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return 

  n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([1.74, -0.444, -0.788, 0.361, -0.028, 0.633])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([1.74, -0.52, -0.788, 0.361, -0.028, 0.633])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.open_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.close_gripper(TOOL_GRIPPER_3_ID, 250)
  check_end = pause(n,interaction,rate)
  if check_end == 1:
    return
  n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])

  #Fin du programme
  n.activate_learning_mode(True)

  talker(rate)

  #Fin de l'action
  return

#############################################################################
#############################################################################

# INITIALISATION

#Declaration du node
rospy.init_node('actions_niryo')

#Variable du robot liee a l'API
n = NiryoOne()

# On commence par la calibration du robot
n.calibrate_auto()
#n.calibrate_manual()
print("Fin de la calibration !\n")

# Test du mode d'apprentissage
n.activate_learning_mode(False)
print("Le mode apprentissage est il actif ?")
if n.get_learning_mode() == False :
	print("Non")
else :
	print("Oui")

############################################################################

# ACTIONS DU ROBOT

#Vitesse des moteurs au maximum
n.set_arm_max_velocity(100) 

#On ecoute les demandes de pause
interaction = Niryo_Listener() 

rate = rospy.Rate(10) # 10hz

#Mode de repos des moteurs
n.activate_learning_mode(True)

while(True) :

  if interaction.ask == 10 :
    #global memo_action
    memo_action = 10
    servir(n,interaction,rate)
    interaction.ask = -1

  if interaction.ask == 11 :
    #global memo_action
    memo_action = 11
    ranger(n,interaction,rate)
    interaction.ask = -1

  rate.sleep()


#Sortie du programme
sys.exit() 

