
// ����ͨ������

#include "Control.h"

#include "common_sys.h"
#include "gereral_Data_variable.h"
 
void init_emergency() //��ʼ������ͨ�� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file\n'init_emergency");OFFWORK = 0;
	}
	printf("���ڿ�ʼ��������ͨ��\n");
	fprintf(fp,"%s\n","���ڿ�ʼ��������ͨ��\n");
	Emergency_window->Queue = (branch*)malloc(sizeof(branch));
	Emergency_window->Queue->next = NULL;
	Emergency_window->ServeLen = 0;
	Emergency_window->state = 0;
	Emergency_window->Current = 0;
	fclose(fp);
}

void Add_emergency(int NO) //������ͨ������ӳ˿� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("Add_emergency  can't open the file\n'");OFFWORK=0;
	}
	branch *ptr = Emergency_window->Queue;
	while(ptr->next)
	{
		ptr = ptr->next ;
	}
	Emergency_window->Current  = (end-start-interval)/CLOCKS_PER_SEC;
	branch *new_one = (branch*)malloc(sizeof(branch));
	new_one->next = NULL;
	new_one->NO = NO;
	new_one->dx = Speed;
	//new_one->dx = 10;
	new_one->dy = 0;
	new_one->Reach_Emergency = 0;  //�Ƿ��Ѿ��������ͨ���Ŷ� 
	new_one->y = 680 ;
	new_one->x = 140 ;
	printf("%d �ų˿ͽ������ͨ��\n",NO);
	fprintf(fp,"\n%d �ų˿ͽ������ͨ��\n",NO);
	new_one->CheckTime = 2+rand()%3;
	ptr->next = new_one ;
	ptr = new_one;
	ptr->next = NULL;
	fclose(fp);
}

void print_emergency()    //��ӡ����ͨ����Ϣ 
{
	branch *ptr = Emergency_window->Queue ;
	printf("*******************����ͨ��********************\n");
	printf("\t"); 
	while(ptr->next)
	{
		printf("%d ",ptr->next->NO);
		ptr = ptr->next ;
	}
	printf("\n***********************************************\n"); 
}

            
			 //�����ǻ����� 
void Add_passager(buffer *head,int count) //�ڻ�����ĩβ����³˿�
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file    Add_passager\n'");OFFWORK = 0;
	 }
	buffer *ptr = head;
	while(ptr->next)
	{
		ptr = ptr->next;//��������β 
	}
	int d = 0;
	while(count--)
	{
		buffer *new_one = (buffer*)malloc(sizeof(buffer));
		new_one->ID = initID ;
		new_one->Mouse_add = 0;
		new_one->x = 140-40*d ;
		//printf("  x   =   %d\n",new_one->x);
			d++ ;
		new_one->y = 640;
		new_one->dx = 0;
		new_one->dy = 0;
		new_one->next = NULL ;
		int stock=rand()%300;
		if(stock%20==0&&entry_type!='Q'&&entry_type!='q'&&new_one->ID>=10) //����͸����£���Ȼ��������ֱ�ӷ������ͨ�� ������ 
		{
			new_one->In_Emergency = 1 ;
			Add_emergency(new_one->ID);
		}
		else
		{
			printf("%d ���³˿ͽ����Ŷӻ�����\n",initID);
		    fprintf(fp,"\n%d ���³˿ͽ����Ŷӻ�����\n",initID);
			new_one->In_Emergency=0;
		    ptr->next = new_one;
		    ptr = new_one;
		}
		initID++;
	}
	ptr->next=NULL;  
	fclose(fp);
}


int lenth(buffer *head) //��ȡ���������鳤��
{
	buffer *ptr = head;
	int size = 0;
	while(ptr->next)
	{
		size++;
		ptr = ptr->next;
	}
	return size;
}

