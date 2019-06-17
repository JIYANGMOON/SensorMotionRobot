#include <ros/ros.h>
#include <std_msgs/Bool.h>

void boolcb(const std_msgs::BoolConstPtr& ptr){
    ROS_INFO("Received %d", ptr->data);

}

int main(int argc, char *argv[]){
    ros::init(argc, argv, "ros_tutorials_sub");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/simple_bool", 10, boolcb);

    ros::spin();
    return 0;
}