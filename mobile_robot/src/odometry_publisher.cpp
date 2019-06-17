#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <gazebo_msgs/LinkStates.h>
#include <nav_msgs/Odometry.h>

class DiffDriveOdometry{
private:
ros::NodeHandle nh;
ros::Subscriber gazebo_sub;
ros::Publisher odomPub;
ros::Time last;
ros::Time cur;
tf::TransformBroadcaster broadcaster;
std::string left_wheel;
std::string right_wheel;
std::string custom_base;
std::string custom_odom;
double separation_length;
double x, y, z, theta, seq;
double v, w;
double R_vel, L_vel;
double x_dot, y_dot, theta_dot;

public:
DiffDriveOdometry():seq(0), nh(), x(0), y(0), theta(0), last(ros::Time::now()){
if(!nh.getParam("/mobile_robot_odometry/leftwheel_linkname", left_wheel))
throw std::runtime_error("set leftwhell_linkname");
if(!nh.getParam("/mobile_robot_odometry/rightwheel_linkname", right_wheel))
throw std::runtime_error("set rightwheel_linkname");
if(!nh.getParam("/mobile_robot_odometry/base_link_id", custom_base))
throw std::runtime_error("set base_link_id");
if(!nh.getParam("/mobile_robot_odometry/odom_link_id", custom_odom))
throw std::runtime_error("set odom_link_id");
if(!nh.getParam("/mobile_robot_odometry/separation_length", separation_length))
throw std::runtime_error("set separation_length");

//odomPub = nh.subscribe<gazebo_msgs::LinkStates>("gazebo/link_states",1);
odomPub = nh.advertise<nav_msgs::Odometry>("/custom_odom", 1);
gazebo_sub = nh.subscribe("/gazebo/link_states", 1, &DiffDriveOdometry::calcWheelVelocityGazeboCB, this);
//n_link = static_cast<int>(left_wheel.size());

}
void pub(){
nav_msgs::Odometry odom;
cur = ros::Time::now();
double dt = (cur-last).toSec();
theta_dot = w;
//cur_theta = w * dt;
theta += w *dt;
//ROS_INFO("cur_theta : %lf", theta);
last = cur;
x_dot = cos(theta) * v;
y_dot = sin(theta) * v;

x += x_dot * dt;
y += y_dot * dt;

//ROS_INFO("%lf, %lf, %lf, %lf, %lf", x, y, x_dot, y_dot, theta_dot );
odom.header.seq = seq++;
odom.header.stamp = cur;
odom.header.frame_id = custom_odom;
odom.child_frame_id = custom_base;

odom.pose.pose.position.x = x;
odom.pose.pose.position.y = y;
odom.pose.pose.position.z = 0;
odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(theta);
odom.twist.twist.linear.x = x_dot;
odom.twist.twist.linear.y = y_dot;
odom.twist.twist.angular.z = theta_dot;

ROS_INFO("%lf, %lf, %lf, %lf, %lf", x, y, x_dot, y_dot, theta_dot);
odomPub.publish(odom);

}
void calcWheelVelocityGazeboCB(const gazebo_msgs::LinkStatesConstPtr& ptr){
double x1, y1, z1;
int n = static_cast<int>(ptr->name.size());
for(int i = 0; i < n; i++){
if(ptr->name[i]==left_wheel){
x1 = ptr->twist[i].linear.x;
y1 = ptr->twist[i].linear.y;
z1 = ptr->twist[i].linear.z;

L_vel = sqrt(x1*x1 + y1*y1 + z1*z1);
//ROS_INFO("xxxxx : %lf", x);
}
if(ptr->name[i]==right_wheel){
x1 = ptr->twist[i].linear.x;
y1 = ptr->twist[i].linear.y;
z1 = ptr->twist[i].linear.z;

R_vel = sqrt(x1*x1 + y1*y1 + z1*z1);
//ROS_INFO("yyyyy : %lf", y);
}
}
v = (L_vel + R_vel) /2.0;
w = (R_vel - L_vel) / separation_length;


}
void broadcastTrasform(){
tf::Transform transform;
transform.setOrigin(tf::Vector3(x,y,0.0)); //원점 지정
tf::Quaternion q;
q.setRPY(0,0,theta);
transform.setRotation(q);

// broadcaster.sendTransform(tf::StampedTransform(transform, ros::Time::now(), custom_odom,"custom_base"));
broadcaster.sendTransform(tf::StampedTransform(transform, ros::Time::now(), custom_odom.c_str(),"base_link"));
}
};

int main(int argc, char **argv){
ros::init(argc, argv, "mobile_robot_odometry");

DiffDriveOdometry d;
ros::Rate loop_rate(100);
while(ros::ok()){
ros::spinOnce();
d.pub();
d.broadcastTrasform();
loop_rate.sleep();
}
return 0;
}
