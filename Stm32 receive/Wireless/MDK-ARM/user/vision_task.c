/* Includes ------------------------------------------------------------------*/
#include "vision_task.h"
#include "cmsis_os.h"
#include "pid.h"
#include <math.h>
#include "kalman.h"
#include "rc.h"
/* Private variables ---------------------------------------------------------*/
uint8_t aimbot_transmit_data[5];
/* Private typedef -----------------------------------------------------------*/
extern UART_HandleTypeDef huart4;

vision_info_t vision_info=
{
	.Aimbot_mode=AIMBOT_MODE_OFF,
	.aimbot_rec_data.aimbot_yaw_angle=0,
	.aimbot_rec_data.aimbot_pit_angle=0,
	.aimbot_lpf=0.02f,
};
/* Private functions ---------------------------------------------------------*/
void Aimbot_Mode(void);
void Aimbot_Transmit(void);
/**
 * @brief 视觉总控
 * @param 
 */
void VISION_Ctrl(void)
{
	Aimbot_Mode();
}

/**
 *	@brief	自瞄数据接收
 */
int cnt19=0;
int esp_01s_date;
void Aimbot_Receive(uint8_t *aimbol_buffer)
{
	if(aimbol_buffer[0]==0x80&&aimbol_buffer[2]==0x7F)
	{
		cnt19++;
		/*0-180 -> 0-65535*/
		esp_01s_date=(int)aimbol_buffer[1];
	}
}


/**
 *	@brief	自瞄模式选择
 */
void Aimbot_Mode(void)
{
	if(MODE==3)/*key R */
	{
	 vision_info.Aimbot_mode=AIMBOT_MODE_OFF;
	}
	else if(MODE==1)/*key F */
	{
	 vision_info.Aimbot_mode=LOCK_ENEMY;
	}
}


/**
* @brief 视觉任务
* @param void 
* @return void
* @berif  3ms
*/
void StartVisionTask(void const * argument)
{
	uint32_t previousWakeTime=osKernelSysTick();
    for(;;)
    {
      VISION_Ctrl();
		  osDelayUntil(&previousWakeTime,3);
    }
}
