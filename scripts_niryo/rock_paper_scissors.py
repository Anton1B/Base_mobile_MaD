#!/usr/bin/env python

from niryo_one_python_api.niryo_one_api import *
import rospy
rospy.init_node('niryo_one_run_python_api_code')

n = NiryoOne()

import random

i = None
j1 = None
flag = None


n.change_tool(TOOL_GRIPPER_3_ID)
for i in range(1, 4):
 n.close_gripper(TOOL_GRIPPER_3_ID, 1000)
 j1 = random.randint(1, 3)
 flag = 0
 n.move_joints([0, 0.423, -1.18, 0.077, 0.022, -2.573])
 n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -1.124])
 n.move_joints([0, 0.453, -0.939, 0.158, 1.315, -1.124])
 n.wait(1)
 n.move_joints([0, 0.453, -0.939, 0.158, 1.315, -1.124])
 n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -1.124])
 n.move_joints([0, 0.453, -0.939, 0.158, 1.315, -1.124])
 n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -1.124])
 n.move_joints([0, 0.453, -0.939, 0.158, 1.315, -1.124])
 n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -1.124])
 if j1 == 1:
   n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
   n.wait(1)
 if j1 == 2:
   n.wait(1)
 if j1 == 3:
   n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -2.573])
   n.wait(1)
 n.wait(5)
 n.close_gripper(TOOL_GRIPPER_3_ID, 1000)
  #Move to an observation position:
 n.move_joints([0, 0.373, -0.203, 0.04, -1.576, -2.566])
  #Loop until there is an object detected:
 while flag == 0:
   if n.pick('default_workspace', float(-3undefined)/100, "CIRCLE", "BLUE")[0]:
      #If an object has been taken, do:
     n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
     n.move_joints([1.74, -0.444, -0.788, 0.361, -0.028, 0.633])
     n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
     n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -1.124])
     n.close_gripper(TOOL_GRIPPER_3_ID, 1000)
     flag = 1
   if n.pick('default_workspace', float(-3undefined)/100, "SQUARE", "BLUE")[0]:
      #If an object has been taken, do:
     n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
     n.move_joints([1.073, -0.47, -0.743, 0.366, -0.175, 1.048])
     n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
     n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -1.124])
     n.close_gripper(TOOL_GRIPPER_3_ID, 1000)
     n.move_joints([-1.461, 0.425, -0.585, 0.041, 1.662, -2.359])
     n.wait(0.5)
     n.move_joints([-1.44, 0.076, 0.067, 0.126, 1.385, -2.359])
     flag = 1
   if n.pick('default_workspace', float(-3undefined)/100, "CIRCLE", "RED")[0]:
      #If an object has been taken, do:
     n.move_joints([1.016, 0.619, -0.914, 0.355, -0.473, 0.121])
     n.move_joints([0.912, -0.872, -0.562, -0.095, 0.791, 0.471])
     n.open_gripper(TOOL_GRIPPER_3_ID, 1000)
     n.move_joints([0, -0.265, -0.72, 0.022, 0.958, -1.124])
     n.close_gripper(TOOL_GRIPPER_3_ID, 1000)
     n.wait(0.5)
     flag = 1
