#include "General_Data.h"
//#include "gereral_Data_variable.h"

#ifndef GENERAL_DATA_VAROABLE_C
#define GENERAL_DATA_VAROABLE_C

HANDLE hMutex;
int fps;
int Get_input_OK;

int Go_hotel;

int i;
int OFFWORK;//���û���°��һֱ���У��յ��°�ָ�����Ϊ0��ֹͣ����
char Operation_pattern; //����ģʽ���ֶ������ļ�
char window_pattern; //����ڷ���ģʽ

int Passager_NO;
int initID;     //����ϵͳ�� �˿ͱ�� ��1 ��ʼ����
clock_t start , end , interval ,Pre_interval; //ʱ�����
int CurMaxWindow;   //ȫ�ֱ��� ��ǰ��������ڷ���� �����
int entry_NO;  //�¼���ţ�ȫ�ֱ���

char entry_type;     // �¼�����
int entry_sec;       // �¼����
int entry_mans;      // �˿�����
int entry_check;     // ��Ϣ�İ����
int entry_randtime;  //��Ϣʱ��

int Passager_flow;
int StartWork;   //�߳̿��ƿ�ʼ
int Signal;      //ͬ����
int Entry_OK;    //�������
int Rest_OK;     //��Ϣ�¼����
int OK;          //����һ������е� �����������˵��β���
int time_OK;     //������Ϣ update_window ���β���
int Destroy_OK;  //����ֻ��һ����������
int SIGN;        //ѭ����־���۲��°���Ƿ����г˿Ͷ��������
int Print_cycle; //�����������

int MaxCheck;                 //���İ��������
int MinCheck;                 //���ٵİ��������
int MaxCustSingleLine;	 	  //�������������
int MaxLines;
int MaxSeqLen;                //��������ڵı�־
int EasySeqLen;	              //�رհ���ڵı�־
int MaxCustCheck;   	      //����ڶ�������
int MaxSec;


buffer *Buffer_list;
window *WINDOW;
emergency *Emergency_window;
Window_Graph Window_graph[100];


int Draw_Entry_Once;  //����ֻ��ʼ����һ�Σ���ʼ�����λ�� 
int Speed;    //�޸��ٶ� .....Ŀǰ���޸ĵ�ֵ 1 2 5 10 20 
int sub[30];




#endif
