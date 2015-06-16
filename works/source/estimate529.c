//算法相关运算函数
#include "game.h"
#include "estimate.h"
Card FlopInOrder[5];//公牌阶段安顺序排列的五张牌
Card TurnInOrder[6];
Card RiverInOrder[7];

int MaxCeed;//最大点数连续张数
int MaxSameColor;//最大花色相同张数
int MaxSamePoint;//最大点数相同张数
int MaxPair;//最大对数
float WinPos;//赢牌概率
float PotPos;//总注比
int CalCurrentPrice(void)//计算当前参与下一轮的代价
{
	MaxBet = 0;
	if(MyGame.ButtonID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.ButtonID.Bet>MaxBet)
			MaxBet = MyGame.ButtonID.Bet;
		if(MyGame.ButtonID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.ButtonID.RaiseInCeed;
	}
	
	if(MyGame.SBlindID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.SBlindID.Bet>MaxBet)
			MaxBet = MyGame.SBlindID.Bet;
		if(MyGame.SBlindID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.SBlindID.RaiseInCeed;
	}

	if(MyGame.BBlindID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.BBlindID.Bet>MaxBet)
			MaxBet = MyGame.BBlindID.Bet;
		if(MyGame.BBlindID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.BBlindID.RaiseInCeed;
	}

	if(MyGame.FirstID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.FirstID.Bet>MaxBet)
			MaxBet = MyGame.FirstID.Bet;
		if(MyGame.FirstID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.FirstID.RaiseInCeed;
	}

	
	if(MyGame.SecondID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.SecondID.Bet>MaxBet)
			MaxBet = MyGame.SecondID.Bet;
		if(MyGame.FirstID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.FirstID.RaiseInCeed;
	}

	if(MyGame.ThirdID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.ThirdID.Bet>MaxBet)
			MaxBet = MyGame.ThirdID.Bet;
		if(MyGame.ThirdID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.ThirdID.RaiseInCeed;
	}

	if(MyGame.FourthID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.FourthID.Bet>MaxBet)
			MaxBet = MyGame.FourthID.Bet;
		if(MyGame.FourthID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.FourthID.RaiseInCeed;
	}

	if(MyGame.FifthID.OnLine)//玩家没弃牌时才参与比较
	{
		if(MyGame.FifthID.Bet>MaxBet)
			MaxBet = MyGame.FifthID.Bet;
		if(MyGame.FifthID.RaiseInCeed>MaxRaiseInCeed)
			MaxRaiseInCeed = MyGame.FifthID.RaiseInCeed;
	}
	
	CurrentPrice = MaxBet - MyID.Bet;
	printf("MaxBet: %d, MyBet: %d, MaxRaiseInCeed: %d\n",MaxBet,MyID.Bet,MaxRaiseInCeed);
	return 0;
}
int InitOrder(int CardNum)//排序之前的初始化
{
	if(CardNum==5)
	{

		FlopInOrder[0] = MyCard.Hand[0];
		FlopInOrder[1] = MyCard.Hand[1];
		FlopInOrder[2] = MyCard.Flop[0];
		FlopInOrder[3] = MyCard.Flop[1];
		FlopInOrder[4] = MyCard.Flop[2];
	}
	else if(CardNum==6)
	{
		TurnInOrder[0] = MyCard.Hand[0];
		TurnInOrder[1] = MyCard.Hand[1];
		TurnInOrder[2] = MyCard.Flop[0];
		TurnInOrder[3] = MyCard.Flop[1];
		TurnInOrder[4] = MyCard.Flop[2];
		TurnInOrder[5] = MyCard.Turn;
	}
	else if(CardNum==7)
	{
		RiverInOrder[0] = MyCard.Hand[0];
		RiverInOrder[1] = MyCard.Hand[1];
		RiverInOrder[2] = MyCard.Flop[0];
		RiverInOrder[3] = MyCard.Flop[1];
		RiverInOrder[4] = MyCard.Flop[2];
		RiverInOrder[5] = MyCard.Turn;
		RiverInOrder[6] = MyCard.River;
	}

}
int IsAbleCheck(void)//判断是否可以让牌，不是算法上允许，是规则上允许与否,1表示可以,0表示不可以
{
	if(MaxBet == MyID.Bet)
		return 1;
	else 
		return 0;
}

