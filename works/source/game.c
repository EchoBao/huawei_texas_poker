#include "game.h"
#include "decode.h"
#include "debug.h"
#include "sendmsg.h"
#include "estimate.h"
int client_sockfd;//客户端套接字描述符
struct sockaddr_in client_addr;//客户端网络地址结构体
struct sockaddr_in server_addr;//服务器网络地址结构体
char buf[BUFFSIZE];//数据接收缓冲区
char SendBuf[BUFFSIZE];//发送数据缓冲区

IDInfo MyID;//本玩家身份信息
GameInfo MyGame;//本牌局信息

CardType MyCard;//我的牌型信息

IDInfo MyUpper;//存储我的上家信息

int whole=0;//1表示此包中有头无尾,2表示此包有尾无头,3表示此包是完整的

int SB=0;//小盲注大小
int BB=0;//大盲注大小

int CurrentJetton=0;//当前注码
IDInfo TempID;//中间变量，起过度作用

int GameStatus=0;//牌局阶段指示变量，0为手牌之前阶段，1为手牌阶段，2为公牌阶段，3为转牌阶段，4为河牌阶段，5为摊牌阶段
int ReadLen=0;//消息的完整实际长度
int PeekRet=0;
int CurrentPrice=0;//当前状况下参与下一轮所需要的最低投入注码数
int MaxBet=0;//当前最高投注玩家的投注额
int GameNum=0;
int MaxRaiseInCeed = 0;
int Init(char** argv)//初始化相关全局变量的函数
{
	MyID.ID = atoi(argv);
	MyID.OnLine = 1;//在线
	MyID.Order = 0;//未获取
	MyID.JettonLeft = 0;
	MyID.Money = 0;
	MyID.Bet = 0;
	MyID.LastAction = 0;

	TempID.ID = 0;
	TempID.OnLine = 0;//在线
	TempID.Order = 0;//未获取
	TempID.JettonLeft = 0;
	TempID.Money = 0;
	TempID.Bet = 0;
	TempID.LastAction = 0;
	TempID.OperNum = 0;
	TempID.FoldNum = 0;
	TempID.Type = 0;
	TempID.RaiseInCeed =0;

	MyGame.Players = 0;
	MyGame.ButtonID = TempID;
	MyGame.SBlindID = TempID;
	MyGame.BBlindID = TempID;
	MyGame.FirstID = TempID;
	MyGame.SecondID = TempID;
	MyGame.ThirdID = TempID;
	MyGame.FourthID = TempID;
	MyGame.FifthID = TempID;

	MyCard.Hand[0].Color = 0;
	MyCard.Hand[0].Point = 0;

	MyCard.Hand[1].Color = 0;
	MyCard.Hand[1].Point = 0;

	MyCard.Flop[0].Color = 0;
	MyCard.Flop[1].Color = 0;
	MyCard.Flop[2].Color = 0;
	MyCard.Flop[0].Point = 0;
	MyCard.Flop[1].Point = 0;
	MyCard.Flop[2].Point = 0;
	

	MyCard.Turn.Color = 0;
	MyCard.Turn.Point = 0;

	MyCard.River.Color = 0;
	MyCard.River.Point = 0;

	MyUpper.ID = 0;
	MyUpper.OnLine = 0;//在线
	MyUpper.Order = 0;//未获取
	MyUpper.JettonLeft = 0;
	MyUpper.Money = 0;
	MyUpper.Bet = 0;
	MyUpper.LastAction = 0;
	MyUpper.OperNum =0;
	MyUpper.FoldNum = 0;

	whole =0;
	SB=0;
	BB=0;

	CurrentJetton = 0;
	
	GameStatus = 0;
	
	CurrentPrice = 0;
	
	MaxBet = 0;
	MaxRaiseInCeed = 0;
	return 0;
}

