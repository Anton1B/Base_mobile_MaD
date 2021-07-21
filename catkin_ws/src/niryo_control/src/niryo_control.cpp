#include <ros/ros.h>
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include <boost/container/string.hpp>

// Définition de la classe Niryo_Listener qui va servir à récupérer les informations envoyée depuis le Niryo
class Niryo_Listener
{
public:
	int reponse;

	void callback(const std_msgs::Int32ConstPtr &response);
};

void Niryo_Listener::callback(const std_msgs::Int32ConstPtr &response)
{
	reponse = response->data;
};

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



int main(int argc, char **argv)
{

	// Initialisation du noeud
	ros::init(argc, argv, "niryo_control");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	Choice_Listener choice_listener;
	Niryo_Listener niryo_listener;
	//Docking_Listener docking_listener;

	// On indique que l'on va lire les infos du topic /niryo_response (Signale au node si l'action est terminée ou non)
	ros::Subscriber sub1 = nh.subscribe<std_msgs::Int32>("reponse", 1, &Niryo_Listener::callback, &niryo_listener);

	// On indique que l'on va lire les infos du topic /choix (information en provenance des boutons de l'interface web)
	ros::Subscriber sub2 = nh.subscribe<std_msgs::Int32>("choix", 1, &Choice_Listener::callback2, &choice_listener);

	// On indique que l'on va publier des messages sur le topic /messages_niryo (Publication des messages d'état sur l'interface web)
	ros::Publisher client_pub = nh.advertise<std_msgs::String>("messages_niryo", 1);

	// On indique que l'on va publier des messages sur le topic /interactions_niryo (Pour mettre en pause et interrompre l'action)
	ros::Publisher niryo_pub = nh.advertise<std_msgs::Int32>("interactions_niryo", 1);

	std_msgs::String message;
	std_msgs::Int32 ask_niryo;
	std::string commande;
	int id;
	choice_listener.choix = -1;
	niryo_listener.reponse = 0;

	int test = 0;		//variable permettant de savoir savoir si le node de docking peut être lancé
	int flag = 0;		//Vérification de l'arrêt ou de la pause
	int test_case = 0;	//Vérification de l'étape du switch en cours
	ask_niryo.data = 0; //Variable permettant de lancer la mise en pause

	while (true)
	{

		commande = "\0";
		niryo_listener.reponse = -1;
		test_case = 0;
		test = 0;

		ros::spinOnce();

		id = choice_listener.choix - 9;

		switch (id)
		{
		// Si on veut quitter :
		case 0:
			return 0;

			//-------------------------------------------------------------------------------------------------------------------------------
			// SERVIR
			//-------------------------------------------------------------------------------------------------------------------------------

		case 1:
			system("rosnode kill simple_navigation_goals");

			test_case = 10;

			system("gnome-terminal -x roslaunch niryo_control activ_arm_servir.launch");

			std::cout << " \n Objectif envoye\n";
			message.data = "Vous avez demandé le service d'un objet, vous ne pouvez pas déplacer la base mobile. Veuillez faire attention aux mouvements du bras";
			client_pub.publish(message);

			while (test == 0)
			{
				//std::cout << niryo_listener.reponse << std::endl ;
				ros::spinOnce();						//On réactualise choice_listener
				if (choice_listener.choix != test_case) // Si la commande est différente de la commande initiale (ie on a cliqué sur un autre bouton)
				{

					if (test_case == 14)
					{
						ask_niryo.data = 2;
					}

					else
					{
						ask_niryo.data = 0;
					}
					niryo_pub.publish(ask_niryo); //On signale au bras qu'on veut interrompre l'action

					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le bras n'a pas atteint son objectif";
					client_pub.publish(message);

					test = 1;
					flag = 1;
				}

				if (niryo_listener.reponse == 1) //Si l'action est terminée
				{
					//docking_listener.drapeau = 0;
					std::cout << " \n Fin de l'action\n";
					std::cout << "\n Le bras a depose l'objet sur la zone de depot\n";
					message.data = "Le bras a déposé l'objet sur la zone de dépot\n";
					client_pub.publish(message);

					ros::Duration(2).sleep();
					niryo_listener.reponse = -1;
					test = 1;
					system("gnome-terminal -x rosrun simple_navigation_goals simple_navigation_goals");
				}
				ros::Duration(0.5).sleep();
			}
			if (flag == 1)
			{
				flag = 0;
				break;
			}
			choice_listener.choix = -1;
			ros::spinOnce();
			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// PAUSE
			//-------------------------------------------------------------------------------------------------------------------------------

		case 2:

			test_case = 11;

			ask_niryo.data = 0; //Demande de pause

			niryo_pub.publish(ask_niryo); //On signale au bras qu'on veut interrompre l'action
			ros::spinOnce();

			std::cout << " \n Objectif envoye\n";
			message.data = "L'action a été mise en pause. Cliquez sur [Marche] pour reprendre l'action";
			client_pub.publish(message);

			choice_listener.choix = -1;
			ros::spinOnce();

			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// MARCHE
			//-------------------------------------------------------------------------------------------------------------------------------

		case 3:

			test_case = 12;

			ask_niryo.data = 1; //Demande de reprise de l'action
			niryo_pub.publish(ask_niryo);
			ros::spinOnce();

			ros::Duration(2).sleep();

			std::cout << " \n Objectif envoye\n";
			message.data = "L'action a repris";
			client_pub.publish(message);

			choice_listener.choix = -1;
			ros::spinOnce();

			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// RANGER
			//-------------------------------------------------------------------------------------------------------------------------------

		case 4:

			system("rosnode kill simple_navigation_goals");

			test_case = 13;

			// commande = "gnome-terminal -x sshpass -p \'robotics\' ssh -t niryo@192.168.1.130  \"source /opt/ros/kinetic/setup.bash; source ~/catkin_ws/devel/setup.bash; export ROS_MASTER_URI=http://192.168.1.122:11311; export ROS_HOSTNAME=192.168.1.130; python catkin_ws/src/niryo_one_python_api/examples/ranger.py;\" ";
			// system(commande.c_str()); //Envoi de la commande

			system("gnome-terminal -x roslaunch niryo_control activ_arm_ranger.launch");

			std::cout << " \n Objectif envoye\n";
			message.data = "Vous avez demandé le rangement d'un objet, vous ne pouvez pas déplacer la base mobile. Veuillez faire attention aux mouvements du bras";
			client_pub.publish(message);

			while (test == 0)
			{
				ros::spinOnce();						//On réactualise choice_listener
				if (choice_listener.choix != test_case) // Si la commande est différente de la commande initiale (ie on a cliqué sur un autre bouton)
				{
					std::cout << " \n Arret de la commande en cours\n";
					std::cout << "\n Le robot n'a pas atteint son objectif\n";
					message.data = "Arrêt de la commande en cours, le bras n'a pas atteint son objectif";
					client_pub.publish(message);

					if (test_case == 14)
					{
						ask_niryo.data = 2;
					}

					else
					{
						ask_niryo.data = 0;
					}

					niryo_pub.publish(ask_niryo); //On signale au bras qu'on veut interrompre l'action

					test = 1;
					flag = 1;
				}

				if (niryo_listener.reponse == 1) //Si l'action est terminée
				{
					//docking_listener.drapeau = 0;
					std::cout << " \n Fin de l'action'\n";
					std::cout << "\n Le bras a range l'objet dans le meuble\n";
					message.data = "Le bras a rangé l'objet dans le meuble\n";
					client_pub.publish(message);

					ros::Duration(2).sleep();
					niryo_listener.reponse = -1;
					test = 1;

					system("gnome-terminal -x rosrun simple_navigation_goals simple_navigation_goals");
				}
				ros::Duration(0.5).sleep();
			}

			if (flag == 1)
			{
				flag = 0;
				break;
			}
			choice_listener.choix = -1;
			ros::spinOnce();
			break;

			//-------------------------------------------------------------------------------------------------------------------------------
			// ARRET DE L'ACTION
			//-------------------------------------------------------------------------------------------------------------------------------

		case 5:

			test_case = 14;

			ask_niryo.data = 2; //Demande d'arret de l'action
			niryo_pub.publish(ask_niryo);
			ros::spinOnce();

			std::cout << " \n Objectif envoye\n";
			message.data = "L'action a été arrêtée, veuillez attendre que le bras se replie avant de lancer une autre action ou de déplacer la base mobile";
			client_pub.publish(message);

			choice_listener.choix = -1;
			ros::spinOnce();

			system("gnome-terminal -x rosrun simple_navigation_goals simple_navigation_goals");

			break;

		}

		loop_rate.sleep();
	}
	return 0;
}