int IsAbleCall(void)//判断规则是否允许跟注，1允许，2不允许
{
	if((MyID.JettonLeft >= CurrentPrice)&&(CurrentPrice)&&(CurrentPrice<=MyGame.Players*40))
		return 1;
	else 
		return 0;
}

int IsAbleRaise(void)
{
	if(MyID.JettonLeft > (2*MaxBet))
		return 1;
	else 
		return 0;
}

int IsAbleAllIn(void)
{
	if(MyID.JettonLeft >0)
		return 1;
	else 
		return 0;
}

int MakeDecision(void)//做出操作决策的函数,返回2表示check,返回3表示call,返回4表示raise,返回5表示all_in,返回6表示fold
{
	int Power;
	MaxCeed=1;
	MaxSameColor=1;
	MaxSamePoint=1;
	MaxPair=0;
	if(GameStatus==1)//在手牌阶段
	{
		CalCurrentPrice();
		CalPotPos(GameStatus);
		Power = CalPower();
		printf("Power: %d\n",Power);
		printf("MyBet: %d, MaxBet: %d\n",MyID.Bet,MaxBet);

		if(CurrentPrice==0)//可以让牌，手牌阶段就让牌
			return 2;//check
			
		if(Power<12)
			return 6;//牌力小于10弃牌
		else if((Power>=12)&&(Power<=20))//参考以下总注比
			{
				if(MaxRaiseInCeed>3)//有玩家在手牌阶段连续两次以上加注
					return 6;
				if(CurrentPrice>=(MyGame.Players*40))//如果当前需要加注超过500就弃牌
					return 6;//fold		
				return 3;
			}
		else if((Power>20)&&(Power<=34))
			{
				if(MaxRaiseInCeed>4)//有玩家在手牌阶段连续两次以上加注
					return 6;
				if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
					return 6;//fold
				if(IsAbleCall())
					return 3;//跟注
			}
		if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
			return 6;//fold
		if(IsAbleCall())
			return 3;//跟注			
		return 6;
	}
	else if(GameStatus==2)//公牌阶段
	{
		AnalyCard(5);//分析公牌
		CalCurrentPrice();
		printf("MaxCeed: %d, MaxSameColor: %d, MaxSamePoint: %d, MaxPair: %d\n",MaxCeed,MaxSameColor,MaxSamePoint,MaxPair);
		CalPotPos(GameStatus);
		CalWinPos(GameStatus);
		printf("WinPos: %f, PotPos: %f, WinPos-PotPos = %f\n",WinPos,PotPos,WinPos-PotPos);
		printf("CurrentPrice is: %d\n",CurrentPrice);
		if(CurrentPrice==0)//表示可让牌的情况
		{
			if(WinPos>=0.8)
			{
				if(IsAbleCall())
					return 4;
			}
			return 2;
		}
		if(WinPos-PotPos>0.3)
		{
			//if(IsAbleAllIn())
				//return 5;//all_in
			if(MaxRaiseInCeed>4)//有玩家在手牌阶段连续两次以上加注
			{
				if(Power>25)
				{
					if(IsAbleCall())
					 	return 3;
				}
				else
					return 6;
			}
			if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
					return 6;//fold
			if(IsAbleCall())
				return 4;//raise
			if(IsAbleCall())
				return 3;
		}
		else if(WinPos-PotPos>0)
		{
			if(MaxRaiseInCeed>4)//有玩家在手牌阶段连续两次以上加注
			{
				if(Power>25)
				{
					if(IsAbleCall())
					 	return 3;
				}
				else
					return 6;
			}
			if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
					return 6;//fold
			if(IsAbleCall())
				return 3;
		}
			return 6;
				
	}
	else if(GameStatus==3)//转牌阶段
	{
		AnalyCard(6);//分析公牌
		CalCurrentPrice();
		printf("MaxCeed: %d, MaxSameColor: %d, MaxSamePoint: %d, MaxPair: %d\n",MaxCeed,MaxSameColor,MaxSamePoint,MaxPair);
		CalPotPos(GameStatus);
		CalWinPos(GameStatus);
		printf("WinPos: %f, PotPos: %f, WinPos-PotPos = %f\n",WinPos,PotPos,WinPos-PotPos);
		printf("CurrentPrice is: %d\n",CurrentPrice);
		if(CurrentPrice==0)//表示可让牌的情况
		{
			if(WinPos>=0.8)
			{
				if(IsAbleCall())
					return 4;
			}
			return 2;
		}
		if(WinPos-PotPos>0.2)
		{
			if(MaxRaiseInCeed>4)//有玩家在手牌阶段连续两次以上加注
			{
				if(Power>25)
				{
					if(IsAbleCall())
					 	return 3;
				}
				else
					return 6;
			}
			if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
					return 6;//fold
			if(CurrentPrice>=MyID.JettonLeft)
				return 6;
			if(IsAbleCall())
				return 3;
		}
		else if(WinPos-PotPos>0)
		{
			//if(IsAbleRaise())
				//return 4;//raise
			if(MaxRaiseInCeed>4)//有玩家在手牌阶段连续两次以上加注
			{
				if(Power>25)	
				{
					if(IsAbleCall())
					 	return 3;
				}
				else
					return 6;
			}
			if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
					return 6;//fold
			if(IsAbleCall())
				return 3;
		}
				return 6;

			
	}
	else if(GameStatus==4)
	{
		AnalyCard(7);
		CalCurrentPrice();
		printf("MaxCeed: %d, MaxSameColor: %d, MaxSamePoint: %d, MaxPair: %d\n",MaxCeed,MaxSameColor,MaxSamePoint,MaxPair);
		CalPotPos(GameStatus);
		CalWinPos(GameStatus);
		printf("WinPos: %f, PotPos: %f, WinPos-PotPos = %f\n",WinPos,PotPos,WinPos-PotPos);
		printf("CurrentPrice is: %d\n",CurrentPrice);
		if(CurrentPrice==0)//表示可让牌的情况
		{
			if(WinPos>=0.9)
			{
				if(IsAbleCall())
					return 4;
			}
				return 2;
		}
		if(WinPos-PotPos>0.2)
		{
			if(MaxRaiseInCeed>4)//有玩家在手牌阶段连续两次以上加注
			{
				if(Power>25)
				{
					if(IsAbleCall())
					 	return 3;
				}
				else
					return 6;
			}
			if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
					return 6;//fold
			if(IsAbleCall())
				return 4;//raise
			if(IsAbleCall())
				return 3;
		}
		else if(WinPos-PotPos>0)
		{
			if(MaxRaiseInCeed>4)//有玩家在手牌阶段连续两次以上加注
			{
				if(Power>25)
				{
					if(IsAbleCall())
					 	return 3;
				}
				else
					return 6;
			}
			if(CurrentPrice>=(MyGame.Players*80))//如果当前需要加注超过500就弃牌
					return 6;//fold
			if(IsAbleCall())
				return 3;
		}
				return 6;

			
	}
}

