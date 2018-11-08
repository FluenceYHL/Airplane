#include "common_sys.h"
#include "General_Data.h"
#include "Get_input.h"
#include "Control.h"
extern int entry_type;
extern window *WINDOW;
extern buffer *Buffer_list;
extern int OFFWORK;
extern int initID;
extern int entry_randtime;
extern int MaxCustSingleLine;
extern int MaxLines;
extern clock_t end;
extern clock_t start;

int On_Quit_Button(int x,int y)
{
	return (x>=50&&x<=180&&y<=70&&y>=30)?1:0;
}

int On_Rest_Button(int ID,int x,int y)
{
	return ((x-(60+(ID-1)*90))*(x-(60+(ID-1)*90))+(y-125)*(y-125))<=625?1:0;
}

int On_Add_Button(int x,int y)
{
	return (x>=10&&x<=120&&y<=660&&y>=620)?1:0;
}

void Mouse_add_passager(buffer *head,int count) //在缓冲区末尾添加新乘客
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file    Add_passager\n'");OFFWORK = 0;
	 }
	buffer *ptr = head;
	while(ptr->next)
	{
		ptr = ptr->next;//遍历到队尾 
	}
	count = (count+lenth(Buffer_list)<=MaxCustSingleLine*MaxLines)?count:MaxCustSingleLine*MaxLines-lenth(Buffer_list);
	int d = 0 ;
	while(count--)
	{
		buffer *new_one = (buffer*)malloc(sizeof(buffer));
		new_one->ID = initID ;
	    new_one->Mouse_add = 1;
	    new_one->x = 140-40*d ;
		printf("  x   =   %d\n",new_one->x);
			d++ ;
		new_one->y = 640;
		new_one->dx = 0;
		new_one->dy = 0;
		new_one->next = NULL ;
		int stock=rand()%300;
		if(stock%20==0) //如果低概率下，仍然紧急，就直接放入紧急通道 ，安检 
		{
			new_one->In_Emergency = 1 ;
			Add_emergency(new_one->ID);
		}
		else
		{
			printf("%d 号新乘客进入排队缓冲区\n",initID);
		    fprintf(fp,"\n%d 号新乘客进入排队缓冲区\n",initID);
			new_one->In_Emergency=0;
		    ptr->next = new_one;
		    ptr = new_one;
		}
		initID++;
	}
	ptr->next=NULL;  
	fclose(fp);
}

void Search_mouse(int x,int y)
{
	if(On_Quit_Button(x,y))
	{
		entry_type = 'Q' ;
	}
	if(On_Add_Button(x,y))
	{
		Mouse_add_passager(Buffer_list,trypossion());
	}
	window *ptr = WINDOW ;
	while(ptr->Next)
	{
		if(On_Rest_Button(ptr->Next->ID,x,y))
		{
			ptr->Next->Rest_Times++;
			if(ptr->Next->Rest_Times%2==0)
			{
				if(Lenth(ptr->Next->Queue)==0)
				{
					ptr->Next->state = 0 ;   //注意时间只能加一次......注意状态会转变，所以只会加一次
				}
				else if((end-start)/CLOCKS_PER_SEC==ptr->Next->Current)
				{
					ptr->Next->state = 2 ;
				}
				else{
					ptr->Next->state = 1 ;
				}
			}
			else if(ptr->Next->Rest_Times%2==1)
			{
				ptr->Next->state = 3 ;
				printf("%d 号安检口休息\n",ptr->Next->ID);
				entry_randtime = 25+rand()%10 ;
				ptr->Next->Rest_Len += entry_randtime ;
		        ptr->Next->Begin_rest = entry_randtime ;
			}
		}
		ptr = ptr->Next ;
	}
}

