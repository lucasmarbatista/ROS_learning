#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "talker"); //Inicializa o nó talker
	ros::NodeHandle n_teste; //Define objeto n_teste como NodeHandle 
	ros::Publisher chatter_pub = n_teste.advertise<std_msgs::String>("chatter",1000);
	//Incializa um publicador do ROS como chatter_pub = avisa ao nó n_teste que o tópico chatter vai ser enviado em 1000 mensagens, configurando o tópico

	ros::Rate loop_rate(10); //Realiza uma volta a cada 10 ms

	int count = 0; //Inicia Contador igual a 0

	while(ros::ok()) //Enquanto estiver rodando o ross
	{
		std_msgs::String msg; //Define a variável msg como String

		std::stringstream ss; // Define objeto ss como stringstream
		ss << ":hello world " << count; //ss = ":hello world" + contador count
		msg.data = ss.str(); //retorna uma string da stringStream ss e envia para os dados da mensagem

		std::cout << msg.data.c_str() << std::endl; 
		//Imprime os dados (cout) dos dados da mensagem msg, separando
		// std::endl = "/n" ou pular linha

		chatter_pub.publish(msg);
    // utiliza o tópico chatter_pub para publicar a partir da variável msg. Condigurado anteriormente em chatter.pub

		ros::spinOnce(); //linha para continuar rodando código

		loop_rate.sleep(); // pega a referência de loop_rate(10) para analisar o tempo de espera

		++count; //Contador aumentando
	}

	return 0;
}
