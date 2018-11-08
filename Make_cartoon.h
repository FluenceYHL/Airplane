#include "common_sys.h"
#include "General_Data.h"
#include "gereral_Data_variable.h"
#ifndef MAKE_CARTOON_H
#define MAKE_CARTOON_H

void Read();     //读取配置信息文件的函数 

void init_background();

int On_which_left(int NO,int x,int y);

int On_which_right(int NO,int x,int y);

int On_end(int x,int y);

int On_A(int x,int y);

int On_B(int x,int y);

void init_change();

void Choose_Pattern();

void init_choose();

void Check_Buffer();

void Draw_Emergency();

void Draw_Windows();

void Draw_Buffer();

void Draw_Ball();

void Init_Passager();

void Update_Ball();

void Go_from_four();

void Go_from_three();

void Go_freom_two();

void Go_from_one();

void Go_to_hotel();

#endif
