
#ifndef GENERAL_DATA_VARIABLE_H
#define GENERAL_DATA_VARIABLE_H
extern int i;
extern int OFFWORK;//���û���°��һֱ���У��յ��°�ָ�����Ϊ0��ֹͣ����
extern char Operation_pattern; //����ģʽ���ֶ������ļ�
extern char window_pattern; //����ڷ���ģʽ

extern int initID;     //����ϵͳ�� �˿ͱ�� ��1 ��ʼ����
extern clock_t start , end , interval ,Pre_interval; //ʱ�����
extern int CurMaxWindow;   //ȫ�ֱ��� ��ǰ��������ڷ���� �����
extern int entry_NO;  //�¼���ţ�ȫ�ֱ���

extern char entry_type;     // �¼�����
extern int entry_sec;       // �¼����
extern int entry_mans;      // �˿�����
extern int entry_check;     // ��Ϣ�İ����
extern int entry_randtime;  //��Ϣʱ��

extern int Passager_flow;
extern int StartWork;   //�߳̿��ƿ�ʼ
extern int Signal;      //ͬ����
extern int Entry_OK;    //�������
extern int Rest_OK;     //��Ϣ�¼����
extern int OK;          //����һ������е� �����������˵��β���
extern int time_OK;     //������Ϣ update_window ���β���
extern int Destroy_OK;  //����ֻ��һ����������
extern int SIGN;        //ѭ����־���۲��°���Ƿ����г˿Ͷ��������
extern int Print_cycle; //�����������


extern int MaxCheck;                 //���İ��������
extern int MinCheck;                 //���ٵİ��������
extern int MaxCustSingleLine;	 	  //�������������
extern int MaxLines;
extern int MaxSeqLen;                //��������ڵı�־
extern int EasySeqLen;	              //�رհ���ڵı�־
extern int MaxCustCheck;   	      //����ڶ�������
extern int MaxSec;


extern buffer *Buffer_list;
extern window *WINDOW;
extern emergency *Emergency_window;
extern Window_Graph Window_graph[100];


extern int Draw_Entry_Once;  //����ֻ��ʼ����һ�Σ���ʼ�����λ�� 
extern int Speed;    //�޸��ٶ� .....Ŀǰ���޸ĵ�ֵ 1 2 5 10 20 

extern HANDLE hMutex;
extern int fps;


extern int Go_hotel;
extern int sub[30];


#endif
