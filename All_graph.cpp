
#include "All_graph.h"
#include "common_sys.h"
#include "gereral_Data_variable.h"
#include "General_Data.h"
#include "Control.h"
#include "Get_input.h"
void init_title()   //初始化标题 
{
	setfillcolor(EGERGB(242,156,177));
	bar(240,30,720,70);                     
	setcolor(WHITE);
	setfontbkcolor(EGERGB(0x80,0x00,0x80));//设置文字背景色 
	setfont(20,0,"宋体");                  //选择文字，（高度 宽度 字体） 
	setbkmode(TRANSPARENT);   
	outtextxy(320,40,"机场安检口系统");
	setfont(30,0,"宋体");
	setcolor(WHITE);
	end = clock();
	outtextxy(480,35,"Time:     ");
	int  total=(end-start)/CLOCKS_PER_SEC;
	int num1=total/60;
	int num2=total%60;
	char a[32];
	char b[32];
	sprintf(a,"%d",num1);
	sprintf(b,"%d",num2);
	if(num1<10)
	{
		outtextxy(567,35,"0");
	    outtextxy(580,35,a);
	}
	else 
	{
		outtextxy(580,35,a);
	}
	outtextxy(590,35,":");
	if(num2>=10)
	  outtextxy(600,35,b);
	else
	{
		outtextxy(600,35,"0");
		outtextxy(613,35,b);
	}
}



void init_window()   //初始化安检口 
{ 
    int j;
	for(j=1;j<=MaxCheck;j++)
	{
		Window_graph[j].picture=newimage();
		Window_graph[j].Cur_people = 0;
		Window_graph[j].During_Rest=0;
		getimage(Window_graph[j].picture,"window.jpg");
		setfillcolor(YELLOW);
		bar(30+(j-1)*90,150,90*(j),190); 
		setcolor(BLACK);
	    setbkmode(TRANSPARENT); 
	    setfont(16,0,"宋体");
	    char a[10];
	    memset(a,0,9);
	    sprintf(a,"%d",j);
		outtextxy(53+90*(j-1),162,a);
	}
    for(j=1;j<=MaxCheck;j++)
    {
    	putimage(30+(j-1)*90,150,Window_graph[j].picture);    //安检口尺寸 50 X 50 左右 
	}
	for(j=1;j<=MaxCheck;j++)
	{
		delimage(Window_graph[j].picture);
	}
 }
 
void init_Rest_Button()   //初始化安检口休息按钮 
{
	setcolor(WHITE);
	setbkmode(TRANSPARENT); 
	for(i=0;i<MaxCheck;i++)
	{
	    setfillcolor(LIGHTRED);
		fillellipse(60+i*90,125,25,25);
	}
}

void Init_emergency()    //初始化紧急通道 
{
	setcolor(WHITE);
	line(780+60*(MaxCheck-8),110,780+60*(MaxCheck-8),210);
	line(920+60*(MaxCheck-8),110,920+60*(MaxCheck-8),210);
	setfillcolor(LIGHTRED);
	bar(780+60*(MaxCheck-8),70,920+60*(MaxCheck-8),100);
	setfont(16,0,"宋体");
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(813+60*(MaxCheck-8),80,"紧急通道");
	setfillcolor(EGERGB(242,156,177));
    bar(790+60*(MaxCheck-8),110,810+60*(MaxCheck-8),210);   //紧急通道实际上 从  810  到  890 ，宽度 80 
    bar(890+60*(MaxCheck-8),110,910+60*(MaxCheck-8),210);
}

void init_Quit()     //初始化下班按钮 
{
	setfillcolor(EGERGB(242,156,177));
	if(entry_type=='q'||entry_type=='Q')
	{
		setfillcolor(EGERGB(160,32,240));
	}
	bar(50,30,180,70);    
	setfont(20,0,"宋体");
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(95,40,"下班");
}

void init_C_Button()   //初始化添加乘客按钮 
{
	setfillcolor(EGERGB(0,191,255));
	bar(10,620,120,660);
	setfont(21,0,"宋体");
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(25,630,"添加乘客");
}