void print_ID(buffer *head)//��ӡ����������˿ͱ��
{
	if(entry_type!='Q'&&entry_type!='q')
	{
		FILE *fp;
	    if((fp=fopen("output.txt","a+"))==NULL)
	   {
		   printf("can't open the file\n'print_ID");OFFWORK = 0 ;
	   }
	    buffer *ptr = head;
	    printf("\n\n������������������������������ �Ŷӻ����� ������������������������������������\n"); 
	    if(lenth(head))
	    {
		    fprintf(fp,"����������Ϊ %d\n",lenth(head));
		    printf("\n\t\t\t��ǰ������ %d\n\n\t\t\t",lenth(head));
		    fprintf(fp,"\n%s","�Ŷӻ������ĳ˿�����  \t\t");
	    }
	    else  if(entry_type=='q'||entry_type=='Q') fprintf(fp,"\n%s","\n�������Ѿ����\n");
	    else  fprintf(fp,"\n%s","������û�г˿�\n");
	    while(ptr->next)
	   {
		    printf("%d\t",ptr->next->ID);
		    fprintf(fp,"%d\t",ptr->next->ID);
		    ptr = ptr->next;
	   }
	   fprintf(fp,"%s\n\n","\n");
	   printf("\n");  
	   fclose(fp);	
	   printf("��������������������������������������������������������������������������������\n"); 
	}
	
}


int deletehead(buffer *head)   //ɾ����������һ���ˣ����ر��
{
	if(lenth(head)==0)
	{
		printf("������û�г˿�\n");
		return initID;
	}
	else if(lenth(head)==1)
	   {
	   	  int NO = head->next->ID ;
	   	  head->next = NULL;
	   	  return NO;
	   }
	else
	{
		buffer *ptr=head->next;
	    buffer *q=ptr->next;
	    int NO = ptr->ID;
	    head->next = q;
	    free(ptr);
	    return NO;
	}
 }
 
 		//�����ǰ���� 
void *add_passager(branch *head,int NO,int window_ID)       //��	����ڶ���ĩβ�����µĳ˿�
{
	branch *ptr=head;
	int i = 1;
	while(ptr->next)
	{
		ptr=ptr->next;
		i++;
	}
	branch *s=(branch*)malloc(sizeof(branch));
	s->NO=NO;
	if(window_pattern=='B'||window_pattern=='b')
	{
		s->CheckTime = 9 +rand()%2;
	}
	else
	    s->CheckTime = 7 +rand()%2 ; //�涨�˿Ͱ����ʱ�� ���������ʱ��Ͱ�����˿�ɾ��
	s->CheckOver = 0 ;
	//s->y = 240+40*i ;  
	if(lenth(Buffer_list)<=MaxCustSingleLine)  //��һ�ſڳ� 
	{
		s->x = 100+40*MaxCustSingleLine ;
		s->y = 640 ;
	}
	if(lenth(Buffer_list)>MaxCustSingleLine && lenth(Buffer_list)<=2*MaxCustSingleLine)//�Ӷ��ſڳ� 
	{
		s->x = 140 ;
		s->y = 600 ;
	}
	if(lenth(Buffer_list)>2*MaxCustSingleLine && lenth(Buffer_list)<=3*MaxCustSingleLine) //�����ſڳ� 
	{
		s->x = 100 +40*MaxCustSingleLine ;
		s->y = 560 ;
	}
	if(lenth(Buffer_list)>3*MaxCustSingleLine && lenth(Buffer_list)<=4*MaxCustSingleLine)//���ĺſڳ� 
	{
		s->x = 140 ;
		s->y = 520 ;
	}
	s->dy = -Speed/2 ;
	s->dx = 0 ;
	s->which_NO = window_ID ;
	ptr->next=s;
	ptr=s;
	ptr->next=NULL;
}

void creat(window *head)       //���������
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file\n'   creat");OFFWORK=0;
	}
	printf("���ڿ�ʼ���������\n");
	fprintf(fp,"%s\n","���ڿ�ʼ���������\n");
	window *ptr=head;
	int initID=1;
	int num =MinCheck ;
	while(num--)
	{
		printf(" ��%d������ڴ����ɹ�!\n",initID);
		fprintf(fp," ��%d������ڴ����ɹ�!\n",initID);
		window *s=(window*)malloc(sizeof(window));   //����ڵ��ڴ� 
		s->Next=NULL;
		s->Queue=(branch*)malloc(sizeof(branch));  //����ڶ�����ڴ� 
		s->Queue->next=NULL;
		s->ID=initID;
		initID++;
		s->state = 0;
		s->Current = 0 ;
		s->ServeLen = 0;
		s->Rest_Len = 0;
		s->Begin_rest = 0;
		s->In_repair=0;
		s->Rest_Times = 0;
		ptr->Next=s;
		ptr=s;
		CurMaxWindow++;
	}
	fclose(fp);
	ptr->Next=NULL;
}

int Lenth(branch *head)   //��ȡ����ڶ��鳤��
{
	branch *ptr=head;
	int size=0;
	while(ptr->next)
	{
		size++;
		ptr=ptr->next;
	}
	return size;
}

