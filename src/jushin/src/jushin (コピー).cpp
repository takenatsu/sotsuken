#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/JoyFeedback.h>
#include "geometry_msgs/Twist.h"
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <fstream>
#include <time.h>
#include <sys/time.h>
#include <iomanip> 
#include <sstream>
using namespace std;

bool button = false;

double sum = 0;

double x_div, y_div, raw_x, raw_y, x_div_avg, y_div_avg;

double CoordinateX(double weigh[4]) {
		return (weigh[2] + weigh[0] - weigh[1] - weigh[3]) / 4;
}

double CoordinateY(double weigh[4]) {
		return (weigh[2] + weigh[3] - weigh[1] - weigh[0] ) / 4;
}

void ControllerCallback(const sensor_msgs::Joy& joy_msg) {
		int now, nowsw;
		int static lastsw;
		int count = 0;

		while(count < 1000){
				int static last;
				now = joy_msg.buttons[2];
				usleep(2);
				if(now == last)
						count++;
				last = now;
		}
		nowsw = now;

		if(nowsw == 1 && lastsw == 0){
				button = true;
		}else{
				button = false;
		}

		lastsw = nowsw;
}

void JoyCallback(const sensor_msgs::Joy& joy_msg) {
		double weigh[4];
		int x_border = 200, y_border = 200;
		int x_avg_times = 20;
		int y_avg_times = 10;
		static double x_div_sum = 0;
		static double y_div_sum = 0;
		static int x_log_times = 0;
		static int y_log_times = 0;
		static double x_div_log[20];
		static double y_div_log[10];

		for(int i = 0; i < 4; i++)
			weigh[i] = joy_msg.axes[i];
		raw_x = CoordinateX(weigh);
		raw_y = CoordinateY(weigh);
		sum = weigh[0] + weigh[1] + weigh[2] + weigh[3];

		if(abs(raw_x) > x_border)
			x_div = 5 * raw_x / sum;
		else
			x_div = 0;

		if(abs(raw_y) > y_border)
			y_div = 12 * raw_y / sum;
		else
			y_div = 0;

		if(x_log_times < x_avg_times){
				x_div_sum += x_div;
				x_div_log[x_log_times] = x_div;
				x_log_times ++;
		}else{
				x_div_sum -= x_div_log[0];
				x_div_sum += x_div;
				for(int i = 1; i < x_avg_times; i++)
						x_div_log[i-1] = x_div_log[i];
				x_div_log[x_avg_times-1] = x_div;
				x_div_avg = x_div_sum / x_avg_times;
		}
		if(y_log_times < y_avg_times){
				y_div_sum += y_div;
				y_div_log[y_log_times] = y_div;
				y_log_times ++;
		}else{
				y_div_sum -= y_div_log[0];
				y_div_sum += y_div;
				for(int i = 1; i < y_avg_times; i++)
						y_div_log[i-1] = y_div_log[i];
				y_div_log[y_avg_times-1] = y_div;
				y_div_avg = y_div_sum / y_avg_times;
		}

		if(x_div_avg < 0)
				y_div_avg = -y_div_avg;

		if(abs(x_div_avg) < 0.01)
				x_div_avg = 0.0;
		if(abs(y_div_avg) < 0.01)
				y_div_avg = 0.0;

		/*
		if(raw_x > 0) {
				if(sum > weight_border) {
						x_div = log(((raw_x - x_border) / sum)+ 1) * 1.5;
				} else {
						x_div = 0.0;
				}
				if(raw_x < x_border){
						x_div = 0.0;
				}
		} else if(raw_x <= 0){
				if(sum > weight_border) {
						x_div = -log(((-raw_x + x_border) / sum) + 1) * 1.5;
				} else {
						x_div = 0.0;
				}
				if(raw_x > -x_border){
						x_div = 0.0;
				}
		}

		if(raw_y > 0){
				if(sum > weight_border) {
						y_div = log((((raw_y - y_border) / sum) * 2) + 1) * 3;
				} else {
						y_div = 0.0;
				}
				if(raw_y < y_border) {
						y_div = 0.0;
				}
		} else if(raw_y <= 0){
				if(sum > weight_border) {
						y_div = -log((((-raw_y + y_border) / sum) * 2) + 1) * 3;
				} else {
						y_div = 0.0;
				}
				if(raw_y > -y_border){
						y_div = 0.0;
				}
		}
		*/
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "jushin_node");
	ros::NodeHandle nh;

	ros::Subscriber joy_sub = nh.subscribe("ps4", 1 , ControllerCallback);
	ros::Subscriber board_sub = nh.subscribe("xwiimote_node/joy", 1 , JoyCallback);

	ros::Publisher cmd_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
	ros::Publisher odom_pub  = nh.advertise<nav_msgs::Odometry>("board_xy", 1);

	tf::TransformBroadcaster odom_broadcaster;

	ros::Time current_time, last_time;
	current_time = ros::Time::now();
	last_time = ros::Time::now();

	ros::Rate loop_rate(100);
	ROS_INFO("jushin_node running");

	/*
	time_t t = time(nullptr);
	const tm* lt = localtime(&t);
	stringstream s;
	s<<"/home/natsuki/catkin_ws/src/jushin/src/";
	s<<"20"; s<<lt->tm_year-100; s<<lt->tm_mon+1; s<<lt->tm_mday;
	s<<"-"; s<<lt->tm_hour; s<<lt->tm_min; s<<lt->tm_sec;
	s<<".csv";
	string result = s.str();
	ofstream log;
	log.open(result);
	
	if(log)
		ROS_INFO_STREAM("csv file: " << result);
	else
		ROS_ERROR("csv file error!");
		*/

	int count = 0;

	double devi_x = 0, devi_y = 0;

	while(ros::ok()){
		ros::spinOnce();
		current_time = ros::Time::now();

		//since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(0);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "board_xy_link";

		

    odom_trans.transform.translation.x = -y_div;
    odom_trans.transform.translation.y = x_div;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = -y_div;
    odom.pose.pose.position.y = x_div;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //publish the message
    odom_pub.publish(odom);

		geometry_msgs::Twist cmd_vel;
		cmd_vel.linear.x = x_div_avg;
		cmd_vel.angular.z = y_div_avg;
		cmd_pub.publish(cmd_vel);

/*		if(button) {
			if(count == 0) {
				devi_x = raw_x;
				devi_y = raw_y;
				ROS_INFO("devi_x : %3.4f, devi_y : %3.4f", devi_x, devi_y);
				log << "deviation" << "," << devi_x << "," << devi_y << endl;
			}
			ROS_INFO("%3d%% | raw_x : %3.4f, raw_y : %3.4f", count, raw_x - devi_x, raw_y - devi_y);
			log << count << "," << raw_x - devi_x << "," << raw_y - devi_y << endl;
			count = count + 25;
		}
		*/

		cout << "x_div_avg:" << x_div_avg << " y_div_avg:" << y_div_avg << endl;

    last_time = current_time;
    loop_rate.sleep();
	}
	log.close();
	return 0;
}
