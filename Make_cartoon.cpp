
#include "common_sys.h"
#include "common_sys.h"
//#include "gereral_Data_variable.h"
#include "General_Data.h"
#include "Control.h"
extern int entry_type;
extern int Speed;
extern int MaxCheck;
extern int MaxCustSingleLine;
extern int MaxLines;
extern int MinCheck;
extern int MaxSeqLen;
extern int EasySeqLen;
extern int MaxCustCheck;
extern int MaxSec;
extern int window_pattern;
extern int Pre_Buffer_mans;
extern buffer *Buffer_list;
extern window *WINDOW;
extern emergency *Emergency_window;
extern int sub[30];

void Read()     //��ȡ������Ϣ�ļ��ĺ��� 
{
	FILE *fp;
	if((fp=fopen("����.dat","r+b"))==NULL) 
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	char ch = fgetc(fp);
	int a[8],i=0;
	while(!feof(fp))
	{
		if(isdigit(ch))
		{
			char help = fgetc(fp);
			if(isdigit(help))
			{
				a[i] = (ch-'0')*10 + (help-'0');//���Ҽٶ��������ݶ�С��100
			}
			else
			{
				a[i] = ch-'0';
			}
			i++;
		}
		ch = fgetc(fp);
	}
	MaxCheck = a[0];
    MinCheck= a[1];
    MaxCustSingleLine = a[2];
    MaxLines = a[3];
    MaxSeqLen = a[4];
    EasySeqLen = a[5];
    MaxCustCheck = a[6];
    MaxSec = a[7];
	printf("\n\n\n\n\n\t\t\t��󰲼��������%d\n\t\t\t��С���������: %d\n",MaxCheck,MinCheck);
	printf("\t\t\t���������ȴ��˿���: %d\n\t\t\t������ֱ������: %d\n",MaxCustSingleLine,MaxLines);
	printf("\t\t\t�������ȴ�����: %d\n\t\t\t���ɵȳ��ȣ�%d\n",MaxSeqLen,EasySeqLen);
	printf("\t\t\tÿ�����������󳤶�: %d\n\t\t\tһ�ΰ������Ϣ�ʱ����%d\n",MaxCustCheck,MaxSec);
	Sleep(1000); system("cls");
	fclose(fp); 
}

void init_background()
{
	PIMAGE img=newimage();
	getimage(img,"C:\\Users\\Administrator\\Desktop\\����.png",0,0);
	putimage(0,0,img);
	delimage(img);
	setfont(22,0,"����");
	setbkmode(TRANSPARENT);
	setcolor(BLACK); 
	outtextxy(200,50,"��󰲼������"); 
    outtextxy(200,100,"��С���������"); 
    outtextxy(200,150,"���������ȴ��˿���"); 
    outtextxy(200,200,"������ֱ������"); 
    outtextxy(200,250,"�������ȴ�����"); 
    outtextxy(200,300,"���ɵȴ�����"); 
    outtextxy(200,350,"ÿ�����������󳤶�"); 
    outtextxy(200,400,"һ�ΰ������Ϣ�ʱ��");
    setfillcolor(YELLOW);
	bar(800,380,860,420);
	setfont(18,0,"����");
	outtextxy(810,383,"ȷ��");
    outtextxy(810,403,"�޸�");
	int i;
	for(i=1;i<=8;i++)
	{
		setfillcolor(YELLOW);
		bar(500,50+(i-1)*50,520,70+(i-1)*50);
		bar(580,50+(i-1)*50,600,70+(i-1)*50);
		setfillcolor(GREEN);
		bar(660,50*i-10,760,50*i+30);
		char a[20];
		memset(a,0,19);
		sprintf(a,"%d",sub[i]);
		setfont(22,0,"����");
		setcolor(BLACK);
		setfont(18,0,"����");
		outtextxy(550,50*i,a);
		setcolor(WHITE);
		outtextxy(670,50*i,"��������");
	}
	
}

int On_which_left(int NO,int x,int y)
{
	return (x>=500&&x<=520&&y>=50*NO&&y<=50*NO+20)?1:0;
}

int On_which_right(int NO,int x,int y)
{
	return (x>=580&&x<=600&&y>=50*NO&&y<=50*NO+20)?1:0;
}

int On_end(int x,int y)
{
	return(x<=860&&x>=800&&y>=380&&y<=420)?1:0;
 } 

