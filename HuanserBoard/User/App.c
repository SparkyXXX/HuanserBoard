/*
 * @Author: Hatrix 3113624526@qq.com
 * @LastEditTime: 2025-03-19 04:20:28
 * @Description: 上层应用程序和中断处理函数
 */

#include "App.h"
#include "usart.h"

Dev_MotorMG513_Typedef MotorLeft;
Dev_MotorMG513_Typedef MotorRight;
Dev_EncoderHall_Typedef EncoderLeft;
Dev_EncoderHall_Typedef EncoderRight;

void Init_All(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
    MotorMG513_Init(&MotorLeft, &EncoderLeft, &htim3, &htim1, TIM_CHANNEL_1, 13, 60, AIN1_GPIO_Port, AIN1_Pin, AIN2_GPIO_Port, AIN2_Pin);
    MotorMG513_Init(&MotorRight, &EncoderRight, &htim4, &htim1, TIM_CHANNEL_2, 13, 60, BIN1_GPIO_Port, BIN1_Pin, BIN2_GPIO_Port, BIN2_Pin);
    MotorMG513_SetPwmPulse(&MotorLeft, 0);
    MotorMG513_SetPwmPulse(&MotorRight, 0);
}

void Run_All(void)
{
    if ((&MotorLeft)->pencoder->decode_flag == 1)
    {
        MotorMG513_GetRotateSpeed(&MotorLeft);
    }
    if ((&MotorRight)->pencoder->decode_flag == 1)
    {
        MotorMG513_GetRotateSpeed(&MotorRight);
    }
    Test_All();
}

int16_t test_pulse = 0;
void Test_All(void)
{
    MotorMG513_SetPwmPulse(&MotorLeft, test_pulse);
    MotorMG513_SetPwmPulse(&MotorRight, test_pulse);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        (&MotorLeft)->pencoder->decode_flag = 1;
        (&MotorRight)->pencoder->decode_flag = 1;
    }
}