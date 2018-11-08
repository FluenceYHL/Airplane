#include "common_sys.h"
#ifndef GENERAL_DATE_H
#define GENERAL_DATE_H


typedef struct window_graph{
	PIMAGE picture;       //安检口的图 
	int Cur_people;   //安检口目前的人数 
	int During_Rest;  //安检口是否在休息 
}Window_Graph;
 
struct output_window{   //输出文件格式
    int window_ID;                    //安检口编号
	char duty;                        //安检口是否关闭
	int ServeLen;                     //安检口的服务时长
	int PlanLen;                      //安检口的计划服务时长
	int RestLen;                      //安检口的休息时长
	int WinListCustCount;             //安检口队伍的长度
	int a[10];                        //安检口队伍的乘客编号
};

typedef struct Branch{   //安检口队伍
	int NO;                       //安检口乘客的号码
	int CheckTime;                //乘客安检的时间
	int CheckOver;                //乘客是否安检完毕 1-安检完了 0-还没安检完
	struct Branch *next;          //安检口队伍的下一个乘客
	
	int Reach_Emergency;   //判断是否到了缓冲区 
	int x,y;               //紧急通道乘客 的 坐标,如果是在安检，就 判断 再删除，再显示 
	int dx,dy ;            //移动方向 
	int which_NO ;        //去哪个安检口 
}branch;

typedef struct Window{   //安检口
	int ID;                          //安检口的编号
	int EverOpen;                    //安检口是否曾经开过，再增开一个安检口时，需要考虑
	int Current;                     //安检口开始安检的当前时间
	int state;                       //安检口目前的状态
	int Begin_rest;                  //安检口开始休息的倒计时时钟
	int Rest_Len;                    //安检口的休息时长
	int ServeLen;                    //安检口的服务时长
	int In_repair;
	PIMAGE picture;
	int Rest_Times;
	branch *Queue;                   //每个安检口 的队伍
	struct Window *Next;             //下一个安检口
}window;

typedef struct Buffer{   //缓冲区队伍
	int ID;                         //缓冲区乘客的编号
	int In_Emergency; 
	struct Buffer *next;            //下一个乘客
	
	int x,y;
	int dx,dy;
	int Mouse_add;
}buffer;

typedef struct Emergency{
	int Current;                     //开始安检的当前时间
	int state;                       //目前的状态           
	int ServeLen;                    //服务时长
	branch *Queue;   
}emergency;


typedef struct Entry{
	int NO;           //事情序号
	int sec;          //事情时间间隔
	char type;        //事件类型  C—乘客到达  R—安检口申请暂停 Q—下班
	int mans;         //新来的乘客数量
	int check;        //申请休息的安检口编号
	int randtime;     //休息时长
}entry;

typedef struct Equip{  //配置文件格式 
	char a[30];
	char b[30];
	char c[30];
	char d[30];
	char e[30];
	char f[30];
	char g[30];
	char h[30];
}equip;


#endif