int On_which_key(int NO,int x,int y)   //bar(660,50*i-10,760,50*i+30);
{
	return (x>=660&&x<=760&&y>=50*NO-10&&y<=50*NO+30)?1:0;
 } 

void init_change()     //�޸����ý��� 
{
	int change_end=0;
	
	FILE *fp;
	if((fp=fopen("����.dat","w+b"))==NULL)
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	equip One={"MaxCheck = 8","MinCheck= 4","MaxCustSingleLine = 15","MaxLines = 4","MaxSeqLen = 5","EasySeqLen = 5","MaxCustCheck = 5","MaxSec = 50"};
	printf("\n\n\n\n\n\t\t\t");
	fwrite(&One,sizeof(One),1,fp);fclose(fp);
	Read();
	
	sub[1]=MaxCheck;                 //���İ��������
	sub[2]=MinCheck;                 //���ٵİ��������
	sub[3]=MaxCustSingleLine;	 	  //�������������
	sub[4]=MaxLines;
	sub[5]=MaxSeqLen;                //��������ڵı�־
	sub[6]=sub[6]=EasySeqLen;	              //�رհ���ڵı�־
	sub[7]=MaxCustCheck;   	      //����ڶ�������
	sub[8]=MaxSec;
	//printf("2�ŵ�����\n");

	    for( ;is_run()&&change_end==0;delay_fps(60))
	{
		cleardevice();
		
		init_background();
		
		char a[100],str[32];
		memset(a,0,100);	memset(str,0,32);
		int x,y;
		mousepos(&x,&y);  //��ȡ������� 
		sprintf(str,"%4d %4d",x,y);
		outtextxy(850,540,str);
		
		mouse_msg mouse = {0}; 
		while(mousemsg())   //ֱ����ȡ�����Ϣ 
		{
			mouse = getmouse();
		}
		
		if((int)mouse.is_down()&&(int)mouse.is_left())   //&&(int)mouse.is_up()
		{
			int k ;
			for(k=1;k<=8;k++)
			{
				if(On_which_left(k,x,y))
				{
					sub[k]--;
				}
			}
			
			for(k=1;k<=8;k++)
			{
				if(On_which_right(k,x,y))
				{
					sub[k]++;
				}
			}
			for(k=1;k<=8;k++)
			{
				if(On_which_key(k,x,y))
				{
					char str[100];
					memset(str,0,99);
	                inputbox_getline("������", "\n\n\n\t\t��Ҫ�޸ĵĲ���", str, 100);
	                sub[k]=atoi(str);
				}
			}
			if(On_end(x,y))
		    {
			    change_end=1;break;
		    }
		}
		
	}
	MaxCheck=sub[1];                 //���İ��������
	MinCheck=sub[2];                 //���ٵİ��������
	MaxCustSingleLine=sub[3];	 	  //�������������
	MaxLines=sub[4];
	MaxSeqLen=sub[5];                //��������ڵı�־
	EasySeqLen=sub[6];	              //�رհ���ڵı�־
	MaxCustCheck=sub[7];   	      //����ڶ�������
	MaxSec=sub[8];
 } 
 

void init_choose()
 {
 	
	PIMAGE img=newimage();
	getimage(img,"ģʽ.jpg",0,0);
	putimage(0,0,img);
	delimage(img);
	setfont(22,0,"����");
	setbkmode(TRANSPARENT);
	setcolor(BLACK); 
	outtextxy(350,200,"��ѡ�񰲼�ڷ���˿͵�ģʽ");
	outtextxy(350,250,"A:�˿���ȥ�����С�İ����");
	outtextxy(350,300,"B���˿���ȥ�������ٵİ����");
	setfillcolor(YELLOW);
	bar(350,350,400,400);
	bar(450,350,500,400);
	outtextxy(368,360,"A");
	outtextxy(468,360,"B");	
} 
  
int On_A(int x,int y)
{
  	return(x<=400&&x>=350&&y<=400&&y>=350)?1:0;
}


int On_B(int x,int y)
{
  	return(x<=500&&x>=450&&y<=400&&y>=350)?1:0;
}
  
