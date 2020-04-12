#ifndef __CYNOS_CFG_H
#define __CYNOS_CFG_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//debug 



#ifndef USE_CYNOS
#define USE_CYNOS (1) 
#endif




#define CPU_LEN             (16) 
#define USER_TASK_MAX        5   
#define SYSTICK_FRQ          10  
#define OS_ASSERT_EN         0   

#define TASK_SYSTICK_EN      0   
#define TASK_TIME_HOOK_EN    0   
#define TASK_PEND_HOOK_EN    0   
#define TASK_RESUM_HOOK_EN   0   


/*=======================================================*/
#define DEBUG_KERNEL_EN      0
#define DEBUG_KERNEL_PRINTF printf

#define USE_CYNOS_MUTEX      0
#define USE_CYNOS_SEM        1
#define USE_CYNOS_FIFO       0
#define USE_CYNOS_FIFO_EX    0  
/*FIFO CFG*/
#if USE_CYNOS_FIFO
#define CYNOS_FIFO_SIZE      10 
#if USE_CYNOS_FIFO_EX
#define CYNOS_FIFO_SIZE_EX   5  
#endif
#else
#define CYNOS_FIFO_SIZE      0 
#endif
/*MUTEX CFG*/
#if USE_CYNOS_MUTEX


#endif


/*SEM CFG*/
#if USE_CYNOS_SEM



#endif


#if OS_ASSERT_EN 
#define OS_ASSERT_HardFault  0  
#define OS_Warning_Assert    1  
#endif


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