void print_window(window *Head)    //��ӡ����ڵ���Ϣ
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file   print_window\n'");OFFWORK=0;
	}
	if((end-start-interval)/CLOCKS_PER_SEC>=0)
	printf("\t\t\t\t\n\nTime  =  %d s\n\n\n",(end-start-interval)/CLOCKS_PER_SEC);
	if(entry_type=='q'||entry_type=='Q'){
		printf("��ʼ�°�   ��������%d\n\n",Passager_flow);
	}else printf("��Ӫҵ�С�   ��������%d\n\n",Passager_flow);
	window *ptr=Head;
	while(ptr->Next)
	{
		if(ptr->Next->In_repair==0)
		{
			printf("�� %d �Ű���ڶ��� ��:  ",ptr->Next->ID); 
			if(ptr->Next->state==0)      printf("\t ���� \t  ");
			else if(ptr->Next->state==1) printf("\t������ \t  ");
			else if(ptr->Next->state==2) printf("\t�������  ");
			else if(ptr->Next->state==3) printf("\t ��Ϣ \t  "); 
			else if(ptr->Next->state==4) printf("\t �°� \t  "); 
			fprintf(fp,"\n%d �Ű����:\t",ptr->Next->ID);
			if(ptr->Next->state==0)fprintf(fp,"%s"," ���� ");else if(ptr->Next->state==1)fprintf(fp,"%s","������ ");else if(ptr->Next->state==2)fprintf(fp,"%s","�������");else if(ptr->Next->state==3)fprintf(fp,"%s"," ��Ϣ ");else if(ptr->Next->state==4)fprintf(fp,"%s"," �°� "); 
			fprintf(fp,"  �ŶӶ�������%d���˿�:\t\t",Lenth(ptr->Next->Queue));
		    branch *Que = ptr->Next->Queue;
		    while(Que->next)
	       {
			    printf("%d ",Que->next->NO);
		        fprintf(fp," %d ",Que->next->NO);
		        Que = Que->next ;
		   }
		    fprintf(fp,"%s\n","\n");
		    printf("\n\n");
		}
		ptr=ptr->Next;
	}
	fprintf(fp,"%s","\n");
	fclose(fp);
}

void Cycle_output()
{
	FILE *fp;
	if((fp=fopen("print_cycle.txt","a+"))==NULL)
	{
		printf("can't open the file\n'Cycle_output");OFFWORK = 0;
	}
	if((end-start-interval)/CLOCKS_PER_SEC>=0)
	fprintf(fp,"\t\t\t\t Time  =  %d s\n\n\n",(end-start-interval)/CLOCKS_PER_SEC);
	window *ptr=WINDOW;
	while(ptr->Next)
	{
		if(ptr->Next->In_repair==0)
		{
			fprintf(fp,"\n%d �Ű����:\t",ptr->Next->ID);
			if(ptr->Next->state==0)fprintf(fp,"%s"," ���� ");else if(ptr->Next->state==1)fprintf(fp,"%s","������ ");else if(ptr->Next->state==2)fprintf(fp,"%s","�������");else if(ptr->Next->state==3)fprintf(fp,"%s"," ��Ϣ ");else if(ptr->Next->state==4)fprintf(fp,"%s"," �°� "); 
			fprintf(fp,"  �ŶӶ�������%d���˿�:\t\t",Lenth(ptr->Next->Queue));
		    branch *Que = ptr->Next->Queue;
		    while(Que->next)
	       {
		        fprintf(fp," %d ",Que->next->NO);
		        Que = Que->next ;
		   }
		    fprintf(fp,"%s\n","\n");
		}
		ptr=ptr->Next;
	}
	if(lenth(Buffer_list))
	{
		fprintf(fp,"����������Ϊ %d\n",lenth(Buffer_list));
		fprintf(fp,"\n%s","�Ŷӻ������ĳ˿�����  \t\t");
	}
	else  if(entry_type=='q'||entry_type=='Q') fprintf(fp,"\n%s","\n�������Ѿ����\n");
	else  fprintf(fp,"\n%s","������û�г˿�\n");
	buffer *qtr = Buffer_list;
	while(qtr->next)
	{
		fprintf(fp,"%d\t",qtr->next->ID);
		qtr = qtr->next;
	}
	fprintf(fp,"%s\n\n\n","\n\n");
	fclose(fp);
}