void  Choose_Pattern()
{
	//init_choose();
	cleardevice();
	mouse_msg mouse={0};
	int end=0;
	for(;is_run&&end==0;delay_fps(60))
	{
		cleardevice();
		init_choose();
		
		int x,y;
		mousepos(&x,&y);
		while(mousemsg())
		{
			mouse=getmouse();
		}
		if((int)mouse.is_down()&&(int)mouse.is_left())
		{
			if(On_A(x,y))
			{
				window_pattern='A';	
				end=1;
			}
			if(On_B(x,y))
			{
				window_pattern='B';	
				end=1;
			}
		}
	}
}





void Check_Buffer()
{
	int len = lenth(Buffer_list) ;
	buffer *ptr = Buffer_list ;
	if(len<=MaxCustSingleLine)    //�ȿ��ǵڶ��� ��� ��һ�е���� 
	{
		int flag = 0 ;
		while(ptr->next)
		{
			if(ptr->next->y == 600)
			{
				flag = 1 ; break ;
			}
			ptr = ptr->next ;
		}
		//printf("flag = %d\n",flag);
		if(flag)   //��������б��ȥ�ģ�������  ���е���ص���һ�� 
		{
			buffer *reset = Buffer_list ;
			int  i = 0 ; 
			while(reset->next)
			{
				reset->next->x = 100+40*MaxCustSingleLine-40*i ;
				reset->next->y = 640 ;
				i++;
				reset = reset->next ;
			}
		}
	} 
	if(len>MaxCustSingleLine && len<=2*MaxCustSingleLine)  //���������г˿ͣ����ǳ���Ҫ������ά 
	{
		int flag = 0 ;
		while(ptr->next)
		{
			if(ptr->next->y == 560)
			{
				flag = 1 ; break ;
			}
			ptr = ptr->next ;
		}
		if(flag)   //��ȷ�г˿ͻ��� ������    ���������·ŵ�һ���� 
		{
			buffer *reset = Buffer_list ;
			int  i = 0 ; 
			while(reset->next)
			{
				if(i<MaxCustSingleLine)
				{
					reset->next->x = 140 +40*i ;
					reset->next->y = 600 ;
				}
				if(i>=MaxCustSingleLine)
				{
					reset->next->x = 100+40*MaxCustSingleLine-40*(i-MaxCustSingleLine) ;
					reset->next->y = 640 ;
				}
				i++ ;
				reset = reset->next ;
			 } 
		}
	}
	if(len>2*MaxCustSingleLine && len<=3*MaxCustSingleLine)  //�����У�����������ǲ����г˿� 
	{
		int flag = 0 ;
		while(ptr->next)
		{
			if(ptr->next->y == 520 )
			{
				flag = 1 ; break ;
			}
			ptr = ptr->next ;
		}
		if(flag)
		{
			int i = 0 ;
			buffer *reset = Buffer_list ;
			while(reset->next)
			{
				if(i<MaxCustSingleLine)
				{
					reset->next->x = 100+40*MaxCustSingleLine-40*i ;
					reset->next->y = 560 ;
				} 
				if(i>=MaxCustSingleLine && i<2*MaxCustSingleLine)
				{
					reset->next->x = 140 + 40*(i-MaxCustSingleLine) ;
					reset->next->y = 600 ;
				}
				if(i>=2*MaxCustSingleLine)
				{
					reset->next->x = 100+40*MaxCustSingleLine-40*(i-2*MaxCustSingleLine) ;
					reset->next->y = 640 ;
				}
				i++ ;
				reset = reset->next ;
			}
		}
	}
}

void Draw_Emergency()
{
	emergency *emerge = Emergency_window;
	branch *ptr = emerge->Queue;
	setcolor(BLUE);
	setfillcolor(RED);
	setfont(15,0,"����");                  //ѡ�����֣����߶� ��� ���壩 
	setbkmode(TRANSPARENT);
	int len = Lenth(emerge->Queue);
	int i = 0;
	while(ptr->next)
	{
		if(ptr->next->y==680)
		{
			ptr->next->dx = Speed;
		}
		if(ptr->next->x >= 850+60*(MaxCheck-8) && ptr->next->y==680)
		{
			ptr->next->dx = 0;
			ptr->next->dy = -Speed;
		}
		if(ptr->next->x>=850+60*(MaxCheck-8) && ptr->next->y!=160+i*40)
		{
			ptr->next->dx = 0;
			ptr->next->dy = -Speed;
		}
		if(ptr->next->x>=850+60*(MaxCheck-8) && ptr->next->y<=160+40*i)
		{
			ptr->next->dx = 0;
			ptr->next->dy = 0;
			ptr->next->Reach_Emergency = 1;
		}
		ptr->next->x += ptr->next->dx ;
		ptr->next->y += ptr->next->dy ;
		fillellipse(ptr->next->x,ptr->next->y,20,20);
		char a[32];
		memset(a,0,30);
		sprintf(a,"%d",ptr->next->NO);
		setcolor(WHITE);
		setfont(15,0,"����");                  //ѡ�����֣����߶� ��� ���壩 
	    setbkmode(TRANSPARENT);
		outtextxy(ptr->next->x-10,ptr->next->y-9,a);
		i++;
		ptr = ptr->next;
	}
}



