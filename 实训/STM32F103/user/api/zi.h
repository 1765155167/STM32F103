#ifndef _ZI__H_
#define _ZI__H_

extern unsigned char zf[];	
extern unsigned char zf_index[];

extern unsigned char hz[];
extern unsigned char hz_index[];

/*****************************************************************************
*****函数名：  ASCII_NUM()
*****参数：    无
*****功能：    返回ASCII字符个数
*****备注：创建这个函数是解决KEIL中sizeof()必须和结构变量同一个文件才准确识别的BUGE
*****************************************************************************/  
extern unsigned int ASCII_NUM(void);

/*****************************************************************************
*****函数名：  GB16_NUM()
*****参数：    无
*****功能：    返回GB16字符个数
*****备注：创建这个函数是解决KEIL中sizeof()必须和结构变量同一个文件才准确识别的BUGE
*****************************************************************************/  
extern unsigned int GB16_NUM(void) ;

#endif

