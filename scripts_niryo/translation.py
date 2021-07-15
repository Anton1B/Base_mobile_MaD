#!/usr/bin/env python

# To use the API, copy these 4 lines on each Python file you create
from niryo_one_python_api.niryo_one_api import *
import math
import rospy
import time
import numpy as np
import cv2
import sys

import markers_detection as m
import math_functions as math

#workspace_ratio = n.get_workspace_ratio('default_workspace')
workspace_ratio = 1.0
check_workspace = 1


def f(compressed_image):
    np_arr = np.fromstring(compressed_image, np.uint8)
    img = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
    return img


rospy.init_node('niryo_one_example_python_api')
print "--- Start"

n = NiryoOne()

try:
    # Calibrate robot first
    n.calibrate_auto()
    print "Calibration finished !"

    n.activate_learning_mode(False)

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

    # print(list_good_candidates)
    # print(check_workspace)
    # print(list_good_candidates[0].cx, list_good_candidates[0].cy)

    temoin_x = 203
    temoin_y = 50

    px_test = list_good_candidates[0].cx
    py_test = list_good_candidates[0].cy

    lx = temoin_x - px_test
    ly = temoin_y - py_test

    print("-----------------------------")
    print(lx,ly)

    mm = 172.0/192.0 #Il y a 172mm entre le centre de deux marqueurs
    
    tx = mm*lx
    ty = mm*ly

    print("-----------------------------")
    print(tx,ty)


except NiryoOneException as e:
    print e
    # handle exception here
    # you can also make a try/except for each command separately

print "--- End"
os.system('rm /home/niryo/catkin_ws/src/niryo_one_python_api/examples/testImage.jpg')