void Draw_Windows()
{
	window *ptr = WINDOW;
	setcolor(WHITE);
	setfillcolor(EGERGB(89,247,145));
	setfont(15,0,"����");                  //ѡ�����֣����߶� ��� ���壩 
	setbkmode(TRANSPARENT);   
	while(ptr->Next&&ptr->Next->In_repair==0)
	{
		if(Lenth(ptr->Next->Queue)!=0&&ptr->Next->In_repair==0)
		{
			branch *Que = ptr->Next->Queue;
			int h=0;
			while(Que->next)
			{
				if(Que->next->y>440)     //׼��ȥ����ڣ��������� 
				{
					Que->next->dy = -Speed/2 ;
					Que->next->dx = 0 ;
				}
				if(Que->next->y==440)   //��ʼ����ȥ���� 
				{
					if(Que->next->x > 60+90*(ptr->Next->ID-1)) //���Ҫȥ�İ�����ڳ˿� ���
					{
						Que->next->dx = -Speed ;
						Que->next->dy = 0 ; 
					} 
					if(Que->next->x==60+90*(ptr->Next->ID-1))  //�������ھ����Լ����� 
					{
						Que->next->dx = 0 ;
						Que->next->dy = -1 ;
					}
					if(Que->next->x < 60+90*(ptr->Next->ID-1))  //�����������Լ��ұ� 
					{
						Que->next->dx = Speed ;
						Que->next->dy = 0 ;
					}
				} 
				if(Que->next->x==60+90*(ptr->Next->ID-1))  //����Ѿ����˰���ڵ����� 
				{
					Que->next->dx = 0 ;
					Que->next->dy = -1 ;
				}
				if(Que->next->y!=220+40*h && Que->next->x==60+90*(ptr->Next->ID-1))   //��������Լ���ȥ�ĵط����ͼ��������� 
				{
					Que->next->dy = -1 ;
				}
				if(Que->next->y==220+40*h && Que->next->x==60+90*(ptr->Next->ID-1))   //������Ѿ����˸�ͣ�ĵط�����ͣ�� 
				{
					Que->next->dy = 0;
				}
				if(Que->next->y==220)     //����������ɫ 
				{
					setfillcolor(EGERGB(160,32,240));
				}
				else  setfillcolor(GREEN);
				fillellipse(Que->next->x,Que->next->y,20,20);
				char a[32];
				memset(a,0,30);
				sprintf(a,"%d",Que->next->NO);
				if(Que->next->NO<=99)
				    outtextxy(Que->next->x-7,Que->next->y-7,a);
				else  outtextxy(Que->next->x-10,Que->next->y-7,a);
				h++;  //����������ͣ���������� 
				Que->next->x += Que->next->dx ;
				Que->next->y += Que->next->dy ;
				Que = Que->next ;
			}
		}
		if(ptr->Next->state==0)
		{
			outtextxy(45+90*(ptr->Next->ID-1),115,"����");
		}
		else if(ptr->Next->state==1)
		{
			branch *help = ptr->Next->Queue ;
			while(help->next)
			{
				help = help->next ;
			}
			if(help->y==180+40*MaxCustCheck)
			    outtextxy(40+90*(ptr->Next->ID-1),115,"������");
			else  outtextxy(45+90*(ptr->Next->ID-1),115,"����");
		}
        else if(ptr->Next->state==2)
		{
			outtextxy(45+90*(ptr->Next->ID-1),110,"����");
			outtextxy(45+90*(ptr->Next->ID-1),130,"����");
		} 
		else if(ptr->Next->state==3)
		{
			if(Lenth(ptr->Next->Queue)==0)
		 	    outtextxy(45+90*(ptr->Next->ID-1),115,"��Ϣ");
		 	else 
		 	{
		 		outtextxy(45+90*(ptr->Next->ID-1),110,"�ȴ�");
			    outtextxy(45+90*(ptr->Next->ID-1),130,"��Ϣ");
			}
		}
		else if(ptr->Next->state==4)
		{
		 	outtextxy(45+90*(ptr->Next->ID-1),115,"�°�");
		}
		ptr = ptr->Next;
	}
}

