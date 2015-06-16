//game.c头文件
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define BUFFSIZE 1024

typedef struct
{
	int ID;//player注册ID，从argv[5]获得
	int OnLine;//本玩家是否在线标志，未弃牌为1，弃牌为0
	int Order;//本玩家在牌局中的行动顺序，大盲注为8，小盲注为7，大盲注的下一家为1，即第一个行动
	int JettonLeft;//剩余筹码
	int Money;//剩余金币
	int Bet;//本手牌累积投注额
	int LastAction;//最后一次操作，1表示blind,2表示check让牌，3表示call跟注，4表示raise加注，5表示all_in全压，6表示fold弃牌
	int FoldNum;//本场中累积弃牌操作数
	int OperNum;//本场中累积操作数
	int Type;//0为中间型，1为激进型，2为保守型
	int RaiseInCeed;
}IDInfo;//玩家身份信息结构体

typedef struct
{
	int Pot;//池底注码数
	int Players;//在线玩家数,指未弃牌玩家数
	IDInfo ButtonID;//庄家ID
	IDInfo SBlindID;//小盲注ID
	IDInfo BBlindID;//大盲注ID
	IDInfo FirstID;//第一个决策玩家ID
	IDInfo SecondID;//第二个决策玩家ID
	IDInfo ThirdID;
	IDInfo FourthID;
	IDInfo FifthID;
}GameInfo;//牌局信息，待完善

typedef struct
{
	int ID;
	int Type;
	int OnLine;
	int LastAction;
	int OperNum;
	int FoldNum;
}Gamer;

typedef struct
{
	int Color;//花色
	int Point;//点数
}Card;//牌结构体

typedef struct
{
	Card Hand[2];//手牌信息
	Card Flop[3];//公牌消息
	Card Turn;//转牌消息
	Card River;//河牌消息
}CardType;//牌型结构体


extern int client_sockfd;//客户端套接字描述符
extern struct sockaddr_in client_addr;//客户端网络地址结构体
extern struct sockaddr_in server_addr;//服务器网络地址结构体
extern char buf[BUFFSIZE];//数据传送缓冲区
extern char SendBuf[BUFFSIZE];//发送数据缓冲区

extern IDInfo MyID;//本玩家身份信息
extern GameInfo MyGame;//本牌局信息

extern CardType MyCard;//我的牌型信息

extern IDInfo MyUpper;//存储我的上家信息

extern int whole;//1表示此包中有头无尾,2表示此包有尾无头,3表示此包是完整的

extern int SB;//小盲注大小
extern int BB;//大盲注大小

extern int CurrentJetton;//当前注码
extern IDInfo TempID;//中间变量，起过度作用

extern int GameStatus;//牌局阶段指示变量，0为手牌之前阶段，1为手牌阶段，2为公牌阶段，3为转牌阶段，4为河牌阶段，5为摊牌阶段
extern int CurrentPrice;//当前状况下参与下一轮所需要的最低投入注码数
extern int MaxBet;//当前最高投注玩家的投注额
extern Gamer MyGamers[8];
extern int GamerInitFlag;
extern int GameNum;//游戏局数
extern int MaxRaiseInCeed;
