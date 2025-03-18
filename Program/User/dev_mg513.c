/*
 * @Author: Hatrix 3113624526@qq.com
 * @LastEditTime: 2025-03-19 04:29:12
 * @Description: MG513Hall带编码器减速电机TB6612FNG驱动
 */

#include "dev_mg513.h"
#include "stdlib.h"

void MotorMG513_Init(Dev_MotorMG513_Typedef *pmotor, Dev_EncoderHall_Typedef *pencoder,
                     TIM_HandleTypeDef *enc_htim, TIM_HandleTypeDef *pwm_htim, uint32_t pwm_ch, uint8_t enc_lines, uint8_t dec_ratio,
                     GPIO_TypeDef *in1_port, uint16_t in1_pin, GPIO_TypeDef *in2_port, uint16_t in2_pin)
{
    pmotor->pencoder = pencoder;
    pmotor->pencoder->enc_htim = enc_htim;
    pmotor->pencoder->enc_lines = enc_lines;
    pmotor->pencoder->decode_flag = 0;
    pmotor->pwm_htim = pwm_htim;
    pmotor->pwm_ch = pwm_ch;
    pmotor->dec_ratio = dec_ratio;
    pmotor->in1_port = in1_port;
    pmotor->in1_pin = in1_pin;
    pmotor->in2_port = in2_port;
    pmotor->in2_pin = in2_pin;
    HAL_TIM_Encoder_Start(pmotor->pencoder->enc_htim, TIM_CHANNEL_ALL);
    HAL_TIM_PWM_Start(pmotor->pwm_htim, pmotor->pwm_ch);
}

void MotorMG513_GetRotateSpeed(Dev_MotorMG513_Typedef *pmotor)
{
    if (pmotor->pencoder->decode_flag)
    {
        pmotor->pencoder->cnt = __HAL_TIM_GET_COUNTER(pmotor->pencoder->enc_htim);
        pmotor->pencoder->tick = HAL_GetTick();
        pmotor->pencoder->delta_cnt = pmotor->pencoder->cnt - pmotor->pencoder->last_cnt;
        if (pmotor->pencoder->delta_cnt > 32768)
        {
            pmotor->pencoder->delta_cnt -= 65535;
        }
        else if (pmotor->pencoder->delta_cnt < -32768)
        {
            pmotor->pencoder->delta_cnt += 65535;
        }
        pmotor->rotate_speed = (float)pmotor->pencoder->delta_cnt * 1000 * 60 / 4 / (pmotor->pencoder->enc_lines * pmotor->dec_ratio) / (pmotor->pencoder->tick - pmotor->pencoder->last_tick);
        pmotor->pencoder->last_cnt = pmotor->pencoder->cnt;
        pmotor->pencoder->last_tick = pmotor->pencoder->tick;
        pmotor->pencoder->decode_flag = 0;
    }
}

void MotorMG513_SetPwmPulse(Dev_MotorMG513_Typedef *pmotor, int16_t pulse)
{
    HAL_GPIO_WritePin(pmotor->in1_port, pmotor->in1_pin, (pulse > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(pmotor->in2_port, pmotor->in2_pin, (pulse < 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(pmotor->pwm_htim, pmotor->pwm_ch, (pulse == 0) ? 0 : abs(pulse));
}