void Draw_Buffer()
{
	buffer *help = Buffer_list ;
	setcolor(WHITE);
	setfont(15,0,"����");                  //ѡ�����֣����߶� ��� ���壩 
	setbkmode(TRANSPARENT);
    while(help->next)          //&&help->next->y>=500
	{
		if(help->next->Mouse_add==0)
		{
	        setfillcolor(GREEN);
		}
	    else if(help->next->Mouse_add==1)
	    {
	    	setfillcolor(BLUE);
		}
		if(help->next->x<=920)
		{
			fillellipse(help->next->x,help->next->y,20,20);
		    char a[10];
		    sprintf(a,"%d",help->next->ID);
		    outtextxy(help->next->x-8,help->next->y-8,a);
		}
		
	    help = help->next;
	}
}

void Draw_Ball()
{
	int len = lenth(Buffer_list);
	if(entry_type=='Q'||entry_type=='q')
	{
		len = 0 ;
	}
	setcolor(WHITE);
	setfont(15,0,"����");                  //ѡ�����֣����߶� ��� ���壩 
	setbkmode(TRANSPARENT);   
	setfillcolor(LIGHTRED);
	bar(10,520,120,620);
	char a[32];
	sprintf(a,"%d",len);
	outtextxy(15,540,"����������");
	outtextxy(50,575,a);
	if(len==MaxLines*MaxCustSingleLine)
	{
		outtextxy(15,595,"��������");
	}
	else
	{
		outtextxy(30,595,"δ��");
	}
	setcolor(WHITE);
	setfillcolor(GREEN);
	buffer *ptr = Buffer_list;
	if(len<=MaxCustSingleLine)
	{
		int k=1;
		while(ptr->next)
		{
			ptr->next->x = 100+40*MaxCustSingleLine-40*(k-1);
			ptr->next->y = 640 ;
	        ptr = ptr->next ;
	        k++ ;
		}
		Draw_Buffer();
	}
	else if(len>MaxCustSingleLine&&len<=2*MaxCustSingleLine)
	{
		int k=1;
		while(ptr->next)
		{
			if(k<=MaxCustSingleLine)
			{
				ptr->next->x = 140+40*(k-1);
				ptr->next->y = 600 ;
			}
			else if(k>MaxCustSingleLine)
			{
				ptr->next->x =  100+40*(MaxCustSingleLine)-40*(k-MaxCustSingleLine-1) ;
				ptr->next->y = 640 ;
			}
			k++;
			ptr = ptr->next ;
		}
		Draw_Buffer();
	}
	else if(len>2*MaxCustSingleLine&&len<=3*MaxCustSingleLine)
	{
		int k = 1;
		while(ptr->next)
		{
			if(k<=MaxCustSingleLine)
			{
				ptr->next->x = 100+40*(MaxCustSingleLine)-40*(k-1);
				ptr->next->y = 560 ;
			}
			else if(k>MaxCustSingleLine && k<=2*MaxCustSingleLine)
			{
				ptr->next->x = 140+40*(k-MaxCustSingleLine-1);
				ptr->next->y = 600 ;
			}
			else if(k>2*MaxCustSingleLine && k<=3*MaxCustSingleLine)
			{
				ptr->next->x = 100+40*(MaxCustSingleLine)-40*(k-2*MaxCustSingleLine-1);
				ptr->next->y = 640;
			}
			k++;
			ptr = ptr->next ;
		}
		Draw_Buffer();
	}
	else if(len>3*MaxCustSingleLine&&len<=4*MaxCustSingleLine)
	{
		int k = 1;
		while(ptr->next)
		{
			if(k<=MaxCustSingleLine)
			{
				ptr->next->x = 140+40*(k-1);
				ptr->next->y = 520 ;
			}
			else if(k>MaxCustSingleLine && k<=2*MaxCustSingleLine)
			{
				ptr->next->x = 100+40*(MaxCustSingleLine)-40*(k-MaxCustSingleLine-1);
				ptr->next->y = 560 ;
			}
			else if(k>2*MaxCustSingleLine && k<=3*MaxCustSingleLine)
			{
				ptr->next->x = 140+40*(k-2*MaxCustSingleLine-1);
				ptr->next->y = 600;
			}
			else if(k>3*MaxCustSingleLine && k<=4*MaxCustSingleLine)
			{
				ptr->next->x = 100+40*(MaxCustSingleLine)-40*(k-3*MaxCustSingleLine-1);
				ptr->next->y = 640;
			}
			k++;
			ptr = ptr->next;
		}
		Draw_Buffer();
	}
}


