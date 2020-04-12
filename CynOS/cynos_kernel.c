/*
Copyright 2020 chenyanan

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include "cynos_kernel.h"
#include "cynos_time.h"

cynos_status gcynos_sta;
userTaskRun gUserTask[USER_TASK_MAX];
/*
	�ں˽�ֹ���ó�time�����ģ�飬��ֻ֤�����ں��Լ�time�ļ��ɶ������У�
	�Է���ü�ϵͳʵ��ϵͳ�ľ���ռ�ü��ٵ���Դ������С��Դ�������У�
	����ռ�ü�����Դ������¼�����Ӧ��������������ܹ�ʵ����Ը��ӵĹ��ܡ�
	
	��ǰÿ������RAMԼռ��Լ 44Byte  {kernel:40(���Ȳ�����) timer:4(�����ʱ����)}
*/




/*
	����1��������������ʱ��Ƭ�жϹ�����
	����2���������ʼ������
	����3�����������壨������������
	����4��ʱ��Ƭ
	
	���񴴽����Ĭ��Ϊ����̬
*/
CynOS_U8 CynosTask_Creat(void(*time_hook)(CynOS_U32 time),void(*taskInit)(void),void(*task)(void * arg),CynOS_U32 tasktick)
{
	CynOS_U8 index=0;
	if(gcynos_sta.init_sta==0x55)
	{
		for(index=0;index<USER_TASK_MAX;index++)
		{
			if(gUserTask[index].task==0)
			{
				gUserTask[index].task_event=CynOS_TASK_EVENT_NULL;
				gUserTask[index].task_sta=CynOS_TASK_EVENT_RUN;
				gUserTask[index].task_id=index;
				gUserTask[index].task_priority=gUserTask[index].task_id;
				gUserTask[index].task=task;
				gUserTask[index].taskInit=taskInit;
				gUserTask[index].time_hook=time_hook;
				gUserTask[index].task_tick=tasktick;
				cynos_tim_base_login(gUserTask[index].time_hook);
				return index;
			}
		}
	}
	return 0xff;
}

CynOS_U8 CynosTask_Delete(CynOS_U8 task_id)
{
	if((gUserTask[task_id].task)&&(gUserTask[task_id].task_id==task_id))
	{
		cynos_tim_base_logout(gUserTask[task_id].time_hook);
		gUserTask[task_id].task_event=CynOS_TASK_EVENT_NULL;
		gUserTask[task_id].task_sta=CynOS_TASK_EVENT_NULL;
		gUserTask[task_id].task_id=0;
		gUserTask[task_id].task=0;
		gUserTask[task_id].taskInit=0;
		gUserTask[task_id].taskInit=0;
		gUserTask[task_id].time_hook=0;
		gUserTask[task_id].task_tick=0;
		return CYNOS_OK;
	}
	return CYNOS_ERR;
}

//�ں˵���tick
void CynOs_Systick(CynOS_U32 cnt)
{
    CynOS_U8 iii=0;
	for(iii=0;iii<USER_TASK_MAX;iii++)
	{
		if(gUserTask[iii].task)
		{
			gUserTask[iii].task_tick_cnt+=cnt;
		}
	}
}


int compar(const void *p1, const void *p2)
{
	return ((*(CynOS_U8*)p1)-(*(CynOS_U8*)p2));
}
/*
	����ʵ�����ȵ��Ȼ��ƣ����ȼ�Խ��ֵԽС��
*/
void CynOsTaskSchedule(CynOS_U8*taskfifo,CynOS_U32 size,CynOS_U8 typesize)
{
	qsort(taskfifo,size,typesize,compar);
}

void CynOS_Init(void)
{
	memset(gUserTask,0,sizeof(userTaskRun));
	memset(&gcynos_sta,0,sizeof(cynos_status));
	gcynos_sta.init_sta=0x55;
	cynos_tim_base_login(CynOs_Systick); //ע���ں�tick
}

void CynOS_PENDING(CynOS_U8 taskid)
{
	if(taskid<USER_TASK_MAX)
	{
		gUserTask[taskid].task_event|=CynOS_TASK_EVENT_PEND;
	}
}

void CynOS_RESUM(CynOS_U8 taskid)
{
	if(taskid<USER_TASK_MAX)
	{
		gUserTask[taskid].task_event|=CynOS_TASK_EVENT_RESUM;
	}
}


/*�ں˻ص�ע��*/
void CynOS_Login_Hook(CynOS_U8 taskid,CynOS_TASK_STA task_type,void(*eventhook)(void))
{
	if(taskid<USER_TASK_MAX)
	{
		switch(task_type)
		{
			case CynOS_TASK_EVENT_TIME:
#if TASK_TIME_HOOK_EN
			    gUserTask[taskid].task_event_time_hook=eventhook;
#endif
				break;
			case CynOS_TASK_EVENT_PEND:
#if TASK_PEND_HOOK_EN
                gUserTask[taskid].task_event_pend_hook=eventhook;
#endif
				break;
			case CynOS_TASK_EVENT_RESUM:
#if TASK_TIME_HOOK_EN
                gUserTask[taskid].task_event_resume_hook=eventhook;
#endif

				break;
			default:
				break;
		}
	}
}


