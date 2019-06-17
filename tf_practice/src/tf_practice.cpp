#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

constexpr static double PI = 3.14529265359;
constexpr static int angular_velocity = 2 * PI / 2;

class CircleTF{
public:
    CircleTF(): cur_theta(0), last(ros::Time::now()) {}     //현재 시간은 계속 변하므로..
    void pubTF(){
        ros::Time cur = ros::Time::now();
        double dt = (cur - last).toSec();

        cur_theta += angular_velocity * dt;
        last = cur;

        double x = sin(cur_theta);
        double y = cos(cur_theta);
        double yaw = cur_theta;

        tf::Transform transform;
        transform.setOrigin(tf::Vector3(x,y,0.0));      //원점 지정
        tf::Quaternion q;
        q.setRPY(0,0,yaw);
        transform.setRotation(q);

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "parent_link","child_link"));
    }
private:
    double cur_theta;
    ros::Time last;

    tf::TransformBroadcaster br;

};

int main(int argc, char *argv[]){
   ros::init(argc, argv, "tf_practice");
   ros::NodeHandle nh;

   CircleTF c;
   ros::Rate r(50);

   while(ros::ok()){
       c.pubTF();
       r.sleep();
   } 
   return 0;
}