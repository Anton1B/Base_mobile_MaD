#!/usr/bin/env python

from niryo_one_python_api.niryo_one_api import *
import rospy
import random
import sys
import time

#Declaration du node
rospy.init_node('activation')

#Variable du robot liee a l'API
n = NiryoOne()

# On commence par la calibration du robot
n.calibrate_auto()
#n.calibrate_manual()
print("Fin de la calibration !\n")

# Test du mode d apprentissage
n.activate_learning_mode(False)
print("Le mode apprentissage est il actif ?")
if n.get_learning_mode() == False :
	print("Non")
else :
	print("Oui")

#Fin du programme
n.activate_learning_mode(True)


#print "\nHardware status: "
#print n.get_hardware_status()
n.wait(1)

#Sortie du programme
sys.exit() 
