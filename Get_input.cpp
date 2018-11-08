// ���뷽��
#include"Get_input.h"
#include "common_sys.h"
#include "gereral_Data_variable.h"
#include "Control.h"
char Get_type() //��ȡ�¼����� 
{
	int type = 1+rand()%300;
	if((end-start)/CLOCKS_PER_SEC>=240||(type%30==0&&((end-start)/CLOCKS_PER_SEC>180))) //�����¼�����
	    return 'Q';        // �°�
	else if(type%20==0&&((end-start)/CLOCKS_PER_SEC)>20)
	    return 'R';        //�����������ͣ
	else
	    return 'C';        //�˿͵���
}

int trypossion() //���ɷֲ�ģ�������������
{
  double u = U_Random();
  int p = possion();
  return p;

}

int possion()
{
    int Lambda = 3, k = 0;
    long double p = 1.0;
    long double l=exp(-Lambda); //exp������e�Ĵη���
    while (p>=l)
    {
        double u = U_Random();
        p *= u;
        k++;
    }
    return k-1;
}

double U_Random()  //u��һ��С��1���������
{
  double f;
  f = (float)(rand() % 100);

  return f/100;
}


void Get_entry()  //��ȡһ���¼�
{
	if(entry_type!='Q'&&entry_type!='q')
	{
		FILE *fp,*output_fp;
	    if((fp=fopen("entry.dat","a+b"))==NULL||(output_fp=fopen("output.txt","a+"))==NULL)
	   {
		   printf("can't open the file����entry_dat!\n");
		   OFFWORK = 0 ;
	   }
	    else
	   {
		   entry one={0,0,' ',0,0,0};                //��ʼ��
		   one.NO = entry_NO ;                       //�¼������
		   one.sec = rand()%2+ 2;          //��������¼��ķ���ʱ��
		   one.type = Get_type();                    //�漴��ȡ�¼����ͣ��°࣬��ͣ���г˿͵���
		   switch(one.type)
		  {
			    case 'C':{
				    
				    one.mans = 1+trypossion();
				    /*if(lenth(Buffer_list)>=3*MaxCustSingleLine && lenth(Buffer_list)-3*MaxCustSingleLine<=5)
				    {
				    	one.mans = 6+trypossion();
					}*/
					if((end-start)/CLOCKS_PER_SEC>250) 
				        //one.mans = 1+rand()%2 ;
				    one.mans = 1+rand()%2;
				    fprintf(output_fp,"\n%d ���³˿ͽ����Ŷӻ�����\n",one.mans);
				    break;
			    }
			    case 'R':{
				    one.check = 1+rand()%CurMaxWindow ;
				    while(one.check==entry_check)
				    {
				    	one.check = 1+rand()%CurMaxWindow ;//����ͬʱ��Ϣ�������� 
					}
			        one.randtime = 30+rand()%20 ;
			        printf("%d �Ű����������Ϣ %d s\n",one.check,one.randtime);
			        fprintf(output_fp,"\n%d �Ű����������Ϣ %d s\n",one.check,one.randtime);
				    break;
			    }
			    case 'Q':{
				    printf("�°�ʱ�䵽!\n");
				    fprintf(output_fp,"\n\n%s\n","�°�ʱ�䵽!\n");
				    break;
			    }
			    default:break;
		  }
		   fseek(fp , (one.NO-1)*sizeof(entry) , SEEK_SET);          // Ѱ��д���ļ���λ��
		   fwrite( &one , sizeof(entry) , 1 , fp );                  // д���ļ�
	   }
	fclose(fp);
	fclose(output_fp);
	}
}

void Get_input(buffer *Buffer_list)
{

		if(entry_type!='Q')
	   {
		   FILE *fp;
	       if((fp=fopen("entry.dat","r+b"))==NULL)
	      {
		       printf("���ܴ�Ŀ���ļ�entry.dat\n");
		       OFFWORK = 0 ;
	      }
	       rewind(fp);
	       entry one;
	       printf("��%d���¼���",entry_NO);
	       Get_entry();
	       fseek( fp , (entry_NO-1)*sizeof(one) , SEEK_SET );
	       fread(&one , sizeof(one) , 1 , fp);
	       entry_sec=one.sec;
	       //printf("one.sec=%d\n",one.sec);
	       entry_type=one.type;
	       //printf("one.type=%c\n",one.type);
	       switch(entry_type)
	      {
		       case 'C':{
		       	   
			        entry_mans = one.mans ;
			        //entry_mans = 1;
			        break;
		        }
		        case 'R':{
			        entry_check = one.check ;
			        entry_randtime = one.randtime ;
			        break;
		        }
		        case 'Q':{
			        printf("�°�\n");
			    break;
		        }
	      }
	      fclose(fp);
	        entry_NO++;
	    }
	OK=0;       //ÿ���ļ��¼�  ʱ���������һ��
	time_OK = 0;
	Entry_OK = 0;
} 
