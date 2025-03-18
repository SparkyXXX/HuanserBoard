/*
 * @Author: Hatrix 3113624526@qq.com
 * @LastEditTime: 2025-03-19 03:15:15
 * @Description: MG513带霍尔编码器减速电机TB6612FNG驱动
 */

#ifndef __DEV_MG513_H__
#define __DEV_MG513_H__

#include "tim.h"

typedef struct
{
    uint8_t decode_flag; // 令 decode_flag = 1 以获取电机角度
    int32_t cnt;
    int32_t last_cnt;
    int32_t delta_cnt;
    uint32_t tick;
    uint32_t last_tick;
    uint8_t enc_lines;
    TIM_HandleTypeDef *enc_htim;
} Dev_EncoderHall_Typedef;

typedef struct
{
    float rotate_speed;
    uint8_t dec_ratio;
    GPIO_TypeDef *in1_port;
    GPIO_TypeDef *in2_port;
    uint16_t in1_pin;
    uint16_t in2_pin;
    TIM_HandleTypeDef *pwm_htim;
    uint32_t pwm_ch;
    Dev_EncoderHall_Typedef *pencoder;
} Dev_MotorMG513_Typedef;

/**
 * @description: 电机初始化，按照CubeMX配置和实际硬件传入参数
 * @return {*}
 */
void MotorMG513_Init(Dev_MotorMG513_Typedef *pmotor, Dev_EncoderHall_Typedef *pencoder,
                     TIM_HandleTypeDef *enc_htim, TIM_HandleTypeDef *pwm_htim, uint32_t pwm_ch, uint8_t enc_lines, uint8_t dec_ratio,
                     GPIO_TypeDef *in1_port, uint16_t in1_pin, GPIO_TypeDef *in2_port, uint16_t in2_pin);

/**
 * @description: 获取电机转速，单位为rpm；编码器方式方式为T1 and T2，函数实现中脉冲数除以4
 * @param {Dev_MotorMG513_Typedef} *motor
 * @return {*}
 */
void MotorMG513_GetRotateSpeed(Dev_MotorMG513_Typedef *pmotor);

/**
 * @description: 设定pwm电机脉冲比较值并指定转向，开环调节电机转速；注意在调用逻辑中对pulse进行限幅
 * @param {Dev_MotorMG513_Typedef} *motor
 * @param {int} pulse
 * @return {*}
 */
void MotorMG513_SetPwmPulse(Dev_MotorMG513_Typedef *pmotor, int16_t pulse);

#endif /* __DEV_MG513Hall_H__ */