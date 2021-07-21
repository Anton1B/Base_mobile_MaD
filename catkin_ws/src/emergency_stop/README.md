# Base_mobile_MaD

Description :

Le package "emergency-stop" est utilisé par l'interface web pour couper les moteurs du turtlebot à n'importe quel moment. Il est activé par /simple-navigation-goals 

Le node /emergency_stop est activé directement au lancement. Il envoie une commande de vitesse nulle avant de couper les moteurs. Il tue ensuite les nodes publiant sur /cmd-vel (en laissant l'utiliation du joystick possible) et lance le node /emergency-activation

Le node /emergency-activation attend le bouton de réactivation pour relancer les nodes qui ont été tués
