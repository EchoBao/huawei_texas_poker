int CalCurrentPrice(void);
int IsAbleCheck(void);
int IsAbleCall(void);
int IsAbleRaise(void);
int IsAbleAllIn(void);
int MakeDecision(void);
int CheckPoint(int point1,int point2);//检查手牌是否点数为point1和point2,如果是返回1，不是返回0
int CalPower(void);
int CardOrder(int CardNum);//将牌按点数从大到小排列，CardNum=5排列后的结果存入FlopInOrder[5]数组，=6结果存入TurnInOrder,=7结果存入RiverInOrder
int AnalyCard(int CardNum);//分析牌型，获得最大点数连续张数，最大同花张数，最大点数相同张数，最大对数，CardNum是牌的张数，公牌阶段为5，转牌阶段为6，河牌阶段为7
int InitOrder(int CardNum);//排序之前的初始化
int GetMaxCeed(int CardNum);//获取最大点数连续张数

int GetMaxSamePoint(int CardNum);//获取对大点数相同张数

int GetMaxSameColor(int CardNum);//获取颜色相同的最大张数

int GetMaxPair(int CardNum);//获取最大对数，有且仅有两张

float CalPotPos(int GameStatus);

float CalWinPos(int GameStatus);

int SurrivePlay(void);
