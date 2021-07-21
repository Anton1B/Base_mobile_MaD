# Base_mobile_MaD

Description :

Le package "emergency-stop-for-test" permet de réaliser des arrêts d'urgence hors des phases d'utilisation de l'interface web. Il est ainsi possible d'utiliser la commande "a_u" dans un terminal pour activer le node /emergency-stop-for-tests

Le fonctionnement de ce package est similaire à celui utilisé avec l'interface web à la différence près que celui ci utilise un système de thread attendant une interruption au clavier pour la réactivation. Pendant cette attente, la commande au clavier est activée 
