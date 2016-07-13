#include "ros/ros.h"
#include "cob_perception_msgs/DetectionArray.h"

void chatterCallback(const cob_perception_msgs::DetectionArray &face_position_msg_out)
{    FILE *fp;
	for (int i=0; i<(int)face_position_msg_out.detections.size(); i++)
	       {
	     	ROS_INFO("Iheard: %s",face_position_msg_out.detections[i].label.c_str());
   		fp = fopen("/home/exbot/1.txt", "w+");
	 	fputs(face_position_msg_out.detections[i].label.c_str(),fp);
		fclose(fp);
	       }	
}


int main(int argc, char **argv)
{
	FILE *fp;
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("cob_people_detection/detection_tracker/face_position_array", 1000, chatterCallback);
   	ros::spin();
	return 0;
}
