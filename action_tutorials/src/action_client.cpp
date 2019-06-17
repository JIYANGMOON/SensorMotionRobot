#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"
#include "action_tutorials/fibonacciAction.h"

int main(int argc, char **argv){
	ros::init(argc, argv, "action_client");
	actionlib::SimpleActionClient<action_tutorials::fibonacciAction> ac("action_tutorials", true);

	ROS_INFO("waiting for action server to start.");
	ac.waitForServer();

	ROS_INFO("Action server started, sending goal.");
	action_tutorials::fibonacciGoal goal;
	goal.order = 20;
	ac.sendGoal(goal);

	bool finished_before_timeout = ac.waitForResult(ros::Duration(30,0));

	if(finished_before_timeout)
	{
		actionlib::SimpleClientGoalState state = ac.getState();
		ROS_INFO("Action finished : %s", state.toString().c_str());
	}
	else{
		ROS_INFO("Actiondid not finish before the time out.");
	}
	
	return 0;
}
