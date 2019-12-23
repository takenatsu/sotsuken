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

//グローバル変数定義
bool button = false;
double sum, x_div, y_div, x_div_avg, y_div_avg, weight_right, weight_left, output, calisum;
int calitime = 500, enter;

//関数宣言
double CoordinateX(double *);
double CoordinateY(double *);
double XAverage(double, int);
double YAverage(double, int);
void ControllerCallback(const sensor_msgs::Joy& joy_msg);
void JoyCallback(const sensor_msgs::Joy& joy_msg);
void Calibration(int, double);

int main(int argc, char **argv){
		//ROS設定
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
		cout << "enter:";
		while(getchar() != '\n');

		//ローカル変数定義
		int static count = 0, sw = 0;
		double out_x, out_y, weight_border = 4000, x_max = 0.2, y_max = 1.2, front_max, right_max, back_max, left_max, frontright_max, frontleft_max, backright_max, backleft_max;
		bool first = false, foot = false, cali = true;                                                                
                                                                                                                  
		//センサ値計算、較正、速度情報送信:メイン処理                                                                  
		while(ros::ok()){
				//ROS
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

				//較正
				if(cali){
						switch(sw){
								case 0:
										cout << "calibration start" << endl;
										cout << "前に体を倒してください" << endl;
										sleep(2);
										sw ++;
										break;
								case 1:
										count ++;
										Calibration(count, x_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												front_max = output;
												cout << "後ろに体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 2:
										count ++;
										Calibration(count, x_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												back_max = output;
												cout << "右に体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 3:
										count ++;
										Calibration(count, y_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												right_max = output;
												cout << "左に体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 4:
										count ++;
										Calibration(count, y_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												left_max = output;
												cout << "右前に体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 5:
										count ++;
										Calibration(count, y_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												frontright_max = output;
												cout << "左前に体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 6:
										count ++;
										Calibration(count, y_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												frontleft_max = output;
												cout << "右後ろに体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 7:
										count ++;
										Calibration(count, y_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												backright_max = output;
												cout << "左後ろに体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 8:
										count ++;
										Calibration(count, y_div_avg);
										if(count == calitime){
												count = 0;
												sw ++;
												backleft_max = output;
												cout << "右後ろに体を倒してください" << endl;
												sleep(2);
										}
										break;
								case 9:
										cali = false;
										cout << "START:";
										while(getchar() != '\n');
										sleep(3);
										break;
						}
				}

				//出力値計算
				if(sum >= weight_border && !cali){
						if(x_div_avg > 0){
								if(y_div_avg > 0){
										if(abs(y_div_avg) > frontright_max)
												y_div_avg = frontright_max;
										out_y = y_div_avg * y_max / frontright_max - y_max / 8;
										if(out_y <= 0)
												out_y = 0;
								}else{
										if(abs(y_div_avg) > frontleft_max)
												y_div_avg = -frontleft_max;
										out_y = y_div_avg * y_max / frontleft_max + y_max / 8;
										if(out_y >= 0)
												out_y = 0;
								}

								if(abs(x_div_avg) > front_max)
										x_div_avg = front_max;
								out_x = x_div_avg * x_max / front_max - x_max / 4;

								if(out_x <= 0){
										out_x = 0;
										if(y_div_avg > 0){
												if(abs(y_div_avg) > right_max)
														y_div_avg = right_max;
												out_y = y_div_avg * y_max / right_max - y_max / 8;
												if(out_y <= 0)
														out_y = 0;
										}else{
												if(abs(y_div_avg) > left_max)
														y_div_avg = -left_max;
												out_y = y_div_avg * y_max / left_max + y_max / 8;
												if(out_y >= 0)
														out_y = 0;
										}
										
								}
						}else{
								if(y_div_avg > 0){
										if(abs(y_div_avg) > backright_max)
												y_div_avg = -backright_max;
										out_y = y_div_avg * y_max / backright_max + y_max / 8;
										if(out_y >= 0)
												out_y = 0;
								}else{
										if(abs(y_div_avg) > backleft_max)
												y_div_avg = backleft_max;
										out_y = y_div_avg * y_max / backleft_max - y_max / 8;
										if(out_y <= 0)
												out_y = 0;
								}

								if(abs(x_div_avg) > back_max)
										x_div_avg = -back_max;
								out_x = x_div_avg * x_max / back_max + x_max / 2;

								if(out_x >= 0){
										out_x = 0;
										if(y_div_avg > 0){
												if(abs(y_div_avg) > right_max)
														y_div_avg = right_max;
												out_y = y_div_avg * y_max / right_max - y_max / 8;
												if(out_y <= 0)
														out_y = 0;
										}else{
												if(abs(y_div_avg) > left_max)
														y_div_avg = -left_max;
												out_y = y_div_avg * y_max / left_max + y_max / 8;
												if(out_y >= 0)
														out_y = 0;
										}
								}
						}

						//速度情報
						printf("out_x:%f, out_y:%f\n",out_x,out_y);
						
						if(first){
								out_x = 0;
								out_y = 0;
								odom_trans.transform.translation.x = -out_y;
								odom_trans.transform.translation.y = out_x;
								odom_trans.transform.translation.z = 0.0;
								odom_trans.transform.rotation = odom_quat;

								//send the transform
								odom_broadcaster.sendTransform(odom_trans);

								//set the position
								odom.pose.pose.position.x = -out_y;
								odom.pose.pose.position.y = out_x;
								odom.pose.pose.position.z = 0.0;
								odom.pose.pose.orientation = odom_quat;

								//publish the message
								odom_pub.publish(odom);

								cmd_vel.linear.x = out_x;
								cmd_vel.angular.z = out_y;
								cmd_pub.publish(cmd_vel);
								if(weight_right >= sum / 3 && weight_left >= sum / 3)
										first = false;
						}else{
								if(!foot){
										odom_trans.transform.translation.x = -out_y;
										odom_trans.transform.translation.y = out_x;
										odom_trans.transform.translation.z = 0.0;
										odom_trans.transform.rotation = odom_quat;

										//send the transform
										odom_broadcaster.sendTransform(odom_trans);

										//set the position
										odom.pose.pose.position.x = -out_y;
										odom.pose.pose.position.y = out_x;
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
										out_x = 0;
										out_y = 0;
										odom_trans.transform.translation.x = -out_y;
										odom_trans.transform.translation.y = out_x;
										odom_trans.transform.translation.z = 0.0;
										odom_trans.transform.rotation = odom_quat;

										//send the transform
										odom_broadcaster.sendTransform(odom_trans);

										//set the position
										odom.pose.pose.position.x = -out_y;
										odom.pose.pose.position.y = out_x;
										odom.pose.pose.position.z = 0.0;
										odom.pose.pose.orientation = odom_quat;

										//publish the message
										odom_pub.publish(odom);

										cmd_vel.linear.x = out_x;
										cmd_vel.angular.z = out_y;
										cmd_pub.publish(cmd_vel);
										first = true;
								}
						}
				}else{
						out_x = 0;
						out_y = 0;
						odom_trans.transform.translation.x = -out_y;
						odom_trans.transform.translation.y = out_x;
						odom_trans.transform.translation.z = 0.0;
						odom_trans.transform.rotation = odom_quat;

						//send the transform
						odom_broadcaster.sendTransform(odom_trans);

						//set the position
						odom.pose.pose.position.x = -out_y;
						odom.pose.pose.position.y = out_x;
						odom.pose.pose.position.z = 0.0;
						odom.pose.pose.orientation = odom_quat;

						//publish the message
						odom_pub.publish(odom);

						cmd_vel.linear.x = out_x;
						cmd_vel.angular.z = out_y;
						cmd_pub.publish(cmd_vel);
						first = true;
						foot = false;
				}
		last_time = current_time;
		loop_rate.sleep();
		}
		return 0;
}

//座標変換
double CoordinateX(double weigh[4]) {
		return (weigh[2] + weigh[0] - weigh[1] - weigh[3]) / 4;
}

double CoordinateY(double weigh[4]) {
		return (weigh[2] + weigh[3] - weigh[1] - weigh[0] ) / 4;
}

//較正用コントローラの読み取り
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

//バランスWiiボードの値の読み取り、座標変換
void JoyCallback(const sensor_msgs::Joy& joy_msg) {
		double weigh[4];
		static int x_avg_times = 10;
		static int y_avg_times = 5;
		for(int i = 0; i < 4; i++)
			weigh[i] = joy_msg.axes[i];
		sum = weigh[0] + weigh[1] + weigh[2] + weigh[3];
		x_div = CoordinateX(weigh) / sum;
		y_div = CoordinateY(weigh) / sum;
		weight_right = weigh[0] + weigh[1];
		weight_left = weigh[2] + weigh[3];

		x_div_avg = XAverage(x_div, x_avg_times);
		y_div_avg = YAverage(y_div, y_avg_times);
}

//座標変換した値の平均化
double XAverage(double now, int times){
		static double sum = 0;
		static int log_times = 0;
		int avg_times = times;
		static double log[10];

		if(log_times < avg_times){
				sum += now;
				log[log_times] = now;
				log_times ++;
				return sum / log_times - 1;
		}else{
				sum -= log[0];
				sum += now;
				for(int i = 1; i < avg_times; i++)
						log[i-1] = log[i];
				log[avg_times-1] = now;
				return sum / avg_times;
		}
}

double YAverage(double now, int times){
		static double sum = 0;
		static int log_times = 0;
		int avg_times = times;
		static double log[5];

		if(log_times < avg_times){
				sum += now;
				log[log_times] = now;
				log_times ++;
				return sum / log_times - 1;
		}else{
				sum -= log[0];
				sum += now;
				for(int i = 1; i < avg_times; i++)
						log[i-1] = log[i];
				log[avg_times-1] = now;
				return sum / avg_times;
		}
}

//較正
void Calibration(int count, double x){
		if(count == 1){
				output = 0;
				calisum = 0;
		}
		calisum += abs(x);
		if(count == calitime){
				output = calisum / calitime;
		}
}
