#include "stm32f10x.h" 
#include "stdio.h"
#include <string.h>
#include "app_uart.h"
#include "usart.h"

at_state_list_t g_at_state;

char at_cmd_list[][32] = { AT , AT_MANU_ID , AT_IMEI , AT_CCID , AT_NORMAL , AT_RSSI };

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
		p_rx = (char*)p_data;
    switch( *cmd )
    {
        case GET_AT:
						//printf(p_rx);
            break;
        case GET_MANU_ID:
						//printf(p_rx);
            break;
        case GET_IMEI:
						//printf(p_rx);
            break;
        case GET_ICCID:
						//printf(p_rx);
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
		memset( send , 0 , 100 );
    memset(rx1_buff , 0 , RX_BUFF_SIZE);
    switch( *cmd )
    {
        case GET_AT:
            my_delay(200);
						g_at_state = STATE_POWER_ON;
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_MANU_ID]);
						USART2_printf( send );
            break;
        case GET_MANU_ID:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_IMEI]);
						USART2_printf( send );
            break;
        case GET_IMEI:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_ICCID]);
						USART2_printf( send );
            break;
        case GET_ICCID:
            my_delay(200);
            sprintf(send,"%s\r\n",(char*)&at_cmd_list[SET_NORMAL]);
						USART2_printf( send );					
            break;
				case SET_NORMAL:
						g_at_state = STATE_GET_RSSI;
					break;
				case GET_RSSI:

					break;

    }
}

void at_cmd_rssi(void)
{
	char send[100];
	memset( send , 0 , 100 );
	sprintf(send,"%s\r\n",(char*)&at_cmd_list[GET_RSSI]);
	USART2_printf( send );		
}

void at_cmd_pwron(void)
{
	USART2_printf("AT\r\n");
}


void uart2_at_handle(void)
{
    char *p_rx;

    int8_t cmd=-1;

    uint16_t len=0;
	
		uint16_t i;
	
		uint8_t buf[100];

    if( rx2_cnt_in != 0 )
    {
				
        while(rx2_cnt_in>rx2_cnt_out)
        {
						//p_rx = strstr((char *)&rx2_buff[rx2_cnt_out], "\r\r\n");
					
						p_rx = strstr((char *)&rx2_buff[rx2_cnt_out], "\r\n");
            
            if(p_rx !=  NULL)
            {
							
							len = (p_rx-(char*)&rx2_buff[rx2_cnt_out]);				
							
								if( len != 0 )
								{
/*
									for( i=len-1 ; i>0 ; i-- )
									{
										if( rx2_buff[rx2_cnt_out+i] == '\r' )
										{
											len--;
										}
									}		
*/								memset( buf , 0 , 100 );
									uart1_log( "\r\n" , 2  );
									uart1_log( &rx2_buff[rx2_cnt_out] , len  );
									uart1_log( "\r\n" , 2  );
									memcpy( buf , &rx2_buff[rx2_cnt_out] , len  );

									if( cmd != -1 )
									{
											//at_data_analysis( &cmd , &rx2_buff[rx2_cnt_out] , len );
											//at_cmd_send( &cmd , &rx2_buff[rx2_cnt_out] , len );
											at_data_analysis( &cmd , buf , len );
											at_cmd_send( &cmd , buf , len );
									}
									else
									{
											//cmd = at_cmd_analysis( &rx2_buff[rx2_cnt_out] , len );
											cmd = at_cmd_analysis( buf , len );
									}
								}
                rx2_cnt_out = (uint16_t)(p_rx-(char*)&rx2_buff)+2;
            }
            else
            {
              break;
            }
        }
				memset(rx2_buff,0,sizeof(rx2_buff));
        rx2_cnt_in = 0;
        rx2_cnt_out = 0;
    }
}

static void my_delay(uint32_t x)
{
  uint32_t y;
  for(;x>0;x--)
  {
    for(y=18000;y>0;y--);
  }
}