int GetMaxCeed(int CardNum)//获取最大点数连续张数
{
	int i=0;
	int j=0;
	int ceed=1;	
	if(CardNum==5)
	{
		for(i=0;i<CardNum-1;i++)
		{
			if(FlopInOrder[i].Point==FlopInOrder[i+1].Point)
			{
				i=i+1;
				continue;
			}
			else if(FlopInOrder[i].Point == FlopInOrder[i+1].Point + 1)
				ceed++;
			else
			{
				if(MaxCeed<ceed)
					MaxCeed=ceed;
				ceed=1;
			}
		}
				if(MaxCeed<ceed)
					MaxCeed=ceed;
	}
	else if(CardNum==6)
	{
		for(i=0;i<CardNum-1;i++)
		{
			if(TurnInOrder[i].Point==TurnInOrder[i+1].Point)
			{
				i=i+1;
				continue;
			}
			else if(TurnInOrder[i].Point == TurnInOrder[i+1].Point + 1)
				ceed++;
			else
			{
				if(MaxCeed<ceed)
					MaxCeed=ceed;
				ceed=1;
			}
		}
				if(MaxCeed<ceed)
					MaxCeed=ceed;
	}
	else if(CardNum==7)
	{
		for(i=0;i<CardNum-1;i++)
		{
			if(RiverInOrder[i].Point==RiverInOrder[i+1].Point)
			{
				i=i+1;
				continue;
			}
			else if(RiverInOrder[i].Point == RiverInOrder[i+1].Point + 1)
				ceed++;
			else
			{
				if(MaxCeed<ceed)
					MaxCeed=ceed;
				ceed=1;
			}
				if(MaxCeed<ceed)
					MaxCeed=ceed;
		}
	}
}

