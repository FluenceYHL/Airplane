#include "common_sys.h"
#include "General_Data.h"
#include "gereral_Data_variable.h"

#include "All_graph.h"
#include "Make_cartoon.h"
#include "Get_mouse.h"

#include "Cartoon.h"
extern char entry_type;

void Cartoon(buffer *Buffer_list)
{
	for( ;is_run();delay_fps(60))
	{
		while(kbhit())
		{
			char ch = getch();
		}
		
		cleardevice();
		fps ++;
		
		setcolor(BLUE);setbkmode(TRANSPARENT);
		char a[100],str[32];
		memset(a,0,100);	memset(str,0,32);
		int x,y;
		mousepos(&x,&y);  //获取鼠标坐标 
		sprintf(str,"%4d %4d",x,y);
		outtextxy(850,540,str);
		
		mouse_msg mouse = {0}; 
		while(mousemsg())   //直到获取鼠标信息 
		{
			mouse = getmouse();
		}
		if((int)mouse.is_down()&&(int)mouse.is_left())   //&&(int)mouse.is_up()
		{
			Search_mouse(x,y);
		}
		
		init_All();   //重画一次，关键是 安检口状态（后期再处理）,还有蛇形区域 
		
		if(entry_type!='Q' && entry_type!='q')
		    Check_Buffer();
		
		if(entry_type!='Q' && entry_type!='q')
		{
		    Update_Ball();
		}
		
		//Draw_Ball();
		
		if((entry_type=='Q'||entry_type=='q'))
		{
			Go_to_hotel();   //剩余的乘客去 旅馆 
		}
		
		Draw_Buffer();
		
		Draw_Windows();
		
		Draw_Emergency();
	}
} 
