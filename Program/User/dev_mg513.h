/*
 * @Author: Hatrix 3113624526@qq.com
 * @LastEditTime: 2025-03-19 03:15:15
 * @Description: MG513���������������ٵ��TB6612FNG����
 */

#ifndef __DEV_MG513_H__
#define __DEV_MG513_H__

#include "tim.h"

typedef struct
{
    uint8_t decode_flag; // �� decode_flag = 1 �Ի�ȡ����Ƕ�
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
 * @description: �����ʼ��������CubeMX���ú�ʵ��Ӳ���������
 * @return {*}
 */
void MotorMG513_Init(Dev_MotorMG513_Typedef *pmotor, Dev_EncoderHall_Typedef *pencoder,
                     TIM_HandleTypeDef *enc_htim, TIM_HandleTypeDef *pwm_htim, uint32_t pwm_ch, uint8_t enc_lines, uint8_t dec_ratio,
                     GPIO_TypeDef *in1_port, uint16_t in1_pin, GPIO_TypeDef *in2_port, uint16_t in2_pin);

/**
 * @description: ��ȡ���ת�٣���λΪrpm����������ʽ��ʽΪT1 and T2������ʵ��������������4
 * @param {Dev_MotorMG513_Typedef} *motor
 * @return {*}
 */
void MotorMG513_GetRotateSpeed(Dev_MotorMG513_Typedef *pmotor);

/**
 * @description: �趨pwm�������Ƚ�ֵ��ָ��ת�򣬿������ڵ��ת�٣�ע���ڵ����߼��ж�pulse�����޷�
 * @param {Dev_MotorMG513_Typedef} *motor
 * @param {int} pulse
 * @return {*}
 */
void MotorMG513_SetPwmPulse(Dev_MotorMG513_Typedef *pmotor, int16_t pulse);

#endif /* __DEV_MG513Hall_H__ */