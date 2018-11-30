#include "ros/ros.h"
#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include "sensor_msgs/LaserScan.h" // Biblioteca LaserScan
#include <iostream>
#include <sstream>
#include <geometry_msgs/Twist.h> // Biblioteca para adicionar a variável geometry_msgs


//#include <algorithm>    // std::min_element, std::max_element

using namespace std;

namespace husky_highlevel_controller {

float min_test = 1000.0;
int  angle;
int count = 0;


void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
//sensor_msgs::LaserScan é o tipo do tópico a ser subscrito
// msg é onde a informação do tópico é armazenada

//1.0 - Subscriber
    float array_test2[720];
    int i;
    min_test=1000.0;

   for(i=0; i < 719; i=i+1){

     // Usar em float

     array_test2[i] = msg->ranges[i];

     if(array_test2[i] < min_test){
      min_test = array_test2[i];
      angle = i;
      }
    }
}


HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{

  ros::NodeHandle husky_teste; //Define husky_teste como NodeHandle

  ros::Subscriber sub = husky_teste.subscribe("/scan", 1, chatterCallback);
 //Inicia o subscriber //subscreve no topico "/scan"

  ros::Publisher pub_vel = husky_teste.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel",10);

  ros::Rate loop_rate(10);

  while(ros::ok()){

    geometry_msgs::Twist msg_pub;

    std::cout << "Min is " << min_test << std::endl;
    std::cout << "Angle: " << angle << std::endl;
    int angle_min = 352;
    int angle_gre = 368;
    int count ;
    //loop_rate.sleep();

    if(angle <= angle_min && count == 0 )
    {

      msg_pub.angular.z = 0.1;
      cout << "Angular Min Movement" << std::endl;
      loop_rate.sleep();
    }
    else if(angle>=angle_gre && count == 0)
    {
      msg_pub.angular.z = -0.1;

      cout << "Angular Gre Movement" << std::endl;
      loop_rate.sleep();

    }
    else if(angle<angle_gre && angle>angle_min && count == 0)
    {
      std::cout << "Moving Foward" << std::endl;
      msg_pub.linear.x = 2.5;
      msg_pub.angular.z = 0.0;

      if(min_test<1.5)
      {
        count = 1;
        cout << count << std::endl;
      }
      loop_rate.sleep();

    }

    else if(count == 1)
    {
      //count = count +1;
      std::cout << "Moving Foward" << std::endl;
      msg_pub.linear.x = 2.5;
      msg_pub.angular.z = 0.0;
      loop_rate.sleep();
    }
    pub_vel.publish(msg_pub);

   ros::spinOnce(); //linha para continuar rodando código e chamar o callback

  }

}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

} /* namespace */
