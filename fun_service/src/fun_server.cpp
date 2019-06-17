#include "ros/ros.h"
#include "fun_service/SrvAngle.h"
#include <math.h>

#define PI  3.14529265359
class changeAngle{
protected:
    ros::NodeHandle nh;
    ros::ServiceServer fun_service;
    std::string ser_name;
    int function;
public:
    changeAngle(std::string name): ser_name(name){
       
        fun_service=nh.advertiseService(name.c_str(), &changeAngle::change, this);

    }    
    bool change(fun_service::SrvAngle::Request &req, fun_service::SrvAngle::Response &res){
         nh.param("function",function,0);
        switch(function){
            case 0:
                res.funValue = sin(req.angle * PI);
                break;
            case 1:
                res.funValue = cos(req.angle * PI);
                break;
            default:
                ROS_WARN("UNKOWN NUMBER. IT MUST BE 0, 1");
                break;
        }
        ROS_INFO("Request : angle = %f", req.angle);
        ROS_INFO("sending back response : %f", res.funValue);

        return true;
    }   
};


int main(int argc, char *argv[]){
    ros::init(argc, argv, "fun_server");
    changeAngle cg("angleSrv");
    ROS_INFO("ready srv server!");
    ros::spin();

    return 0;
}