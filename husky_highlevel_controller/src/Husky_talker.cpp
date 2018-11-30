#include "ros/ros.h"
#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include "sensor_msgs/LaserScan.h" // Biblioteca LaserScan
#include <iostream>
#include <sstream>
#include <geometry_msgs/Twist.h> // Biblioteca para adicionar a variável geometry_msgs
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>

#define PI 3.14159265

//#include <algorithm>    // std::min_element, std::max_element

using namespace std;

namespace husky_highlevel_controller {

float min_test = 1000.0;
float  angle;
int count = 0;
int range;
float array_test2[720];
float angle_rad;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
//sensor_msgs::LaserScan é o tipo do tópico a ser subscrito
// msg é onde a informação do tópico é armazenada

//1.0 - Subscriber

    int i;
    min_test=1000.0;

   for(i=0; i < 719; i=i+1){

     // Usar em float

     array_test2[i] = msg->ranges[i];
     range = msg->ranges[i];

     if(array_test2[i] < min_test){
      min_test = array_test2[i];
      angle_rad  = msg->angle_min +(i * msg->angle_increment);
      }
    }
  angle = angle_rad*180/PI;
}


HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{

  ros::NodeHandle husky_teste; //Define husky_teste como NodeHandle

  ros::Subscriber sub = husky_teste.subscribe("/scan", 1, chatterCallback);
 //Inicia o subscriber //subscreve no topico "/scan"

  ros::Publisher pub_vel = husky_teste.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel",10);

  //ros::Publisher pub_vel_2 = husky_teste.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel",10);

  //-------------------------------Transformer-----------------------------------
      tf::TransformListener listener;
      listener.waitForTransform("/base_laser", "/odom", ros::Time(0), ros::Duration(10.0));

  //-------------------------------Transformer-----------------------------------


  ros::Rate loop_rate(10);

  int count =0;
  while(ros::ok()){

    geometry_msgs::Twist msg_pub;

    //std::cout << "Min is " << min_test << std::endl;
    std::cout << "Angle: " << angle << std::endl;
    float angle_min = -176.0;
    float angle_gre = 176.0;

    //loop_rate.sleep();

    if(angle <= angle_gre && angle > 0.0 && count == 0 )
    {

      //msg_pub.angular.z = 0.1;
      msg_pub.linear.x = 1.0;
      cout << "Angular Min Movement" << std::endl;
      loop_rate.sleep();
    }
    else if(angle >= angle_min && angle <= 0.0 && count == 0)
    {
      //msg_pub.angular.z = -0.1;
      msg_pub.linear.x = -1.0;

      cout << "Angular Gre Movement" << std::endl;
      loop_rate.sleep();

    }
    else if(angle<angle_gre && angle>angle_min && count == 0)
    {
      std::cout << "Moving Foward" << std::endl;
      msg_pub.linear.x = 1.0;
      //msg_pub.angular.z = 0.1;
      if(min_test<1.5)
      {
        //count = 1;
     //   cout << count << std::endl;
      }
      loop_rate.sleep();

    }

    else if(count == 1)
    {
      //count = count +1;
      std::cout << "Moving Foward" << std::endl;
     // msg_pub.linear.x = 2.5;
      //msg_pub.angular.z = 0.0;
      loop_rate.sleep();
    }

   // cout << angle << " new" << std::endl;
    pub_vel.publish(msg_pub);
//?AAAAAAAAAAAAAA
    //TESSSTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
     //-------------------------------Transformer-----------------------------------

        geometry_msgs::PointStamped laser_point;
        geometry_msgs::PointStamped odom_point;

        laser_point.header.frame_id = "base_laser";
        laser_point.header.stamp = ros::Time();
        laser_point.point.x = min_test*cos(angle_rad);
        laser_point.point.y = min_test*sin(angle_rad);
        //laser_point.point.x = 1.0;
        //laser_point.point.y = 2.0;
        laser_point.point.z = 0.0;

        cout << "A " << laser_point.point << std::endl;

        try{
          listener.transformPoint("odom", laser_point, odom_point);

        }
        catch(tf::TransformException& ex){
          ROS_ERROR("Received an exception trying to transform a point : %s", ex.what());
        }

        cout << "C " << odom_point.point << std::endl;
    //------------------------------Transformer-------------------------------------

    ros::spinOnce(); //linha para continuar rodando código
  }

}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

} /* namespace */
