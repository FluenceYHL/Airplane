#include"General_Data.h"   //�������� 
#include"init.h"           //��ʼ�� 
#include"Thread.h"
#include"Control.h"
#include"Get_input.h"
#include"state_trans.h"
#include "gereral_Data_variable.h"
#include "Make_cartoon.h"
#include "Cartoon.h"

int main()
{
    initgraph(1000,750);
	//system("mode con cols=80 lines=40");
	srand(time(NULL));
	setbkcolor(EGERGB(168,248,249)); 
	
	init_change();
	
	Choose_Pattern();
	
	init();
	
	WINDOW=(window*)malloc(sizeof(window));  //����� 
	WINDOW->Next=NULL;
	creat(WINDOW);         

	Buffer_list = (buffer*)malloc(sizeof(buffer)); //������ 
	Buffer_list->next = NULL;

    Emergency_window = (emergency*)malloc(sizeof(emergency));//����ͨ�� 
    init_emergency();
   
	start = clock();	
	
	hMutex=CreateMutex(NULL,FALSE,NULL);
	
	HANDLE Thread1=(HANDLE)_beginthreadex(NULL,0,Control,NULL,0,NULL);
	
	Cartoon(Buffer_list);
	
	WaitForSingleObject(Thread1,INFINITE);
	CloseHandle(Thread1);
	if(OFFWORK==0)
	{
		closegraph();
	}
	Finish();
	return 0;
}

						   
	           
