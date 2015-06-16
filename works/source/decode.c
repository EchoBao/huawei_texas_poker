//解析消息相关函数
#include "game.h"
#include "decode.h"

int DecodeFrame(const char* buf,int type)//解析包函数，type表示包的类型，1表示解析座次消息
{
	char* p,*q,*start,*end;
	char str[10];
	if(1==type)//解析座次消息
	{
		memset(str,0,sizeof(str));
		if((start=strstr(buf,"seat/"))&&(end=strstr(buf,"/seat")))
		{
			whole=3;//有头有尾
			p=strstr(buf,"button: ");
			p=p+8;
			q=p;
			memset(&str,0,sizeof(str));
			while(*q!=' ')//提取庄家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.ButtonID.ID=atoi(str);//更新牌局信息
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取庄家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.ButtonID.JettonLeft=atoi(str);//更新派军信息中庄家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取庄家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.ButtonID.Money=atoi(str);//更新牌局信息中庄家金币数
			MyGame.Players++;//玩家数加一
			MyGame.ButtonID.OnLine = 1;//在线标志置1



			
			p=strstr(buf,"small blind: ");//定位小盲注字段
			p=p+13;
			q=p;
			
			memset(str,0,sizeof(str));
			while(*q!=' ')//提取小盲注玩家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.SBlindID.ID=atoi(str);//更新牌局小盲注玩家ID
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取小盲注玩家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.SBlindID.JettonLeft=atoi(str);//更新牌局信息小盲注玩家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取小盲注玩家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.SBlindID.Money=atoi(str);//更新牌局信息中庄家金币数
			MyGame.Players++;//玩家数加一
			MyGame.SBlindID.OnLine = 1;


			p=strstr(buf,"big blind: ");//定位大盲注字段
			if(p==NULL) goto UpdateMyID;
			p=p+11;
			q=p;
			
			memset(str,0,sizeof(str));
			while(*q!=' ')//提取大盲注玩家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.BBlindID.ID=atoi(str);//更新牌局大盲注玩家ID
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取大盲注玩家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.BBlindID.JettonLeft=atoi(str);//更新牌局信息大盲注玩家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取大盲注玩家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.BBlindID.Money=atoi(str);//更新牌局信息中大盲注金币数
			MyGame.Players++;//玩家数加一
			MyGame.BBlindID.OnLine = 1;


			q=q+2;
			p=q;
			if(q==end)
				goto UpdateMyID;	
			
			memset(str,0,sizeof(str));
			while(*q!=' ')//提取first玩家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FirstID.ID=atoi(str);//更新牌局First玩家ID
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取First玩家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FirstID.JettonLeft=atoi(str);//更新牌局信息First玩家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取First玩家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FirstID.Money=atoi(str);//更新牌局信息中First金币数
			MyGame.Players++;//玩家数加一
			MyGame.FirstID.OnLine = 1;



			
			q=q+2;
			p=q;
			if(q==end)
				goto UpdateMyID;	
			
			memset(str,0,sizeof(str));
			while(*q!=' ')//提取Sencond玩家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.SecondID.ID=atoi(str);//更新牌局Second玩家ID
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取Second玩家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.SecondID.JettonLeft=atoi(str);//更新牌局信息Second玩家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取Second玩家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.SecondID.Money=atoi(str);//更新牌局信息中Second金币数
			MyGame.Players++;//玩家数加一
			MyGame.SecondID.OnLine = 1;



			
			q=q+2;
			p=q;
			if(q==end)
				goto UpdateMyID;	
			
			memset(str,0,sizeof(str));
			while(*q!=' ')//提取Third玩家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.ThirdID.ID=atoi(str);//更新牌局Third玩家ID
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取Third玩家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.ThirdID.JettonLeft=atoi(str);//更新牌局信息Third玩家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取Third玩家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.ThirdID.Money=atoi(str);//更新牌局信息中First金币数
			MyGame.Players++;//玩家数加一
			MyGame.ThirdID.OnLine = 1;



			q=q+2;
			p=q;
			if(q==end)
				goto UpdateMyID;	
			
			memset(str,0,sizeof(str));
			while(*q!=' ')//提取Fourth玩家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FourthID.ID=atoi(str);//更新牌局Fourth玩家ID
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取Fourth玩家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FourthID.JettonLeft=atoi(str);//更新牌局信息Fourth玩家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取Fourth玩家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FourthID.Money=atoi(str);//更新牌局信息中Fourth金币数
			MyGame.Players++;//玩家数加一
			MyGame.FourthID.OnLine = 1;



			q=q+2;
			p=q;
			if(q==end)
				goto UpdateMyID;	
			
			memset(str,0,sizeof(str));
			while(*q!=' ')//提取Fifth玩家ID
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FifthID.ID=atoi(str);//更新牌局FifthID玩家ID
			while(*(q)==' ')q++;
			p=q;
			
			memset(str,0,sizeof(str));
			
			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取FifthID玩家筹码数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FifthID.JettonLeft=atoi(str);//更新牌局信息First玩家筹码数
			while((*q==' ')&&(q<end))q++;
			p=q;
			
			memset(str,0,sizeof(str));

			while((*q!=' ')&&(q<end)&&(*q!='\n'))//提取FifthID玩家金币数
			{
				str[q-p]=*q;
				q++;
			}
			MyGame.FifthID.Money=atoi(str);//更新牌局信息中FifthID金币数
			MyGame.Players++;//玩家数加一
			MyGame.FifthID.OnLine = 1;

			
	UpdateMyID:	if(MyID.ID == MyGame.ButtonID.ID)
			{
				MyID.JettonLeft = MyGame.ButtonID.JettonLeft;
				MyID.Money = MyGame.ButtonID.Money;
				MyID.Order = MyGame.Players-2;
			}
			else if(MyID.ID == MyGame.SBlindID.ID)
			{
			MyID.JettonLeft = MyGame.SBlindID.JettonLeft;
			MyID.Money = MyGame.SBlindID.Money;
			MyID.Order = MyGame.Players-1;
			}
			else if(MyID.ID ==  MyGame.BBlindID.ID)
			{
			MyID.JettonLeft = MyGame.BBlindID.JettonLeft;
			MyID.Money = MyGame.BBlindID.Money;
			MyID.Order = MyGame.Players;
			}
			else if(MyID.ID == MyGame.FirstID.ID)
			{
			MyID.JettonLeft = MyGame.FirstID.JettonLeft;
			MyID.Money = MyGame.FirstID.Money;
			MyID.Order = 1;
			}
			else if(MyID.ID == MyGame.SecondID.ID)
			{
			MyID.JettonLeft = MyGame.SecondID.JettonLeft;
			MyID.Money = MyGame.SecondID.Money;
			MyID.Order = 2;
			}
			else if(MyID.ID == MyGame.ThirdID.ID)
			{
			MyID.JettonLeft = MyGame.ThirdID.JettonLeft;
			MyID.Money = MyGame.ThirdID.Money;
			MyID.Order = 3;
			}
			else if(MyID.ID == MyGame.FourthID.ID)
			{
			MyID.JettonLeft = MyGame.FourthID.JettonLeft;
			MyID.Money = MyGame.FourthID.Money;
			MyID.Order = 4;
			}
			else if(MyID.ID == MyGame.FifthID.ID)
			{
			MyID.JettonLeft = MyGame.FifthID.JettonLeft;
			MyID.Money = MyGame.FifthID.Money;
			MyID.Order =5;
			}

			return whole;
		}
	}
	if(2==type)//解析盲注消息，消息形式广播
	{
		
		memset(str,0,sizeof(str));
		if((start=strstr(buf,"blind/"))&&(end=strstr(buf,"/blind")))
		{
			whole =3;
			p = start + 8;
			while(*p!=' ')p++;
			p++;
			q = p;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;	
				q++;
			}
			SB = atoi(str);//提取小盲注大小
			memset(str,0,sizeof(str));

			q=q+2;
			if(q==end)
				return whole;
			
			
			while(*q!=' '&&(q<end))q++;
			q++;
			p = q;

			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;	
				q++;
			}
			BB = atoi(str);//提取小盲注大小
			memset(str,0,sizeof(str));
			return whole;
		}
	}			
	if(3 == type)//解析手牌
	{
		memset(str,0,sizeof(str));
		if((start=strstr(buf,"hold/"))&&(end=strstr(buf,"/hold")))
		{
			whole =3;
			p = start + 7;
			q=p;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;	
				q++;
			}
			if(strcmp(str,"SPADES")==0)
			{
				MyCard.Hand[0].Color = 1;//黑桃
			}
			else if(strcmp(str,"HEARTS")==0)
			{
				MyCard.Hand[0].Color = 2;//红心
			}
			else if(strcmp(str,"CLUBS")==0)
			{
				MyCard.Hand[0].Color = 3;//梅花
			}
			else if(strcmp(str,"DIAMONDS")==0)
			{
				MyCard.Hand[0].Color = 4;//方片
			}
			else
			{
				MyCard.Hand[0].Color = 0;
			}
			
			memset(str,0,sizeof(str));
			p = start+7;
			while((*p!=' ')&&(p<end)) p++;
			p=p+1;
			q=p;
			while((*q!=' ')&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			if(strcmp(str,"J")==0)
			{
				MyCard.Hand[0].Point = 11;
			}
			else if(strcmp(str,"Q")==0)
			{
				MyCard.Hand[0].Point = 12;
			}
			else if(strcmp(str,"K")==0)
			{
				MyCard.Hand[0].Point = 13;
			}
			else if(strcmp(str,"A")==0)
			{
				MyCard.Hand[0].Point = 14;
			}
			else
			{
				MyCard.Hand[0].Point = atoi(str);
			}
			
			memset(str,0,sizeof(str));
			q=q+2;
			p=q;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			
			if(strcmp(str,"SPADES")==0)
			{
				MyCard.Hand[1].Color = 1;//黑桃
			}
			else if(strcmp(str,"HEARTS")==0)
			{
				MyCard.Hand[1].Color = 2;//红心
			}
			else if(strcmp(str,"CLUBS")==0)
			{
				MyCard.Hand[1].Color = 3;//梅花
			}
			else if(strcmp(str,"DIAMONDS")==0)
			{
				MyCard.Hand[1].Color = 4;//方片
			}
			else
			{
				MyCard.Hand[1].Color = 0;
			}



			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			if(strcmp(str,"J")==0)
			{
				MyCard.Hand[1].Point = 11;
			}
			else if(strcmp(str,"Q")==0)
			{
				MyCard.Hand[1].Point = 12;
			}
			else if(strcmp(str,"K")==0)
			{
				MyCard.Hand[1].Point = 13;
			}
			else if(strcmp(str,"A")==0)
			{
				MyCard.Hand[1].Point = 14;
			}	
			else
			{
				MyCard.Hand[1].Point = atoi(str);
			}
		}
	return whole;
	}
	if(4 == type)//解析询问消息
	{
		int flag=0;//临时计数
		int OperTemp=0;
		int FoldTemp=0;
		memset(str,0,sizeof(str));
		if((start=strstr(buf,"inquire/"))&&(end=strstr(buf,"total")))
		{
			whole =3;
			MyUpper.OnLine = 1;
			p = start + 10;
	
			q=p;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			MyUpper.ID = atoi(str);
			
			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			MyUpper.JettonLeft = atoi(str);

			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			MyUpper.Money = atoi(str);

			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			MyUpper.Bet = atoi(str);

			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			printf("%s\n",str);
			MyUpper.OperNum++;//操作数加一
			if(strncmp(str,"blind",5) == 0)
			{
				MyUpper.LastAction = 1;//盲注
				MyUpper.RaiseInCeed=0;
			}
			else if(strncmp(str,"check",5) == 0)
			{
				MyUpper.RaiseInCeed=0;
				MyUpper.LastAction = 2;//让牌
			}
			else if(strncmp(str,"call",4) == 0)
			{
				MyUpper.RaiseInCeed=0;
				MyUpper.LastAction = 3;//跟注
			}
			else if(strncmp(str,"raise"),5 == 0)
			{
				if(MyUpper.LastAction == 4)
					MyUpper.RaiseInCeed++;
				else
					MyUpper.RaiseInCeed=1;
				MyUpper.LastAction = 4;//加注
			}
			else if(strncmp(str,"all_in",6) == 0)
			{
				MyUpper.RaiseInCeed=0;
				MyUpper.LastAction = 5;//全压
				MyUpper.OnLine = 2;//表示敢玩家已全压
			}
			else if(strncmp(str,"fold",4) == 0)
			{
				MyUpper.RaiseInCeed=0;
				MyUpper.LastAction = 6;//弃牌
				MyUpper.FoldNum++;//弃牌操作加1
				MyUpper.OnLine = 0;//表示该玩家已掉线
			}
			
			if(MyGame.SBlindID.ID==MyUpper.ID)
			{
				MyGame.SBlindID=MyUpper;
			}
			else if(MyGame.BBlindID.ID==MyUpper.ID)
			{
				MyGame.BBlindID=MyUpper;	
			}
			else if(MyGame.FirstID.ID==MyUpper.ID)
			{
				MyGame.FirstID=MyUpper;	
			}
			else if(MyGame.SecondID.ID==MyUpper.ID)
			{
				MyGame.SecondID=MyUpper;
			}	
			else if(MyGame.ThirdID.ID==MyUpper.ID)
			{
				MyGame.ThirdID=MyUpper;	
			}
			else if(MyGame.FourthID.ID==MyUpper.ID)
			{
				MyGame.FourthID=MyUpper;
			}	
			else if(MyGame.FifthID.ID==MyUpper.ID)
			{
				MyGame.FifthID=MyUpper;	
			}
			else if(MyGame.ButtonID.ID==MyUpper.ID)
			{
				MyGame.ButtonID=MyUpper;
			}
				

			q=q+2;//换到下一行
			while(q<end)//还未到码池信息行，就继续解析操作消息
			{
			TempID.OnLine = 1;
			p=q;
			memset(str,0,sizeof(str));		
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			TempID.ID = atoi(str);
			
			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			TempID.JettonLeft = atoi(str);

			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			TempID.Money = atoi(str);

			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			TempID.Bet = atoi(str);

			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			printf("%s\n",str);
			if(strcmp(str,"blind") == 0)
			{
				TempID.LastAction = 1;//盲注
			}
			else if(strcmp(str,"check") == 0)
			{
				TempID.LastAction = 2;//让牌
			}
			else if(strcmp(str,"call") == 0)
			{
				TempID.LastAction = 3;//跟注
			}
			else if(strcmp(str,"raise") == 0)
			{
				TempID.LastAction = 4;//加注
			}
			else if(strcmp(str,"all_in") == 0)
			{
				TempID.LastAction = 5;//全压
				TempID.OnLine = 2;//表示玩家全压
			}
			else if(strcmp(str,"fold") == 0)
			{
				TempID.LastAction = 6;//弃牌
				TempID.OnLine = 0;
			}
			int LastAct=0;	
			int LastRaiseInCeed = 0;
			if(MyGame.SBlindID.ID==TempID.ID)
			{
				LastAct = MyGame.SBlindID.LastAction;
				LastRaiseInCeed = MyGame.SBlindID.RaiseInCeed;
				MyGame.SBlindID=TempID;
				if((LastAct==4)&&(MyGame.SBlindID.LastAction==4))
				{
					MyGame.SBlindID.RaiseInCeed=LastRaiseInCeed+1;
				}
				else
				{
					
					MyGame.SBlindID.RaiseInCeed=0;
				}
				
			}
			else if(MyGame.BBlindID.ID==TempID.ID)
			{
				LastAct = MyGame.BBlindID.LastAction;
				LastRaiseInCeed = MyGame.BBlindID.RaiseInCeed;
				MyGame.BBlindID=TempID;
				if((LastAct==4)&&(MyGame.BBlindID.LastAction==4))
				{
					MyGame.BBlindID.RaiseInCeed = LastRaiseInCeed+1;
				}
				else
				{
					
					MyGame.BBlindID.RaiseInCeed=0;
				}
			}
			else if(MyGame.FirstID.ID==TempID.ID)
			{
				LastAct = MyGame.FirstID.LastAction;
				LastRaiseInCeed = MyGame.FirstID.RaiseInCeed;
				MyGame.FirstID=TempID;
				if((LastAct==4)&&(MyGame.FirstID.LastAction==4))
				{
					MyGame.FirstID.RaiseInCeed=LastRaiseInCeed+1;
				}
				else
				{
					
					MyGame.FirstID.RaiseInCeed=0;
				}
			}
			else if(MyGame.SecondID.ID==TempID.ID)
			{
				LastAct = MyGame.SecondID.LastAction;
				LastRaiseInCeed = MyGame.SecondID.RaiseInCeed;
				MyGame.SecondID=TempID;
				if((LastAct==4)&&(MyGame.SecondID.LastAction==4))
				{
					MyGame.SecondID.RaiseInCeed=LastRaiseInCeed+1;
				}
				else
				{
					
					MyGame.SecondID.RaiseInCeed=0;
				}
			}
			else if(MyGame.ThirdID.ID==TempID.ID)
			{
				LastAct = MyGame.ThirdID.LastAction;
				LastRaiseInCeed = MyGame.ThirdID.RaiseInCeed;
				MyGame.ThirdID=TempID;
				if((LastAct==4)&&(MyGame.ThirdID.LastAction==4))
				{
					MyGame.ThirdID.RaiseInCeed=LastRaiseInCeed+1;
				}
				else
				{
					
					MyGame.ThirdID.RaiseInCeed=0;
				}
			}
			else if(MyGame.FourthID.ID==TempID.ID)
			{
				LastAct = MyGame.FourthID.LastAction;
				LastRaiseInCeed = MyGame.FourthID.RaiseInCeed;
				MyGame.BBlindID=TempID;
				if((LastAct==4)&&(MyGame.FourthID.LastAction==4))
				{
					MyGame.FourthID.RaiseInCeed = LastRaiseInCeed+1;
				}
				else
				{
					
					MyGame.FourthID.RaiseInCeed=0;
				}
			}
			else if(MyGame.FifthID.ID==TempID.ID)
			{
				LastAct = MyGame.FifthID.LastAction;
				LastRaiseInCeed = MyGame.FifthID.RaiseInCeed;
				MyGame.BBlindID=TempID;
				if((LastAct==4)&&(MyGame.FifthID.LastAction==4))
				{
					MyGame.FifthID.RaiseInCeed=LastRaiseInCeed+1;
				}
				else
				{
					
					MyGame.FifthID.RaiseInCeed=0;
				}
			}	
			else if(MyGame.ButtonID.ID==TempID.ID)
			{
				LastAct = MyGame.ButtonID.LastAction;
				LastRaiseInCeed = MyGame.ButtonID.RaiseInCeed;
				MyGame.ButtonID=TempID;
				if((LastAct==4)&&(MyGame.ButtonID.LastAction==4))
				{
					MyGame.ButtonID.RaiseInCeed = LastRaiseInCeed + 1;
				}
				else
				{
					
					MyGame.ButtonID.RaiseInCeed=0;
				}
			}
				
			TempID.OperNum=0;
			TempID.FoldNum=0;

			if(MyID.ID==TempID.ID)
				MyID=TempID;
			else if(MyID.ID==TempID.ID)
				MyID=TempID;	
			else if(MyID.ID==TempID.ID)
				MyID=TempID;	
			else if(MyID.ID==TempID.ID)
				MyID=TempID;	
			else if(MyID.ID==TempID.ID)
				MyID=TempID;	
			else if(MyID.ID==TempID.ID)
				MyID=TempID;	
			else if(MyID.ID==TempID.ID)
				MyID=TempID;	
			else if(MyID.ID==TempID.ID)
				MyID=TempID;
			q=q+2;//换到下一行
					
			}	
			p=end+11;
			q=p;
			memset(str,0,sizeof(str));	
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			MyGame.Pot = atoi(str);//更新池底信息
			memset(str,0,sizeof(str));
			
		}	
		return whole;
	}
	if(5 == type)//解析公牌消息
	{
		whole=3;	
		memset(str,0,sizeof(str));
		if((start=strstr(buf,"flop/"))&&(end=strstr(buf,"/flop")))
		{
			p = start + 7;
			q=p;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;	
				q++;
			}
			
			if(strcmp(str,"SPADES")==0)
			{
				MyCard.Flop[0].Color = 1;//黑桃
			}
			else if(strcmp(str,"HEARTS")==0)
			{
				MyCard.Flop[0].Color = 2;//红心
			}
			else if(strcmp(str,"CLUBS")==0)
			{
				MyCard.Flop[0].Color = 3;//梅花
			}
			else if(strcmp(str,"DIAMONDS")==0)
			{
				MyCard.Flop[0].Color = 4;//方片
			}
			else
			{
				MyCard.Flop[0].Color = 0;
			}
			
			memset(str,0,sizeof(str));
			p = start+7;
			while((*p!=' ')&&(p<end)) p++;
			p=p+1;
			q=p;
			while((*q!=' ')&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			if(strcmp(str,"J")==0)
			{
				MyCard.Flop[0].Point = 11;
			}
			else if(strcmp(str,"Q")==0)
			{
				MyCard.Flop[0].Point = 12;
			}
			else if(strcmp(str,"K")==0)
			{
				MyCard.Flop[0].Point = 13;
			}
			else if(strcmp(str,"A")==0)
			{
				MyCard.Flop[0].Point = 14;
			}
			else
			{
				MyCard.Flop[0].Point = atoi(str);
			}

			memset(str,0,sizeof(str));
			q=q+2;
			p=q;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			
			if(strcmp(str,"SPADES")==0)
			{
				MyCard.Flop[1].Color = 1;//黑桃
			}
			else if(strcmp(str,"HEARTS")==0)
			{
				MyCard.Flop[1].Color = 2;//红心
			}
			else if(strcmp(str,"CLUBS")==0)
			{
				MyCard.Flop[1].Color = 3;//梅花
			}
			else if(strcmp(str,"DIAMONDS")==0)
			{
				MyCard.Flop[1].Color = 4;//方片
			}
			else
			{
				MyCard.Flop[1].Color = 0;
			}



			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			if(strcmp(str,"J")==0)
			{
				MyCard.Flop[1].Point = 11;
			}
			else if(strcmp(str,"Q")==0)
			{
				MyCard.Flop[1].Point = 12;
			}
			else if(strcmp(str,"K")==0)
			{
				MyCard.Flop[1].Point = 13;
			}
			else if(strcmp(str,"A")==0)
			{
				MyCard.Flop[1].Point = 14;
			}	
			else
			{
				MyCard.Flop[1].Point = atoi(str);
			}

			memset(str,0,sizeof(str));
			q=q+2;
			p=q;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			
			if(strcmp(str,"SPADES")==0)
			{
				MyCard.Flop[2].Color = 1;//黑桃
			}
			else if(strcmp(str,"HEARTS")==0)
			{
				MyCard.Flop[2].Color = 2;//红心
			}
			else if(strcmp(str,"CLUBS")==0)
			{
				MyCard.Flop[2].Color = 3;//梅花
			}
			else if(strcmp(str,"DIAMONDS")==0)
			{
				MyCard.Flop[2].Color = 4;//方片
			}
			else
			{
				MyCard.Flop[2].Color = 0;
			}



			memset(str,0,sizeof(str));
			q=q+1;
			p=q;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			if(strcmp(str,"J")==0)
			{
				MyCard.Flop[2].Point = 11;
			}
			else if(strcmp(str,"Q")==0)
			{
				MyCard.Flop[2].Point = 12;
			}
			else if(strcmp(str,"K")==0)
			{
				MyCard.Flop[2].Point = 13;
			}
			else if(strcmp(str,"A")==0)
			{
				MyCard.Flop[2].Point = 14;
			}	
			else
			{
				MyCard.Flop[2].Point = atoi(str);
			}
		}	
	}
	if(6 == type)//解析转牌消息
	{
	
		whole=3;	

		memset(str,0,sizeof(str));
		if((start=strstr(buf,"turn/"))&&(end=strstr(buf,"/turn")))
		{
			p = start + 7;
			q=p;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;	
				q++;
			}
			
			if(strcmp(str,"SPADES")==0)
			{
				MyCard.Turn.Color = 1;//黑桃
			}
			else if(strcmp(str,"HEARTS")==0)
			{
				MyCard.Turn.Color = 2;//红心
			}
			else if(strcmp(str,"CLUBS")==0)
			{
				MyCard.Turn.Color = 3;//梅花
			}
			else if(strcmp(str,"DIAMONDS")==0)
			{
				MyCard.Turn.Color = 4;//方片
			}
			else
			{
				MyCard.Turn.Color = 0;
			}
			
			memset(str,0,sizeof(str));
			p = start+7;
			while((*p!=' ')&&(p<end)) p++;
			p=p+1;
			q=p;
			while((*q!=' ')&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			if(strcmp(str,"J")==0)
			{
				MyCard.Turn.Point = 11;
			}
			else if(strcmp(str,"Q")==0)
			{
				MyCard.Turn.Point = 12;
			}
			else if(strcmp(str,"K")==0)
			{
				MyCard.Turn.Point = 13;
			}
			else if(strcmp(str,"A")==0)
			{
				MyCard.Turn.Point = 14;
			}
			else
			{
				MyCard.Turn.Point = atoi(str);
			}
		}
	}
	if(7 == type)//解析河牌消息
	{
		whole=3;	

		memset(str,0,sizeof(str));
		if((start=strstr(buf,"river/"))&&(end=strstr(buf,"/river")))
		{
			p = start + 8;
			q=p;
			while(*q!=' '&&(q<end))
			{
				str[q-p] = *q;	
				q++;
			}
			
			if(strcmp(str,"SPADES")==0)
			{
				MyCard.River.Color = 1;//黑桃
			}
			else if(strcmp(str,"HEARTS")==0)
			{
				MyCard.River.Color = 2;//红心
			}
			else if(strcmp(str,"CLUBS")==0)
			{
				MyCard.River.Color = 3;//梅花
			}
			else if(strcmp(str,"DIAMONDS")==0)
			{
				MyCard.River.Color = 4;//方片
			}
			else
			{
				MyCard.River.Color = 0;
			}
			
			memset(str,0,sizeof(str));
			p = start+8;
			while((*p!=' ')&&(p<end)) p++;
			p=p+1;
			q=p;
			while((*q!=' ')&&(q<end))
			{
				str[q-p] = *q;
				q++;
			}
			if(strcmp(str,"J")==0)
			{
				MyCard.River.Point = 11;
			}
			else if(strcmp(str,"Q")==0)
			{
				MyCard.River.Point = 12;
			}
			else if(strcmp(str,"K")==0)
			{
				MyCard.River.Point = 13;
			}
			else if(strcmp(str,"A")==0)
			{
				MyCard.River.Point = 14;
			}
			else
			{
				MyCard.River.Point = atoi(str);
			}
		}
	
	}
	if(8 == type)//解析摊牌消息
	{
		whole=3;	

	}
	if(9 == type)//解析彩池分配消息
	{
		char IDStr[10];
		memset(IDStr,0,sizeof(IDStr));
		sprintf(IDStr,"%d",MyID.ID);
		printf("IDStr is %s\n",IDStr);
		memset(str,0,sizeof(str));
		if((start=strstr(buf,"pot-win/"))&&(end=strstr(buf,"/pot-win")))
		{
			whole=3;
			printf("end - start is %d\n",(end-start));
			if((end-start)<=10)
				return whole;
			p=strstr(buf,IDStr);
			if(p==NULL) 
				return whole;
			p=p+strlen(IDStr)+2;
			q=p;
			while(*q!=' '&&(*q!='\n'))
			{
				str[q-p] = *q;
				q++;
			}
			MyID.JettonLeft-=atoi(str);
			memset(str,0,sizeof(str));
		}
		return whole;
		
	}
	return whole;
}



