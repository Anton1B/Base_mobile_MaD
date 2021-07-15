#!/usr/bin/env python

#Voir le script servir.py pour avoir les commentaires

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
terminaison = None

class Niryo_Listener:
  def __init__(self):
    self.sub = rospy.Subscriber("interactions_niryo",Int32,self.callback,queue_size=1)
    self.fin = -1
  def callback(self,data):
    self.fin = data.data

def pause_2(n, interaction):
  while terminaison !=1 :
    if interaction.fin == 0:
        print("Action en pause")
        while interaction.fin == 0:
            n.wait(2)
            #time.sleep(1)
            #rospy.spin()
        print("Reprise de l'action")

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


def talker():
    pub = rospy.Publisher('reponse', Int32, queue_size=1)
    pub2 = rospy.Publisher('messages_niryo', String, queue_size=1)
    rate = rospy.Rate(10) # 10hz
    count = 0
    mes = "Le bras a range l'objet dans le meuble"
    fin_action = 1
    while not rospy.is_shutdown():
	#print(memo_pause)
	if count>10:
		if memo_pause == 1:
			pub2.publish(mes)
		break

        pub.publish(fin_action)
        count = count + 1
        rate.sleep()

 
rospy.init_node('ranger')

n = NiryoOne()


# Calibrate robot first
n.calibrate_auto()
#n.calibrate_manual()
print("Fin de la calibration !\n")

n.wait(1)

# Test learning mode
n.activate_learning_mode(False)
n.activate_learning_mode(False)
print("Le mode apprentissage est il actif ?")
if n.get_learning_mode() == False :
	print("Non")
else :
	print("Oui")

# Move
n.set_arm_max_velocity(100)

interaction = Niryo_Listener()

#x = threading.Thread(target=pause, args=(n,interaction))
#x.start()



n.change_tool(TOOL_GRIPPER_3_ID)
#pause(n,interaction)
#n.move_joints([0.25, 0.272, -1.281, 0.043, 0.035, 0.486])
#pause(n,interaction)
#n.move_joints([0.25, -0.257, -0.721, 0.038, 0.989, -1.134])
#pause(n,interaction)
#n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
#pause(n,interaction)
#n.close_gripper(TOOL_GRIPPER_3_ID, 250)
#pause(n,interaction)
#n.move_joints([0.9, 0.272, -1.281, 0.043, 0.035, 0.486])
#pause(n,interaction)
#n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
#pause(n,interaction)
#n.close_gripper(TOOL_GRIPPER_3_ID, 250)
#pause(n,interaction)
#n.move_joints([0.25, -0.257, -0.721, 0.038, 0.989, -1.134])

pause(n,interaction)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])
pause(n,interaction)

#Move to an observation position:
n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
pause(n,interaction)

#Loop until there is an object detected:
while not (n.vision_pick('default_workspace', 0, "CIRCLE", "BLUE")[0]):
  #Wait for a short time:
  n.wait(1)
  pause(n,interaction)

#Your program:
#If an object has been taken, do:
n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
pause(n,interaction)
n.move_joints([1.74, -0.444, -0.788, 0.361, -0.028, 0.633])
pause(n,interaction)
n.move_joints([1.74, -0.52, -0.788, 0.361, -0.028, 0.633])
pause(n,interaction)
n.open_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
pause(n,interaction)
n.move_joints([-0.027, 0.373, -0.203, 0.04, -1.576, -2.566])
pause(n,interaction)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
pause(n,interaction)
n.move_joints([0.019, 0.101, -1.08, 0.06, -0.573, -2.556])

terminaison = 1

#Fin du programme
n.activate_learning_mode(True)
#response.publish(terminaison)
talker()

#print "\nHardware status: "
#print n.get_hardware_status()
n.wait(1)
#x.join()

sys.exit()

