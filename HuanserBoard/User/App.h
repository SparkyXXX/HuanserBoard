/*
 * @Author: Hatrix 3113624526@qq.com
 * @LastEditTime: 2025-03-19 03:19:09
 * @Description: 上层应用程序和中断处理函数
 */

#ifndef __APP_H__
#define __APP_H__

#include "dev_mg513.h"

extern Dev_MotorMG513_Typedef MotorLeft;
extern Dev_EncoderHall_Typedef EncoderLeft;

/**
 * @description: 外设初始化
 * @return {*}
 */
void Init_All(void);

/**
 * @description: 主程序逻辑
 * @return {*}
 */
void Run_All(void);

/**
 * @description: 单元测试
 * @return {*}
 */
void Test_All(void);

#endif /* __APP_H__ */
