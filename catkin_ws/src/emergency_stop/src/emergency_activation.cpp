#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

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
    ros::init(argc, argv, "emergency_activation");
    ros::NodeHandle nh;
    ros::Publisher client_pub = nh.advertise<std_msgs::String>("client", 1);

    // Publication sur le topic /motor_power sur lequel le noeud va publier l'information oour arrêter les moteurs dynamixel
    ros::Publisher activ_pub = nh.advertise<std_msgs::Bool>("motor_power", 1);

    Choice_Listener choice_listener;
    // On indique que l'on va lire les infos du topic /choix
    ros::Subscriber sub2 = nh.subscribe<std_msgs::Int32>("choix", 1, &Choice_Listener::callback2, &choice_listener);

    ros::Rate loop_rate(10);
    std_msgs::String message;
    std_msgs::Bool etat_moteurs;

    int flag = 0; //Test pour la publication des messages

    // Création d'un vecteur qui va prendre la liste des noeuds en cours d'utilisation
    std::vector<std::string> V;
    std::vector<std::string>::iterator it;

    choice_listener.choix = -1;

    ros::master::getNodes(V);
    bool alive = false;
    bool docking = false;
    it = V.begin();

    // On va regarder si le noeud /noeud battery_monitoring est vivant, si ce n'est pas le cas alors cela signifie que l'on doit redémarrer /simple_navigation_goals
    for (it = V.begin(); it < V.end(); it++)
    {
        if (*it == "/battery_monitoring")
        {
            alive = true;
        }

        if (*it == "/ar_track_alvar")
        {
            docking = true;
        }
    }

    while (ros::ok)
    {

        if (flag == 2) //Pourquoi 2 ? Je ne sais pas, avec 1 cela ne suffisait pas
        {
            ROS_INFO("\nReactivation des moteurs en cours\n");
            message.data = "Les moteurs du robot ont été réactivés, vous pouvez utiliser le joystick\n";
            client_pub.publish(message);
            break;
        }

        etat_moteurs.data = true;
        activ_pub.publish(etat_moteurs);
        ros::Duration(2).sleep();

        flag++;

        ros::spinOnce();
    }

    while (ros::ok)
    {
        ros::spinOnce();
        if (choice_listener.choix == 9)
        {
            message.data = "La réactivation des fonctionnalités du robot est en cours. Veuillez attendre 10s avant d'utiliser l'interface web";
            client_pub.publish(message);

            if (alive == true)
            {
                system("gnome-terminal -x rosrun simple_navigation_goals simple_navigation_goals");
		system("gnome-terminal -x rosrun niryo_control niryo_control_v2");
            }

            if (docking == true)
            {
                system("gnome-terminal -x rosrun turtlebot3_automatic_parking_vision automatic_parking_vision");
		system("gnome-terminal -x rosrun niryo_control niryo_control_v2");
            }
            
            choice_listener.choix = -1;
            break;
        }
    }

    return 0;
}
