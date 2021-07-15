#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    // Initialisation du noeud
    ros::init(argc, argv, "emergency_stop");
    ros::NodeHandle nh;
    ros::Publisher client_pub = nh.advertise<std_msgs::String>("client", 1);

    // Publication sur le topic /motor_power sur lequel le noeud va publier l'information oour arrêter les moteurs dynamixel
    ros::Publisher stop_pub = nh.advertise<std_msgs::Bool>("motor_power", 1);

    // Publication sur le topic /cmd_vel sur lequel le noeud va publier la commande 0 qui sera la dernière commande prise en compte
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    ros::Rate loop_rate(10);
    std_msgs::String message;
    std_msgs::Bool etat_moteurs;
    geometry_msgs::Twist cmd_arret;

    cmd_arret.linear.x = 0;
    cmd_arret.linear.y = 0;
    cmd_arret.linear.z = 0;

    cmd_arret.angular.x = 0;
    cmd_arret.angular.y = 0;
    cmd_arret.angular.z = 0;

    // Création d'un vecteur qui va prendre la liste des noeuds en cours d'utilisation
    std::vector<std::string> V;
    std::vector<std::string>::iterator it;

    ros::master::getNodes(V);

    std::string node_actif;
    int compteur_nodes = 0;

    while (ros::ok)
    {
        ros::spinOnce();

        if (V.empty())
        {
            break;
        }

        for (it = V.begin(); it < V.end(); it++)
        {
            //if (*it != "/emergency_stop" && *it != "/turtlebot3_diagnostics" && *it != "/turtlebot3_core" && *it != "/turtlebot3_lds" && *it != "/rosout")

	    if (*it == "/simple_navigation_goals" || *it == "/turtlebot3" || *it == "/turtlebot3_client" || *it == "/automatic_parking_vision")
            {
                node_actif = *it;
                system(("rosnode kill " + node_actif).c_str());
                compteur_nodes += 1;
            }
        }

        V.clear();
        vel_pub.publish(cmd_arret);

        if (compteur_nodes == 0)
        {
            break;
        }

        else
        {
            etat_moteurs.data = false;
            stop_pub.publish(etat_moteurs);
            ros::Duration(2).sleep();

            ROS_INFO("\nArret du robot et annulation de toutes les commandes\n");

            message.data = "Les moteurs du robot ont été coupés\n";
            client_pub.publish(message);
            compteur_nodes = 0;
        }
    }
    ros::shutdown();

    system("rosrun emergency_stop emergency_activation");
    return 0;
}
