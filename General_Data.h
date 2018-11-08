#include "common_sys.h"
#ifndef GENERAL_DATE_H
#define GENERAL_DATE_H


typedef struct window_graph{
	PIMAGE picture;       //����ڵ�ͼ 
	int Cur_people;   //�����Ŀǰ������ 
	int During_Rest;  //������Ƿ�����Ϣ 
}Window_Graph;
 
struct output_window{   //����ļ���ʽ
    int window_ID;                    //����ڱ��
	char duty;                        //������Ƿ�ر�
	int ServeLen;                     //����ڵķ���ʱ��
	int PlanLen;                      //����ڵļƻ�����ʱ��
	int RestLen;                      //����ڵ���Ϣʱ��
	int WinListCustCount;             //����ڶ���ĳ���
	int a[10];                        //����ڶ���ĳ˿ͱ��
};

typedef struct Branch{   //����ڶ���
	int NO;                       //����ڳ˿͵ĺ���
	int CheckTime;                //�˿Ͱ����ʱ��
	int CheckOver;                //�˿��Ƿ񰲼���� 1-�������� 0-��û������
	struct Branch *next;          //����ڶ������һ���˿�
	
	int Reach_Emergency;   //�ж��Ƿ��˻����� 
	int x,y;               //����ͨ���˿� �� ����,������ڰ��죬�� �ж� ��ɾ��������ʾ 
	int dx,dy ;            //�ƶ����� 
	int which_NO ;        //ȥ�ĸ������ 
}branch;

typedef struct Window{   //�����
	int ID;                          //����ڵı��
	int EverOpen;                    //������Ƿ�����������������һ�������ʱ����Ҫ����
	int Current;                     //����ڿ�ʼ����ĵ�ǰʱ��
	int state;                       //�����Ŀǰ��״̬
	int Begin_rest;                  //����ڿ�ʼ��Ϣ�ĵ���ʱʱ��
	int Rest_Len;                    //����ڵ���Ϣʱ��
	int ServeLen;                    //����ڵķ���ʱ��
	int In_repair;
	PIMAGE picture;
	int Rest_Times;
	branch *Queue;                   //ÿ������� �Ķ���
	struct Window *Next;             //��һ�������
}window;

typedef struct Buffer{   //����������
	int ID;                         //�������˿͵ı��
	int In_Emergency; 
	struct Buffer *next;            //��һ���˿�
	
	int x,y;
	int dx,dy;
	int Mouse_add;
}buffer;

typedef struct Emergency{
	int Current;                     //��ʼ����ĵ�ǰʱ��
	int state;                       //Ŀǰ��״̬           
	int ServeLen;                    //����ʱ��
	branch *Queue;   
}emergency;


typedef struct Entry{
	int NO;           //�������
	int sec;          //����ʱ����
	char type;        //�¼�����  C���˿͵���  R�������������ͣ Q���°�
	int mans;         //�����ĳ˿�����
	int check;        //������Ϣ�İ���ڱ��
	int randtime;     //��Ϣʱ��
}entry;

typedef struct Equip{  //�����ļ���ʽ 
	char a[30];
	char b[30];
	char c[30];
	char d[30];
	char e[30];
	char f[30];
	char g[30];
	char h[30];
}equip;


#endif