void Add_window(window *head)
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file   Add_window\n'");OFFWORK = 0 ;
	}
	CurMaxWindow++;
	window *ptr = head ;
	int i = 1,Add_OK=1;
	while(ptr->Next)
	{
	    if(ptr->Next->Next!=NULL)   //����������ڵ���һ���ڵ㲻Ϊ��
	    {
	    	if(ptr->Next->Next->In_repair==1) //��һ�����������ά����
	    	{
	    		Add_OK = 0;            //���Ӱ����
	    		ptr->Next->Next->In_repair = 0;   //���´���������
	    		break;
			 }
		}
		ptr=ptr->Next;
		i++;
	}
	if(Add_OK==1)
	{
		window *New_window = (window*)malloc(sizeof(window));
	    New_window->Next = NULL;
	    New_window->Queue = (branch*)malloc(sizeof(branch));
	    New_window->Queue->next = NULL;
	    New_window->ID = i;
	    fprintf(fp,"���������� %d �Ű����\n",i);
	    New_window->state = 0;
	    New_window->Current = 0 ;
	    New_window->ServeLen = 0;
	    New_window->Rest_Len = 0;
	    New_window->Begin_rest = 0;
	    New_window->Rest_Times = 0;
	    New_window->In_repair = 0; //����ά��
	    ptr->Next = New_window ;
	    ptr = New_window ;
	    ptr->Next = NULL ;
	    fclose(fp);
	}
	fclose(fp);
}

void Delete_Passager(branch *head)
{
	if(Lenth(head)<=1)
	{
		head->next = NULL;
	}
	else
	{
		branch *ptr = head ;
		branch *FirstPassager = ptr->next ;//��һ���˿� 
		ptr->next = FirstPassager->next ;  //ɾ����һ���˿� 
		free(FirstPassager);
	}
}


void Allocate_Passager(branch *Que)  //�ٷ��� 
{
	printf("��������������������������������������������\n");
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file  �źŵ�\n'");OFFWORK = 0;
	}
	FILE *Fp;
	if((Fp=fopen("print_cycle.txt","a+"))==NULL)
	{
		printf("can't open the file   ʮ�ŵ�\n'");OFFWORK = 0;
	}
	int NO ;
	if(Lenth(Que)>1)  //�������ڶ��黹��2�������� 
	{
		int num = Lenth(Que)-1 ;
		while(num--)     //���·��� num�����˿� 
		{
			branch *qtr = Que ;
			while(qtr->next)
			{
				if(qtr->next->next==NULL)
				{
					NO = qtr->next->NO;
					qtr->next = NULL;
					break;
				}
				qtr = qtr->next ;  //һֱ��������β y
			}
			window *ptr = WINDOW ;  //��ʼ��������� 
		        while(ptr->Next)
		       {
			        if(ptr->Next->state!=3 && ptr->Next->state!=4 && ptr->Next->In_repair==0)      //������������ڷ�����
			       {
				        if(Lenth(ptr->Next->Queue)<=MaxCustCheck-1)     //����������ڵĶ��� �������ټ�һ����
			           {
			    	            add_passager(ptr->Next->Queue,NO,ptr->Next->ID);     //������˿Ͱ��ŵ� ��������
			    	            Passager_flow++;
			    	            printf("  ������������������������%d �ų˿��뿪���½��� %d �Ű���ڡ���������������������\n",NO,ptr->Next->ID);
			    	            fprintf(fp,"\n%d �ų˿����½��� %d �Ű�����ŶӶ���\n",NO,ptr->Next->ID);
			    	            fprintf(Fp,"\n%d �ų˿����½��� %d �Ű�����ŶӶ���\n",NO,ptr->Next->ID);
			    	            if(Lenth(ptr->Next->Queue)==1)
			                   {
				                    ptr->Next->Current = (end-start)/CLOCKS_PER_SEC ;//��ȡ�����ǡ�����˰����ʱ��
			                   }
							
				            break;
				        //�������ڲ��ȥһ���ˣ��͵ȴ���һ���˿ͣ�ÿ��ֻ��һ���˿ͣ���������ѭ��
				       }
				        else
				       {
					        ptr = ptr->Next ; // ����������Ȼ�ڷ����У����ǣ���������� ���Ͱѳ˿Ͳ嵽��һ�������
				       }
			        }
			        else
			       {
				        ptr = ptr->Next ;  //����������ڲ����Լ��ˣ��Ϳ���һ�������
			       }
		        }
		}
	}fclose(fp);fclose(Fp);	
}

