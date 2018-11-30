#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg) 
{//Inicia a função para imprimir os dados no terminal  

    std::cout << "I heard" << msg->data.c_str() << std:: endl;
    //Imprime no terminal "I heard" + a mensagem que vem do outro nó
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener"); // Inicia o nó "listener" no ROS

    ros::NodeHandle n_teste; //Define n_teste como NodeHandle

    ros::Subscriber sub = n_teste.subscribe("chatter", 1000, chatterCallback);
   //Inicia o subscriber //subscreve no topico "chatter"
     
    ros::spin();

    return 0;
}
