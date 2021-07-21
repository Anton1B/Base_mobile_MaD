#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include <pthread.h>
#include <iostream>

static volatile bool keep_running = true;

static void *userInput_thread(void *)
{
    while (keep_running)
    {
        if (std::cin.get() != '\0')
        {
            //Si on a une interruption au clavier
            system("rosnode kill turtlebot3_teleop_keyboard");
            keep_running = false;
        }
    }
}

int main(int argc, char **argv)
{
    // Initialisation du noeud
    ros::init(argc, argv, "emergency_activation_for_tests");
    ros::NodeHandle nh;
    ros::Publisher client_pub = nh.advertise<std_msgs::String>("client", 1);

    // Publication sur le topic /motor_power sur lequel le noeud va publier l'information oour arrêter les moteurs dynamixel
    ros::Publisher activ_pub = nh.advertise<std_msgs::Bool>("motor_power", 1);

    ros::Rate loop_rate(10);
    std_msgs::String message;
    std_msgs::Bool etat_moteurs;

    int flag = 0; //Test pour la publication des messages

    // Création d'un vecteur qui va prendre la liste des noeuds en cours d'utilisation
    std::vector<std::string> V;
    std::vector<std::string>::iterator it;

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
            message.data = "Les moteurs du robot ont été réactivés, vous pouvez utiliser le clavier pour commander\n";
            client_pub.publish(message);
            break;
        }

        etat_moteurs.data = true;
        activ_pub.publish(etat_moteurs);
        ros::Duration(2).sleep();

        flag++;

        ros::spinOnce();
    }

    ROS_INFO("\nLa commande au clavier va s'activer\n");
    system("gnome-terminal -x roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch");
    ROS_INFO("\nRelancer les nodes en appuyant sur une touche du clavier puis Enter \n");

    pthread_t tId;
    (void)pthread_create(&tId, 0, userInput_thread, 0);

    while (keep_running)
    {
    }

    (void)pthread_join(tId, NULL);

    ros::spinOnce();

    ROS_INFO("\nRéactivation des fonctionnalités en cours\n");
    message.data = "La reactivation des fonctionnalites du robot est en cours";
    client_pub.publish(message);

    if (alive == true)
    {
        system("gnome-terminal -x rosrun simple_navigation_goals simple_navigation_goals");
    }

    if (docking == true)
    {
        system("gnome-terminal -x rosrun turtlebot3_automatic_parking_vision automatic_parking_vision");
    }
    //system("gnome-terminal -x roslaunch emergency_stop activ_arm.launch");

    return 0;
}
