// 初始化
#include"init.h"
#include "common_sys.h"
#include "gereral_Data_variable.h"

void print_heart() //特效 
{
	float y;
	for (y = 1.5f; y > -1.5f; y -= 0.1f) {
	printf("\t");
	float x;
        for (x = -1.5f; x < 1.5f; x += 0.05f) {
            float z = x * x + y * y - 1;
            float f = z * z * z - x * x * y * y * y;
            putchar(f <= 0.0f ? ".:-=+*#%@"[(int)(f * -8.0f)] : ' ');
        }
        putchar('\n');  Sleep(50);
    } Sleep(1000);
	 system("cls");
}

void update(char *str)   //更新配置信息
{
	char *ptr=str;
	while(!isdigit(*ptr))
   {
		ptr++;
   }
	str[strlen(str)-1]='\0';   //直接舍弃后面的字符 
	char new_num[5];
	fflush(stdin);
	scanf("%s",new_num);
	strcat(str,new_num);   //链接新数字 
}

 


void Introduce()
{
	printf("\n\n\n\n\t接下来，程序的运行过程中，可以选择如下操作：\n\n\t\tC ：【乘客进入排队缓冲区】\n");
	printf("\t\tR ：【随机选择安检口休息，然后选择几号安检口休息】\n");
	printf("\t\tQ ：【开始下班】\n");
	printf("\n\n\t\t 温馨提示：1.线程输入版不许停顿，但是稍有延迟\n\n");
	printf("\t\t \t    2.其他按键默认输入 C\n");
	Sleep(1000);
	system("cls");
}

void Get_pattern()
{
	printf("\n\n\n\n\n\t\t\t请选择安检口分配乘客的模式——   \n\t\t\tA: 乘客先去序号最小的安检口\n");
	printf("\t\t\tB: 乘客先去人数最少的安检口\n");
	printf("              您的选择是:    ");
    fflush(stdin);     //清空缓存区 
	scanf("%c",&window_pattern);
	getchar(); Sleep(1000); system("cls");
	printf("\n\n\n");
}

void init()
{
    OFFWORK = 1 ;
	initID = 1 ;
	entry_NO = 1;
	Speed = 5;
	//system("color 97");
    /*printf("\n\n\n\n\t\t ^* _ *^欢迎使用机场安检口模拟系统^* _ *^\n");Sleep(1000);
	print_heart();
	printf("\n\n\n\n\n\t\t\t\t【程序");
	printf("课程");Sleep(300);printf("设计");Sleep(300);printf("展示】");Sleep(300);printf("\n\n\t\t\t\t【机场");Sleep(300);printf("安检口");Sleep(300);printf("模拟】\n\n");Sleep(300);printf("\t\t\t\t小组成员：");Sleep(300);
	printf("\n\t\t\t\t\t吴慧雯\t");Sleep(400);printf("潘庭婕\t");Sleep(400);printf("刘畅\n\n\t\t\t");
	Sleep(1000);system("cls");*/
	FILE *fp;
	if((fp=fopen("配置.dat","w+b"))==NULL)
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	 /*equip One={"MaxCheck = 8","MinCheck= 4","MaxCustSingleLine = 15","MaxLines = 4","MaxSeqLen = 5","EasySeqLen = 2","MaxCustCheck = 5","MaxSec = 5"};
	printf("\n\n\n\n\n\t\t\t");
	fwrite(&One,sizeof(One),1,fp);fclose(fp);
	Read();
	
	if((fp=fopen("配置.dat","r+b"))==NULL)
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	equip one;
	fread(&one,sizeof(one),1,fp);
	printf("\n\n\n\n\n\t请问你是否需要修改配置参数  ?\n\n \t\t\t输入 Yes 或者以 y 开头的指令则修改配置\n\n\t\t\t输入 N 或者其他字母就不修改配置\n\n"); //提示，是否需要修改配置参数
	char Change[4];
	printf("\t我的选择是： ");
	gets(Change);        //读取 Yes 或者 No
	fflush(stdin);
	if(Change[0]=='Y'||Change[0]=='y')
	{
		printf("\t请输入你要修改的个数:  ");
		int change_sum;
		fflush(stdin);
		scanf("%d",&change_sum);
		while(change_sum--)
		{
			printf("\t请输入你要修改哪一个【输入数字，修改第几个】:  ");  //输入 1 到 8
		    int change_NO;
		    fflush(stdin);
		    scanf("%d",&change_NO);      //修改的序号
		    switch(change_NO)
		    {
		    	case 1:{
		    		printf("\t修改MaxCheck也会影响到MaxCustSingleLine!\n\t请问您是否继续选择修改:\n");
		    		int again_OK;
		    		printf("\t【按下非 0 表示继续修改】: ");
		    		scanf("%d",&again_OK);
		    		if(again_OK)
		    		{
		    			printf("\t\tMaxCheck = ");
		    		    update(one.a);
					}
					break;
				}
				case 2:{
					printf("\t\tMinCheck = ");
		    		update(one.b);
					break;
				}
				case 3:{
					printf("\t\tMaxCustSingleLine = ");
		    		update(one.c);
					break;
				}
				case 4:{
					printf("\t\tMaxLines = ");
		    		update(one.d);
					break;
				}
				case 5:{
					printf("\t\tMaxSeqLen = ");
		    		update(one.e);
					break;
				}
				case 6:{
					printf("\t\tEasySeqLen = ");
		    		update(one.f);
					break;
				}
				case 7:{
					printf("\t\tMaxCustCheck = ");
		    		update(one.g);
					break;
				}
				case 8:{
					printf("\t\tMaxCheck = ");
		    		update(one.h);
					break;
				}
			}
		}
		Sleep(1000);
	    system("cls");
		printf("\n\n\n\n\n\t\t\t\t修改配置信息成功!\n\n");
		Sleep(500);
		system("cls");
	}
	if((fp=fopen("配置.dat","w+b"))==NULL)
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	fwrite( &one , sizeof(equip) , 1 , fp );
	fclose(fp);
	Read();   //读取文件 
	Sleep(1000);*/
	FILE *another_fp;
	if((another_fp=fopen("entry.dat","w+b"))==NULL)
	{
		printf("不能打开目标文件 entry.dat！\n");
	}
	fclose(another_fp);
	FILE *output_fp;
	if((output_fp=fopen("output.txt","w+"))==NULL)
	{
		printf("不能打开输出文件output.txt\n");
	}   fclose(output_fp);
	FILE *cycle_fp;
	if((cycle_fp=fopen("print_cycle.txt","w+"))==NULL)
	{
		printf("can't open the print_cycle file\n'");
	}
	//Get_pattern();
	fflush(stdin);
	system("cls");
}

