# Base_mobile_MaD

Description :

Contenu du dossier "example" disponible dans sftp://niryo@192.168.1.130/home/niryo/catkin_ws/src/niryo_one_python_api/examples

Fonction de chaque programme :

- actions_niryo.py : première version aboutie du fonctionnement du niryo avec des fonctions pour chaque action. Il manque l'observation.
- actions_niryo_final.py : dernière version du fonctionnement du nyrio avec des fonctions pour chaque action et pour l'observation. C'est ce programme qui est lancé lors de l'activation du robot.
- activation.py : programme utilisé lorsque la calibration du robot était lancée avant le programme avec les actions
- markers_detection.py : programme issu du package niryo_one_camera utilisé pour ses fonctions permettant d'estimer la position des marqueurs du workspace
- math_function.py : programme issu du package niryo_one_camera utilisé pour ses fonctions de calculs
- pick_n_place_with_conveyor.py : demonstrateur fourni par l'entreprise Niryo (jamais testé)
- prise_photo_temoin : programme permettant de prendre une photo témoin du workspace et la sauvegarder dans le dossier actuel
- ranger.py : programme remplissant la fonction de rangement lorsque le fonctionnement impliquait de lancer les actions séparéments 
- ranger_and_corr.py : programme remplissant la fonction de rangement lorsque le fonctionnement impliquait de lancer les actions séparéments mais en ajoutant une correction en foncton de la position relative du Niryo One par rapport au workspace
- ranger_ov.py : version originale du programme de rangement avec des mouvements ne correspondant pas encore au démonstrateur final
- rock_paper_scissors.py : démonstrateur permettant de jouer au célèbre jeu portant le nom du script. Il y a 3 manches et un comptage de points faisant intervenir les fonctions de vision.
- servir.py : programme remplissant la fonction de service lorsque le fonctionnement impliquait de lancer les actions séparéments
- servir_ov.py : version originale du programme de service avec des mouvements ne correspondant pas encore au démonstrateur final
- take_photo_with_camera.py : programme similaire à prise_photo_temoin (sans doute l'original)
- translation.py : test de la correction de positionnement en translation. Il n'y a pas de mouvements, seulement une comparaison entre une image prise sur le moment et l'image témoin pour ensuite afficher les écarts de posiiton des marqueurs.
- which_hand.py : demonstrateur interactif ou le robot essaye de "deviner" dans quelle main de l'utilisateur se trouve l'objet. Le robot saisit ensuite l'objet pour comptabiliser les points.