void Update_window(window *WINDOW)   //���°���� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file   Update_window\n'");OFFWORK = 0;
	}
	if((entry_type=='R'||entry_type=='r') )
	{
		time_OK = 1 ;  //ֻ����һ�� 
		Rest_OK=0;
		int j = 1;
		window *ptr = WINDOW;
		while(ptr->Next && j!=entry_check)  //����Ѱ��Ҫ�رյİ���� 
		{
			j++;
			ptr = ptr->Next ;
		}
		if(ptr->Next)
		{
		    ptr->Next->Rest_Len += entry_randtime ;
		    ptr->Next->Begin_rest = entry_randtime ;//��������ڿ�ʼ�����ʱ�䣬ÿ��ѭ����һ
		    ptr->Next->state = 3;
		    ptr->Next->Rest_Times++;
		    fprintf(fp,"%d �Ű����������Ϣ %d s\n",entry_check,entry_randtime);
		    printf("\t\t%d �Ű�����Ѿ��ر�\n",ptr->Next->ID);
		    //Allocate_Passager(ptr->Next->Queue);
		}
	}
	else if(entry_type=='Q'||entry_type=='q')
	{
		window *ptr = WINDOW ;
		SIGN = 0 ;
		while(ptr->Next)
		{
			ptr->Next->state = 4 ;
			if(Lenth(ptr->Next->Queue)!=0)  //�����һ�����黹û���
			{
				SIGN = 1;  
			}
			ptr = ptr->Next ;
		}
		if(SIGN==0)
		{
			printf("��ʼ�°� OFFWORK = %d����\n",OFFWORK);
			OFFWORK = 0 ;
			printf("OFFWORK = %d\n",OFFWORK);
			printf("\n%s\n\t\t","����ڵĳ˿Ͷ��Ѿ��������,��ʽ�°࣡\n");
			fprintf(fp,"\n%s\n","����ڵĳ˿Ͷ��Ѿ��������,��ʽ�°࣡\n");
			window *Last_ptr = WINDOW ;
			while(Last_ptr->Next)
			{
				fprintf(fp,"\n%d �Ű���ڣ�",Last_ptr->Next->ID);
				fprintf(fp,"����ʱ�� = %d\t",Last_ptr->Next->ServeLen);
				fprintf(fp,"��Ϣʱ�� = %d\n",Last_ptr->Next->Rest_Len);
				Last_ptr = Last_ptr->Next ;
			}
			fprintf(fp,"����ͨ���ķ���ʱ�� ��%d\n",Emergency_window->ServeLen);
		}
	}
	fclose(fp);
}

