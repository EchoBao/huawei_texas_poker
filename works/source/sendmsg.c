//发送各种消息的函数
#include "game.h"
#include "sendmsg.h"

int SendMsg(int type)//函数作用是向服务器发送消息,type指名消息类型，1表示注册,2表示check,3表示call，type=="action"表示行动消息
{
	char MsgBuf[BUFFSIZE];
	memset(MsgBuf,0,sizeof(MsgBuf));
	if(1==type)//注册消息
	{

		sprintf(MsgBuf,"reg:%d Debugger \n",MyID.ID);
		int nsend=0;
		nsend = send(client_sockfd,MsgBuf,strlen(MsgBuf),0);
		if(nsend>0)
		{
			printf("%s\n",MsgBuf);
		}
		return nsend;
	}
	else if(2==type)//check
	{	
		sprintf(MsgBuf,"check \n");
		int nsend=0;
		nsend = send(client_sockfd,MsgBuf,strlen(MsgBuf),0);
		if(nsend>0)
		{
			printf("%s\n",MsgBuf);
		}
		return nsend;
	}
	else if(3==type)//call
	{
		
		sprintf(MsgBuf,"call \n");
		int nsend=0;
		nsend = send(client_sockfd,MsgBuf,strlen(MsgBuf),0);
		if(nsend>0)
		{
			printf("%s\n",MsgBuf);
		}
		return nsend;
	}
	else if(4==type)//raise
	{
		sprintf(MsgBuf,"raise 50 \n");
		int nsend=0;
		nsend = send(client_sockfd,MsgBuf,strlen(MsgBuf),0);
		if(nsend>0)
		{
			printf("%s\n",MsgBuf);
		}
		return nsend;

	}
	else if(5==type)//all_in
	{

		sprintf(MsgBuf,"all_in \n");
		int nsend=0;
		nsend = send(client_sockfd,MsgBuf,strlen(MsgBuf),0);
		if(nsend>0)
		{
			printf("%s\n",MsgBuf);
		}
		return nsend;
	}
	else if(6==type)//fold
	{	
		memset(MsgBuf,0,sizeof(MsgBuf));
		sprintf(MsgBuf,"fold \n");
		int nsend=0;
		nsend = send(client_sockfd,MsgBuf,strlen(MsgBuf),0);
		if(nsend>0)
		{
			printf("%s\n",MsgBuf);
		}
		return nsend;
	}
	return 2;
}
