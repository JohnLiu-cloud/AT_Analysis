#ifndef AT_H_
#define AT_H_

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


typedef enum
{
    GET_AT,             //"AT\r\n"
    GET_CGMI,           //"AT+CGMI\r\n" Text string identifying the manufacturer.
    GET_UPSV,           //"AT+UPSV?\r\n" power saving configuration.
    GET_CGSN,           //"AT+CGSN\r\n" Returns the International Mobile station Equipment Identity (IMEI) number.
    GET_ICCID,          //"AT+CCID\r\n" Returns the ICCID (Integrated Circuit Card ID) of the SIM-card.
    GET_CPIN,           //"AT+CPIN?\r\n" PIN
    SET_UMNOPROF,       //Automatically configures the module to be compliant to the requirements of various Mobile Network Operators.
    GET_CFUN,           //Selects the level of functionality <fun> in the MT.
    SET_CFUN_1,          //Selects the level of functionality <fun> in the MT.
    GET_CSQ,            //Returns the radio signal strength <signal_power> and <qual> from the MT.
    CMD_LIST
}at_cmd_list_t;

void at_handle(void);

#endif