void A_pattern(window *WINDOW,buffer *Buffer_list) //�ļ����� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file\nʮһ�ŵ�'");OFFWORK = 0;
	}
	FILE *Fp;
	if((Fp=fopen("print_cycle.txt","a+"))==NULL)
	{
		printf("can't open the file  ʮ���ŵ�\n'");OFFWORK = 0;
	}
	if((entry_type!='Q'&&entry_type!='q')&&lenth(Buffer_list)!=0&&(end-start)/CLOCKS_PER_SEC>1)  //���������û�ˣ���ֱ������whileѭ�� ���ȴ��������г˿��ټ���
	{
		//int allocate_num = 1+(rand()%(lenth(Buffer_list)))%4;
		int allocate_num;
		if(lenth(Buffer_list)<=2*MaxCustSingleLine)
		{
			allocate_num = 1+rand()%2 ;
		}
		else
		{
			allocate_num = 3+rand()%2 ;
		}
		
		while(allocate_num--)
		{
			int min=10;
		    //����ڷ��棬���ϴӻ���������ӳ˿�
				window *ptr = WINDOW ;
		        while(ptr->Next)
		       {
			        if(ptr->Next->state!=3 && ptr->Next->state!=4 && ptr->Next->In_repair==0)      //������������ڷ�����
			       {
				        if(Lenth(ptr->Next->Queue)<=MaxCustCheck-1)     //����������ڵĶ��� �������ټ�һ����
			           {
			           	    int len = lenth(Buffer_list);    
							int x,y;
			           	    if(len<=MaxCustSingleLine)
			           	    {
			           	    	x = 100+40*MaxCustSingleLine ;
			           	    	y = 640 ;
							}
							else if(len>MaxCustSingleLine&&len<=2*MaxCustSingleLine)
							{
								x = 140 ;
								y = 600 ;
							}
							else if(len>2*MaxCustSingleLine&&len<=3*MaxCustSingleLine)
							{
								x = 100 +40*MaxCustSingleLine;
								y = 560 ;
							}
							else if(len>3*MaxCustSingleLine&&len<=4*MaxCustSingleLine)
							{
								x = 140 ;
								y = 520 ;
							}
					        if(len!=0 && (Buffer_list->next->y<=y && abs(Buffer_list->next->x-x)<=40)&&(Buffer_list->next->x==x && Buffer_list->next->y == y)) //||
					        //if(len!=0 && ((Buffer_list->next->x==x && Buffer_list->next->y == y)||Buffer_list->next->y<y))
							{
					        	int newNO = deletehead(Buffer_list);    //�ӻ�������ó˿ͱ��
					        	
					        	
			    	            add_passager(ptr->Next->Queue,newNO,ptr->Next->ID);     //������˿Ͱ��ŵ� ��������
			    	            Passager_flow++;
			    	            printf("  %d �ų˿ͽ��� %d �Ű����\n",newNO,ptr->Next->ID);
			    	            fprintf(Fp,"\n%d �ų˿ͽ��� %d �Ű�����ŶӶ���\n",newNO,ptr->Next->ID);
			    	            fprintf(fp,"\n%d �ų˿ͽ��� %d �Ű�����ŶӶ���\n",newNO,ptr->Next->ID);
			    	            if(Lenth(ptr->Next->Queue)==1)
			                   {
				                    ptr->Next->Current = (end-start)/CLOCKS_PER_SEC ;//��ȡ�����ǡ�����˰����ʱ��
			                   }
							}
				            break;
				        //�������ڲ��ȥһ���ˣ��͵ȴ���һ���˿ͣ�ÿ��ֻ��һ���˿ͣ���������ѭ��
				       }
				        else
				       {
					        ptr = ptr->Next ; // ����������Ȼ�ڷ����У����ǣ���������� ���Ͱѳ˿Ͳ嵽��һ�������
				       }
			        }
			        else
			       {
				        ptr = ptr->Next ;  //����������ڲ����Լ��ˣ��Ϳ���һ�������
			       }
		        }
		}
	}
	fclose(fp);fclose(Fp);
}

void B_pattern(window *head,buffer *Buffer_list)   //�ֶ����� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file B_pattern\n'");OFFWORK = 0;
	}
	if(lenth(Buffer_list)==0&&(end-start)/CLOCKS_PER_SEC<=2)
	{
		printf("������û����\n");
		fprintf(fp,"%s\n","������û����\n");
	}
	else if(entry_type!='Q'&&entry_type!='q')
	{
		int allocate_num = 1+rand()%2;
		while(allocate_num--)
		{
				int min = 10 ;
		        window *again = head,*last = head;
	            while(again->Next)
	           {
	   	            if(Lenth(again->Next->Queue)<=min && again->Next->state!=3&&again->Next->state!=4&&again->Next->In_repair==0)
		           {
			           min = Lenth(again->Next->Queue); //Ѱ���������ٵ� ����� 
		           }
		            again = again->Next ;
	           }
	            while(last->Next)
	           {
	    	        if(min==Lenth(last->Next->Queue) && last->Next->state!=3&&last->Next->state!=4&&last->Next->In_repair==0)
	    	       {
	    		       break;    //ǡ���ҵ���һ���������ٵİ���� 
			       }
			       last = last->Next ;
		        }
		        if(last->Next&&Lenth(last->Next->Queue)<=MaxCustCheck-1)
		        {
		        	    int len = lenth(Buffer_list);    
							int x,y;
			           	    if(len<=MaxCustSingleLine)
			           	    {
			           	    	x = 100+40*MaxCustSingleLine ;
			           	    	y = 640 ;
							}
							else if(len>MaxCustSingleLine&&len<=2*MaxCustSingleLine)
							{
								x = 140 ;
								y = 600 ;
							}
							else if(len>2*MaxCustSingleLine&&len<=3*MaxCustSingleLine)
							{
								x = 100 +40*MaxCustSingleLine;
								y = 560 ;
							}
							else if(len>3*MaxCustSingleLine&&len<=4*MaxCustSingleLine)
							{
								x = 140 ;
								y = 520 ;
							}
					if(len!=0 && ((Buffer_list->next->x==x && Buffer_list->next->y == y)||(Buffer_list->next->y<=y && abs(Buffer_list->next->x-x)<=40))) //||
		   	        {
		   	        	int newNO = deletehead(Buffer_list);    //�ӻ�������ó˿ͱ��
		   	        	add_passager(last->Next->Queue,newNO,last->Next->ID);     //������˿Ͱ��ŵ� ��������
		   	        	Passager_flow++;
						fprintf(fp,"\n%d �ų˿ͽ��� %d �Ű�����ŶӶ���\n",newNO,last->Next->ID);
		                printf("  %d �ų˿ͽ��� %d �Ű����\n",newNO,last->Next->ID);
		                if(Lenth(last->Next->Queue)==1)
		               {
			               last->Next->Current = (end-start)/CLOCKS_PER_SEC ;//��ȡ�����ǡ�����˰����ʱ��
		               }
				    }
		        }
		}
	}
	fclose(fp);
}