void Update_Ball()
{
	int len = lenth(Buffer_list);
	buffer *ptr = Buffer_list ;
	if(len<=MaxCustSingleLine)
	{
		int i = 0;
		while(ptr->next)
		{
			if(ptr->next->x!=100+40*(MaxCustSingleLine-i) && ptr->next->y==640)
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			//printf(" ͣ�� %d \n",100+40*(MaxCustSingleLine-i));
			if(ptr->next->x == 100+40*(MaxCustSingleLine)-40*i && ptr->next->y==640)
			{
				ptr->next->dx == 0;
				ptr->next->dy = 0;
			}
			if(ptr->next->y==640 && ptr->next->x== 100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = 0;
				ptr->next->dy = 0;
			}
			if(ptr->next->x==100+40*(MaxCustSingleLine)-40*i)
			{
				ptr->next->dx = 0 ;
			}
			ptr->next->x += ptr->next->dx ;
			ptr->next->y += ptr->next->dy ;
			i++ ;
			ptr = ptr->next ;
		}
	}
	if(len>MaxCustSingleLine&&len<=2*MaxCustSingleLine)
	{
		int i = 0;
		while(ptr->next)
		{
			if(ptr->next->y==640 && ptr->next->x!=100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==640 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
			if(ptr->next->y==600 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==600 && ptr->next->x==140)
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = 0 ;
			}
		    if(i<MaxCustSingleLine)  //�����С�� �����������������һ�� 
		    {
		    	if(ptr->next->y==600 && ptr->next->x!=140+40*i)
		    	{
		    		ptr->next->dx = -Speed ;
		    		ptr->next->dy = 0 ;
				}
		    	if(ptr->next->y==600 && ptr->next->x==140+40*i)
				{
					ptr->next->dx = 0;
					ptr->next->dy = 0;
			    } 
			}
			if(i>=MaxCustSingleLine) //���˵ڶ��� 
			{
				if(ptr->next->y==640&&ptr->next->x!=100+40*(MaxCustSingleLine)-40*(i-MaxCustSingleLine))
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640&&ptr->next->x==100+40*(MaxCustSingleLine)-40*(i-MaxCustSingleLine))
				{
					ptr->next->dx = 0;
					ptr->next->dy = 0;
				}
			}
			ptr->next->x += ptr->next->dx ;
			ptr->next->y += ptr->next->dy ;
			i++ ;
			ptr = ptr->next ;
		}
	}
	if(len>2*MaxCustSingleLine&&len<=3*MaxCustSingleLine)//�������� 
	{
		int i = 0;
		while(ptr->next)
		{
			if(ptr->next->y==640 && ptr->next->x!=100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==640 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
			if(ptr->next->y==600 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==600 && ptr->next->x!=140)
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==600 && ptr->next->x==140)
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
			if(ptr->next->y==560 && ptr->next->x==140)
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==560 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==560 && ptr->next->x!=100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(i<MaxCustSingleLine) //��Ȼ�ڵ����еĳ˿� 
			{
				if(ptr->next->y==560 && ptr->next->x!=100+40*(MaxCustSingleLine)-40*i)
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==560 && ptr->next->x==100+40*(MaxCustSingleLine)-40*i)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==600 && ptr->next->x!=140)
				{
					ptr->next->dx = -Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==600 && ptr->next->x==140)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = -Speed ;
				}
			}
			if(i>=MaxCustSingleLine&&i<2*MaxCustSingleLine)  // ���ڵڶ��еĳ˿� 
			{
				 if(ptr->next->y==600 && ptr->next->x!=140+(i-MaxCustSingleLine)*40)
				{
					ptr->next->dx = -Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==600 && ptr->next->x==140+(i-MaxCustSingleLine)*40)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x!=100+MaxCustSingleLine*40)
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x==100+MaxCustSingleLine*40)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = -Speed ;
				}
			} 
			if(i>=2*MaxCustSingleLine)  //���ڵ�һ�� 
			{
				if(ptr->next->y==640 && ptr->next->x!=100+40*(MaxCustSingleLine)-40*(i-2*MaxCustSingleLine))
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x==100+40*(MaxCustSingleLine)-40*(i-2*MaxCustSingleLine))
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x==100+40*MaxCustSingleLine)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ; 
				}
				if(ptr->next->x==100+40*(MaxCustSingleLine)-40*(i-2*MaxCustSingleLine))
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				}
			}
			ptr->next->x += ptr->next->dx ;
			ptr->next->y += ptr->next->dy ;
			i++ ;
			ptr = ptr->next ;
		}
	}
	if(len>3*MaxCustSingleLine&&len<=4*MaxCustSingleLine)
	{
		int i = 0 ;
		while(ptr->next)
		{
			if(ptr->next->y==640 && ptr->next->x!=100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==640 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
			if(ptr->next->y==600 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==600 && ptr->next->x!=140)
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==600 && ptr->next->x==140)
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
			if(ptr->next->y==560 && ptr->next->x==140)
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==560 && ptr->next->x==100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
			if(ptr->next->y==560 && ptr->next->x!=100+40*(MaxCustSingleLine))
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->y==520 && ptr->next->x==100+MaxCustSingleLine*40)
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ; 
			}
			if(ptr->next->y==520 && ptr->next->x!=100+MaxCustSingleLine*40)
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ; 
			}
			if(ptr->next->y==520 && ptr->next->x==140)
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = 0 ;
			}
			if(i<MaxCustSingleLine)  //���ڵ����� 
			{
				if(ptr->next->y==520 && ptr->next->x!=140+40*i)
				{
					ptr->next->dx = -Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==520 && ptr->next->x==140+i*40)
				{
					ptr->next->dx = 0 ; 
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==560 && ptr->next->x!=100+40*MaxCustSingleLine)
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==560 && ptr->next->x==100+40*MaxCustSingleLine)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = -Speed ;
				}
			}
			if(i>=MaxCustSingleLine && i<2*MaxCustSingleLine)  //���ڵ����� 
			{
				if(ptr->next->y==560 && ptr->next->x!=100+40*MaxCustSingleLine-40*(i-MaxCustSingleLine))
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				} 
				if(ptr->next->y==560 && ptr->next->x==100+40*MaxCustSingleLine-40*(i-MaxCustSingleLine))
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				} 
				if(ptr->next->y==600 && ptr->next->x!=140)
				{
					ptr->next->dx = -Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==600 && ptr->next->x==140)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = -Speed ;
				}
			}
			if(i>=2*MaxCustSingleLine && i<3*MaxCustSingleLine)  //���ڵڶ��� 
			{
				if(ptr->next->y==600 && ptr->next->x!=140+40*(i-2*MaxCustSingleLine))
				{
					ptr->next->dx = -Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==600 && ptr->next->x==140+40*(i-2*MaxCustSingleLine))
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x!=100+40*MaxCustSingleLine)
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x==100+40*MaxCustSingleLine)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = -Speed ;
				}
			}
			if(i>=3*MaxCustSingleLine && i<4*MaxCustSingleLine)
			{
				if(ptr->next->y==640 && ptr->next->x!=100+40*MaxCustSingleLine-40*(i-3*MaxCustSingleLine))
				{
					ptr->next->dx = Speed ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x==100+40*MaxCustSingleLine-40*(i-3*MaxCustSingleLine))
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				}
				if(ptr->next->y==640 && ptr->next->x==100+40*MaxCustSingleLine)
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ; 
				}
				if(ptr->next->x==100+40*MaxCustSingleLine-40*(i-3*MaxCustSingleLine))
				{
					ptr->next->dx = 0 ;
					ptr->next->dy = 0 ;
				}
			}
			ptr->next->x += ptr->next->dx ;
			ptr->next->y += ptr->next->dy ;
			i++;
			ptr = ptr->next ;
		}
	}
}

