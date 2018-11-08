
// 紧急通道操作

#include "Control.h"

#include "common_sys.h"
#include "gereral_Data_variable.h"
 
void init_emergency() //初始化紧急通道 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file\n'init_emergency");OFFWORK = 0;
	}
	printf("现在开始建立紧急通道\n");
	fprintf(fp,"%s\n","现在开始建立紧急通道\n");
	Emergency_window->Queue = (branch*)malloc(sizeof(branch));
	Emergency_window->Queue->next = NULL;
	Emergency_window->ServeLen = 0;
	Emergency_window->state = 0;
	Emergency_window->Current = 0;
	fclose(fp);
}

void Add_emergency(int NO) //往紧急通道中添加乘客 
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
	new_one->Reach_Emergency = 0;  //是否已经进入紧急通道排队 
	new_one->y = 680 ;
	new_one->x = 140 ;
	printf("%d 号乘客进入紧急通道\n",NO);
	fprintf(fp,"\n%d 号乘客进入紧急通道\n",NO);
	new_one->CheckTime = 2+rand()%3;
	ptr->next = new_one ;
	ptr = new_one;
	ptr->next = NULL;
	fclose(fp);
}

void print_emergency()    //打印紧急通道信息 
{
	branch *ptr = Emergency_window->Queue ;
	printf("*******************紧急通道********************\n");
	printf("\t"); 
	while(ptr->next)
	{
		printf("%d ",ptr->next->NO);
		ptr = ptr->next ;
	}
	printf("\n***********************************************\n"); 
}

            
			 //以下是缓冲区 
void Add_passager(buffer *head,int count) //在缓冲区末尾添加新乘客
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file    Add_passager\n'");OFFWORK = 0;
	 }
	buffer *ptr = head;
	while(ptr->next)
	{
		ptr = ptr->next;//遍历到队尾 
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
		if(stock%20==0&&entry_type!='Q'&&entry_type!='q'&&new_one->ID>=10) //如果低概率下，仍然紧急，就直接放入紧急通道 ，安检 
		{
			new_one->In_Emergency = 1 ;
			Add_emergency(new_one->ID);
		}
		else
		{
			printf("%d 号新乘客进入排队缓冲区\n",initID);
		    fprintf(fp,"\n%d 号新乘客进入排队缓冲区\n",initID);
			new_one->In_Emergency=0;
		    ptr->next = new_one;
		    ptr = new_one;
		}
		initID++;
	}
	ptr->next=NULL;  
	fclose(fp);
}


int lenth(buffer *head) //获取缓冲区队伍长度
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

void print_ID(buffer *head)//打印缓冲区队伍乘客编号
{
	if(entry_type!='Q'&&entry_type!='q')
	{
		FILE *fp;
	    if((fp=fopen("output.txt","a+"))==NULL)
	   {
		   printf("can't open the file\n'print_ID");OFFWORK = 0 ;
	   }
	    buffer *ptr = head;
	    printf("\n\n——————————————— 排队缓冲区 ——————————————————\n"); 
	    if(lenth(head))
	    {
		    fprintf(fp,"缓冲区人数为 %d\n",lenth(head));
		    printf("\n\t\t\t当前人数： %d\n\n\t\t\t",lenth(head));
		    fprintf(fp,"\n%s","排队缓冲区的乘客如下  \t\t");
	    }
	    else  if(entry_type=='q'||entry_type=='Q') fprintf(fp,"\n%s","\n缓冲区已经封闭\n");
	    else  fprintf(fp,"\n%s","缓冲区没有乘客\n");
	    while(ptr->next)
	   {
		    printf("%d\t",ptr->next->ID);
		    fprintf(fp,"%d\t",ptr->next->ID);
		    ptr = ptr->next;
	   }
	   fprintf(fp,"%s\n\n","\n");
	   printf("\n");  
	   fclose(fp);	
	   printf("————————————————————————————————————————\n"); 
	}
	
}


