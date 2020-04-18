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



#include "cynos_funlib.h"



/*==============================================MEM================================================================*/
/*
*********************************************************************************************************
* ��������: CynOS_Mem_Cpy
*
* ����˵��: ���鿽������
*
* ��ڲ���:
*
* ���ز���: ��������
*
* ����˵��:
*********************************************************************************************************
*/

CynOS_U32 CynOS_Mem_Cpy (void *dst, void *src, CynOS_U32 len, CynOS_U32 limit)
{
	len=(len>limit)?(limit):(len);
	memcpy(dst,src,len);
	return len;
}
/*
*********************************************************************************************************
* ��������: CynOS_Mem_Set
*
* ����˵��: ��������
*
* ��ڲ���:
*
* ���ز���: ��������
*
* ����˵��:
*********************************************************************************************************
*/

CynOS_U32 CynOS_Mem_Set (void *src,CynOS_U8 data, CynOS_U32 len, CynOS_U32 limit)
{
	len=(len>limit)?(limit):(len);
	memset(src,data,len);
	return len;
}


/*==============================================SOFTCRC================================================================*/




