void Go_from_four()   //���ĺſڳ����� 
{
	buffer *ptr = Buffer_list;
	while(ptr->next)
	{
		//  ���ڿ�ʼ  �������λ����� ���������� 
		if(ptr->next->y==640 && ptr->next->x!=100+40*MaxCustSingleLine)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==640 && ptr->next->x==100+40*MaxCustSingleLine)
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->y==600 && ptr->next->x==100+40*MaxCustSingleLine)
		{
			ptr->next->dx = -Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==600 && ptr->next->x!=140)
		{
			ptr->next->dx = -Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==600 && ptr->next->x==140)  //�ڶ��� 
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->y==560 && ptr->next->x==140)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ; 
		}
		if(ptr->next->y==560 && ptr->next->x!=100+40*MaxCustSingleLine)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==560 && ptr->next->x==100+40*MaxCustSingleLine) //������ 
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->y==520 && ptr->next->x==100+40*MaxCustSingleLine)
		{
			ptr->next->dx = -Speed/2 ;
			ptr->next->dy = 0 ;
		}
		
		if(ptr->next->y==520 && ptr->next->x!=140) //������ 
		{
			ptr->next->dx = -Speed/2 ;
			ptr->next->dy = 0 ;
		}
		
		
		if(ptr->next->x==140 && ptr->next->y==520)
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->x==140 && ptr->next->y==440)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		ptr->next->x += ptr->next->dx ;
		ptr->next->y += ptr->next->dy ;
		ptr = ptr->next ;
	}
}

