
#ifndef __SOFT_IIC_H__
#define __SOFT_IIC_H__
/******************************************************************************/
#include <stdint.h>
/******************************************************************************/
typedef enum
{
    SOFT_IIC_NACK,
    SOFT_IIC_ACK
} en_Soft_IIC_Ack;
#define SOFT_IIC_DELAY_TIME 2
typedef enum
{
    SOFT_IIC_CMD_SCL_H,
    SOFT_IIC_CMD_SCL_L,
    SOFT_IIC_CMD_SDA_H,
    SOFT_IIC_CMD_SDA_L,
    SOFT_IIC_CMD_READ_SDA,
    SOFT_IIC_CMD_SDA_IN,
    SOFT_IIC_CMD_SDA_OUT,
    SOFT_IIC_CMD_SCL_IN,
    SOFT_IIC_CMD_SCL_OUT,
} en_Soft_IIC_Cmd;
typedef struct
{
    int32_t (*Cmd)(en_Soft_IIC_Cmd Cmd);
    void (*Delay)(uint32_t Time);
} Soft_IIC_t;
/******************************************************************************/
void Soft_IIC_Ack(Soft_IIC_t *Handler);
void Soft_IIC_NAck(Soft_IIC_t *Handler);
void Soft_IIC_Stop(Soft_IIC_t *Handler);
void Soft_IIC_Start(Soft_IIC_t *Handler);
uint8_t Soft_IIC_Wait_Ack(Soft_IIC_t *Handler);
uint8_t Soft_IIC_Read_Byte(Soft_IIC_t *Handler, en_Soft_IIC_Ack Ack);
void Soft_IIC_Send_Byte(Soft_IIC_t *Handler, uint8_t Byte);
/******************************************************************************/
#endif
/******************************************************************************/
// File End
