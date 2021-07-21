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

#Variable de fin de l'action
terminaison = None 

#Ecoute les demandes de mise en pause ou d'arret
class Niryo_Listener:
  def __init__(self):
    self.sub = rospy.Subscriber("interactions_niryo",Int32,self.callback,queue_size=1)
    self.fin = -1
  def callback(self,data):
    #print(data.data)
    self.fin = data.data

def pause_2(n, interaction):
  while terminaison !=1 :
    if interaction.fin == 0:
        print("Action en pause")
        while interaction.fin != 1:
            n.wait(2)
        print("Reprise de l'action")

#Action si on a demande une pause ou un arret
def pause(n,interaction):
    if interaction.fin == 0:
        print("Action en pause")
        while interaction.fin == 0:
            n.wait(0.5)
	    global memo_pause
	    memo_pause = 1
        print("Reprise de l'action")

    if interaction.fin == 2:
	n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
	n.close_gripper(TOOL_GRIPPER_3_ID, 250)
	n.activate_learning_mode(True)
	talker()
	sys.exit()

#Signale au node de controle que l'action est terminee et publie le message de fin
def talker():
    pub = rospy.Publisher('reponse', Int32, queue_size=10)
    pub2 = rospy.Publisher('messages_niryo', String, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    count = 0
    mes = "Le bras a depose l'objet sur la zone de depot"
    fin_action = 1
    while not rospy.is_shutdown():
	if count>10:
		if memo_pause == 1:
			pub2.publish(mes)
		break
        pub.publish(fin_action)
        count = count + 1
        rate.sleep()

#Declaration du node
rospy.init_node('servir')

#Variable du robot liee a l'API
n = NiryoOne()

# On commence par la calibration du robot
n.calibrate_auto()
#n.calibrate_manual()
print("Fin de la calibration !\n")

#n.wait(1)

# Test du mode d apprentissage
n.activate_learning_mode(False)
print("Le mode apprentissage est il actif ?")
if n.get_learning_mode() == False :
	print("Non")
else :
	print("Oui")

# ACTION DU ROBOT

#Vitesse des moteurs au maximum
#n.wait(0.5)
n.set_arm_max_velocity(100) 

#On ecoute les demandes de pause
interaction = Niryo_Listener() 

#x = threading.Thread(target=pause_2, args=(n,interaction))
#x.start()

n.change_tool(TOOL_GRIPPER_3_ID)

pause(n,interaction)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
pause(n,interaction)
n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
pause(n,interaction)
n.open_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([1.74, -0.444, -0.788, 0.361, -0.028, 0.633])
pause(n,interaction)
n.move_joints([1.74, -0.52, -0.788, 0.361, -0.028, 0.633])
pause(n,interaction)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
pause(n,interaction)
n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
pause(n,interaction)
n.move_joints([0.012, -0.597, -0.15, 0.035, -0.788, -2.556])
pause(n,interaction)
n.move_joints([0.012, -0.65, -0.15, 0.035, -0.788, -2.556])
pause(n,interaction)
n.open_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([0.012, -0.5, -0.15, 0.035, -0.788, -2.556])
pause(n,interaction)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])

#Fin de l action
terminaison = 1 

#Fin du programme
n.activate_learning_mode(True)
#response.publish(terminaison)
talker()

#print "\nHardware status: "
#print n.get_hardware_status()
n.wait(1)
#x.join()

#Sortie du programme
sys.exit() 

