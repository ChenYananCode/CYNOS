#ifndef __CYNOS_SEM_H
#define __CYNOS_SEM_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
#include "cynos_base.h"


typedef struct cynos_sem
{
/*public����*/
	CYNOS_STATUS(*post)(struct cynos_sem * mutex);
	CYNOS_STATUS(*pend)(struct cynos_sem * mutex);
	CYNOS_STATUS(*clear)(struct cynos_sem * mutex);
/*protect��Ա��ֱֹ�ӷ���*/	
	unsigned int sem_type;
	unsigned int sem_val;
}CynOS_Sem;

/*
0-1:��ֵ�ź���
>1: ��ֵ�ź���
*/
/*sem���ʼ��*/
CYNOS_STATUS CynOs_Sem_Init(CynOS_Sem * sem,unsigned int sem_type);





/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif



