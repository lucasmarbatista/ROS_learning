#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Int32.h"
#include <iostream>
#include <sstream>
#include <string>


//#include <algorithm>    // std::min_element, std::max_element

using namespace std;

template <typename T, size_t N>
inline
size_t SizeOfArray( const T(&)[ N ] )
{
  return N;
}

namespace husky_highlevel_controller {


void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
//sensor_msgs::LaserScan é o tipo do tópico a ser subscrito
// msg é onde a informação do tópico é armazenada

    std_msgs::Int32 my_msg;
    stringstream array_test[720];
    float array_test2[720];
    int i;
    int count;
    float min_test=1000;
    int  angle;
    //float ranges[];


   for(i=0; i < 719; i=i+1){

      //std::cout << "I heard " << msg->ranges[i] << std::endl;

     // Transformar em string

     // array_test[i]<< msg->ranges[i];
     // string str = array_test[i].str();

     // std::cout << "I heard " << str << std::endl;

     // Usar em float

     array_test2[i] = msg->ranges[i];
     //std::cout << "I heard " << array_test2[i] << std::endl;

     if(i>0 && array_test2[i] < min_test){
      min_test = array_test2[i];
      angle = i/2;
    }

    }
    std::cout << "Min is " << min_test << std::endl;
    std::cout << "Angle " << angle << std::endl;

    //std::cout << SizeOfArray(ranges) << std::endl;

}

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{

  ros::NodeHandle husky_teste; //Define husky_teste como NodeHandle

  ros::Subscriber sub = husky_teste.subscribe("/scan", 1, chatterCallback);
 //Inicia o subscriber //subscreve no topico "chatter"

  ros::spin();


}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

} /* namespace */
