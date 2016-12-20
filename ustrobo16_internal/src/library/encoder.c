/**
 * ================================================================
 * @File: encoder.c
 * @author: The most handsome Nicole in the world yeahhhh!
 * @brief: encoder.c for robotics team 2016 internal Team 2(0010)
 * @version: v1.1
 * ================================================================
 */

#include "encoder.h"

s16 flag_enc1 = 0;
s16 flag_enc2 = 0;
s32 enc1 = 0;
s32 enc2 = 0;
s32 enc1_curr_vel = 0;
s32 enc2_curr_vel = 0;
s32 enc1_prev = 0;
s32 enc2_prev = 0;
u32 prev_time1 = 0;
u32 prev_time2 = 0;

/**
 * @param: none
 * @return: none
 * @brief: encoder initialization 
 */
void encoder_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure;
	TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;//	TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;
  TIM_ICInitTypeDef TIM4_ICInitStructure;
	TIM_ICInitTypeDef TIM3_ICInitStructure;
	
	/**
	 * Left Encoder(ID:1) initialization and configuration
	 */
	
	/*PB7 (TIM4_CH2) (encoder1 pin A), PB6 (TIM4_CH1) (encoder1 pin B)*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/*TIM4 Configuration*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM4_TimeBaseStructure.TIM_Prescaler = 0x00;                        
  TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM4_TimeBaseStructure.TIM_Period = ENCODER_MAX_COUNT;                            
  TIM4_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            
  //TIM4_TimeBaseStructure.TIM_RepetitionCounter = 0; 
  TIM_TimeBaseInit(TIM4, &TIM4_TimeBaseStructure);
	
	/*TIM4 filer setting*/
  TIM_ICStructInit(&TIM4_ICInitStructure);
  TIM4_ICInitStructure.TIM_ICFilter = 8;
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	/*clear pending interrupts*/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
		
	/*Encoder1 Configuration*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
	TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_SetCounter(TIM4, ENCODER_INIT_COUNT);
	
	/**
	 * Right Encoder(ID:2) initialization and configuration
	 */
	
	//PC6(TIM3_CH1) (encoder2 pin B) and PC7(TIM2_CH2) (encoder2 pin A) for encoder2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // Permit ReMap
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	
	TIM3_TimeBaseStructure.TIM_Prescaler = 0x00;                        
  TIM3_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM3_TimeBaseStructure.TIM_Period = ENCODER_MAX_COUNT;                            
  TIM3_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            
  //TIM2_TimeBaseStructure.TIM_RepetitionCounter = 0; 
  TIM_TimeBaseInit(TIM3, &TIM3_TimeBaseStructure);
	
  TIM_ICStructInit(&TIM3_ICInitStructure);
  TIM3_ICInitStructure.TIM_ICFilter = 8;
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
	TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_SetCounter(TIM3, ENCODER_INIT_COUNT);
	
	/*Enable counter*/
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

/**
 * @param: none
 * @return: none
 * @brief: update encoder data per call (408 / revolution) 
 */
void encoder_update(void)
{
	s32 count1 = TIM_GetCounter(TIM4);
	if(count1 > 62767){
		TIM_SetCounter(TIM4, count1 - 30000);
		flag_enc1++;
	}
	else if(count1 < 2767){
		TIM_SetCounter(TIM4, count1 + 30000);
		flag_enc1--;
	}
	enc1 = (flag_enc1*30000 + (count1 - ENCODER_INIT_COUNT)); //encoder now returns ~408 per revolution
	
	s32 count2 = TIM_GetCounter(TIM3);
	if(count2 > 62767){
		TIM_SetCounter(TIM3, count2 - 30000);
		flag_enc2++;
	}
	else if(count2 < 2767){
		TIM_SetCounter(TIM3, count2 + 30000);
		flag_enc2--;
	}
	enc2 = (flag_enc2*30000 + (count2 - ENCODER_INIT_COUNT)); //encoder now returns ~408 per revolution	
}

/**
 * @param: encoder# , input 1 for left motor and 2 for right motor 
 * @return: signed int of pulse recorded. enc1 for left motor , enc2 for right motor
						-1 if x success
 * @brief: return encoder count for the use of pid
 */
s32 encoder_count(int encoder)
{
	if(encoder == 1)
		return enc1;
	if(encoder == 2)
		return enc2;
	return -1;
}

/**
 * @param: encoder# , input 1 for left motor and 2 for right motor 
 * @return: encoder rate of change per update, -1 for xsuccess
 * @brief: return encoder velocity when call
 */
s32 enc_get_vel(int encoder)
{
	u32 curr_time = get_real_ticks();
	if(encoder == 1)
	{
		enc1_curr_vel = (enc1 - enc1_prev)/(curr_time - prev_time1 + 1);
		enc1_prev = enc1;
		prev_time1 = curr_time;
		
		return enc1_curr_vel;
	}
	else if(encoder == 2)
	{
		enc2_curr_vel = (enc2 - enc2_prev)/(curr_time - prev_time2 + 1);
		enc2_prev = enc2;
		prev_time2 = curr_time;
		
		return enc2_curr_vel;
	}
	return 0;
}

void encoder_reset(void)
{
	TIM_SetCounter(TIM4, 0);
	TIM_SetCounter(TIM3, 0);
}