int deletehead(buffer *head)   //删除缓冲区第一个人，返回编号
{
	if(lenth(head)==0)
	{
		printf("缓冲区没有乘客\n");
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
 
 		//以下是安检口 
void *add_passager(branch *head,int NO,int window_ID)       //在	安检口队伍末尾插入新的乘客
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
	    s->CheckTime = 7 +rand()%2 ; //规定乘客安检的时间 ，超出这个时间就把这个乘客删掉
	s->CheckOver = 0 ;
	//s->y = 240+40*i ;  
	if(lenth(Buffer_list)<=MaxCustSingleLine)  //从一号口出 
	{
		s->x = 100+40*MaxCustSingleLine ;
		s->y = 640 ;
	}
	if(lenth(Buffer_list)>MaxCustSingleLine && lenth(Buffer_list)<=2*MaxCustSingleLine)//从二号口出 
	{
		s->x = 140 ;
		s->y = 600 ;
	}
	if(lenth(Buffer_list)>2*MaxCustSingleLine && lenth(Buffer_list)<=3*MaxCustSingleLine) //从三号口出 
	{
		s->x = 100 +40*MaxCustSingleLine ;
		s->y = 560 ;
	}
	if(lenth(Buffer_list)>3*MaxCustSingleLine && lenth(Buffer_list)<=4*MaxCustSingleLine)//从四号口出 
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

void creat(window *head)       //创建安检口
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file\n'   creat");OFFWORK=0;
	}
	printf("现在开始建立安检口\n");
	fprintf(fp,"%s\n","现在开始建立安检口\n");
	window *ptr=head;
	int initID=1;
	int num =MinCheck ;
	while(num--)
	{
		printf(" 第%d个安检口创建成功!\n",initID);
		fprintf(fp," 第%d个安检口创建成功!\n",initID);
		window *s=(window*)malloc(sizeof(window));   //安检口的内存 
		s->Next=NULL;
		s->Queue=(branch*)malloc(sizeof(branch));  //安检口队伍的内存 
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

int Lenth(branch *head)   //获取安检口队伍长度
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

void print_window(window *Head)    //打印安检口的信息
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file   print_window\n'");OFFWORK=0;
	}
	if((end-start-interval)/CLOCKS_PER_SEC>=0)
	printf("\t\t\t\t\n\nTime  =  %d s\n\n\n",(end-start-interval)/CLOCKS_PER_SEC);
	if(entry_type=='q'||entry_type=='Q'){
		printf("开始下班   客流量：%d\n\n",Passager_flow);
	}else printf("【营业中】   客流量：%d\n\n",Passager_flow);
	window *ptr=Head;
	while(ptr->Next)
	{
		if(ptr->Next->In_repair==0)
		{
			printf("【 %d 号安检口队伍 】:  ",ptr->Next->ID); 
			if(ptr->Next->state==0)      printf("\t 空闲 \t  ");
			else if(ptr->Next->state==1) printf("\t安检中 \t  ");
			else if(ptr->Next->state==2) printf("\t安检结束  ");
			else if(ptr->Next->state==3) printf("\t 休息 \t  "); 
			else if(ptr->Next->state==4) printf("\t 下班 \t  "); 
			fprintf(fp,"\n%d 号安检口:\t",ptr->Next->ID);
			if(ptr->Next->state==0)fprintf(fp,"%s"," 空闲 ");else if(ptr->Next->state==1)fprintf(fp,"%s","安检中 ");else if(ptr->Next->state==2)fprintf(fp,"%s","安检结束");else if(ptr->Next->state==3)fprintf(fp,"%s"," 休息 ");else if(ptr->Next->state==4)fprintf(fp,"%s"," 下班 "); 
			fprintf(fp,"  排队队伍中有%d名乘客:\t\t",Lenth(ptr->Next->Queue));
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
			fprintf(fp,"\n%d 号安检口:\t",ptr->Next->ID);
			if(ptr->Next->state==0)fprintf(fp,"%s"," 空闲 ");else if(ptr->Next->state==1)fprintf(fp,"%s","安检中 ");else if(ptr->Next->state==2)fprintf(fp,"%s","安检结束");else if(ptr->Next->state==3)fprintf(fp,"%s"," 休息 ");else if(ptr->Next->state==4)fprintf(fp,"%s"," 下班 "); 
			fprintf(fp,"  排队队伍中有%d名乘客:\t\t",Lenth(ptr->Next->Queue));
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
		fprintf(fp,"缓冲区人数为 %d\n",lenth(Buffer_list));
		fprintf(fp,"\n%s","排队缓冲区的乘客如下  \t\t");
	}
	else  if(entry_type=='q'||entry_type=='Q') fprintf(fp,"\n%s","\n缓冲区已经封闭\n");
	else  fprintf(fp,"\n%s","缓冲区没有乘客\n");
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
	    if(ptr->Next->Next!=NULL)   //如果这个安检口的下一个节点不为空
	    {
	    	if(ptr->Next->Next->In_repair==1) //下一个安检口正在维修中
	    	{
	    		Add_OK = 0;            //不加安检口
	    		ptr->Next->Next->In_repair = 0;   //重新打开这个安检口
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
	    fprintf(fp,"现在新增开 %d 号安检口\n",i);
	    New_window->state = 0;
	    New_window->Current = 0 ;
	    New_window->ServeLen = 0;
	    New_window->Rest_Len = 0;
	    New_window->Begin_rest = 0;
	    New_window->Rest_Times = 0;
	    New_window->In_repair = 0; //正在维修
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
		branch *FirstPassager = ptr->next ;//第一个乘客 
		ptr->next = FirstPassager->next ;  //删除第一个乘客 
		free(FirstPassager);
	}
}


void Allocate_Passager(branch *Que)  //再分配 
{
	printf("——————————————————————\n");
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file  九号点\n'");OFFWORK = 0;
	}
	FILE *Fp;
	if((Fp=fopen("print_cycle.txt","a+"))==NULL)
	{
		printf("can't open the file   十号点\n'");OFFWORK = 0;
	}
	int NO ;
	if(Lenth(Que)>1)  //如果安检口队伍还有2个人以上 
	{
		int num = Lenth(Que)-1 ;
		while(num--)     //重新分配 num　个乘客 
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
				qtr = qtr->next ;  //一直遍历到队尾 y
			}
			window *ptr = WINDOW ;  //开始遍历安检口 
		        while(ptr->Next)
		       {
			        if(ptr->Next->state!=3 && ptr->Next->state!=4 && ptr->Next->In_repair==0)      //如果这个安检口在服务中
			       {
				        if(Lenth(ptr->Next->Queue)<=MaxCustCheck-1)     //如果这个安检口的队伍 还可以再加一个人
			           {
			    	            add_passager(ptr->Next->Queue,NO,ptr->Next->ID);     //把这个乘客安排到 这个安检口
			    	            Passager_flow++;
			    	            printf("  ————————————%d 号乘客离开重新进入 %d 号安检口———————————\n",NO,ptr->Next->ID);
			    	            fprintf(fp,"\n%d 号乘客重新进入 %d 号安检口排队队伍\n",NO,ptr->Next->ID);
			    	            fprintf(Fp,"\n%d 号乘客重新进入 %d 号安检口排队队伍\n",NO,ptr->Next->ID);
			    	            if(Lenth(ptr->Next->Queue)==1)
			                   {
				                    ptr->Next->Current = (end-start)/CLOCKS_PER_SEC ;//获取安检口恰好有人安检的时间
			                   }
							
				            break;
				        //这个安检口插进去一个人，就等待下一个乘客，每次只进一个乘客，所以跳出循环
				       }
				        else
				       {
					        ptr = ptr->Next ; // 这个安检口虽然在服务中，但是，安检口满了 ，就把乘客插到下一个安检口
				       }
			        }
			        else
			       {
				        ptr = ptr->Next ;  //如果这个安检口不可以加人，就看下一个安检口
			       }
		        }
		}
	}fclose(fp);fclose(Fp);	
}