void Go_from_three()
{
	buffer *ptr = Buffer_list;
	while(ptr->next)
	{
		//  ���ڿ�ʼ  �������λ����� ���������� 
		if(ptr->next->y==640 && ptr->next->x!=100+40*MaxCustSingleLine)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==640 && ptr->next->x==100+40*MaxCustSingleLine)
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->y==600 && ptr->next->x==100+40*MaxCustSingleLine)
		{
			ptr->next->dx = -Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==600 && ptr->next->x!=140)
		{
			ptr->next->dx = -Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==600 && ptr->next->x==140)  //�ڶ��� 
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->y==560 && ptr->next->x==140)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ; 
		}
		if(ptr->next->y==560 && ptr->next->x!=100+40*MaxCustSingleLine)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==560 && ptr->next->x==100+40*MaxCustSingleLine) //������ 
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->y==440 && ptr->next->x==100+40*MaxCustSingleLine)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		ptr->next->x += ptr->next->dx ;
		ptr->next->y += ptr->next->dy ;
		ptr = ptr->next ;
	}
}


void Go_from_two()
{
	buffer *ptr = Buffer_list ;
	while(ptr->next)
	{
		if(ptr->next->y==640)
		{
			if(ptr->next->x!=100+40*MaxCustSingleLine)
			{
				ptr->next->dx = Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->x==100+40*MaxCustSingleLine)
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
		}
		if(ptr->next->y==600)
		{
			if(ptr->next->x==100+40*MaxCustSingleLine)
			{
				ptr->next->dx = -Speed ;
				ptr->next->dy = 0 ;
			}
			if(ptr->next->x==140)
			{
				ptr->next->dx = 0 ;
				ptr->next->dy = -Speed ;
			}
		}
		if(ptr->next->x==140 && ptr->next->y==440)
		{
			ptr->next->dx = Speed ;
			ptr->next->dy = 0 ;
		}
		ptr->next->x += ptr->next->dx ;
		ptr->next->y += ptr->next->dy ;
		ptr = ptr->next ;
	}
}

void Go_from_one()
{
	buffer *ptr = Buffer_list;
	while(ptr->next)
	{
		if(ptr->next->y==640 && ptr->next->x!=100+40*MaxCustSingleLine)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		if(ptr->next->y==640 && ptr->next->x==100+40*MaxCustSingleLine)
		{
			ptr->next->dx = 0 ;
			ptr->next->dy = -Speed/2 ;
		}
		if(ptr->next->x==100+40*MaxCustSingleLine && ptr->next->y==440)
		{
			ptr->next->dx = Speed/2 ;
			ptr->next->dy = 0 ;
		}
		ptr->next->x += ptr->next->dx ;
		ptr->next->y += ptr->next->dy ;
		ptr = ptr->next ;
	}
}

void Go_to_hotel()
{
	int len = lenth(Buffer_list);
	if(len>3*MaxCustSingleLine)
	{
		Go_from_four(); 
	}
	if(len>2*MaxCustSingleLine&&len<=3*MaxCustSingleLine)
	{
		Go_from_three();
	}
	if(len>MaxCustSingleLine&&len<=2*MaxCustSingleLine)
	{
		Go_from_two();
	}
	if(len<=MaxCustSingleLine)
	{
		Go_from_one();
	}
}