int main(int argc,char** argv)//argv[1]服务器IP地址，argv[2]服务器端口，argv[3]客户端IP,argv[4]客户端端口,argv[5]客户端注册ID
{
	int len;
	memset(buf,0,sizeof(buf));

	memset(&client_addr,0,sizeof(client_addr));
	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	int server_port = atoi(argv[2]);
	server_addr.sin_port = htons(server_port);
	
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(argv[3]);
	int client_port = atoi(argv[4]);
	client_addr.sin_port = htons(client_port);

	//创建客户端套接字
	client_sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(client_sockfd<0)
	{
		printf(argv[5]);
		return 1;
	}

	//设置可重复使用
	int reuse=1;
	setsockopt(client_sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	//将客户端套接字和客户端网络地址绑定
	if(bind(client_sockfd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr))<0)
	{
		printf(argv[5]);
	}

	//客户端连接服务器
	while(connect(client_sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))<0)
	{
		sleep(1);
	}

	printf("connected to server!\n");
	//初始化相关全局变量	
	Init(argv[5]);
	//向服务器发送注册消息
	SendMsg(1);

	int ReadLen=0;//消息的完整实际长度
	int PeekRet=0;
MainLoop:	
	
	printf("\n\n\n\n\nNew Round Beigin!\n\n");
	GameNum++;
	printf("GameNum: %d\n",GameNum);
	//初始化相关全局变量	
	Init(argv[5]);


	//判断消息类型，并获取消息长度
	ReadLen=0;//消息的完整实际长度
	PeekRet=0;
	while(PeekRet==0)
	PeekRet = Peek(&ReadLen);
	printf("PeekRet is %d\n",PeekRet);
	if(PeekRet==1)//结束消息
	{
		memset(buf,0,sizeof(buf));
		recv(client_sockfd,buf,ReadLen,0);//接收座次消息，消息形式：广播
		printf("%s recv msg is:\n%s",argv[5],buf);
		close(client_sockfd);//关闭套接字
		return 0;
	}
	else if(PeekRet==2)//座次消息
	{
		//接收座次消息
		memset(buf,0,sizeof(buf));
		recv(client_sockfd,buf,ReadLen,0);//接收座次消息，消息形式：广播
		printf("%s recv msg is:\n%s",argv[5],buf);

		if(DecodeFrame(buf,1))//解析座次信息
		{

		//PrintGameInfo();//向文件打印GameInfo信息

		//PrintIDInfo();//打印MyID
		}
	
	}

	//是否盲注玩家，如果是盲注玩家，更新Bet
		
	PeekRet = Peek(&ReadLen);//判断消息类型，如果有盲注消息，说明是盲注玩家，需更新相应信
	if(PeekRet == 10)
	{	
		memset(buf,0,sizeof(buf));
		recv(client_sockfd,buf,ReadLen,0);//接收盲注信息，消息形式：广播
		printf("Blind Msg is:\n%s",buf);
		if(DecodeFrame(buf,2))//解析盲注消息
		{
			//PrintBlindInfo();
		}
		if(MyID.ID == MyGame.SBlindID.ID)//小盲注
		{
			MyID.Bet = SB;//更新自己的Bet
			MyID.JettonLeft = MyID.JettonLeft - SB;
		}
		else if(MyID.ID == MyGame.BBlindID.ID)//大盲注
		{
			MyID.Bet = BB;//更新自己的Bet
			MyID.JettonLeft = MyID.JettonLeft - BB;//减去大盲注筹码
		}
	}

	PeekRet = Peek(&ReadLen);//判断消息类型
	if(PeekRet == 3)//手牌消息,解析手牌消息
	{
		memset(buf,0,sizeof(buf));
		recv(client_sockfd,buf,ReadLen,0);//接收手牌消息，消息形式：单播
		printf("Hand Msg is:\n%s",buf);
		if(DecodeFrame(buf,3))//解析手牌消息
		{
			GameStatus = 1;//标志进入手牌阶段
		}
	}