void init_Buffer()
{
	int len=lenth(Buffer_list);
	//MaxCustSingleLine=15;
	setcolor(BLACK);
	line(120,660,120+40*MaxCustSingleLine,660);
	line(120+40*MaxCustSingleLine,660,120+40*MaxCustSingleLine,620);
	line(120,620,120+40*(MaxCustSingleLine-1),620);
	if(len>MaxCustSingleLine)
	{
		line(120+40*MaxCustSingleLine,620,120+40*MaxCustSingleLine,580);
		line(160,580,120+40*MaxCustSingleLine,580);
		line(120,580,120,620);
        if(len-MaxCustSingleLine<=4)
		{
			//Get_input(Buffer_list);
			Add_passager(Buffer_list,2+rand()%2);
		}
	}
	if(len>2*MaxCustSingleLine)
	{
		line(120,540,120,580);
		line(120,540,120+40*(MaxCustSingleLine-1),540);
		line(120+40*MaxCustSingleLine,540,120+40*MaxCustSingleLine,580);
		/*if(len-2*MaxCustSingleLine<=4)
		{
			Add_passager(Buffer_list,2+rand()%2);
		}*/ 
	}
	if(len>3*(MaxCustSingleLine))
	{
		line(120,500,120,540);
		line(160,500,120+40*MaxCustSingleLine,500);
		line(120+40*MaxCustSingleLine,500,120+40*MaxCustSingleLine,540);
		/*if(len-3*MaxCustSingleLine<=4)
		{
			Add_passager(Buffer_list,4+rand()%2);
		}*/ 
	}
	setcolor(WHITE);
	setfont(15,0,"宋体");                  //选择文字，（高度 宽度 字体） 
	setbkmode(TRANSPARENT);   
	setfillcolor(LIGHTRED);
	bar(10,520,120,620);
	char a[32];
	if(entry_type=='Q'||entry_type=='q')
	{
		len = 0 ;
	}
	sprintf(a,"%d",len);
	outtextxy(15,540,"缓冲区人数");
	outtextxy(50,565,a);
	if(len==MaxLines*MaxCustSingleLine)
	{
		outtextxy(15,595,"已满！！");
	}
	else
	{
		outtextxy(30,595,"未满");
	}
}

void draw()
{
	window *ptr = WINDOW;
	int i=0;
	for(i=60;i<700&&ptr->Next;i+=90)
	{
		int b  =0 ;
		setfillcolor(EGERGB(255,255,0 ));
		char a[30];
		branch *help = ptr->Next->Queue ;
	    while(help->next)
	    {
	    	if(help->next->y>=220+40*b&&help->next->y<=380)
	            b++;
			help = help->next ;
		}
		//setcolor(WHITE);
		setfont(15,0,"宋体");
		setbkmode(TRANSPARENT);
		if(b==5)
		{
		    setfillcolor(LIGHTRED);bar(i-25,460,i+30,500);outtextxy(i-5,480,"满");
		} 
		else	
		{
			setfillcolor(EGERGB(255,255,0 ));setcolor(BLUE);bar(i-25,460,i+30,500);
			outtextxy(i-5,480,"不满");
		}
		sprintf(a,"%d",b);
		outtextxy(i-3,465,a);
		memset(a,0,30);
		ptr=ptr->Next; 
	}
 } 

void Draw_hotel()
{
	PIMAGE img=newimage();
	getimage(img,"旅馆2.jpg",0,0);
	putimage(939,400,img);
	delimage(img);
	setcolor(WHITE);
	setfillcolor(EGERGB(30,144,255));
	bar(939,360,1000,400);
	setcolor(WHITE);
	setfont(14,0,"宋体");
	setbkmode(TRANSPARENT);
	outtextxy(942,375,"临时旅馆");
}

void init_All()  //初始化所有 
{
	draw(); 
	Draw_hotel();
	init_title();
	init_window();
	init_Rest_Button();
	Init_emergency();
	init_Quit();
	init_C_Button();
	init_Buffer();
}

