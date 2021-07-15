#!/usr/bin/env python

from niryo_one_python_api.niryo_one_api import *
import rospy
rospy.init_node('which_hand')

n = NiryoOne()

import random

j1 = None
flag = None


# Calibrate robot first
n.calibrate_auto()
#n.calibrate_manual()
print "Calibration finished !\n"

n.wait(1)

# Test learning mode
n.activate_learning_mode(False)
print "Learning mode activated? "
print n.get_learning_mode()

# Move
n.set_arm_max_velocity(100)


n.change_tool(TOOL_GRIPPER_3_ID)
n.move_joints([0.25, 0.272, -1.281, 0.043, 0.035, 0.486])
n.move_joints([0.219, -0.257, -0.721, 0.038, 0.989, -1.134])
for count in range(1):
 n.close_gripper(TOOL_GRIPPER_3_ID, 1000)
 j1 = random.randint(1, 2)
 flag = 1.887
 n.wait(1)
 n.move_joints([1.887, -0.317, -1.039, 0.065, 1.339, -1.169])
 while flag >= 0.2:
   flag = flag - 0.2
   n.move_joints([flag, -0.317, -1.039, 0.065, 1.339, -1.169])
 n.move_joints([0.219, -0.257, -0.721, 0.038, 0.989, -1.134])
 n.wait(3)
 if j1 == 1:
   n.move_joints([-0.093, -0.257, -0.478, 0.155, 0.776, -1.124])
 if j1 == 2:
   n.move_joints([0.667, -0.289, -0.581, 0.089, 0.922, -1.189])
 n.wait(1)
 n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
 n.wait(3)
 n.close_gripper(TOOL_GRIPPER_3_ID, 250)
 n.move_joints([0.25, 0.272, -1.281, 0.043, 0.035, 0.486])
 n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
 n.move_joints([0.219, -0.257, -0.721, 0.038, 0.989, -1.134])


#Fin du programme
n.activate_learning_mode(True)

print "\nHardware status: "
print n.get_hardware_status()

print "--- End"
