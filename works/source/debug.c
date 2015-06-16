//与调试相关的函数
#include "game.h"
#include "debug.h"


void PrintGameInfo(void)//打印GameInfo结构体信息函数，用于调试
{
	printf("The pot now is: %d\n",MyGame.Pot);
	printf("There are %d players in game!\n",MyGame.Players);
	printf("Button ID is %d,Button JettonLeft is %d,Button Money is %d,Button OnLine is:%d,Button Order is %d,Button Bet is %d,Button LastAction is %d\n",MyGame.ButtonID.ID,MyGame.ButtonID.JettonLeft,MyGame.ButtonID.Money,MyGame.ButtonID.OnLine,MyGame.ButtonID.Order,MyGame.ButtonID.Bet,MyGame.ButtonID.LastAction);
			
	printf("Small Blind ID is %d,Small Blind JettonLeft is %d,Small Blind Money is %d,Small Blind OnLine is %d,Small Blind Order is %d,Small Blind Bet is %d,Small Blind LastLocation is %d\n",MyGame.SBlindID.ID,MyGame.SBlindID.JettonLeft,MyGame.SBlindID.Money,MyGame.SBlindID.OnLine,MyGame.SBlindID.Order,MyGame.SBlindID.Bet,MyGame.SBlindID.LastAction);

	printf("Big Blind ID is %d,Big Blind JettonLeft is %d,Big Blind Money is %d,Big Blind OnLine is %d,Big Blind Order is %d,Big Blind Bet is %d,Big Blind LastAction is %d\n",MyGame.BBlindID.ID,MyGame.BBlindID.JettonLeft,MyGame.BBlindID.Money,MyGame.BBlindID.OnLine,MyGame.BBlindID.Order,MyGame.BBlindID.Bet,MyGame.BBlindID.LastAction);


	printf("First ID is %d,First ID JettonLeft is %d,First ID Money is %d,First OnLine is %d,First Order is %d,First Bet is %d,First LastAction is %d\n",MyGame.FirstID.ID,MyGame.FirstID.JettonLeft,MyGame.FirstID.Money,MyGame.FirstID.OnLine,MyGame.FirstID.Order,MyGame.FirstID.Bet,MyGame.FirstID.LastAction);
			
	printf("Second ID is %d,Second ID JettonLeft is %d,Second ID Money is %d,Second OnLine is %d,Second Order is %d,Second Bet is %d,Second LastAction is %d\n",MyGame.SecondID.ID,MyGame.SecondID.JettonLeft,MyGame.SecondID.Money,MyGame.SecondID.OnLine,MyGame.SecondID.Order,MyGame.SecondID.Bet,MyGame.SecondID.LastAction);

	printf("Third ID is %d,Third ID JettonLeft is %d,Third ID Money is %d,Third OnLine is %d,Third Order is %d,Third Bet is %d,Thid LastAction is %d\n",MyGame.ThirdID.ID,MyGame.ThirdID.JettonLeft,MyGame.ThirdID.Money,MyGame.ThirdID.OnLine,MyGame.ThirdID.Order,MyGame.ThirdID.Bet,MyGame.ThirdID.LastAction);
			
	printf("Fourth ID is %d,Fourth ID JettonLeft is %d,FourthID Money is %d,Fourth OnLine is %d,Fourth Order is %d,Fourth Bet is %d,Fourth LastAction is %d\n",MyGame.FourthID.ID,MyGame.FourthID.JettonLeft,MyGame.FourthID.Money,MyGame.FourthID.OnLine,MyGame.FourthID.Order,MyGame.FourthID.Bet,MyGame.FourthID.LastAction);

	printf("Fifth ID is %d,Fifth ID JettonLeft is %d,Fifth ID Money is %d,Fifth OnLine is %d,Fifth Order is %d,Fifth Bet is %d,Fifth LastAction is %d\n",MyGame.FifthID.ID,MyGame.FifthID.JettonLeft,MyGame.FifthID.Money,MyGame.FifthID.OnLine,MyGame.FifthID.Order,MyGame.FifthID.Bet,MyGame.FourthID.LastAction);


}

void PrintAnaly(void)
{
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.ButtonID.ID,MyGame.ButtonID.OperNum,MyGame.ButtonID.FoldNum);
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.SBlindID.ID,MyGame.SBlindID.OperNum,MyGame.SBlindID.FoldNum);
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.BBlindID.ID,MyGame.BBlindID.OperNum,MyGame.BBlindID.FoldNum);
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.FirstID.ID,MyGame.FirstID.OperNum,MyGame.FirstID.FoldNum);
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.SecondID.ID,MyGame.SecondID.OperNum,MyGame.SecondID.FoldNum);
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.ThirdID.ID,MyGame.ThirdID.OperNum,MyGame.ThirdID.FoldNum);
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.FourthID.ID,MyGame.FourthID.OperNum,MyGame.FourthID.FoldNum);
	printf("%d's OperNum: %d,FoldNum: %d\n",MyGame.FifthID.ID,MyGame.FifthID.OperNum,MyGame.FifthID.FoldNum);
}
	
int PrintIDInfo(void)//打印IDInfo结构体信息，用于调试
{
	printf("MyID is %d\n",MyID.ID);
	printf("My OnLine Status is %d\n",MyID.OnLine);
	printf("My Order is %d\n",MyID.Order);
	printf("My JettonLeft is %d\n",MyID.JettonLeft);
	printf("My Money is %d\n",MyID.Money);
	printf("My Bet is %d\n",MyID.Bet);
	return 0;
}


int PrintBlindInfo(void)//打印盲注信息
{
	printf("Small Blind is %d\n",SB);
	printf("Big Blind is %d\n",BB);
	return 0;
}

int PrintCardInfo(void)//打印牌型信息
{
	printf("Hand1 is %d %d\n",MyCard.Hand[0].Color,MyCard.Hand[0].Point);
	printf("Hand2 is %d %d\n",MyCard.Hand[1].Color,MyCard.Hand[1].Point);

	printf("Flop1 is %d %d\n",MyCard.Flop[0].Color,MyCard.Flop[0].Point);
	printf("Flop2 is %d %d\n",MyCard.Flop[1].Color,MyCard.Flop[1].Point);
	printf("Flop3 is %d %d\n",MyCard.Flop[2].Color,MyCard.Flop[2].Point);

	printf("Turn is %d %d\n",MyCard.Turn.Color,MyCard.Turn.Point);
	printf("River is %d %d\n",MyCard.River.Color,MyCard.River.Point);
	return 0;
}

int PrintMyUpper(void)//打印我的上家信息
{
	
	printf("MyUpper ID is %d,MyUpper JettonLeft is %d,MyUpper Money is %d,MyUpper OnLine is %d,MyUpper Order is %d,MyUpper Bet is %d,MyUpper LastAction is %d\n",MyUpper.ID,MyUpper.JettonLeft,MyUpper.Money,MyUpper.OnLine,MyUpper.Order,MyUpper.Bet,MyUpper.LastAction);
}