void Update_window(window *WINDOW)   //更新安检口 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file   Update_window\n'");OFFWORK = 0;
	}
	if((entry_type=='R'||entry_type=='r') )
	{
		time_OK = 1 ;  //只操作一次 
		Rest_OK=0;
		int j = 1;
		window *ptr = WINDOW;
		while(ptr->Next && j!=entry_check)  //遍历寻找要关闭的安检口 
		{
			j++;
			ptr = ptr->Next ;
		}
		if(ptr->Next)
		{
		    ptr->Next->Rest_Len += entry_randtime ;
		    ptr->Next->Begin_rest = entry_randtime ;//保留安检口开始安检的时间，每个循环减一
		    ptr->Next->state = 3;
		    ptr->Next->Rest_Times++;
		    fprintf(fp,"%d 号安检口申请休息 %d s\n",entry_check,entry_randtime);
		    printf("\t\t%d 号安检口已经关闭\n",ptr->Next->ID);
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
			if(Lenth(ptr->Next->Queue)!=0)  //如果有一个队伍还没清空
			{
				SIGN = 1;  
			}
			ptr = ptr->Next ;
		}
		if(SIGN==0)
		{
			printf("开始下班 OFFWORK = %d正常\n",OFFWORK);
			OFFWORK = 0 ;
			printf("OFFWORK = %d\n",OFFWORK);
			printf("\n%s\n\t\t","安检口的乘客都已经处理完毕,正式下班！\n");
			fprintf(fp,"\n%s\n","安检口的乘客都已经处理完毕,正式下班！\n");
			window *Last_ptr = WINDOW ;
			while(Last_ptr->Next)
			{
				fprintf(fp,"\n%d 号安检口：",Last_ptr->Next->ID);
				fprintf(fp,"服务时长 = %d\t",Last_ptr->Next->ServeLen);
				fprintf(fp,"休息时长 = %d\n",Last_ptr->Next->Rest_Len);
				Last_ptr = Last_ptr->Next ;
			}
			fprintf(fp,"紧急通道的服务时长 是%d\n",Emergency_window->ServeLen);
		}
	}
	fclose(fp);
}

