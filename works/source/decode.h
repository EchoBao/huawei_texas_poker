//decode.c头文件，声明函数

int DecodeFrame(const char* buf,int type);//解析包函数，type表示包的类型，1表示解析座次消息
int MsgPeek(int type);//TCP嗅探函数，其作用是嗅探出TCP缓冲区中我们所需要包的长度,type表示要嗅探的消息类型，1座次消息，2盲注消息，3手牌消息，依次类推。函数返回从TCP缓冲区中取出的长度，可用于实际的读数据
int Peek(int* len);//探测消息类型函数，返回值表示消息类型，1表示结束消息，2表示座次消息，3表示手牌消息，4表示询问消息，5表示公牌消息，6表示转牌消息，7表示河牌消息，8表示摊牌消息，9表示彩池分配消息
int GetOnLinePlayers(void);//获得未弃牌玩家数
