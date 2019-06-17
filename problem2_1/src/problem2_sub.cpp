#include <ros/ros.h>
#include <cstdlib>
#include <math.h>
#include "problem2_1/problem2_msg.h"

using namespace std; 

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v){
    out << "{";
    size_t last = v.size() -1;
    for(size_t i = 0; i<v.size(); ++i) {
        out<<pow(v[i],2);
        if(i != last)
            out<<", ";
    }
  
    out<<"}";
    return out;
}

void subCallback(const problem2_1::problem2_msgPtr& ptr){
    ROS_INFO("Received %d", ptr->stamp.sec);
    ROS_INFO("Received %d", ptr->r);
    ROS_INFO_STREAM("Received msg vector "<< ptr->v);
}

int main(int argc, char *argv[]){
    ros::init(argc, argv, "problem2_sub");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("problem2", 10, subCallback);

    ros::spin();
    return 0;
}