int MsgPeek(int type)//TCP嗅探函数，其作用是嗅探出TCP缓冲区中我们所需要包的长度,type表示要嗅探的消息类型，1座次消息，2盲注消息，3手牌消息，依次类推。函数返回从TCP缓冲区中取出的长度，可用于实际的读数据
{
	char buf[BUFFSIZE];
	char *begin,*last;
	int ReadLen=0;
	memset(buf,0,sizeof(buf));	
	recv(client_sockfd,buf,sizeof(buf),MSG_PEEK);//MSG_PEEK为接收试探，并不将数据从缓冲区挪走
	switch(type)//判断要嗅探的类型
	{
	case 1://座次消息
	begin = strstr(buf,"seat/");
	last = strstr(buf,"/seat");
	ReadLen = last + 6 - begin +1;		
	break;

	case 2://盲注消息	
	begin = strstr(buf,"blind/");
	last = strstr(buf,"/blind");
	ReadLen = last + 7 - begin +1;		
	break;
	
	case 3://手牌消息
	begin = strstr(buf,"hold/");
	last = strstr(buf,"/hold");
	ReadLen = last + 6 - begin +1;
	break;

	case 4://询问消息
	begin = strstr(buf,"inquire/");
	last = strstr(buf,"/inquire");
	ReadLen = last + 9 - begin +1;
	break;
	default:break;
	}
	
	memset(buf,0,sizeof(buf));
	return ReadLen;
}

