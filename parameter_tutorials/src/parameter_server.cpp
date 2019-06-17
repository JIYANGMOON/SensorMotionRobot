#include "ros/ros.h"
#include "parameter_tutorials/SrvTutorials.h"

enum {PLUS = 1, MINUS, MULTIPLICATION, DIVISION};

class SimpleCalculator{
protected:
	ros::NodeHandle nh_;
	ros::ServiceServer service_server;
	std::string service_name_;
	int op_;

public:
	SimpleCalculator(std::string name): service_name_(name){
		nh_.setParam("calculation_method", PLUS);
		service_server = nh_.advertiseService(name.c_str(), &SimpleCalculator::calculation,this);
	}

	bool calculation(parameter_tutorials::SrvTutorials::Request &req, parameter_tutorials::SrvTutorials::Response &res){
		nh_.getParam("calculation_method", op_);
		//nh_.param("op", op_, default);
		switch(op_){
			case PLUS:
				res.result = req.a + req.b; break;
			case MINUS:
				res.result = req.a - req.b; break;
			case MULTIPLICATION:
				res.result = req.a * req.b; break;
			case DIVISION:
				res.result = (req.b == 0) ? 0 : req.a / req.b; break;
			default:
				ROS_WARN("UNKNOWN OPERATOR TYPE. It must be 1, 2, 3, 4. The value of operator is %d", op_);
				break;
		}	
		
	ROS_INFO("Request: x = %ld, y=%ld", static_cast<long int>(req.a), static_cast<long int>(req.b));
	ROS_INFO("sending back response : %ld", static_cast<long int>(res.result));

	return true;
	}
};



int main(int argc, char* argv[]){
	ros::init(argc, argv, "parameter_server");

	SimpleCalculator calculator("parameter_tutorial");

	ROS_INFO("ready srv server!");
	ros::spin();

	return 0;
}
