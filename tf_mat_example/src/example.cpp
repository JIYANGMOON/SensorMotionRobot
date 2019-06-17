#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main(){
    Eigen::Matrix4d m1;
    m1<<cos(1), -sin(1), 0, 0, 
        sin(1), cos(1), 0, 0, 
        0 ,0, 1, 0,
         0, 0, 0, 1;
   // std::cout<<m1;
    Eigen::Matrix4d m2;
    m2<<1, 0, 0, 0, 
        0, 1, 0, 0, 
        0, 0, 1, 1, 
        0, 0, 0, 1;
    Eigen::Matrix4d m3;
    m3<<1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1;
    Eigen::Matrix4d m4;
    m4 << 1, 0, 0, 0, 
         0, 0, -1, 0, 
         0, 1, 0, 0,
         0, 0, 0, 1;
    
    Eigen::Matrix4d m5 = m1 * m2 * m3 * m4;
 
    std::cout<<m5<<std::endl;


}