int GetMaxSamePoint(int CardNum)//获取对大点数相同张数
{
	int same = 1;
	int i=0;
	if(CardNum==5)
	{
	for(i=0;i<CardNum-1;i++)//获得最大连续张数
	{
		if(FlopInOrder[i].Point == FlopInOrder[i+1].Point)
			same++;
		else
		{
			if(MaxSamePoint<same)
				MaxSamePoint=same;
		}
	}
	if(MaxSamePoint<same)
			MaxSamePoint=same;
	}
	if(CardNum==6)
	{
	for(i=0;i<CardNum-1;i++)//获得最大连续张数
	{
		if(TurnInOrder[i].Point == TurnInOrder[i+1].Point)
			same++;
		else
		{
			if(MaxSamePoint<same)
				MaxSamePoint=same;
		}
	}
	if(MaxSamePoint<same)
			MaxSamePoint=same;
	}
	if(CardNum==7)
	{
	for(i=0;i<CardNum-1;i++)//获得最大连续张数
	{
		if(RiverInOrder[i].Point == RiverInOrder[i+1].Point)
			same++;
		else
		{
			if(MaxSamePoint<same)
				MaxSamePoint=same;
		}
	}
	if(MaxSamePoint<same)
			MaxSamePoint=same;
	}
}

int GetMaxSameColor(int CardNum)//获取颜色相同的最大张数
{
	int spade=0;
	int heart=0;
	int clubs=0;
	int diamond=0;
	int i=0;
	if(CardNum==5)
	{
	for(i=0;i<CardNum;i++)
	{
	
		switch(FlopInOrder[i].Color)
			{
				case 1:
					spade++;
					break;
				case 2:
					heart++;
					break;
				case 3:
					clubs++;
					break;
				case 4:
					diamond++;
					break;
			}
	}
	}
	if(CardNum==6)
	{
	for(i=0;i<CardNum;i++)
	{
		switch(TurnInOrder[i].Color)
			{
				case 1:
					spade++;
					break;
				case 2:
					heart++;
					break;
				case 3:
					clubs++;
					break;
				case 4:
					diamond++;
					break;
			}
	}
	}
	if(CardNum==7)
	{
	for(i=0;i<CardNum;i++)
	{
		switch(RiverInOrder[i].Color)
			{
				case 1:
					spade++;
					break;
				case 2:
					heart++;
					break;
				case 3:
					clubs++;
					break;
				case 4:
					diamond++;
					break;
			}
	}
	}
	MaxSameColor = spade;
	if(MaxSameColor<heart)
		MaxSameColor=heart;
	else if(MaxSameColor<clubs)
		MaxSameColor=clubs;
	else if(MaxSameColor<diamond)
		MaxSameColor=diamond;
}