CynOS_U8 CynOS_Get_KernelVersion(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_VERSION,strlen(CYNOS_KERNEL_VERSION));
	return strlen(CYNOS_KERNEL_VERSION);
}

CynOS_U8 CynOS_Get_KernelDate(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_DATE,strlen(CYNOS_KERNEL_DATE));
	return strlen(CYNOS_KERNEL_DATE);
}

CynOS_U8 CynOS_Get_KernelBuildDate(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_BUILD_DATA,strlen(CYNOS_KERNEL_BUILD_DATA));
	return strlen(CYNOS_KERNEL_BUILD_DATA);
}

CynOS_U8 CynOS_Get_KernelBuildTime(void * out)
{
	CynOS_U8* buf=out;
	
	 memcpy(buf,CYNOS_KERNEL_BUILD_TIME,strlen(CYNOS_KERNEL_BUILD_TIME));
	return strlen(CYNOS_KERNEL_BUILD_TIME);
}

/*
	0Ϊϵͳ�����쳣
	��0Ϊһ��ɺ����쳣
*/	
void CynOS_Assert(char asslv,char*head,void *arg)
{
	#if DEBUG_KERNEL_EN
	DEBUG_KERNEL_PRINTF("[%s]:%s\r\n",head,(char*)arg);
	#endif
	if(asslv==0)
	{
		while(1);
	}
}

void CynOsStart(void)
{
	CynOS_U8 iii=0;
	#if DEBUG_KERNEL_EN
	DEBUG_KERNEL_PRINTF("\r\n");
	DEBUG_KERNEL_PRINTF(CYNOS_KERNEL_DESC);
	DEBUG_KERNEL_PRINTF("\r\n");
	DEBUG_KERNEL_PRINTF("kernel will start\r\n");
	DEBUG_KERNEL_PRINTF(CYNOS_KERNEL_VERSION);
	DEBUG_KERNEL_PRINTF("\r\n");
	DEBUG_KERNEL_PRINTF(CYNOS_KERNEL_DATE);
	DEBUG_KERNEL_PRINTF("\r\n");
	#endif
	for(iii=0;iii<USER_TASK_MAX;iii++)
	{
		if(gUserTask[iii].taskInit)
		{
			#if DEBUG_KERNEL_EN
			DEBUG_KERNEL_PRINTF("task[%02d] will ihit...\r\n",iii);
			#endif
			gUserTask[iii].taskInit();
		}
	}
	#if DEBUG_KERNEL_EN
	DEBUG_KERNEL_PRINTF("Scheduling\r\n");
	#endif
	while(1)
	{
		for(iii=0;iii<USER_TASK_MAX;iii++)
		{
			if(gUserTask[iii].task)
			{
				if(gUserTask[iii].task_event&CynOS_TASK_EVENT_PEND)
				{
					#if DEBUG_KERNEL_EN
					DEBUG_KERNEL_PRINTF("task[%02d] is suspended\r\n",gUserTask[iii].task_id);
					#endif
					gUserTask[iii].task_event&=(~CynOS_TASK_EVENT_PEND);
					gUserTask[iii].task_sta=CynOS_TASK_EVENT_PEND;
#if TASK_PEND_HOOK_EN
					{
						#if DEBUG_KERNEL_EN
						DEBUG_KERNEL_PRINTF("task[%02d] event_pend_hook\r\n",gUserTask[iii].task_id);
						#endif
						if(gUserTask[iii].task_event_pend_hook)
						{
							gUserTask[iii].task_event_pend_hook();
						}
					}
#endif
				}
				else if(gUserTask[iii].task_event&CynOS_TASK_EVENT_RESUM)
				{
					#if DEBUG_KERNEL_EN
					DEBUG_KERNEL_PRINTF("task[%02d] is resumed\r\n",gUserTask[iii].task_id);
					#endif
					gUserTask[iii].task_event&=(~CynOS_TASK_EVENT_RESUM);
					gUserTask[iii].task_sta=CynOS_TASK_EVENT_RUN;
#if TASK_RESUM_HOOK_EN
					{
						#if DEBUG_KERNEL_EN
						DEBUG_KERNEL_PRINTF("task[%02d] event_resume_hook\r\n",gUserTask[iii].task_id);
						#endif
						if(gUserTask[iii].task_event_resume_hook)
						{
							gUserTask[iii].task_event_resume_hook();
						}
					}
#endif
				}
				
				if(gUserTask[iii].task_sta==CynOS_TASK_EVENT_RUN)
				{
					#if TASK_SYSTICK_EN
					
					if(gUserTask[iii].task_tick_cnt>=gUserTask[iii].task_tick)
					{
						gUserTask[iii].task_tick_cnt=0;
						if(TASK_TIME_HOOK_EN)
						{
							if(gUserTask[iii].task_event_time_hook)
							{
								gUserTask[iii].task_event_time_hook();
							}
						}
						gUserTask[iii].task(gUserTask[iii].prm);
					}
					#else
					gUserTask[iii].task(gUserTask[iii].prm);
					#endif
				}
			}
		}
	}
}


/*
	ϵͳ���쳣����
*/

#if OS_ASSERT_HardFault
void HardFault_Handler()
{
	CynOS_Assert(0,"HardFault_Handler","\r\nCynOS_Assert Hard Fault Handler\r\n");
}
#endif 







