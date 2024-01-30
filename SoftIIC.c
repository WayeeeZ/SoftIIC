#include "SoftIIC.h"
/**
 * @brief start signal
 */
void Soft_IIC_Start(Soft_IIC_t *Handler)
{
    Handler->Cmd(SOFT_IIC_CMD_SDA_OUT);
    Handler->Cmd(SOFT_IIC_CMD_SDA_H);
    Handler->Cmd(SOFT_IIC_CMD_SCL_H);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SDA_L);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
}

/**
 * @brief stop signal
 */
void Soft_IIC_Stop(Soft_IIC_t *Handler)
{
    Handler->Cmd(SOFT_IIC_CMD_SDA_OUT);
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
    Handler->Cmd(SOFT_IIC_CMD_SDA_L);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SCL_H);
    Handler->Cmd(SOFT_IIC_CMD_SDA_H);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
}

/**
 * @brief ack signal
 */
void Soft_IIC_Ack(Soft_IIC_t *Handler)
{
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
    Handler->Cmd(SOFT_IIC_CMD_SDA_OUT);
    Handler->Cmd(SOFT_IIC_CMD_SDA_L);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SCL_H);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
}

/**
 * @brief nack signal
 */
void Soft_IIC_NAck(Soft_IIC_t *Handler)
{
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
    Handler->Cmd(SOFT_IIC_CMD_SDA_OUT);
    Handler->Cmd(SOFT_IIC_CMD_SDA_H);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SCL_H);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
}

/**
 * @brief wait for ack
 */
uint8_t Soft_IIC_Wait_Ack(Soft_IIC_t *Handler)
{
    uint8_t TimeOut = 0;
    Handler->Cmd(SOFT_IIC_CMD_SDA_IN);
    Handler->Cmd(SOFT_IIC_CMD_SDA_H);
    Handler->Delay(SOFT_IIC_DELAY_TIME);
    Handler->Cmd(SOFT_IIC_CMD_SCL_H);
    Handler->Delay(SOFT_IIC_DELAY_TIME);

    while (Handler->Cmd(SOFT_IIC_CMD_READ_SDA))
    {
        TimeOut = TimeOut;
        if (TimeOut++ > 250)
        {
            Soft_IIC_Stop(Handler);
            Handler->Cmd(SOFT_IIC_CMD_SCL_L);
            Handler->Cmd(SOFT_IIC_CMD_SDA_OUT);
            return 1;
        }
    }
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
    return 0;
}

/**
 * @brief send a byte
 */
void Soft_IIC_Send_Byte(Soft_IIC_t *Handler, uint8_t Byte)
{
    uint8_t i;
    Handler->Cmd(SOFT_IIC_CMD_SDA_OUT);
    Handler->Cmd(SOFT_IIC_CMD_SCL_L);
    for (i = 0; i < 8; i++)
    {
        if (Byte & 0x80)
            Handler->Cmd(SOFT_IIC_CMD_SDA_H);
        else
            Handler->Cmd(SOFT_IIC_CMD_SDA_L);
        Byte <<= 1;
        Handler->Delay(SOFT_IIC_DELAY_TIME);
        Handler->Cmd(SOFT_IIC_CMD_SCL_H);
        Handler->Delay(SOFT_IIC_DELAY_TIME);
        Handler->Cmd(SOFT_IIC_CMD_SCL_L);
        Handler->Delay(SOFT_IIC_DELAY_TIME);
    }
}

/**
 * @brief read a byte
 */
uint8_t Soft_IIC_Read_Byte(Soft_IIC_t *Handler, en_Soft_IIC_Ack Ack)
{
    uint8_t i;
    uint8_t Ret = 0;
    Handler->Cmd(SOFT_IIC_CMD_SDA_IN);
    for (i = 0; i < 8; i++)
    {
        Handler->Cmd(SOFT_IIC_CMD_SCL_L);
        Handler->Cmd(SOFT_IIC_CMD_SCL_H);
        Ret <<= 1;
        if (Handler->Cmd(SOFT_IIC_CMD_READ_SDA))
            Ret++;
    }

    if (Ack == SOFT_IIC_ACK)
        Soft_IIC_Ack(Handler); // send a ack signal
    else
        Soft_IIC_NAck(Handler); // send a nack signal

    return Ret;
}
// File End