int GetMaxPair(int CardNum)//获取最大对数，有且仅有两张
{
	int pair = 0;
	int i=0;
	if(CardNum==5)
	{
	for(i=0;i<CardNum-1;i++)//获得最大连续张数
	{
		if(FlopInOrder[i].Point == FlopInOrder[i+1].Point)
		{
			if((i>0)&&(i<CardNum-2))
			{
				
			if((FlopInOrder[i].Point != FlopInOrder[i-1].Point)&&(FlopInOrder[i+1].Point!=FlopInOrder[i+2].Point))
				pair++;
			}
			else if(i==0)
			{
			
			if((FlopInOrder[i+1].Point != FlopInOrder[i+2].Point))
				pair++;
			}	
			else if(i==CardNum-2)
			{
				
			if((FlopInOrder[i].Point != FlopInOrder[i-1].Point))
				pair++;

			}
		}
		else
		{
			if(MaxPair<pair)
				MaxPair=pair;
		}
	}
	if(MaxPair<pair)
			MaxPair=pair;
	}
	if(CardNum==6)
	{
	for(i=0;i<CardNum-1;i++)//获得最大连续张数
	{
		if(TurnInOrder[i].Point == TurnInOrder[i+1].Point)
		{
			if((i>0)&&(i<CardNum-2))
			{
				
			if((TurnInOrder[i].Point != TurnInOrder[i-1].Point)&&(TurnInOrder[i+1].Point!=TurnInOrder[i+2].Point))
				pair++;
			}
			else if(i==0)
			{
			
			if((TurnInOrder[i+1].Point != TurnInOrder[i+2].Point))
				pair++;
			}	
			else if(i==CardNum-2)
			{
				
			if((TurnInOrder[i].Point != TurnInOrder[i-1].Point))
				pair++;

			}
		}
		else
		{
			if(MaxPair<pair)
				MaxPair=pair;
		}
	}
	if(MaxPair<pair)
			MaxPair=pair;
	}
	if(CardNum==7)
	{
	for(i=0;i<CardNum-1;i++)//获得最大连续张数
	{
		if(RiverInOrder[i].Point == RiverInOrder[i+1].Point)
		{
			if((i>0)&&(i<CardNum-2))
			{
				
			if((RiverInOrder[i].Point != RiverInOrder[i-1].Point)&&(RiverInOrder[i+1].Point!=RiverInOrder[i+2].Point))
				pair++;
			}
			else if(i==0)
			{
			
			if((RiverInOrder[i+1].Point != RiverInOrder[i+2].Point))
				pair++;
			}	
			else if(i==CardNum-2)
			{
				
			if((RiverInOrder[i].Point != RiverInOrder[i-1].Point))
				pair++;

			}
		}
		else
		{
			if(MaxPair<pair)
				MaxPair=pair;
		}
	}
	if(MaxPair<pair)
			MaxPair=pair;
	}
}


int CardOrder(int CardNum)//将牌按点数从大到小排列，CardNum=5排列后的结果存入FlopInOrder[5]数组，=6结果存入TurnInOrder,=7结果存入RiverInOrder
{
	int i=0;
	int j=0;
	Card TempCard;
	if(CardNum==5)
	{
		InitOrder(5);
		for(i=0;i<CardNum-1;++i)
		{
			for(j=i+1;j<CardNum;++j)
			{
				if(FlopInOrder[i].Point<FlopInOrder[j].Point)
				{
					TempCard = FlopInOrder[i];
					FlopInOrder[i] = FlopInOrder[j];
					FlopInOrder[j] = TempCard;
				}
			}
		}
	}
	else if(CardNum==6)
	{
		InitOrder(6);
		for(i=0;i<CardNum-1;++i)
		{
			for(j=i+1;j<CardNum;++j)
			{
				if(TurnInOrder[i].Point<TurnInOrder[j].Point)
				{
					TempCard = TurnInOrder[i];
					TurnInOrder[i] = TurnInOrder[j];
					TurnInOrder[j] = TempCard;
				}
			}
		}
	}
	else if(CardNum==7)
	{
		InitOrder(7);
		for(i=0;i<CardNum-1;++i)
		{
			for(j=i+1;j<CardNum;++j)
			{
				if(RiverInOrder[i].Point<RiverInOrder[j].Point)
				{
					TempCard = RiverInOrder[i];
					RiverInOrder[i] = RiverInOrder[j];
					RiverInOrder[j] = TempCard;
				}
			}
		}
	}

}
int AnalyCard(int CardNum)//分析牌型，获得最大点数连续张数，最大同花张数，最大点数相同张数，最大对数，CardNum是牌的张数，公牌阶段为5，转牌阶段为6，河牌阶段为7
{
	CardOrder(CardNum);
	GetMaxCeed(CardNum);
	GetMaxSameColor(CardNum);
	GetMaxSamePoint(CardNum);
	GetMaxPair(CardNum);

}