void control_Window(window *WINDOW,buffer *Buffer_list)  //���ƴ��� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file control_Window\n'");OFFWORK = 0;
	}
	fprintf(fp," \n\n%d s ��ʱ��\n\n",(end-start-interval)/CLOCKS_PER_SEC);
	fclose(fp);
	
	Update_window(WINDOW);
	
	if(window_pattern=='A'||window_pattern=='a')
	{
		A_pattern(WINDOW,Buffer_list);
	}
	else if(window_pattern=='B'||window_pattern=='b')
	{
		B_pattern(WINDOW,Buffer_list);
	}
	
}

void control_Buffer(window *WINDOW,buffer *Buffer_list)  //�����Ŷӻ����� 
{
	//���������棬��������³˿�  ͬʱ����������ڵ�����
	if((entry_type=='Q'||entry_type=='q')&&Destroy_OK==0)     //����°࣬�Ͱ��Ŷӻ������˿�ɾ��
	{
		Destroy_OK++;
		//Buffer_list->next = NULL;
	}
	else if((entry_type=='C'||entry_type=='c'))
   {
		if(lenth(Buffer_list)+entry_mans<=MaxCustSingleLine*MaxLines)    //�����ǰ�����������Լ��� newcount ���˿�
		{
			if(OK==0)     //ѭ����ִֻ��һ��
			{
				
				Add_passager(Buffer_list,entry_mans); //�ڻ�����ĩβ����newcount���˿�
		
				if(lenth(Buffer_list)/CurMaxWindow>=MaxSeqLen && CurMaxWindow<=MaxCheck-1) ////�������̫�࣬������һ������ڣ�������࿪ 8�� �����
			   {
				    Add_window(WINDOW);
			   }
			    //if((end-start)/CLOCKS_PER_SEC>30 && lenth(Buffer_list)/CurMaxWindow<EasySeqLen && CurMaxWindow>MinCheck)  ////�����̫�٣��͡��ر�һ��������ڣ� ���ٱ����ĸ������
			   //printf("lenth(Buffer_list)=%d CurMaxWindow=%d EasySeqLen=%d MinCheck = %d\n",lenth(Buffer_list),CurMaxWindow,EasySeqLen,MinCheck);
			   if((end-start)/CLOCKS_PER_SEC>20 && lenth(Buffer_list)/CurMaxWindow<EasySeqLen && CurMaxWindow>MinCheck)
			   {
			   	    //printf("1�ŵ�����\n");
				    window *ptr = WINDOW ;
				    while(ptr->Next&&ptr->Next->In_repair==0) //������������ڽṹ
				   {
					   ptr = ptr->Next ;  //һֱ�ƶ�ָ�룬ֱ�����һ�����İ����
				   }
				    //printf("2�ŵ�����\n");
				    //printf("Inrepair = %d\n",ptr->In_repair);
				   if(Lenth(ptr->Queue)==0)
				   {
				   	    //printf("3�ŵ�����\n");
				   	    //printf("Inrepair = %d\n",ptr->In_repair);
				   	    if(ptr->In_repair==0)
				   	    {
				   	    	//printf("4�ŵ�����\n");
				   	    	//printf("%d �Ű����\n",ptr->ID);
				   	    	CurMaxWindow--; //��ǰ��������ڷ���İ���� ��һ */
				            ptr->In_repair = 1; //������������ά����
				            //printf("5�ŵ�����\n");
				   	        //printf("Inrepair = %d\n",ptr->In_repair);
						}
				       
				   }
			   }
				OK++;
			} //����if 
		}
		else
		{
			printf("�Ŷӻ������Ѿ����ˣ�\n"); //����Ӳ���������
		}
   }
}

