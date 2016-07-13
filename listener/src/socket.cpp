#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "iconv.h"

int main(int argc,char **argv)
{
	ros::init(argc,argv,"talker");//初始化ROS，说明节点名称
	ros::NodeHandle n;//创建节点句柄
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter",1000);//告诉主机，我们将在话题chatter上发布（std——msgs：：String类型）信息，能缓冲1000条信息
	ros::Rate loop_rate(10);//循环频率为10Hz
	int count = 0;

    	int server_sockfd;//服务器端套接字
    	int client_sockfd;//客户端套接字    
    	int len;  
    	struct sockaddr_in my_addr;   //服务器网络地址结构体
    	struct sockaddr_in remote_addr; //客户端网络地址结构体   
    	socklen_t sin_size=0;  
    	char buf[BUFSIZ];  //数据传送的缓冲区  
    	memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零  
    	my_addr.sin_family=AF_INET; //设置为IP通信  
    	my_addr.sin_addr.s_addr=INADDR_ANY;//inet_addr("")IP地址//服务器IP地址--允许连接到所有本地地址上  
    	my_addr.sin_port=htons(60000); //服务器端口号  

	/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/  
    	if((server_sockfd=socket(AF_INET,SOCK_STREAM,0))<0)  
    	{    
        	perror("socket");  
        	return 1;  
    	}  

        /*将套接字绑定到服务器的网络地址上*/  
    	if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)  
    	{  
        	perror("bind");  
       		return 1;  
    	}    
  
    	//len=send(client_sockfd,"Welcome to my server/n",21,0);//发送欢迎信息  
	//connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr));
	int i=0;
	while(ros::ok())
	{
		std_msgs::String msg;
		std::stringstream ss;
		//ss<<"hello world"<<count;
		/*监听连接请求--监听队列长度为10*/  
    		if(listen(server_sockfd,10)<0)
		{
			perror("listen");  
        		return 1;
		}
	    	sin_size=sizeof(struct sockaddr_in);  
      
   	 	/*等待客户端连接请求到达*/  
    		if((client_sockfd=accept(server_sockfd,(struct sockaddr      *)&remote_addr,&sin_size))<0)  
    		{  
       			perror("accept");  
        		return 1;  
    		} 
		printf("accept client %s ->",inet_ntoa(remote_addr.sin_addr));
		if((len=recv(client_sockfd,buf,BUFSIZ,0))<0)
		{
			perror("recv");
			return 1;
		}
		//else{
	        //	buf[len]='\0';
		//	while(i++<len)
		//		putchar(buf[i-1]);
		//	putchar('\n');
		//	i=0;				
		//} 
		ss<<buf[2];
		msg.data = ss.str();
		//printf("%c\n",buf[2]);  
		ROS_INFO("%s",msg.data.c_str());//输出与printf和cout等同
		chatter_pub.publish(msg);//向话题chatter发布消息
		ros::spinOnce();//回调
		loop_rate.sleep();//延时0.1s
		++count;
		close(client_sockfd); 
	}
	 
    	close(server_sockfd); 

	return 0;
}
