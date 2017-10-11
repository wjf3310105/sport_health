/**
  ******************************************************************************
  * 文件名程: bsp_EEPROM.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2015-10-04
  * 功    能: I2C配置程序
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F1Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/
#include "i2c/bsp_I2C.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
I2C_HandleTypeDef I2cHandle;

/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: I2C外设初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void MX_I2C_EEPROM_Init(void)
{
  I2cHandle.Instance             = I2Cx;
  I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;
  I2cHandle.Init.OwnAddress1     = I2C_OWN_ADDRESS;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0xFF;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&I2cHandle);
}

/**
  * 函数功能: I2C外设硬件初始化配置
  * 输入参数: hi2c：I2C句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* 使能外设时钟 */
  I2C_RCC_CLK_ENABLE();        
  I2C_GPIO_CLK_ENABLE();
  
  /**I2C1 GPIO Configuration    
  PB6     ------> I2C1_SCL
  PB7     ------> I2C1_SDA 
  */
  GPIO_InitStruct.Pin = I2C_SCL_PIN|I2C_SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(I2C_GPIO_PORT, &GPIO_InitStruct);
  
  HAL_NVIC_SetPriority(I2C1_ER_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
  HAL_NVIC_SetPriority(I2C1_EV_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
}

/**
  * 函数功能: I2C外设硬件反初始化配置
  * 输入参数: hi2c：I2C句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  /* 禁用外设时钟 */
  I2C_GPIO_CLK_DISABLE();

  /**I2C1 GPIO Configuration    
  PB6     ------> I2C1_SCL
  PB7     ------> I2C1_SDA 
  */
  HAL_GPIO_DeInit(I2C_GPIO_PORT, I2C_SCL_PIN|I2C_SDA_PIN);
  HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
  HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);

}




/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
