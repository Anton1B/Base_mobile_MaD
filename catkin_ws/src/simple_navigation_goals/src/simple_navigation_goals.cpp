#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/BatteryState.h>
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include <boost/container/string.hpp>

int flag_global = 0;

// Ligne qui va servir à communiquer avec /move_base
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

// Définition d'une classe qui va permettre de récupérer la tension de la batterie :
class Battery_Listener
{
public:
	double tension;

	void callback1(const sensor_msgs::BatteryStateConstPtr &msg);
};

void Battery_Listener::callback1(const sensor_msgs::BatteryStateConstPtr &msg)
{
	tension = msg->voltage;
}

// Définition de la classe Choix_Listener qui va servir à récupérer les informations envoyée depuis l'appli Web
class Choice_Listener
{
public:
	int choix;

	void callback2(const std_msgs::Int32ConstPtr &choice);
};

void Choice_Listener::callback2(const std_msgs::Int32ConstPtr &choice)
{
	choix = choice->data;
};

// Fonction appelée lorsque la navigation en cours est terminée
void doneCb(const actionlib::SimpleClientGoalState &state,
			const move_base_msgs::MoveBaseResultConstPtr &result)
{
	flag_global = 1;
};

int main(int argc, char **argv)
{

	// Initialisation du noeud
	ros::init(argc, argv, "simple_navigation_goals");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	Battery_Listener battery_listener;
	Choice_Listener choice_listener;

	// On indique que l'on va lire les infos du topic /battery_state
	ros::Subscriber sub1 = nh.subscribe<sensor_msgs::BatteryState>("battery_state", 1, &Battery_Listener::callback1, &battery_listener);
	// On indique que l'on va lire les infos du topic /choix
	ros::Subscriber sub2 = nh.subscribe<std_msgs::Int32>("choix", 1, &Choice_Listener::callback2, &choice_listener);
	// On indique que l'on va publier des messages sur le topic /messages
	ros::Publisher client_pub = nh.advertise<std_msgs::String>("messages", 1);

	// démarage des programmes et du serveur liés à la navigation du robot
	MoveBaseClient ac("move_base", true);
	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();
	ros::spinOnce();

	std_msgs::String message;
	int id;
	choice_listener.choix = -1;

	//On attend que le serveur action soit lancé
	while (!ac.waitForServer(ros::Duration(5.0)))
	{
		ROS_INFO("\n Attente de l'initialisation du systeme\n");
		// On envoie le message pour l'interface web :
		message.data = "Attente de l'initialisation du systeme";
		client_pub.publish(message);
	}
	ROS_INFO("\n Initialisation du system reussie\n");
	message.data = "Initialisation du system reussie";
	client_pub.publish(message);

	int test = 0; //variable permettant de savoir savoir si le node de docking peut être lancé
	int a_u = 0;  //Vérification de l'arrêt d'urgence

	while (true)
	{
		if (a_u == 1)
		{
			break;
		}
		test = 0;

		// Création d'un vecteur qui va prendre la liste des noeuds en cours d'utilisation
		std::vector<std::string> V;
		std::vector<std::string>::iterator it;

		ros::master::getNodes(V);
		bool alive = false;
		it = V.begin();
		// On va regarder si le noeud /simple_navigation_goals est encore vivant, si ce n'est pas le cas alors le noeud battery_monitoring l'a tué afin de forcer le robot à retourner au dock
		for (it = V.begin(); it < V.end(); it++)
		{
			if (*it == "/simple_navigation_goals")
				alive = true;
		}
		// Fonctionnement provisoire car il faut forcément que le turtle soit éteint pour le recharger donc à changer pour le meuble
		if (alive == false)
		{
			std::cout << "\n Le robot va retourner à sa station de rechargement car il manque de batterie, veuillez l'éteindre et le mettre en charge \n";
			message.data = "Le robot va retourner à sa station de rechargement car il manque de batterie, veuillez l'éteindre et le mettre en charge";
			client_pub.publish(message);
		}
		//	ros::Duration(5).sleep();

		ros::spinOnce();

		id = choice_listener.choix;
		int test_case = 0;
		switch (id)
		{
		// Si on veut quitter :
		case 0:
			return 0;

		//-------------------------------------------------------------------------------------------------------------------------------
		// SALON
		//-------------------------------------------------------------------------------------------------------------------------------
		// Position 1 :
		case 1:

			test_case = 1;
			// Coordonnées du salon :
			goal.target_pose.pose.position.x = 1.35772748295;
			goal.target_pose.pose.position.y = 0.512409598971;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.996273150458;
			goal.target_pose.pose.orientation.w = 0.0862543313475;

			ac.sendGoal(goal, &doneCb); //Envoi de la commande et attente de la fin de la navigation pour déclencher donecb
			std::cout << " \n Objectif envoye\n";
			message.data = "Objectif envoyé, le robot va se déplacer jusqu'au salon";
			client_pub.publish(message);

			while (test == 0)
			{
				ros::spinOnce();						//On réactualise choice_listener
				if (choice_listener.choix != test_case) // Si la commande est différente de la commande initiale (ie on a cliqué sur un autre bouton)
				{
					ac.cancelGoal(); //Annulation de la commande
					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le robot n'a pas atteint son objectif";
					client_pub.publish(message);
					ros::Duration(2).sleep();
					test = 1;
					flag_global = 0;
					//break;
				}

				if (flag_global == 1 && test != 1) //Si la navigation est terminée
				{
					flag_global = 0;
					std::cout << " \n Fin de la navigation\n";
					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						std::cout << "\n Le robot a bien atteint son objectif\n";
						message.data = "Le robot a bien atteint son objectif";
						client_pub.publish(message);
					}
					else
					{
						std::cout << "\n Le robot n'a pas atteint son objectif\n";
						message.data = "Le robot n'a pas atteint son objectif";
						client_pub.publish(message);
					}
					ros::Duration(2).sleep();
					choice_listener.choix = -1;
					test = 1;
					//break;
				}
				ros::Duration(0.5).sleep();
			}
			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// CHAMBRE
			//-------------------------------------------------------------------------------------------------------------------------------

		case 2:

			test_case = 2;
			// Coordonnées de la chambre :
			goal.target_pose.pose.position.x = 0.21694349891;
			goal.target_pose.pose.position.y = -0.266864040157;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.662989981088;
			goal.target_pose.pose.orientation.w = 0.748628268887;

			ac.sendGoal(goal, &doneCb);
			std::cout << " \n Objectif envoye\n";
			message.data = "Objectif envoyé, le robot va se déplacer jusqu'à la chambre";
			client_pub.publish(message);

			while (test == 0)
			{
				ros::spinOnce();
				if (choice_listener.choix != test_case)
				{
					ac.cancelGoal();
					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le robot n'a pas atteint son objectif";
					client_pub.publish(message);
					ros::Duration(2).sleep();
					test = 1;
					flag_global = 0;
					//break;
				}

				if (flag_global == 1 && test != 1)
				{
					flag_global = 0;
					std::cout << " \n Fin de la navigation\n";
					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						std::cout << "\n Le robot a bien atteint son objectif\n";
						message.data = "Le robot a bien atteint son objectif";
						client_pub.publish(message);
					}
					else
					{
						std::cout << "\n Le robot n'a pas atteint son objectif\n";
						message.data = "Le robot n'a pas atteint son objectif";
						client_pub.publish(message);
					}
					ros::Duration(2).sleep();
					test = 1;
					//break;
				}
				ros::Duration(0.5).sleep();
			}
			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// DOCK
			//-------------------------------------------------------------------------------------------------------------------------------

		case 3:

			test_case = 3;
			// Position proche du dock
			goal.target_pose.pose.position.x = 0.209177836221;
			goal.target_pose.pose.position.y = 0.0;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.988473330604;
			goal.target_pose.pose.orientation.w = 0.151395094654;

			ac.sendGoal(goal, &doneCb);
			std::cout << " \n Objectif envoye\n";
			message.data = "Objectif envoyé, le robot va se déplacer jusqu'à sa base de chargement";
			client_pub.publish(message);

			while (test == 0)
			{
				ros::spinOnce();
				if (choice_listener.choix != test_case)
				{
					ac.cancelGoal();
					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le robot n'a pas atteint son objectif";
					client_pub.publish(message);
					ros::Duration(2).sleep();
					test = 1;
					flag_global = 0;
				}

				if (flag_global == 1 && test != 1)
				{
					flag_global = 0;
					std::cout << " \n Fin de la navigation\n";
					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						std::cout << "\n Le robot a bien atteint son objectif\n";
						message.data = "Le robot a bien atteint son objectif";
						client_pub.publish(message);
					}
					else
					{
						std::cout << "\n Le robot n'a pas atteint son objectif\n";
						message.data = "Le robot n'a pas atteint son objectif";
						client_pub.publish(message);
					}
					ros::Duration(2).sleep();
					test = 1;

					//Le robot va ensuite tourner sur lui-même jusqu'à voir le code de son dock, puis va rejoindre le dock :
					system("roslaunch turtlebot3_automatic_parking_vision turtlebot3_automatic_parking_vision.launch");
					std::cout << " \n Le robot est à son dock\n";
					message.data = "Le robot est à son dock";
					client_pub.publish(message);
					choice_listener.choix = -1;
					break;
				}
				ros::Duration(0.5).sleep();
			}

			//-------------------------------------------------------------------------------------------------------------------------------
			// CUISINE
			//-------------------------------------------------------------------------------------------------------------------------------

		case 4:

			test_case = 4;

			// Coordonnées du plan de travail :
			goal.target_pose.pose.position.x = 0.21694349891;
			goal.target_pose.pose.position.y = -0.266864040157;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.662989981088;
			goal.target_pose.pose.orientation.w = 0.748628268887;

			ac.sendGoal(goal, &doneCb);
			std::cout << " \n Objectif envoye\n";
			message.data = "Objectif envoyé, le robot va se déplacer jusqu'au plan de travail";
			client_pub.publish(message);

			while (test == 0)
			{
				ros::spinOnce();
				if (choice_listener.choix != test_case)
				{
					ac.cancelGoal();
					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le robot n'a pas atteint son objectif";
					client_pub.publish(message);
					ros::Duration(2).sleep();
					test = 1;
					flag_global = 0;
					//break;
				}

				if (flag_global == 1 && test != 1)
				{
					flag_global = 0;
					std::cout << " \n Fin de la navigation\n";
					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						std::cout << "\n Le robot a bien atteint son objectif\n";
						message.data = "Le robot a bien atteint son objectif";
						client_pub.publish(message);
					}
					else
					{
						std::cout << "\n Le robot n'a pas atteint son objectif\n";
						message.data = "Le robot n'a pas atteint son objectif";
						client_pub.publish(message);
					}
					ros::Duration(2).sleep();
					test = 1;
					//break;
				}
				ros::Duration(0.5).sleep();
			}
			break;

		case 5:

			test_case = 5;

			// Coordonnées du plan de la table :
			goal.target_pose.pose.position.x = 0.21694349891;
			goal.target_pose.pose.position.y = -0.266864040157;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.662989981088;
			goal.target_pose.pose.orientation.w = 0.748628268887;

			ac.sendGoal(goal, &doneCb);
			std::cout << " \n Objectif envoye\n";
			message.data = "Objectif envoyé, le robot va se déplacer jusqu'à la table de la cuisine";
			client_pub.publish(message);

			while (test == 0)
			{
				ros::spinOnce();
				if (choice_listener.choix != test_case)
				{
					ac.cancelGoal();
					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le robot n'a pas atteint son objectif";
					client_pub.publish(message);
					ros::Duration(2).sleep();
					test = 1;
					flag_global = 0;
					//break;
				}

				if (flag_global == 1 && test != 1)
				{
					flag_global = 0;
					std::cout << " \n Fin de la navigation\n";
					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						std::cout << "\n Le robot a bien atteint son objectif\n";
						message.data = "Le robot a bien atteint son objectif";
						client_pub.publish(message);
					}
					else
					{
						std::cout << "\n Le robot n'a pas atteint son objectif\n";
						message.data = "Le robot n'a pas atteint son objectif";
						client_pub.publish(message);
					}
					ros::Duration(2).sleep();
					test = 1;
					//break;
				}
				ros::Duration(0.5).sleep();
			}
			break;

		case 6:

			test_case = 6;

			// Coordonnées du du frigidaire :
			goal.target_pose.pose.position.x = 0.21694349891;
			goal.target_pose.pose.position.y = -0.266864040157;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.662989981088;
			goal.target_pose.pose.orientation.w = 0.748628268887;

			ac.sendGoal(goal, &doneCb);
			std::cout << " \n Objectif envoye\n";
			message.data = "Objectif envoyé, le robot va se déplacer jusqu'au frigidaire";
			client_pub.publish(message);

			while (test == 0)
			{
				ros::spinOnce();
				if (choice_listener.choix != test_case)
				{
					ac.cancelGoal();
					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le robot n'a pas atteint son objectif";
					client_pub.publish(message);
					ros::Duration(2).sleep();
					test = 1;
					flag_global = 0;
					//break;
				}

				if (flag_global == 1 && test != 1)
				{
					flag_global = 0;
					std::cout << " \n Fin de la navigation\n";
					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						std::cout << "\n Le robot a bien atteint son objectif\n";
						message.data = "Le robot a bien atteint son objectif";
						client_pub.publish(message);
					}
					else
					{
						std::cout << "\n Le robot n'a pas atteint son objectif\n";
						message.data = "Le robot n'a pas atteint son objectif";
						client_pub.publish(message);
					}
					ros::Duration(2).sleep();
					test = 1;
					//break;
				}
				ros::Duration(0.5).sleep();
			}
			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// STOP
			//-------------------------------------------------------------------------------------------------------------------------------

		case 7:

			// Stop :
			std::cout << " \n Arret de la commande en cours\n";
			message.data = "Objectif atteint, le robot s'est arrêté";
			client_pub.publish(message);
			choice_listener.choix = -1;
			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// ARRÊT D'URGENCE
			//-------------------------------------------------------------------------------------------------------------------------------

		case 8:

			// Arrêt des fonctionnalités du robot :
			std::cout << " \n Arret d'urgence en cours\n";
			message.data = "Le bouton d'arrêt d'urgence a été activé mais le joystick reste fonctionnel pour déplacer le robot. Veuillez attendre 10s avant d'appuyer sur le bouton [Réactivation]";
			client_pub.publish(message);
			choice_listener.choix = -1;
			a_u = 1;
			system("rosrun emergency_stop emergency_stop");
			break;
		}

		loop_rate.sleep();
	}
	return 0;
}
