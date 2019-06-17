#include <ros/ros.h>
#include <math.h>
#include "robot_localization/pose_msg.h"
#define PI2 3.14*2
#define INC PI2/360.0
#define RADIUS 1.O

class RobotPose{
private:
    ros::NodeHandle nh;
    ros::Publisher pub;
    robot_localization::pose_msg msg;
    double theta;
public:
    ros::Time last;
    RobotPose():theta(0), last(ros::Time::now()) 
    { pub = nh.advertise<robot_localization::pose_msg>("robotPose",10);}
    void genMsg(){
        msg.stamp = ros::Time::now();
        double dt = (msg.stamp-last).toSec();
        
        theta += INC * dt;
        msg.x = sin(theta);
        msg.y = cos(theta);
        
        
    }
    void publish(){
        pub.publish(msg);
    }

};

int main(int argc, char *argv[]){
    ros::init(argc, argv, "robot_pose");
    RobotPose ms;
    ros::Rate r(100);
    while(ros::ok()){
        ms.genMsg();
        ms.publish();
        r.sleep();
    }
    return 0;

}