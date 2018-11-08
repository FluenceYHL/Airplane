
#ifndef GENERAL_DATA_VARIABLE_H
#define GENERAL_DATA_VARIABLE_H
extern int i;
extern int OFFWORK;//如果没有下班就一直运行，收到下班指令后置为0，停止运行
extern char Operation_pattern; //操作模式，手动或者文件
extern char window_pattern; //安检口分配模式

extern int initID;     //整个系统的 乘客编号 从1 开始递推
extern clock_t start , end , interval ,Pre_interval; //时间变量
extern int CurMaxWindow;   //全局变量 当前最大编号仍在服务的 安检口
extern int entry_NO;  //事件序号，全局变量

extern char entry_type;     // 事件类型
extern int entry_sec;       // 事件间隔
extern int entry_mans;      // 乘客人数
extern int entry_check;     // 休息的安检口
extern int entry_randtime;  //休息时间

extern int Passager_flow;
extern int StartWork;   //线程控制开始
extern int Signal;      //同步锁
extern int Entry_OK;    //输入完毕
extern int Rest_OK;     //休息事件完毕
extern int OK;          //控制一次输出中的 往缓冲区加人单次操作
extern int time_OK;     //控制休息 update_window 单次操作
extern int Destroy_OK;  //控制只有一次销毁链表
extern int SIGN;        //循环标志，观察下班后是否所有乘客都安检结束
extern int Print_cycle; //控制输出周期


extern int MaxCheck;                 //最多的安检口数量
extern int MinCheck;                 //最少的安检口数量
extern int MaxCustSingleLine;	 	  //缓冲区最大人数
extern int MaxLines;
extern int MaxSeqLen;                //增开安检口的标志
extern int EasySeqLen;	              //关闭安检口的标志
extern int MaxCustCheck;   	      //安检口队伍上限
extern int MaxSec;


extern buffer *Buffer_list;
extern window *WINDOW;
extern emergency *Emergency_window;
extern Window_Graph Window_graph[100];


extern int Draw_Entry_Once;  //控制只初始化球一次，初始化球的位置 
extern int Speed;    //修改速度 .....目前能修改的值 1 2 5 10 20 

extern HANDLE hMutex;
extern int fps;


extern int Go_hotel;
extern int sub[30];


#endif
