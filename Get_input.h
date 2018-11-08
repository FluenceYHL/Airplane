// 输入方面

#include "common_sys.h"
#include "General_Data.h"

#ifndef GET_INPUT_H
#define GET_INPUT_H

char Get_type(); //获取事件类型 

int trypossion(); //泊松分布模拟随机到达人数

int possion();

double U_Random();  //u是一个小于1的随机的数


void Get_entry();  //获取一个事件

void Get_input(buffer *Buffer_list);

#endif
