#!/usr/bin/env python

from niryo_one_python_api.niryo_one_api import *
import rospy
import random
import logging
import threading
import sys
import time
from std_msgs.msg import Int32

class Niryo_Listener:
   def __init__(self):
     self.sub = rospy.Subscriber("interactions_niryo", Int32, self.callback)
     self.ask = -1

   def callback(self,data):
     self.ask = data

def pause(n, interaction):
  while terminaison !=1 :
    if interaction.ask == 0:
        print("Action en pause")
        while interaction.ask != 1:
            n.wait(0.9)
            time.sleep(1)
            rospy.spin()
        print("Reprise de l'action")

def talker():
    pub = rospy.Publisher('reponse', Int32, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    count = 0
    while not rospy.is_shutdown():
	if count>10:
		break
        fin_action = 1
        pub.publish(fin_action)
        count = count + 1
        rate.sleep()

rospy.init_node('ranger')

n = NiryoOne()

terminaison = None
j1 = None
flag = None
interaction = Niryo_Listener()

# Calibrate robot first
n.calibrate_auto()
#n.calibrate_manual()
print("Calibration finished !\n")

n.wait(1)

# Test learning mode
n.activate_learning_mode(False)
print("Learning mode activated?")
print(n.get_learning_mode())

# Move
n.set_arm_max_velocity(100)

x = threading.Thread(target=pause, args=(n,interaction))
x.start()

n.change_tool(TOOL_GRIPPER_3_ID)
n.move_joints([0.25, 0.272, -1.281, 0.043, 0.035, 0.486])
n.move_joints([0.219, -0.257, -0.721, 0.038, 0.989, -1.134])
n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
n.close_gripper(TOOL_GRIPPER_3_ID, 250)
n.move_joints([0.25, 0.272, -1.281, 0.043, 0.035, 0.486])
n.move_joints([0.219, -0.257, -0.721, 0.038, 0.989, -1.134])

terminaison = 1

#Fin du programme
n.activate_learning_mode(True)
#response.publish(terminaison)
talker()

print "\nHardware status: "
print n.get_hardware_status()
n.wait(1)
#x.join()

sys.exit()
