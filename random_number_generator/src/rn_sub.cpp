#include <ros/ros.h>
#include "random_number_generator/rn.h"

int count = 0;
int sum = 0;

void randomCB(const random_number_generator::rnPtr& ptr){
	count++;
	sum += ptr->randint;
	ROS_INFO("limit : %d", ptr->limit);
	ROS_INFO("randint : %d", ptr->randint);
	ROS_INFO("sum : %d", sum);
	ROS_INFO("count : %d", count);
	
}

int main(int argc, char *argv[]){
	ros::init(argc, argv, "rn_sub");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("rn_info", 10, randomCB);

	ros::spin();
	return 0;
}
