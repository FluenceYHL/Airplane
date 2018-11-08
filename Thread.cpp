#include "Thread.h"
#include "common_sys.h"
#include "general_Data.h"
#include "Control.h"
#include "Get_input.h"
#include "state_trans.h"
#include "gereral_Data_variable.h"

unsigned _stdcall Control(void *pArguments)
{
	while(OFFWORK)
	{
	    WaitForSingleObject(hMutex,INFINITE);
	    
	    if(entry_sec==0)
	       Get_input(Buffer_list);  //資函並周窃侏
	    
	    if(fps==60)
	    {
	    	fps-=60;
	    	//printf("！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！\n");
	        control(WINDOW,Buffer_list);
		    state_trans(WINDOW);
	        if(OFFWORK==0) break;
	        //printf("entry_sec = %d\n",entry_sec);
			entry_sec--;
		}
        	
	    ReleaseMutex(hMutex);
    }
	_endthreadex(0);
	return 0;
}


