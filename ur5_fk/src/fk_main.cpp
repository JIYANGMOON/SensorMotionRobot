#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

#define N_JOINT 6

static constexpr double a_dh[N_JOINT] = 
    {0.00000, -0.42500, -0.39225, 0.00000, 0.00000, 0.0000};
static constexpr double d_dh[N_JOINT] =
    {0.089159, 0.00000, 0.00000, 0.10915, 0.09465, 0.0823};
static constexpr double alpha_dh[N_JOINT] = 
    {1.570796327, 0, 0, 1.570796327, -1.570796327, 0};


class Ur5{
private:
    ros::NodeHandle nh;
    ros::Subscriber ur_sub;
    double theta[6];
    Eigen::Matrix4d m[6];
public:
    Ur5(){
        ur_sub = nh.subscribe("joint_states", 10, &Ur5::jointInfoCB, this);
    }
    Eigen::Matrix4d matrix(double theta, double d, double a, double alpha){
        Eigen::Matrix4d m1;
        m1<<cos(theta), -sin(theta), 0, 0, 
            sin(theta), cos(theta), 0, 0, 
            0 ,0, 1, 0,
            0, 0, 0, 1;
    // std::cout<<m1;
        Eigen::Matrix4d m2;
        m2<<1, 0, 0, 0, 
            0, 1, 0, 0, 
            0, 0, 1, d, 
            0, 0, 0, 1;
        Eigen::Matrix4d m3;
        m3<<1, 0, 0, a,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;
        Eigen::Matrix4d m4;
        m4 << 1, 0, 0, 0, 
            0, cos(alpha), -sin(alpha), 0, 
            0, sin(alpha), cos(alpha), 0,
            0, 0, 0, 1;
    
        Eigen::Matrix4d m5 = m1 * m2 * m3 * m4;
        return m5;
    }
    void jointInfoCB(const sensor_msgs::JointStateConstPtr& ptr){
        for(int j = 0; j<6; j++)
            theta[j] = ptr->position[j];

   
        for(int i =0; i<6; i++){
            m[i] = matrix(theta[i], d_dh[i], a_dh[i], alpha_dh[i]);
        }
       

        Eigen::Matrix4d final_ = m[0] * m[1]* m[2]* m[3] * m[4] * m[5];
    
        std::cout<<" result tf matrix -" << std::endl<< final_<<std::endl;
    }
   



};

int main(int argc, char *argv[]){
    ros::init(argc, argv, "fk_main");
    Ur5 ur;

    ros::Rate loop_rate(10);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}