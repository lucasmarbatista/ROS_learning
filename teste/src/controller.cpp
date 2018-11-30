#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
// código para publicar e subscrever 


class controller { //Define uma classe controller
    public:
        controller(){
            sub = n_teste.subscribe("chatter", 1000, &controller::callback, this);
            //Inicia o subscriber //subscreve no topico "chatter"
            pub = n_teste.advertise<std_msgs::String>("anotherTopic",1000);
	        //Incializa um publicador do ROS como chatter_pub = avisa ao nó n_teste que o tópico "anotherTopic" vai ser enviado em 1000 mensagens, configurando o tópico
}

    void callback(const std_msgs::String::ConstPtr& msg){
        std_msgs::String pub_str;
        std::stringstream ss;

        ss << "controller heard: " << msg->data.c_str();

        pub_str.data = ss.str();

        std::cout << pub_str.data.c_str() << std::endl;

        pub.publish(pub_str);

        ros::spinOnce();
        
    }


    private:
        ros::NodeHandle n_teste; //Define objeto n_teste como NodeHandle, que permite agir nos nós
        ros::Subscriber sub; //Define objeto sub como Subscriber, que permite se inscrever no tópico 
        ros::Publisher pub; //Define objeto pub como Publisher, que permite publicar no tópico 
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "controller"); //Inicializa o nó controller
    controller ctrl; //inicializa a função controller

    ros::spin(); 

    return 0;

}