void A_pattern(window *WINDOW,buffer *Buffer_list) //文件输入 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file\n十一号点'");OFFWORK = 0;
	}
	FILE *Fp;
	if((Fp=fopen("print_cycle.txt","a+"))==NULL)
	{
		printf("can't open the file  十二号点\n'");OFFWORK = 0;
	}
	if((entry_type!='Q'&&entry_type!='q')&&lenth(Buffer_list)!=0&&(end-start)/CLOCKS_PER_SEC>1)  //如果缓冲区没人，就直接跳出while循环 ，等待缓冲区有乘客再继续
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
		    //安检口方面，不断从缓冲区中添加乘客
				window *ptr = WINDOW ;
		        while(ptr->Next)
		       {
			        if(ptr->Next->state!=3 && ptr->Next->state!=4 && ptr->Next->In_repair==0)      //如果这个安检口在服务中
			       {
				        if(Lenth(ptr->Next->Queue)<=MaxCustCheck-1)     //如果这个安检口的队伍 还可以再加一个人
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
					        	int newNO = deletehead(Buffer_list);    //从缓冲区获得乘客编号
					        	
					        	
			    	            add_passager(ptr->Next->Queue,newNO,ptr->Next->ID);     //把这个乘客安排到 这个安检口
			    	            Passager_flow++;
			    	            printf("  %d 号乘客进入 %d 号安检口\n",newNO,ptr->Next->ID);
			    	            fprintf(Fp,"\n%d 号乘客进入 %d 号安检口排队队伍\n",newNO,ptr->Next->ID);
			    	            fprintf(fp,"\n%d 号乘客进入 %d 号安检口排队队伍\n",newNO,ptr->Next->ID);
			    	            if(Lenth(ptr->Next->Queue)==1)
			                   {
				                    ptr->Next->Current = (end-start)/CLOCKS_PER_SEC ;//获取安检口恰好有人安检的时间
			                   }
							}
				            break;
				        //这个安检口插进去一个人，就等待下一个乘客，每次只进一个乘客，所以跳出循环
				       }
				        else
				       {
					        ptr = ptr->Next ; // 这个安检口虽然在服务中，但是，安检口满了 ，就把乘客插到下一个安检口
				       }
			        }
			        else
			       {
				        ptr = ptr->Next ;  //如果这个安检口不可以加人，就看下一个安检口
			       }
		        }
		}
	}
	fclose(fp);fclose(Fp);
}