int CalPower(void)//手牌阶段计算牌力,返回牌力值
{
	//对牌
	if(MyCard.Hand[0].Point == MyCard.Hand[1].Point)//对牌
	{
		switch(MyCard.Hand[0].Point)
		{
			case 2:
			case 3:
			case 4:
				return 11;
				break;
			case 5:
				return 12;
				break;
			case 6:
			case 7:
				return 13;
				break;
			case 8:
				return 15;
				break;
			case 9:
				return 16;
				break;
			case 10:
				return 19;
				break;
			case 11:
				return 22;
				break;
			case 12:
				return 27;
				break;
			case 13:
				return 34;
				break;
			case 14:
				return 40;
				break;
		}
	}
	else if(MyCard.Hand[0].Color == MyCard.Hand[1].Color)//同花
	{
		if(CheckPoint(3,2))
			return 7;
		else if(CheckPoint(4,2))
			return 7;
		else if(CheckPoint(5,2))
			return 8;
		else if(CheckPoint(6,2))
			return 6;
		else if(CheckPoint(7,2))
			return 6;
		else if(CheckPoint(8,2))
			return 6;
		else if(CheckPoint(9,2))
			return 7;
		else if(CheckPoint(10,2))
			return 8;
		else if(CheckPoint(11,2))
			return 8;
		else if(CheckPoint(12,2))
			return 9;
		else if(CheckPoint(13,2))
			return 9;
		else if(CheckPoint(14,2))
			return 13;

		else if(CheckPoint(4,3))
			return 8;
		else if(CheckPoint(5,3))
			return 9;
		else if(CheckPoint(6,3))
			return 8;
		else if(CheckPoint(7,3))
			return 7;
		else if(CheckPoint(8,3))
			return 6;
		else if(CheckPoint(9,3))
			return 7;
		else if(CheckPoint(10,3))
			return 8;
		else if(CheckPoint(11,3))
			return 9;
		else if(CheckPoint(12,3))
			return 10;
		else if(CheckPoint(13,3))
			return 11;
		else if(CheckPoint(14,3))
			return 14;

		else if(CheckPoint(5,4))
			return 10;
		else if(CheckPoint(6,4))
			return 10;
		else if(CheckPoint(7,4))
			return 7;
		else if(CheckPoint(8,4))
			return 6;
		else if(CheckPoint(9,4))
			return 7;
		else if(CheckPoint(10,4))
			return 8;
		else if(CheckPoint(11,4))
			return 9;
		else if(CheckPoint(12,4))
			return 10;
		else if(CheckPoint(13,4))
			return 12;
		else if(CheckPoint(14,4))
			return 14;

		else if(CheckPoint(6,5))
			return 10;
		else if(CheckPoint(7,5))
			return 7;
		else if(CheckPoint(8,5))
			return 6;
		else if(CheckPoint(9,5))
			return 7;
		else if(CheckPoint(10,5))
			return 8;
		else if(CheckPoint(11,5))
			return 9;
		else if(CheckPoint(12,5))
			return 10;
		else if(CheckPoint(13,5))
			return 12;
		else if(CheckPoint(14,5))
			return 15;

		else if(CheckPoint(7,6))
			return 11;
		else if(CheckPoint(8,6))
			return 11;
		else if(CheckPoint(9,6))
			return 10;
		else if(CheckPoint(10,6))
			return 10;
		else if(CheckPoint(11,6))
			return 9;
		else if(CheckPoint(12,6))
			return 11;
		else if(CheckPoint(13,6))
			return 12;
		else if(CheckPoint(14,6))
			return 15;

		else if(CheckPoint(8,7))
			return 12;
		else if(CheckPoint(9,7))
			return 12;
		else if(CheckPoint(10,7))
			return 11;
		else if(CheckPoint(11,7))
			return 11;
		else if(CheckPoint(12,7))
			return 11;
		else if(CheckPoint(13,7))
			return 13;
		else if(CheckPoint(14,7))
			return 15;

		else if(CheckPoint(9,8))
			return 13;
		else if(CheckPoint(10,8))
			return 13;
		else if(CheckPoint(11,8))
			return 13;
		else if(CheckPoint(12,8))
			return 13;
		else if(CheckPoint(13,8))
			return 13;
		else if(CheckPoint(14,8))
			return 15;

		else if(CheckPoint(10,9))
			return 15;
		else if(CheckPoint(11,9))
			return 15;
		else if(CheckPoint(12,9))
			return 15;
		else if(CheckPoint(13,9))
			return 15;
		else if(CheckPoint(14,9))
			return 18;

		else if(CheckPoint(11,10))
			return 18;
		else if(CheckPoint(12,10))
			return 18;
		else if(CheckPoint(13,10))
			return 18;
		else if(CheckPoint(14,10))
			return 19;

		else if(CheckPoint(12,11))
			return 19;
		else if(CheckPoint(13,11))
			return 20;
		else if(CheckPoint(14,11))
			return 20;

		else if(CheckPoint(13,12))
			return 21;
		else if(CheckPoint(14,12))
			return 22;

		else if(CheckPoint(14,13))
			return 24;
	}
	else//非同花
	{
		
		if((MyCard.Hand[0].Point+MyCard.Hand[1].Point)>=26)
			return 21;
		else if((MyCard.Hand[0].Point+MyCard.Hand[1].Point)>=20)
			return 10;
		else return 5;	
	}
}

