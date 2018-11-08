//state_trans.c


// 自动机转化模型 


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
			case 0:{                  //空闲
				if(entry_type=='Q'||entry_type=='q')                  //收到下班指令
				{
					ptr->Next->state = 4 ;
				}
				else if((entry_type=='C'||entry_type=='c')&&Lenth(ptr->Next->Queue))  //有乘客到来
				{
					ptr->Next->state = 1 ;
				}
				
				break;
			}
			case 1:{                  //正在安检中
				if(entry_type=='Q'||entry_type=='q')
				{
					ptr->Next->state = 4 ;            //收到下班指令
				}
				else if((end-start)/CLOCKS_PER_SEC==ptr->Next->Current)//安检结束 
				{
					ptr->Next->state = 2 ;
				}
				break;                       
			}
			case 2:{                 //安检结束
				if(entry_type=='Q'||entry_type=='q')
				{
					ptr->Next->state = 4 ;      //收到下班指令
				}
				else if(ptr->Next->state==3)
				{                               //收到休息指令
					ptr->Next->state = 3 ;                     //ptr->Next->flag = 0 ;
				}
				else if(Lenth(ptr->Next->Queue)!=0)        //有乘客到来
				{
					ptr->Next->state = 1 ;
				}
				else{
					ptr->Next->state = 0;
			    }
				break;
			}
			case 3:{
				if(entry_type=='Q'||entry_type=='q')                 //收到下班指令
				{
					ptr->Next->state = 4 ;
				}
				printf("\n%d s 后 %d号安检口休息结束\n",ptr->Next->Begin_rest,ptr->Next->ID);
				ptr->Next->Begin_rest--;
				if(ptr->Next->Begin_rest==0)          //休息时间到 
				{
					fprintf(fp,"\n%d号安检口休息结束\n",ptr->Next->Begin_rest);
					printf("\n%d号安检口休息结束\n",ptr->Next->Begin_rest);
					if(Lenth(Que)==0)
					{
						ptr->Next->state = 0 ;   //注意时间只能加一次......注意状态会转变，所以只会加一次
						ptr->Next->Rest_Len +=entry_sec ; //如果休息时间内可以安检完剩余的乘客，加上休息的时间
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
