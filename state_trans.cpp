//state_trans.c


// �Զ���ת��ģ�� 


#include"state_trans.h"

#include "common_sys.h"
#include "Control.h"
#include "gereral_Data_variable.h"

void state_trans(window *head)
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file\n");
	}
	window *ptr = head ;
	while(ptr->Next)
	{
		branch *Que = ptr->Next->Queue ;
		switch(ptr->Next->state)
		{
			case 0:{                  //����
				if(entry_type=='Q'||entry_type=='q')                  //�յ��°�ָ��
				{
					ptr->Next->state = 4 ;
				}
				else if((entry_type=='C'||entry_type=='c')&&Lenth(ptr->Next->Queue))  //�г˿͵���
				{
					ptr->Next->state = 1 ;
				}
				
				break;
			}
			case 1:{                  //���ڰ�����
				if(entry_type=='Q'||entry_type=='q')
				{
					ptr->Next->state = 4 ;            //�յ��°�ָ��
				}
				else if((end-start)/CLOCKS_PER_SEC==ptr->Next->Current)//������� 
				{
					ptr->Next->state = 2 ;
				}
				break;                       
			}
			case 2:{                 //�������
				if(entry_type=='Q'||entry_type=='q')
				{
					ptr->Next->state = 4 ;      //�յ��°�ָ��
				}
				else if(ptr->Next->state==3)
				{                               //�յ���Ϣָ��
					ptr->Next->state = 3 ;                     //ptr->Next->flag = 0 ;
				}
				else if(Lenth(ptr->Next->Queue)!=0)        //�г˿͵���
				{
					ptr->Next->state = 1 ;
				}
				else{
					ptr->Next->state = 0;
			    }
				break;
			}
			case 3:{
				if(entry_type=='Q'||entry_type=='q')                 //�յ��°�ָ��
				{
					ptr->Next->state = 4 ;
				}
				printf("\n%d s �� %d�Ű������Ϣ����\n",ptr->Next->Begin_rest,ptr->Next->ID);
				ptr->Next->Begin_rest--;
				if(ptr->Next->Begin_rest==0)          //��Ϣʱ�䵽 
				{
					fprintf(fp,"\n%d�Ű������Ϣ����\n",ptr->Next->Begin_rest);
					printf("\n%d�Ű������Ϣ����\n",ptr->Next->Begin_rest);
					if(Lenth(Que)==0)
					{
						ptr->Next->state = 0 ;   //ע��ʱ��ֻ�ܼ�һ��......ע��״̬��ת�䣬����ֻ���һ��
						ptr->Next->Rest_Len +=entry_sec ; //�����Ϣʱ���ڿ��԰�����ʣ��ĳ˿ͣ�������Ϣ��ʱ��
					}
					else if((end-start)/CLOCKS_PER_SEC==ptr->Next->Current)
					{
						ptr->Next->state = 2 ;
					}
					else{
						ptr->Next->state = 1 ;
					}
				}
				break;
			}
			case 4:{
				break;
			}
		}
		ptr = ptr->Next ;
	}
	fclose(fp);
}