void B_pattern(window *head,buffer *Buffer_list)   //手动输入 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file B_pattern\n'");OFFWORK = 0;
	}
	if(lenth(Buffer_list)==0&&(end-start)/CLOCKS_PER_SEC<=2)
	{
		printf("缓冲区没有人\n");
		fprintf(fp,"%s\n","缓冲区没有人\n");
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
			           min = Lenth(again->Next->Queue); //寻找人数最少的 安检口 
		           }
		            again = again->Next ;
	           }
	            while(last->Next)
	           {
	    	        if(min==Lenth(last->Next->Queue) && last->Next->state!=3&&last->Next->state!=4&&last->Next->In_repair==0)
	    	       {
	    		       break;    //恰好找到第一个人数最少的安检口 
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
		   	        	int newNO = deletehead(Buffer_list);    //从缓冲区获得乘客编号
		   	        	add_passager(last->Next->Queue,newNO,last->Next->ID);     //把这个乘客安排到 这个安检口
		   	        	Passager_flow++;
						fprintf(fp,"\n%d 号乘客进入 %d 号安检口排队队伍\n",newNO,last->Next->ID);
		                printf("  %d 号乘客进入 %d 号安检口\n",newNO,last->Next->ID);
		                if(Lenth(last->Next->Queue)==1)
		               {
			               last->Next->Current = (end-start)/CLOCKS_PER_SEC ;//获取安检口恰好有人安检的时间
		               }
				    }
		        }
		}
	}
	fclose(fp);
}

void control_Window(window *WINDOW,buffer *Buffer_list)  //控制窗口 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file control_Window\n'");OFFWORK = 0;
	}
	fprintf(fp," \n\n%d s 的时候\n\n",(end-start-interval)/CLOCKS_PER_SEC);
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

void control_Buffer(window *WINDOW,buffer *Buffer_list)  //控制排队缓冲区 
{
	//缓冲区方面，不断添加新乘客  同时，决定安检口的数量
	if((entry_type=='Q'||entry_type=='q')&&Destroy_OK==0)     //如果下班，就把排队缓冲区乘客删除
	{
		Destroy_OK++;
		//Buffer_list->next = NULL;
	}
	else if((entry_type=='C'||entry_type=='c'))
   {
		if(lenth(Buffer_list)+entry_mans<=MaxCustSingleLine*MaxLines)    //如果当前缓冲区还可以加入 newcount 个乘客
		{
			if(OK==0)     //循环中只执行一次
			{
				
				Add_passager(Buffer_list,entry_mans); //在缓冲区末尾加入newcount个乘客
		
				if(lenth(Buffer_list)/CurMaxWindow>=MaxSeqLen && CurMaxWindow<=MaxCheck-1) ////，如果人太多，就增开一个安检口，但是最多开 8个 安检口
			   {
				    Add_window(WINDOW);
			   }
			    //if((end-start)/CLOCKS_PER_SEC>30 && lenth(Buffer_list)/CurMaxWindow<EasySeqLen && CurMaxWindow>MinCheck)  ////如果人太少，就“关闭一个”安检口， 至少保留四个安检口
			   //printf("lenth(Buffer_list)=%d CurMaxWindow=%d EasySeqLen=%d MinCheck = %d\n",lenth(Buffer_list),CurMaxWindow,EasySeqLen,MinCheck);
			   if((end-start)/CLOCKS_PER_SEC>20 && lenth(Buffer_list)/CurMaxWindow<EasySeqLen && CurMaxWindow>MinCheck)
			   {
			   	    //printf("1号点正常\n");
				    window *ptr = WINDOW ;
				    while(ptr->Next&&ptr->Next->In_repair==0) //遍历整个安检口结构
				   {
					   ptr = ptr->Next ;  //一直移动指针，直到最后一个开的安检口
				   }
				    //printf("2号点正常\n");
				    //printf("Inrepair = %d\n",ptr->In_repair);
				   if(Lenth(ptr->Queue)==0)
				   {
				   	    //printf("3号点正常\n");
				   	    //printf("Inrepair = %d\n",ptr->In_repair);
				   	    if(ptr->In_repair==0)
				   	    {
				   	    	//printf("4号点正常\n");
				   	    	//printf("%d 号安检口\n",ptr->ID);
				   	    	CurMaxWindow--; //当前最大编号仍在服务的安检口 减一 */
				            ptr->In_repair = 1; //这个安检口正在维修中
				            //printf("5号点正常\n");
				   	        //printf("Inrepair = %d\n",ptr->In_repair);
						}
				       
				   }
			   }
				OK++;
			} //结束if 
		}
		else
		{
			printf("排队缓冲区已经满了！\n"); //如果加不进缓冲区
		}
   }
}

