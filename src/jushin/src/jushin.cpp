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
#include <unistd.h>
using namespace std;

bool button = false;

double sum = 0;

double x_div, y_div, raw_x, raw_y, x_div_avg, y_div_avg, weight_right, weight_left;

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
		int x_avg_times = 10;
		int y_avg_times = 5;
		static double x_div_sum = 0;
		static double y_div_sum = 0;
		static int x_log_times = 0;
		static int y_log_times = 0;
		static double x_div_log[10];
		static double y_div_log[5];

		for(int i = 0; i < 4; i++)
			weigh[i] = joy_msg.axes[i];
		raw_x = CoordinateX(weigh);
		raw_y = CoordinateY(weigh);
		sum = weigh[0] + weigh[1] + weigh[2] + weigh[3];
		weight_right = weigh[0] + weigh[1];
		weight_left = weigh[2] + weigh[3];
		x_div = raw_x / sum;
		y_div = raw_y / sum;

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

	double out_x, out_y, weight_border = 4000, x_max = 0.2, y_max = 1.0, front_max, right_max, back_max, left_max;
	bool first = false, foot = false, cali = true;
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
			//next, we'll publish the odometry message over ROS
			nav_msgs::Odometry odom;
			odom.header.stamp = current_time;
			odom.header.frame_id = "odom";

			geometry_msgs::Twist cmd_vel;
			if(cali){
					if(button){
							switch(count){
									case 0:
											cout << "[CALIBRATION]" << endl << "FRONT MAX:" << endl;
											break;
									case 1:
											front_max = abs(x_div_avg);
											cout << front_max << endl << "RIGHT MAX:" << endl;
											break;
									case 2:
											right_max = abs(y_div_avg);
											cout << right_max << endl << "BACK MAX:" << endl;
											break;
								case 3:
											back_max = abs(x_div_avg);
											cout << back_max << endl << "LEFT MAX:" << endl;
											break;
								case 4:
											left_max = abs(y_div_avg);
											cout << left_max << endl << "PLESS ○" << endl;
											break;
								case 5:
										cali = false;
										cout << "START" << endl;
										sleep(3);
										break;
						}
						if(count == 5){
								count = 0;
						}
						else{
								count++;
						}
				}
		}

		if(sum >= weight_border && !cali){
				if(x_div_avg > 0){
						if(abs(x_div_avg) > front_max)
								x_div_avg = front_max;
						out_x = x_div_avg * x_max / front_max - x_max / 4;
						if(out_x <= 0)
								out_x = 0;
						if(y_div_avg > 0){
								if(abs(y_div_avg) > right_max)
										y_div_avg = right_max;
								out_y = y_div_avg * y_max / right_max - y_max / 8;
								if(out_y <= 0)
										out_y = 0;
						}
						else{
								if(abs(y_div_avg) > left_max)
										y_div_avg = -left_max;
								out_y = y_div_avg * y_max / left_max + y_max / 8;
								if(out_y >= 0)
										out_y = 0;
						}
				}
				else{
						if(abs(x_div_avg) > back_max)
								x_div_avg = -back_max;
						out_x = x_div_avg * x_max / back_max + x_max * 5 / 8;
						if(out_x >= 0)
								out_x = 0;
						else
								y_div_avg = -y_div_avg;

						if(y_div_avg < 0){
								if(abs(y_div_avg) > right_max)
										y_div_avg = -right_max;
								out_y = y_div_avg * y_max / right_max + y_max / 8;
								if(out_y >= 0)
										out_y = 0;
						}
						else{
								if(abs(y_div_avg) > left_max)
										y_div_avg = left_max;
								out_y = y_div_avg * y_max / left_max - y_max / 8;
								if(out_y <= 0)
										out_y = 0;
						}
				}
				printf("out_x:%f, out_y:%f\n",out_x,out_y);
				if(first){
						odom_trans.transform.translation.x = 0.0;
						odom_trans.transform.translation.y = 0.0;
						odom_trans.transform.translation.z = 0.0;
						odom_trans.transform.rotation = odom_quat;

						//send the transform
						odom_broadcaster.sendTransform(odom_trans);

						//set the position
						odom.pose.pose.position.x = 0.0;
						odom.pose.pose.position.y = 0.0;
						odom.pose.pose.position.z = 0.0;
						odom.pose.pose.orientation = odom_quat;

						//publish the message
						odom_pub.publish(odom);

						cmd_vel.linear.x = 0.0;
						cmd_vel.angular.z = 0.0;
						cmd_pub.publish(cmd_vel);

						if(weight_right >= sum / 3 && weight_left >= sum / 3)
								first = false;
				}else{
						if(!foot){

								odom_trans.transform.translation.x = -y_div;
								odom_trans.transform.translation.y = x_div;
								odom_trans.transform.translation.z = 0.0;
								odom_trans.transform.rotation = odom_quat;

								//send the transform
								odom_broadcaster.sendTransform(odom_trans);

								//set the position
								odom.pose.pose.position.x = -y_div;
								odom.pose.pose.position.y = x_div;
								odom.pose.pose.position.z = 0.0;
								odom.pose.pose.orientation = odom_quat;

								//publish the message
								odom_pub.publish(odom);


								cmd_vel.linear.x = out_x;
								cmd_vel.angular.z = out_y;
								cmd_pub.publish(cmd_vel);
								if(weight_right > 0.9 * sum || weight_left > 0.9 * sum){
										foot = true;
								}
						}else{
								odom_trans.transform.translation.x = 0.0;
								odom_trans.transform.translation.y = 0.0;
								odom_trans.transform.translation.z = 0.0;
								odom_trans.transform.rotation = odom_quat;

								//send the transform
								odom_broadcaster.sendTransform(odom_trans);

								//set the position
								odom.pose.pose.position.x = 0.0;
								odom.pose.pose.position.y = 0.0;
								odom.pose.pose.position.z = 0.0;
								odom.pose.pose.orientation = odom_quat;

								//publish the message
								odom_pub.publish(odom);

								cmd_vel.linear.x = 0.0;
								cmd_vel.angular.z = 0.0;
								cmd_pub.publish(cmd_vel);

								first = true;
						}
				}
		}else{
				odom_trans.transform.translation.x = 0.0;
				odom_trans.transform.translation.y = 0.0;
				odom_trans.transform.translation.z = 0.0;
				odom_trans.transform.rotation = odom_quat;

				//send the transform
				odom_broadcaster.sendTransform(odom_trans);

				//set the position
				odom.pose.pose.position.x = 0.0;
				odom.pose.pose.position.y = 0.0;
				odom.pose.pose.position.z = 0.0;
				odom.pose.pose.orientation = odom_quat;

				//publish the message
				odom_pub.publish(odom);

				cmd_vel.linear.x = 0.0;
				cmd_vel.angular.z = 0.0;
				cmd_pub.publish(cmd_vel);

				first = true;
				foot = false;
		}
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


		last_time = current_time;
		loop_rate.sleep();
		//log.close();
	}
	return 0;
}
