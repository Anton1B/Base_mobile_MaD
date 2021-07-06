#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/BatteryState.h>
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class Listener 
{
  public:
    double tension;

    void callback(const sensor_msgs::BatteryStateConstPtr& msg);
};

void Listener::callback(const sensor_msgs::BatteryStateConstPtr& msg) 
{
    tension = msg->voltage;
}




int main(int argc, char **argv) 
{
	// Initialisation du noeud
	ros::init(argc, argv, "battery_monitoring");
	ros::NodeHandle nh;
	ros::Publisher client_pub = nh.advertise<std_msgs::String>("client",1);
	// Création du topic /battery_level sur lequel le noeud va publier le % de batterie restante
	ros::Publisher battery_pub = nh.advertise<std_msgs::Int32>("battery_level",1);

	// Inscription au topic /battery_state pour récupérer la tension de la batterie
	Listener listener;
	ros::Subscriber sub = nh.subscribe<sensor_msgs::BatteryState>("battery_state", 1, &Listener::callback, &listener);

	ros::Rate loop_rate(10);
	std_msgs::String message;
    	std_msgs::Int32 pourcentage_batterie;
    	
    	MoveBaseClient ac("move_base", true);
     	move_base_msgs::MoveBaseGoal goal;

    	goal.target_pose.header.frame_id = "map";
    	goal.target_pose.header.stamp = ros::Time::now();

    	while(!ac.waitForServer(ros::Duration(5.0))){
    		ROS_INFO("\n Attente de l'initialisation du systeme");
    	}
    	ROS_INFO("\n Initialisation du systeme reussie");

    	while(ros::ok()){
    		ros::spinOnce();
		// Permet d'attendre que battery_state initialise la valeur correcte de la tension (car au début elle est indiquée à 0V)
    		while (listener.tension < 3)
			loop_rate.sleep();
    		
// Calcul qui va permettre de transformer la tension de la batterie en % restant :
// Lorsque la batterie est considérée comme vide (=0%) on a 11V
// Lorsque la batterie est considérée comme pleine (=100%) on a environ 12,42V
// Comme (12,42-11)/100 = 0.0142, on en déduit qu'à chaque fois que la batterie perd 0.0142V elle perd 1%.
//Cela n'est pas exact puisque cette batterie est une batterie au lithium et on a donc une tension qui est stabilisée à 11,1 V (elle va rester quelques temps à ce niveau de tension avant que celle-ci chute). Cependant cela permet d'avoir malgré tout une idée de la charge actuelle de la batterie même si ce % descendra plus vite à certains moments qu'a d'autres

		double pourcentage = (listener.tension - 11)/0.0142;
		// On transforme le résultat à l'entier le plus proche :
		double result = (double)((int)(pourcentage+0.5));
		if (result < 0)
			result=0;
		if (result>100)
			result=100;
		//std::cout << "\n Le pourcentage de batterie est : " << result << " %\n";
		pourcentage_batterie.data = result;
		battery_pub.publish(pourcentage_batterie);
		ros::Duration(2).sleep();


		// Si la batterie est inférieure à 5% (= 11.071 V) :
		if (result < 5){ 
			// On empeche la personne d'envoyer de nouveaux objectifs au robot :
			system("rosnode kill /simple_navigation_goals");
			
			// Position proche du dock
			goal.target_pose.pose.position.x = -0.429485903875;
				goal.target_pose.pose.position.y = -0.187559953614;
				goal.target_pose.pose.position.z = 0;
				goal.target_pose.pose.orientation.x = 0;
			  	goal.target_pose.pose.orientation.y = 0;
			  	goal.target_pose.pose.orientation.z = 0.999156167315;
			  	goal.target_pose.pose.orientation.w = 0.0410725372552;
	

			ac.sendGoal(goal);
			ROS_INFO("\nLe robot va rejoindre son dock car il n'a plus de batterie");
			ac.waitForResult();

			//Le robot va ensuite tourner sur lui-même jusqu'à voir le code de son dock, puis va rejoindre le dock :
			system("roslaunch turtlebot3_automatic_parking_vision turtlebot3_automatic_parking_vision.launch");
			message.data = "Le robot est à sa station de rechargement, veuillez le mettre en charge";
			client_pub.publish(message);
			// Une fois que le robot est à son dock, on ferme tous les terminaux ce qui va quitter ROS
			system("gnome-terminal -x xdotool getactivewindow windowkill");	
			return 0;

       		}
   	}
   
}
