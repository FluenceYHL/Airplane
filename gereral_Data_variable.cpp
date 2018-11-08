#include "General_Data.h"
//#include "gereral_Data_variable.h"

#ifndef GENERAL_DATA_VAROABLE_C
#define GENERAL_DATA_VAROABLE_C

HANDLE hMutex;
int fps;
int Get_input_OK;

int Go_hotel;

int i;
int OFFWORK;//如果没有下班就一直运行，收到下班指令后置为0，停止运行
char Operation_pattern; //操作模式，手动或者文件
char window_pattern; //安检口分配模式

int Passager_NO;
int initID;     //整个系统的 乘客编号 从1 开始递推
clock_t start , end , interval ,Pre_interval; //时间变量
int CurMaxWindow;   //全局变量 当前最大编号仍在服务的 安检口
int entry_NO;  //事件序号，全局变量

char entry_type;     // 事件类型
int entry_sec;       // 事件间隔
int entry_mans;      // 乘客人数
int entry_check;     // 休息的安检口
int entry_randtime;  //休息时间

int Passager_flow;
int StartWork;   //线程控制开始
int Signal;      //同步锁
int Entry_OK;    //输入完毕
int Rest_OK;     //休息事件完毕
int OK;          //控制一次输出中的 往缓冲区加人单次操作
int time_OK;     //控制休息 update_window 单次操作
int Destroy_OK;  //控制只有一次销毁链表
int SIGN;        //循环标志，观察下班后是否所有乘客都安检结束
int Print_cycle; //控制输出周期

int MaxCheck;                 //最多的安检口数量
int MinCheck;                 //最少的安检口数量
int MaxCustSingleLine;	 	  //缓冲区最大人数
int MaxLines;
int MaxSeqLen;                //增开安检口的标志
int EasySeqLen;	              //关闭安检口的标志
int MaxCustCheck;   	      //安检口队伍上限
int MaxSec;


buffer *Buffer_list;
window *WINDOW;
emergency *Emergency_window;
Window_Graph Window_graph[100];


int Draw_Entry_Once;  //控制只初始化球一次，初始化球的位置 
int Speed;    //修改速度 .....目前能修改的值 1 2 5 10 20 
int sub[30];




#endif
