// ��ʼ��
#include"init.h"
#include "common_sys.h"
#include "gereral_Data_variable.h"

void print_heart() //��Ч 
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

void update(char *str)   //����������Ϣ
{
	char *ptr=str;
	while(!isdigit(*ptr))
   {
		ptr++;
   }
	str[strlen(str)-1]='\0';   //ֱ������������ַ� 
	char new_num[5];
	fflush(stdin);
	scanf("%s",new_num);
	strcat(str,new_num);   //���������� 
}

 


void Introduce()
{
	printf("\n\n\n\n\t����������������й����У�����ѡ�����²�����\n\n\t\tC �����˿ͽ����Ŷӻ�������\n");
	printf("\t\tR �������ѡ�񰲼����Ϣ��Ȼ��ѡ�񼸺Ű������Ϣ��\n");
	printf("\t\tQ ������ʼ�°ࡿ\n");
	printf("\n\n\t\t ��ܰ��ʾ��1.�߳�����治��ͣ�٣����������ӳ�\n\n");
	printf("\t\t \t    2.��������Ĭ������ C\n");
	Sleep(1000);
	system("cls");
}

void Get_pattern()
{
	printf("\n\n\n\n\n\t\t\t��ѡ�񰲼�ڷ���˿͵�ģʽ����   \n\t\t\tA: �˿���ȥ�����С�İ����\n");
	printf("\t\t\tB: �˿���ȥ�������ٵİ����\n");
	printf("              ����ѡ����:    ");
    fflush(stdin);     //��ջ����� 
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
    /*printf("\n\n\n\n\t\t ^* _ *^��ӭʹ�û��������ģ��ϵͳ^* _ *^\n");Sleep(1000);
	print_heart();
	printf("\n\n\n\n\n\t\t\t\t������");
	printf("�γ�");Sleep(300);printf("���");Sleep(300);printf("չʾ��");Sleep(300);printf("\n\n\t\t\t\t������");Sleep(300);printf("�����");Sleep(300);printf("ģ�⡿\n\n");Sleep(300);printf("\t\t\t\tС���Ա��");Sleep(300);
	printf("\n\t\t\t\t\t�����\t");Sleep(400);printf("��ͥ�\t");Sleep(400);printf("����\n\n\t\t\t");
	Sleep(1000);system("cls");*/
	FILE *fp;
	if((fp=fopen("����.dat","w+b"))==NULL)
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	 /*equip One={"MaxCheck = 8","MinCheck= 4","MaxCustSingleLine = 15","MaxLines = 4","MaxSeqLen = 5","EasySeqLen = 2","MaxCustCheck = 5","MaxSec = 5"};
	printf("\n\n\n\n\n\t\t\t");
	fwrite(&One,sizeof(One),1,fp);fclose(fp);
	Read();
	
	if((fp=fopen("����.dat","r+b"))==NULL)
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	equip one;
	fread(&one,sizeof(one),1,fp);
	printf("\n\n\n\n\n\t�������Ƿ���Ҫ�޸����ò���  ?\n\n \t\t\t���� Yes ������ y ��ͷ��ָ�����޸�����\n\n\t\t\t���� N ����������ĸ�Ͳ��޸�����\n\n"); //��ʾ���Ƿ���Ҫ�޸����ò���
	char Change[4];
	printf("\t�ҵ�ѡ���ǣ� ");
	gets(Change);        //��ȡ Yes ���� No
	fflush(stdin);
	if(Change[0]=='Y'||Change[0]=='y')
	{
		printf("\t��������Ҫ�޸ĵĸ���:  ");
		int change_sum;
		fflush(stdin);
		scanf("%d",&change_sum);
		while(change_sum--)
		{
			printf("\t��������Ҫ�޸���һ�����������֣��޸ĵڼ�����:  ");  //���� 1 �� 8
		    int change_NO;
		    fflush(stdin);
		    scanf("%d",&change_NO);      //�޸ĵ����
		    switch(change_NO)
		    {
		    	case 1:{
		    		printf("\t�޸�MaxCheckҲ��Ӱ�쵽MaxCustSingleLine!\n\t�������Ƿ����ѡ���޸�:\n");
		    		int again_OK;
		    		printf("\t�����·� 0 ��ʾ�����޸ġ�: ");
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
		printf("\n\n\n\n\n\t\t\t\t�޸�������Ϣ�ɹ�!\n\n");
		Sleep(500);
		system("cls");
	}
	if((fp=fopen("����.dat","w+b"))==NULL)
	{
		printf("can't open the file!\n");
	}
	rewind(fp);
	fwrite( &one , sizeof(equip) , 1 , fp );
	fclose(fp);
	Read();   //��ȡ�ļ� 
	Sleep(1000);*/
	FILE *another_fp;
	if((another_fp=fopen("entry.dat","w+b"))==NULL)
	{
		printf("���ܴ�Ŀ���ļ� entry.dat��\n");
	}
	fclose(another_fp);
	FILE *output_fp;
	if((output_fp=fopen("output.txt","w+"))==NULL)
	{
		printf("���ܴ�����ļ�output.txt\n");
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