void control_delete(window *WINDOW)   //���Ƴ˿͵�ɾ�� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file  control_delete\n");OFFWORK = 0;
	}
	//�������ⲿ����ɾ��������ĳ˿�
		end = clock();     //��ȡ��ǰʱ��
		window *Ptr = WINDOW ;
		while(Ptr->Next)
		{
			branch *Que = Ptr->Next->Queue ;
			if(Lenth(Que)!=0)
			{
			    //printf("%d �ų˿Ϳ�ʼ�����ʱ�� = %d\n",Que->next->NO,Ptr->Next->Current);
				//printf("����ʱ�� = %d\n",Que->next->CheckTime);
				if( Que->next->CheckTime <= ((end-start-interval) /CLOCKS_PER_SEC - Ptr->Next->Current) && Que->next->y==220)
				{
					printf("%d �Ű�������뿪�����\n",Que->next->NO);
					fprintf(fp,"\n %d s   %d �Ű�������뿪�����\n",(end-start-interval)/CLOCKS_PER_SEC,Que->next->NO);
					Ptr->Next->ServeLen += Que->next->CheckTime;
					Delete_Passager(Que);
					Ptr->Next->Current = (end-start-interval)/CLOCKS_PER_SEC ;
					branch *help = Ptr->Next->Queue ;
					while(help->next)
					{
						help->next->dy = -1 ;
						help = help->next ;
					}
				}
			}
			Ptr = Ptr->Next ;
		}
		fclose(fp);
}

void control_emergency() //���ƽ���ͨ���˿͵�ɾ�� 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file  control_emergency\n");OFFWORK = 0 ;
	}
	branch *ptr = Emergency_window->Queue ;
	if(Lenth(Emergency_window->Queue))
	{
		if(ptr->next->Reach_Emergency==1 && ptr->next->y<=160 && ptr->next->CheckTime <= ((end-start-interval) /CLOCKS_PER_SEC - Emergency_window->Current))
		{
			Emergency_window->Current = (end-start-interval)/CLOCKS_PER_SEC;
			Emergency_window->ServeLen += ptr->next->CheckTime ;
			printf("\n%d �ų˿ͽ��������뿪����������\n",ptr->next->NO);
			fprintf(fp,"%d �ų˿ͽ��������뿪����������\n",ptr->next->NO);
			Delete_Passager(Emergency_window->Queue);
		}
	}
	fclose(fp);
}

void control(window *WINDOW,buffer *Buffer_list)  //�������ƽṹ�������� 
{
	end = clock();
	control_Window(WINDOW,Buffer_list); //���ư���ںͰ���ڶ��� 

	control_Buffer(WINDOW,Buffer_list);  //�����Ŷӻ����� 

	control_delete(WINDOW);           //���ư�������ĳ˿� ɾ�� 
	
	control_emergency();   //���ƽ���ͨ�� 
}

void print_message(window *WINDOW,buffer *Buffer_list)
{
	print_window(WINDOW);
	print_emergency();
	print_ID(Buffer_list);
	printf("\n\n\n");
	//Sleep(998);
	Cycle_output();
	//system("cls");
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file  print_message\n'");
	}
	if(entry_type!='Q'&&entry_type!='q'){
		fprintf(fp,"\n%s\n","��ǰ���� Y\n");
	}else{
		fprintf(fp,"\n%s\n","������°� N\n");;
	}
	fclose(fp);
}
void countLen(window *WINDOW)
{
	window *ptr = WINDOW ;
	printf("\n\n\n\n\n");
	while(ptr->Next)
	{
		printf("\t\t%d�Ű���� �ѷ���ʱ�� = %d\t����Ϣʱ�� = %d\n",ptr->Next->ID,ptr->Next->ServeLen,ptr->Next->Rest_Len);
		ptr = ptr->Next ;
	}
	printf("\n\n\t\t����ͨ������ʱ�� = %d\n",Emergency_window->ServeLen);
}

void Finish()
{
	system("cls");
	printf("\n\n\n\n\n\n\t\t^* _ *^ллʹ�û��������ģ��ϵͳ^* _ *^\n");Sleep(1000);
	system("cls");
	countLen(WINDOW);
	//print_heart();
	Sleep(10000);
}



