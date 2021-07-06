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
	int test_case = 0;
	bool test_rviz = true; //On vérifie si /rviz est actif
	bool docking_first_check = false; //On vérifie si le node de docking est actif
	bool docking_exist = false; //On vérifie si le docking a été lancé
	bool alive = false;
	bool check_arm = false;

	// Création d'un vecteur qui va prendre la liste des noeuds en cours d'utilisation
	std::vector<std::string> V;
	std::vector<std::string>::iterator it;

	while (true)
	{
		if (a_u == 1)
		{
			break;
		}
		test = 0;



		ros::master::getNodes(V);
		test_rviz = false;
		alive = false;
		check_arm = false;
		
		it = V.begin();

		// On va regarder si le noeud /simple_navigation_goals est encore vivant, si ce n'est pas le cas alors un des autres nodes l'a tué afin de forcer le robot à retourner à s'arrêter
		for (it = V.begin(); it < V.end(); it++)
		{
			if (*it == "/simple_navigation_goals")
				alive = true;
			if (*it == "/servir" || *it == "/ranger")
				check_arm = true;
			if (*it == "/rviz")
				test_rviz = true;
			if (*it == "/automatic_parking_vision")
				docking_first_check = true;								
		}

		V.clear();


		if (test_rviz == true && docking_first_check == true) //Si le docking a été lancé alors on pourra déclarer que le docking sera fini une fois que /rviz ne sera plus présent
		{
			docking_exist = true;
		}

		if (docking_first_check == true) //test
		{
			std::cout << "Test docking ok\n" ;	
		}

		if (test_rviz == false && docking_exist == true) //On vérifie si /rviz a disparu et si le docking a eu lieu pour relancer la navigation
		{
			// system("rosnode kill automatic_parking_vision");
			// system("rosnode kill rviz");
			system("rosnode kill ar_track_alvar");
            system("rosnode kill joint_state_publisher_gui");
            system("rosnode kill robot_state_publisher");
            system("rosnode kill camera_rgb_optical_frame_to_cam");

			docking_first_check = false;
			docking_exist = false;
			system("gnome-terminal -x roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=/home/chaire/chaire_mad.yaml");
		}


		// Fonctionnement provisoire car il faut forcément que le turtle soit éteint pour le recharger donc à changer pour le meuble
		if (alive == false)
		{
			if (check_arm == true)
			{
				std::cout << "\nLa navigation s'est arretee car le bras est en cours d'utilisation\n";
				message.data = "La navigation s'est arrêtée car le bras est en cours d'utilisation";
				client_pub.publish(message);
			}
			else
			{
				std::cout << "\nLe node de navigation s'est arrete il est possible que le robot doive se recharger\n";
				message.data = "La navigation s'est arrêtée, il est possible que le robot doive aller se recharger.";
				client_pub.publish(message);
			}
			ros::spinOnce();
			return 0;
		}
		//	ros::Duration(5).sleep();

		ros::spinOnce();

		id = choice_listener.choix;
		test_case = 0;
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
			// goal.target_pose.pose.position.x = 0.797766892852;
			// goal.target_pose.pose.position.y = 0.836321304049;
			// goal.target_pose.pose.position.z = 0;
			// goal.target_pose.pose.orientation.x = 0;
			// goal.target_pose.pose.orientation.y = 0;
			// goal.target_pose.pose.orientation.z = 0.91026232607;
			// goal.target_pose.pose.orientation.w = 0.414032000862;

			goal.target_pose.pose.position.x = 5.17235301551;
			goal.target_pose.pose.position.y = 3.11603336181;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = -0.846030728865;
			goal.target_pose.pose.orientation.w = 0.533134134919;

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
			// goal.target_pose.pose.position.x = 1.39836465437;
			// goal.target_pose.pose.position.y = -0.0866317770615;
			// goal.target_pose.pose.position.z = 0;
			// goal.target_pose.pose.orientation.x = 0;
			// goal.target_pose.pose.orientation.y = 0;
			// goal.target_pose.pose.orientation.z = 0.474518836348;
			// goal.target_pose.pose.orientation.w = 0.880245348724;

			goal.target_pose.pose.position.x = 7.38073386966;
			goal.target_pose.pose.position.y = 2.08008514513;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = -0.98944214492;
			goal.target_pose.pose.orientation.w = 0.144928402518;

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
			// goal.target_pose.pose.position.x = -0.638422714931;
			// goal.target_pose.pose.position.y = -0.196174353078;
			// goal.target_pose.pose.position.z = 0;
			// goal.target_pose.pose.orientation.x = 0;
			// goal.target_pose.pose.orientation.y = 0;
			// goal.target_pose.pose.orientation.z = 0.999759637288;
			// goal.target_pose.pose.orientation.w = 0.0219241339678;

			goal.target_pose.pose.position.x = 5.56863107588;
			goal.target_pose.pose.position.y = 4.154874398;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.993903984118;
			goal.target_pose.pose.orientation.w = 0.110249128588;

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
					system("gnome-terminal -x roslaunch turtlebot3_automatic_parking_vision turtlebot3_automatic_parking_vision.launch");
					std::cout << " \n Le robot est à son dock\n";
					message.data = "Le robot est à son dock";
					client_pub.publish(message);
					choice_listener.choix = -1;
				}
				ros::Duration(0.5).sleep();
			}
			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// CUISINE
			//-------------------------------------------------------------------------------------------------------------------------------

		case 4:

			test_case = 4;

			// Coordonnées du plan de travail :
			// goal.target_pose.pose.position.x = 0.561170537189;
			// goal.target_pose.pose.position.y = -0.660492907653;
			// goal.target_pose.pose.position.z = 0;
			// goal.target_pose.pose.orientation.x = 0;
			// goal.target_pose.pose.orientation.y = 0;
			// goal.target_pose.pose.orientation.z = -0.693860522948;
			// goal.target_pose.pose.orientation.w = 0.720109418557;

			goal.target_pose.pose.position.x = 5.8910502669;
			goal.target_pose.pose.position.y = 1.57074158932;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = -0.807062046261;
			goal.target_pose.pose.orientation.w = 0.590466640451;

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
			choice_listener.choix = -1;
			break;

		case 5:

			test_case = 5;

			// Coordonnées de la table :
			goal.target_pose.pose.position.x = -0.11775260212;
			goal.target_pose.pose.position.y = 0.355234211892;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = 0.762233304106;
			goal.target_pose.pose.orientation.w = 0.647302394644;

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
			choice_listener.choix = -1;
			break;

		case 6:

			test_case = 6;

			// Coordonnées du du frigidaire :
			goal.target_pose.pose.position.x = -0.796167706192;
			goal.target_pose.pose.position.y = -0.736104374785;
			goal.target_pose.pose.position.z = 0;
			goal.target_pose.pose.orientation.x = 0;
			goal.target_pose.pose.orientation.y = 0;
			goal.target_pose.pose.orientation.z = -0.973813470984;
			goal.target_pose.pose.orientation.w =  0.227348463223;

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
			choice_listener.choix = -1;
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
			system("gnome-terminal -x rosrun emergency_stop emergency_stop");
			break;
		}

		loop_rate.sleep();
	}
	return 0;
}
