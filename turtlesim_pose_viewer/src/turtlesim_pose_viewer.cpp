#include <ros/ros.h>
#include"turtlesim/Pose.h"


void poseCallBack(const turtlesim::PoseConstPtr& ptr) {
	ROS_INFO("x : %f", ptr->x);
	ROS_INFO("y : %f", ptr->y);
	ROS_INFO("theta : %f", ptr->theta);
	ROS_INFO("linear_velocity : %f", ptr->linear_velocity);
	ROS_INFO("angular_veloctiy : %f", ptr->angular_velocity);
}

int main(int argc, char *argv[]){
	ros::init(argc, argv, "turtlesim_pose_viewer");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000, poseCallBack);

	ros::spin();

	return 0;
}
