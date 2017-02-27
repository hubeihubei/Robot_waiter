# Robot_waiter
It is about face rocognization used cob_people_detection package, text to speech used iFLYTEK SDK,and an android app to control a robot moving
#Tips
1.人脸识别启动    参考网址http://wiki.ros.org/cob_people_detection
2.roslaunch openni2_launch openni2.launch
3.roslaunch cob_people_detection people_detection.launch
4.rosrun cob_people_detection people_detection_client采集人脸图片数据，按C键采集，注意要把鼠标放在终端中
5.根据提示在终端按4
6.播放音频文件参考http://wiki.ros.org/sound_play
7.启动其他节点roslaunch sound_play test.launch