int CheckPoint(int point1,int point2)//检查手牌是否点数为point1和point2,如果是返回1，不是返回0
{
	if((MyCard.Hand[0].Point==point1)&&(MyCard.Hand[1].Point == point2))
			return 1;
	 
	else if((MyCard.Hand[1].Point==point1)&&(MyCard.Hand[0].Point == point2))
			return 1;
	else return 0;
}

float CalPotPos(int GameSatus)//计算总注比，GameStatus表示牌型阶段
{
	PotPos = (CurrentPrice*(1.0))/(MyGame.Pot*1.0);

}

float CalWinPos(int GameStatus)
{
	float temp=0.0;
	if(GameStatus==2)//公牌阶段
	{
		if(MaxSamePoint==4)//金刚牌型
		{
			temp+=0.8;//金刚90%硬派概率
		}
		else if(MaxSamePoint == 3)
		{
			temp+=(0.06*0.7) + (0.0009*0.8)+ 0.4;
		}
	 
		if(MaxSameColor==5)
		{
			temp+=0.6;
		}	
		else if(MaxSameColor==4)//4同花
		{
			temp+=0.19*0.6;
		}
		else if(MaxSameColor==3)//3同花
		{
			temp+=0.03*0.6;
		}
	
		if(MaxCeed == 5)
		{
			temp+=0.5;
		}	
		else if(MaxCeed==4)//两头顺子
		{
			temp+=0.17*0.5;
		}
		else if(MaxCeed==3)
		{
			temp+=0.13*0.5;
		}

		if(MaxPair==2)
		{
			temp+=0.3 + (0.09*0.8) + (0.09*0.7);
		}	
		else if(MaxPair==1)
		{
			temp+=(0.04*0.8) + (0.04*0.4)+0.2;
		}
		
		temp+=0.05;//高牌的硬派概率
		WinPos = temp;
	}
	if(GameStatus==3)//转牌阶段，只能补一张牌
	{
		if(MaxSamePoint==4)//金刚牌型
		{
			temp+=0.8;//金刚90%硬派概率
		}
		else if(MaxSamePoint == 3)
		{
			temp+= (0.0009*0.8)+0.4;
		}
	 	
		if(MaxSameColor==5)
		{
			temp+=0.6;
		}	
		else if(MaxSameColor==4)//4同花
		{
			temp+=0.19*0.6;
		}
		
		if(MaxCeed == 5)
		{
			temp+=0.5;
		}	
		else if(MaxCeed==4)//两头顺子
		{
			temp+=0.17*0.5;
		}

		if(MaxPair==2)
		{
			temp+=0.3  + (0.09*0.7);
		}	
		else if(MaxPair==1)
		{
			temp+= (0.04*0.4)+0.2;
		}
		
		temp+=0.05;//高牌的硬派概率
		WinPos = temp;
	}
	if(GameStatus==4)//转牌阶段，没有补牌了
	{
		if(MaxSamePoint==4)//金刚牌型
		{
			temp+=0.8;//金刚90%硬派概率
		}
		else if(MaxSamePoint == 3)
		{
			temp+= 0.4;
		}
	 	
		if(MaxSameColor==5)//4同花
		{
			temp+=0.6;
		}
		
		if(MaxCeed==5)//两头顺子
		{
			temp+=0.5;
		}

		if(MaxPair==2)
		{
			temp+=0.3;
		}	
		else if(MaxPair==1)
		{
			temp+= 0.2;
		}
		
		temp+=0.05;//高牌的硬派概率
		WinPos = temp;
	}
}
