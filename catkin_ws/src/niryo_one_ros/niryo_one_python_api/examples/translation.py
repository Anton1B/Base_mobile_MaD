#!/usr/bin/env python

# To use the API, copy these 4 lines on each Python file you create
from niryo_one_python_api.niryo_one_api import *
import math
import rospy
import time
import numpy as np
import cv2

import markers_detection as m
import math_functions as math

#workspace_ratio = n.get_workspace_ratio('default_workspace')
workspace_ratio = 1.0
check_workspace = 1

# path 
path = r'/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_python_api/examples/savedImage.jpg'
  
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

print(list_good_candidates)
print(check_workspace)


temoin_x = list_good_candidates[0].cx #218
temoin_y = list_good_candidates[0].cy #52

px_temoin = temoin_x
py_temoin = temoin_y

px_test = list_good_candidates[1].cx
py_test = list_good_candidates[1].cy

lx = px_test - px_temoin
ly = py_test - py_temoin

print("-----------------------------")
print(lx,ly)

mm = 172/215 #Il y a 172mm entre le centre de deux marqueurs

px_test2 = list_good_candidates[3].cx
py_test2 = list_good_candidates[3].cy

print("-----------------------------")
print(px_test2,py_test2)

v_ws = [px_test2-temoin_x, py_test2-temoin_y]

# angle = atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x);
angle = np.arctan2(100,0) - np.arctan2(v_ws[1],v_ws[0])
if angle > np.pi  :
	angle -= 2*np.pi
 
elif angle <= -np.pi :
    angle += 2*np.pi
    
    
print("-----------------------------")
print(angle)

print("-----------------------------")
print(list_good_candidates[0].cx,list_good_candidates[0].cy)
print(list_good_candidates[1].cx,list_good_candidates[1].cy)
print(list_good_candidates[2].cx,list_good_candidates[2].cy)
print(list_good_candidates[3].cx,list_good_candidates[3].cy)

# Window name in which image is displayed
window_name = 'image'
  
# Using cv2.imshow() method 
# Displaying the image 
cv2.imshow(window_name, img_thresh)
  
#waits for user to press any key 
#(this is necessary to avoid Python kernel form crashing)
cv2.waitKey(0) 
  
#closing all open windows 
cv2.destroyAllWindows() 

