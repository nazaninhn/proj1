#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <sstream>
#include <turtlesim/Pose.h>

int x,y,x1,y1;
template <typename T>
void chatterCallback(const T& msg)
{
 x=msg->x;
 y=msg->y;
  ROS_INFO("I heard: [%f],[%f]", x,y);
}
template <typename T>
void chatterCallback1(const T& msg)
{
 x1=msg->x;
 y1=msg->y;
  ROS_INFO("I heard: [%f],[%f]",x1,y1);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talis");

  
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, chatterCallback);
  ros::Subscriber sub = n.subscribe("akbar/pose", 1000, chatterCallback1);

  
  ros::Publisher chatter_pub = n.advertise<geometery_msgs::Twist>("akbar/cmd_vel", 1000);

  ros::Rate loop_rate(10);
  int count = 0;


  while (ros::ok())
  {
    geometery_msgs::Twist msg;

    msg.linear->x=x-x1;
    msg.linear->y=y-y1;

    ROS_INFO("%f  %f",x-x1,y-y1 );

    
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