void control_delete(window *WINDOW)   //控制乘客的删除 
{
	FILE *fp;
	if((fp=fopen("output.txt","a+"))==NULL)
	{
		printf("can't open the file  control_delete\n");OFFWORK = 0;
	}
	//接下来这部分是删除安检完的乘客
		end = clock();     //获取当前时间
		window *Ptr = WINDOW ;
		while(Ptr->Next)
		{
			branch *Que = Ptr->Next->Queue ;
			if(Lenth(Que)!=0)
			{
			    //printf("%d 号乘客开始安检的时间 = %d\n",Que->next->NO,Ptr->Next->Current);
				//printf("安检时间 = %d\n",Que->next->CheckTime);
				if( Que->next->CheckTime <= ((end-start-interval) /CLOCKS_PER_SEC - Ptr->Next->Current) && Que->next->y==220)
				{
					printf("%d 号安检结束离开安检口\n",Que->next->NO);
					fprintf(fp,"\n %d s   %d 号安检结束离开安检口\n",(end-start-interval)/CLOCKS_PER_SEC,Que->next->NO);
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

void control_emergency() //控制紧急通道乘客的删除 
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
			printf("\n%d 号乘客结束安检离开紧急缓冲区\n",ptr->next->NO);
			fprintf(fp,"%d 号乘客结束安检离开紧急缓冲区\n",ptr->next->NO);
			Delete_Passager(Emergency_window->Queue);
		}
	}
	fclose(fp);
}

void control(window *WINDOW,buffer *Buffer_list)  //整个控制结构的整体框架 
{
	end = clock();
	control_Window(WINDOW,Buffer_list); //控制安检口和安检口队伍 

	control_Buffer(WINDOW,Buffer_list);  //控制排队缓冲区 

	control_delete(WINDOW);           //控制安检结束的乘客 删除 
	
	control_emergency();   //控制紧急通道 
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
		fprintf(fp,"\n%s\n","当前机场 Y\n");
	}else{
		fprintf(fp,"\n%s\n","安检口下班 N\n");;
	}
	fclose(fp);
}
void countLen(window *WINDOW)
{
	window *ptr = WINDOW ;
	printf("\n\n\n\n\n");
	while(ptr->Next)
	{
		printf("\t\t%d号安检口 已服务时长 = %d\t已休息时长 = %d\n",ptr->Next->ID,ptr->Next->ServeLen,ptr->Next->Rest_Len);
		ptr = ptr->Next ;
	}
	printf("\n\n\t\t紧急通道服务时长 = %d\n",Emergency_window->ServeLen);
}

void Finish()
{
	system("cls");
	printf("\n\n\n\n\n\n\t\t^* _ *^谢谢使用机场安检口模拟系统^* _ *^\n");Sleep(1000);
	system("cls");
	countLen(WINDOW);
	//print_heart();
	Sleep(10000);
}



