#ifndef __OS_H
#define __OS_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "cynos_base.h"
#include "cynos_cfg.h"



#define CYNOS_KERNEL_DESC    "***************CYNOS***************"
#define CYNOS_KERNEL_VERSION "SV00.001"
#define CYNOS_KERNEL_DATE    "20200222"
#define CYNOS_KERNEL_BUILD_DATA  __DATE__
#define CYNOS_KERNEL_BUILD_TIME  __TIME__


typedef enum
{
	CynOS_TASK_EVENT_NULL=0,
	CynOS_TASK_EVENT_RUN=0X01,
	CynOS_TASK_EVENT_TIME=0X02,
	CynOS_TASK_EVENT_PEND=0X04,
	CynOS_TASK_EVENT_RESUM=0X08,
}CynOS_TASK_STA;


typedef struct
{
	void(*time_hook)(unsigned int time);
	void(*taskInit)(void);
	void(*task)(void *arg);
	void * prm;
	unsigned int task_tick;
	unsigned int task_tick_cnt;
	CynOS_U8 task_id;
	CynOS_U8 task_priority; //���ȼ�δʹ�ã���ֹ���ȵ���ʹ�õ���������ʱ���޷�ִ�У�
	CynOS_U8 task_event;
	CynOS_TASK_STA task_sta;
#if TASK_TIME_HOOK_EN
	void(*task_event_time_hook)(void);
#endif
#if TASK_PEND_HOOK_EN
    void(*task_event_pend_hook)(void);
#endif
#if TASK_RESUM_HOOK_EN
    void(*task_event_resume_hook)(void);
#endif

}userTaskRun;



typedef struct
{
	CynOS_U8 init_sta;
	
}cynos_status;


 

extern cynos_status gcynos_sta;



/*��ȡ�ں˰汾*/
extern CynOS_U8 CynOS_Get_KernelVersion(void * out);  
/*��ȡ�ں�����*/
extern CynOS_U8 CynOS_Get_KernelDate(void * out);     
/*��ȡ�ں˱�������*/
extern CynOS_U8 CynOS_Get_KernelBuildDate(void * out);
/*��ȡ�ں˱���ʱ��*/
extern CynOS_U8 CynOS_Get_KernelBuildTime(void * out);
	

/*ϵͳ��ʼ��*/
extern void CynOS_Init(void);    
/*ϵͳ����*/
extern void CynOsStart(void);
/*�����㷨����֤ÿ��������ִ�У��ں�δʹ�ã��ɶ����ṩ�����㷨��*/
extern void CynOsTaskSchedule(CynOS_U8*taskfifo,unsigned int size,CynOS_U8 typesize);
/*��������*/
extern void CynOS_PENDING(CynOS_U8 taskid);
/*�ָ�����*/
extern void CynOS_RESUM(CynOS_U8 taskid);
/*ע��ϵͳ��������*/
extern void CynOS_Login_Hook(CynOS_U8 taskid,CynOS_TASK_STA task_type,void(*eventhook)(void));
/*��������*/
extern CynOS_U8 CynosTask_Creat(void(*time_hook)(unsigned int time),void(*taskInit)(void),void(*task)(void * arg),unsigned int tasktick);
/*ɾ������*/
extern CynOS_U8 CynosTask_Delete(CynOS_U8 task_id);
/*ϵͳ�쳣*/
extern void CynOS_Assert(char asslv,char*head,void *arg);




/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

