#include "ros/ros.h"
#include "fun_service/SrvAngle.h"
#include <sstream>

int main(int argc, char *argv[]){
    ros::init(argc, argv, "fun_client");

    if(argc != 2){
		ROS_INFO("cmd : rosrun fun_service fun_client arg");
		ROS_INFO("arg0 : float number");
		return 1;
	}
    ros::NodeHandle nh;
    ros::ServiceClient fun_client = nh.serviceClient<fun_service::SrvAngle>("angleSrv");
    fun_service::SrvAngle srv;

    srv.request.angle=atof(argv[1]);
    

    if(fun_client.call(srv)){
        ROS_INFO("send srv, srv.Request.angle : %f", srv.request.angle);

    }
    else{
        ROS_ERROR("Failed to call service ");
        return 1;
    }
    return 0;
}   