WaitInquire:	PeekRet = Peek(&ReadLen);//判断消息类型
	if(PeekRet == 4)//询问消息
	{
DecodeInquire:	memset(buf,0,sizeof(buf));
		recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
		printf("The inquire msg is:\n%s",buf);
		if(DecodeFrame(buf,4))//解析询问消息
		{
			printf("MaxBet: %d, MyBet: %d\n",MaxBet,MyID.Bet);	
			PrintAnaly();//打印统计信息
		}
	}


	int Decision=0;
	printf("Game Status is %d\n",GameStatus);
	Decision=MakeDecision();//做出决策并发送决策消息
	printf("Decision is %d\n",Decision);	
	SendMsg(Decision);//做出决策并发送决策消息	
	PrintGameInfo();//向文件打印GameInfo信息
	printf("CurrentPrice: %d, MyGame.Players: %d\n",CurrentPrice,MyGame.Players);
	if(Decision==6)//是弃牌消息
	{
		PeekRet = Peek(&ReadLen);
		if(PeekRet==5)
		{
			memset(buf,0,sizeof(buf));
			recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
		}
		PeekRet = Peek(&ReadLen);
		if(PeekRet==6)
		{
			memset(buf,0,sizeof(buf));
			recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
		}
		PeekRet = Peek(&ReadLen);
		if(PeekRet==7)
		{
			memset(buf,0,sizeof(buf));
			recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
		}
		PeekRet = Peek(&ReadLen);
		if(PeekRet==8)
		{
			memset(buf,0,sizeof(buf));
			recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
		}
		PeekRet = Peek(&ReadLen);
		if(PeekRet==9)
		{
			memset(buf,0,sizeof(buf));
			recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
		}
				
				
		goto MainLoop;
	}
	else 
	{
		ReadLen=0;//消息的完整实际长度
		PeekRet=0;
		while(PeekRet==0)
		PeekRet = Peek(&ReadLen);//等待直到有消息到来
		if(PeekRet==4)//询问消息
		{
			goto DecodeInquire;
		}
		else if(GameStatus==4)//已经进入河牌阶段
		{
			//接收摊牌消息
			PrintCardInfo();
			if(GetOnLinePlayers>=2)
			{
				//接收摊牌消息
				PeekRet = Peek(&ReadLen);//等待直到有消息到来
				memset(buf,0,sizeof(buf));
				recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
				printf("The showdown msg is:\n%s",buf);
			}
			//接收彩池分配消息
			PeekRet = Peek(&ReadLen);//等待直到有消息到来
			memset(buf,0,sizeof(buf));
			recv(client_sockfd,buf,ReadLen,0);//接收询问消息，消息形式：单播
			printf("The pot-win msg is:\n%s",buf);
			goto MainLoop;
			
		}
		else//接收并解析牌型消息
		{
			//嗅探消息判定是哪种牌型，解析牌型消息，并更新GaomeStatus
			PeekRet = Peek(&ReadLen);//判断消息类型
			if(PeekRet == 5)//公牌消息
			{
				memset(buf,0,sizeof(buf));
				recv(client_sockfd,buf,ReadLen,0);//接收手牌消息，消息形式：单播
		        	if(DecodeFrame(buf,5))//解析手牌消息
		        	{
			        GameStatus = 2;//标志进入公牌阶段
				}
			}
			else if(PeekRet == 6)//转牌消息
			{
				memset(buf,0,sizeof(buf));
				recv(client_sockfd,buf,ReadLen,0);//接收转牌消息，消息形式：单播
		        	if(DecodeFrame(buf,6))//解转牌消息
		        	{
			        GameStatus = 3;//标志进入转牌阶段
				}
			}
			else if(PeekRet == 7)//河牌消息
			{
				memset(buf,0,sizeof(buf));
				recv(client_sockfd,buf,ReadLen,0);//接收河牌消息，消息形式：单播
		        	if(DecodeFrame(buf,7))//解析河牌消息
		        	{
			        GameStatus = 4;//标志进入河牌阶段
				}
			}
			else if(PeekRet == 9)//其他所有人都弃牌了，直接接收pot-win msg
			{
				memset(buf,0,sizeof(buf));
				recv(client_sockfd,buf,ReadLen,0);//接收河牌消息，消息形式：单播
				goto MainLoop;
			}

			goto WaitInquire;
		}
	}
	close(client_sockfd);	
	printf("game end innormal\n");
	return 0;
}	
