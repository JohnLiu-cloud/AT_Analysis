#include "driverlib.h"
#include "stdio.h"
#include "uart3.h"
#include "at.h"

char at_cmd_list[][32] = { AT , AT_CGMI , AT_UPSV , AT_CGSN , AT_CCID  , AT_CFUN , AT_UMNOPROF , AT_CFUN_1 };

static void my_delay(uint32_t x);

static int8_t at_cmd_analysis(  uint8_t *p_data , uint16_t len )
{
    uint8_t cmd;
    uint16_t length;
    uint16_t i;
    char prf[100];

    for( i=0;i<len;i++)
    {
      if( *(p_data+i) == '\r' || *(p_data+i) == '\n' )
      {
        break;
      }
    }
    length = i;

    memset( prf , 0 , 100 );
    memcpy( prf , (char *)p_data , length );
    for( cmd=0 ; cmd<CMD_LIST ; cmd++ )
    {
      if(strstr( prf , at_cmd_list[cmd]) != NULL && (length == strlen(at_cmd_list[cmd])))
      {
          return cmd;
      }
    }
    return -1;
}

static void at_data_analysis(  int8_t *cmd , uint8_t *p_data , uint16_t len )
{
    char *p_rx;
    char send[100];
    switch( *cmd )
    {
        case GET_AT:
            break;
        case GET_CGMI:
            break;
        case GET_UPSV:
            break;
        case GET_ICCID:
            break;
        case GET_CPIN:
            break;
        case SET_UMNOPROF:
            break;
        case GET_CFUN:
            break;
        case SET_CFUN_1:
            break;
    }
}

void at_cmd_send(  int8_t *cmd , uint8_t *p_data , uint16_t len )
{
    char *p_rx;
    char send[100];
    p_rx = strstr((char *)p_data, "OK");
    if( p_rx == NULL )
    {
      return;
    }
    memset(rx_buff , 0 , RX_BUFF_SIZE);
    switch( *cmd )
    {
        case GET_AT:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_CGMI]);
            uart3_send_data((uint8_t*)send,strlen(send));
            break;
        case GET_CGMI:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_UPSV]);
            uart3_send_data((uint8_t*)send,strlen(send));
            break;
        case GET_UPSV:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_ICCID]);
            uart3_send_data((uint8_t*)send,strlen(send));
            break;
        case GET_ICCID:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_CPIN]);
            uart3_send_data((uint8_t*)send,strlen(send));
            break;
        case GET_CPIN:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[SET_UMNOPROF]);
            uart3_send_data((uint8_t*)send,strlen(send));
            break;
        case SET_UMNOPROF:
            break;
        case GET_CFUN:
            break;
        case SET_CFUN_1:
            break;
    }
}

void at_handle(void)
{
    char *p_rx;

    int8_t cmd=-1;

    uint16_t len=0;

    if( rx_cnt_in != 0 )
    {
        while(rx_cnt_in>rx_cnt_out)
        {
            p_rx = strstr((char *)&rx_buff[rx_cnt_out], "\r\n");
            if(p_rx !=  NULL)
            {
                len = (p_rx-(char*)&rx_buff[rx_cnt_out]);
                if( cmd != -1 )
                {
                    at_data_analysis( &cmd , &rx_buff[rx_cnt_out] , len );
                    at_cmd_send( &cmd , &rx_buff[rx_cnt_out] , len );
                }
                else
                {
                    cmd = at_cmd_analysis( &rx_buff[rx_cnt_out] , len );
                }
                rx_cnt_out = (uint16_t)(p_rx-(char*)rx_buff)+2;
            }
            else
            {
              break;
            }
        }
        rx_cnt_in = 0;
        rx_cnt_out = 0;
    }
}

static void my_delay(uint32_t x)
{
  uint32_t y;
  for(;x>0;x--)
  {
    for(y=200;y>0;y--);
  }
}
