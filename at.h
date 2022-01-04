#define AT_H_
/*
#define AT              "AT"
#define AT_CGMI         "AT+CGMI"
#define AT_UPSV         "AT+UPSV?"
#define AT_CGSN         "AT+CGSN"
#define AT_CCID         "AT+CCID"
#define AT_CPIN         "AT+CPIN?"
#define AT_CSQ          "AT+CSQ"
#define AT_UMNOPROF     "AT+UMNOPROF=102"
#define AT_CFUN         "AT+CFUN?"
#define AT_CFUN_1       "AT+CFUN=1"

#define RESP_ERR_SIM "+CME ERROR: SIM failure"
#define RESP_ERR_CFUN "+CME ERROR: operation not allowed"
#define RESP_ERR_PIN "+CME ERROR: Incorrect password"
*/

#define AT              "AT"
#define AT_IMEI					"AT+GSN"				//Request International Mobile Equipment Identity (IMEI)
#define AT_CCID         "AT+CCID" 			//This command returns the ICCID (Integrated Circuit Card Identifier) number of the (U)SIM card.
#define AT_MANU_ID			"AT+GMI"				//This command returns the manufacturer identification text.
#define AT_RSSI					"AT+CSQ"				//The Execution Command returns the received signal strength indication <rssi> and the channel bit error
#define AT_FLIGHT				"AT+CFUN=0"			//Minimum functionality mode. Both (U)SIM and RF functions are disabled.
#define AT_NORMAL				"AT+CFUN=1"			//Full functionality mode (by default).


#define AT_OPEN_GNSS					"AT+QGPS=1" 		//Open GNSS
#define AT_QUERY_GPS					"AT+QGPSLOC?"
#define AT_CLOSE_GNSS					"AT+QGPSEND" 		//Close GNSS

typedef enum
{
	GET_AT,
	GET_MANU_ID,
	GET_IMEI,
	GET_ICCID,
	SET_NORMAL,	
	GET_RSSI,
	//SET_FLIGHT,
	
	CMD_LIST
}at_cmd_list_t;

typedef enum
{
	STATE_POWER_ON,
	STATE_GET_RSSI,
	STATE_EN_STANDBY,
}at_state_list_t;

extern at_state_list_t g_at_state;


void uart2_at_handle(void);

void at_cmd_rssi(void);

void at_cmd_pwron(void);
