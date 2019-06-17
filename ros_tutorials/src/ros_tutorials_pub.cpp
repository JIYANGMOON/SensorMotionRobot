#include <ros/ros.h>
#include <std_msgs/Bool.h>

int main(int argc, char *argv[]){
    ros::init(argc, argv, "ros_tutorials_pub");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<
            std_msgs::Bool>("simple_bool", 10);

    ros::Rate loop_rate(10);
    std_msgs::Bool msg;
    
    while(ros::ok()){
        msg.data = ~msg.data;
        pub.publish(msg);
        loop_rate.sleep();
    }
}