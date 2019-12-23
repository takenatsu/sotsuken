#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"

geometry_msgs::Twist cmd_vel;
void joy_callback(const sensor_msgs::Joy& joy_msg){
		cmd_vel.linear.x =joy_msg.axes[1] * 0.2;
		cmd_vel.angular.z=joy_msg.axes[0] * 1.2;
}

int main(int argc, char **argv){
		ros::init(argc, argv, "basic_twist_publisher");
		ros::NodeHandle n;

		//publish
		ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
		//        //subscriibe
		ros::Subscriber joy_sub   = n.subscribe("ps4", 1, joy_callback);
		//
		ros::Rate loop_rate(100);
		while (ros::ok()){
				cmd_pub.publish(cmd_vel);
				ros::spinOnce();
				loop_rate.sleep();
		}
		return 0;
}
