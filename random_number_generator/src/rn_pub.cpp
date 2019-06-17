#include "ros/ros.h"
#include "random_number_generator/rn.h"


int main(int argc, char *argv[]){
	int limitNumber;

	ros::init(argc, argv, "rn_pub");
	ros::NodeHandle nh;
	nh.setParam("limit_parameter", 10);
	ros::Publisher random_pub = 
		nh.advertise<random_number_generator::rn>("rn_info", 1000);

	ros::Rate loop_rate(10);	
	random_number_generator::rn msg;


	srand(time(NULL));
	u_int16_t num;
	
	while(ros::ok())
	{
		nh.getParam("limit_parameter", limitNumber);

		msg.limit = limitNumber;
		num = rand() % msg.limit;
		
		msg.randint = num;

		ROS_INFO("limit : %d", msg.limit);
		ROS_INFO("randint : %d", msg.randint);
				

		random_pub.publish(msg);
		loop_rate.sleep();
	}
	
	return 0;
}
		
		
	
	
