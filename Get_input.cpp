// 输入方面
#include"Get_input.h"
#include "common_sys.h"
#include "gereral_Data_variable.h"
#include "Control.h"
char Get_type() //获取事件类型 
{
	int type = 1+rand()%300;
	if((end-start)/CLOCKS_PER_SEC>=240||(type%30==0&&((end-start)/CLOCKS_PER_SEC>180))) //控制事件概率
	    return 'Q';        // 下班
	else if(type%20==0&&((end-start)/CLOCKS_PER_SEC)>20)
	    return 'R';        //安检口申请暂停
	else
	    return 'C';        //乘客到达
}

int trypossion() //泊松分布模拟随机到达人数
{
  double u = U_Random();
  int p = possion();
  return p;

}

int possion()
{
    int Lambda = 3, k = 0;
    long double p = 1.0;
    long double l=exp(-Lambda); //exp（）求e的次方的
    while (p>=l)
    {
        double u = U_Random();
        p *= u;
        k++;
    }
    return k-1;
}

double U_Random()  //u是一个小于1的随机的数
{
  double f;
  f = (float)(rand() % 100);

  return f/100;
}


void Get_entry()  //获取一个事件
{
	if(entry_type!='Q'&&entry_type!='q')
	{
		FILE *fp,*output_fp;
	    if((fp=fopen("entry.dat","a+b"))==NULL||(output_fp=fopen("output.txt","a+"))==NULL)
	   {
		   printf("can't open the file——entry_dat!\n");
		   OFFWORK = 0 ;
	   }
	    else
	   {
		   entry one={0,0,' ',0,0,0};                //初始化
		   one.NO = entry_NO ;                       //事件的序号
		   one.sec = rand()%2+ 2;          //随机生成事件的发生时间
		   one.type = Get_type();                    //随即获取事件类型，下班，暂停，有乘客到来
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
				    fprintf(output_fp,"\n%d 名新乘客进入排队缓冲区\n",one.mans);
				    break;
			    }
			    case 'R':{
				    one.check = 1+rand()%CurMaxWindow ;
				    while(one.check==entry_check)
				    {
				    	one.check = 1+rand()%CurMaxWindow ;//避免同时休息这个安检口 
					}
			        one.randtime = 30+rand()%20 ;
			        printf("%d 号安检口申请休息 %d s\n",one.check,one.randtime);
			        fprintf(output_fp,"\n%d 号安检口申请休息 %d s\n",one.check,one.randtime);
				    break;
			    }
			    case 'Q':{
				    printf("下班时间到!\n");
				    fprintf(output_fp,"\n\n%s\n","下班时间到!\n");
				    break;
			    }
			    default:break;
		  }
		   fseek(fp , (one.NO-1)*sizeof(entry) , SEEK_SET);          // 寻找写入文件的位置
		   fwrite( &one , sizeof(entry) , 1 , fp );                  // 写入文件
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
		       printf("不能打开目标文件entry.dat\n");
		       OFFWORK = 0 ;
	      }
	       rewind(fp);
	       entry one;
	       printf("第%d条事件：",entry_NO);
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
			        printf("下班\n");
			    break;
		        }
	      }
	      fclose(fp);
	        entry_NO++;
	    }
	OK=0;       //每次文件事件  时间操作仅仅一次
	time_OK = 0;
	Entry_OK = 0;
} 