int Peek(int* len)//探测消息类型函数，返回值表示消息类型，1表示结束消息，2表示座次消息，3表示手牌消息，4表示询问消息，5表示公牌消息，6表示转牌消息，7表示河牌消息，8表示摊牌消息，9表示彩池分配消息,10表示盲注消息
{
	char buf[BUFFSIZE];
	char *begin,*last;
	memset(buf,0,sizeof(buf));	
	recv(client_sockfd,buf,sizeof(buf),MSG_PEEK);//MSG_PEEK为接收试探，并不将数据从缓冲区挪走
	
	if(strncmp(buf,"game-over/",10)==0)//比较前面10个字符判断是否有游戏结束消息	
	{
		*len = 12;//游戏结束消息的长度
		return 1;
	}
	else if(strncmp(buf,"seat/",5)==0)//座次消息
	{
		begin = strstr(buf,"seat/");
		last = strstr(buf,"/seat");
		*len = last + 6 - begin +1;		
		return 2;
	}
	else if(strncmp(buf,"hold/",5)==0)//手牌消息
	{
		begin = strstr(buf,"hold/");
		last = strstr(buf,"/hold");
		*len = last + 6 - begin +1;
		return 3;
	}
	else if(strncmp(buf,"inquire/",8)==0)//询问消息
	{
		begin = strstr(buf,"inquire/");
		last = strstr(buf,"/inquire");
		*len = last + 9 - begin +1;
		return 4;
	}
	else if(strncmp(buf,"flop/",5)==0)//公牌消息
	{
		begin = strstr(buf,"flop/");
		last = strstr(buf,"/flop");
		*len = last + 6 - begin +1;
		return 5;
	}
	else if(strncmp(buf,"turn/",5)==0)//转牌消息
	{
		begin = strstr(buf,"turn/");
		last = strstr(buf,"/turn");
		*len = last + 6 - begin +1;
		return 6;
	}
	else if(strncmp(buf,"river/",6)==0)//河牌消息
	{
		begin = strstr(buf,"river/");
		last = strstr(buf,"/river");
		*len = last + 7 - begin +1;
		return 7;
	}
	else if(strncmp(buf,"showdown/",9)==0)//摊牌消息
	{
		begin = strstr(buf,"showdown/");
		last = strstr(buf,"/showdown");
		*len = last + 10 - begin +1;
		return 8;
	}
	else if(strncmp(buf,"pot-win/",8)==0)//彩池分配消息
	{
		begin = strstr(buf,"pot-win/");
		last = strstr(buf,"/pot-win");
		*len = last + 9 - begin +1;
		return 9;
	}
	else if(strncmp(buf,"blind/",6)==0)//彩池分配消息
	{
		begin = strstr(buf,"blind/");
		last = strstr(buf,"/blind");
		*len = last + 7 - begin +1;
		return 10;
	}
}

int GetOnLinePlayers(void)//获得未弃牌玩家数
{
	int Players=0;
	if(MyGame.ButtonID.OnLine)
		Players++;
	if(MyGame.SBlindID.OnLine)
		Players++;

	if(MyGame.BBlindID.OnLine)
		Players++;
	if(MyGame.FirstID.OnLine)
		Players++;
	if(MyGame.SecondID.OnLine)
		Players++;
	if(MyGame.ThirdID.OnLine)
		Players++;
	if(MyGame.FourthID.OnLine)
		Players++;
	if(MyGame.FifthID.OnLine)
		Players++;
	return Players;
}
