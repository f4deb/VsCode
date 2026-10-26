#include <stdio.h>
#include <string.h>
#include "interfaceDescriptor.h"
#include "freertos/idf_additions.h"
#include "interface.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"


#define TAG "Interface Descriptor"


    char str[50] = "interface descriptor";

    static char* textResult ="??";

void printDeviceLine(void){
    sprintf(str,"|" );
    const char *str1="-";
    for (int i = 0;i < TABLE_SIZE ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    str1="|";
    strncat (str,str1,strlen(str1)+1);
    ESP_LOGI(TAG,"%s",str);
    vTaskDelay(10);
    uartDataBackLF(str);
}

void printDeviceStar(void){
    sprintf(str,"|" );
    const char *str1="*";
    for (int i = 0;i < TABLE_SIZE ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    str1="|";
    strncat (str,str1,strlen(str1)+1);
    ESP_LOGI(TAG,"%s",str);
    uartDataBackLF(str);
}


void printHelpTitle(char *text1,char *text2,char *text3,char *text4){
    
    char strc[3]  = " : ";

    sprintf (str,"| " );
    strncat (str,text1,strlen(text1));
    strncat (str,text2,strlen(text2));
    strncat (str,text3,strlen(text3));
    strncat (str,strc,3);
    strncat (str,text4,strlen(text4));
    const char *str1=" ";

    int j = TABLE_SIZE - strlen(str);

    for (int i = 0;i < j ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    text1 = " |";
    strncat (str,text1,strlen(text1)+1);
    ESP_LOGI(TAG,"%s",str);
    uartDataBackLF(str);
}

char *printHelpFirstColumn(char *text){
    sprintf(str,"| " );
    strncat (str,text,strlen(text));

    int j = TABLE_FIRST_COLUMN_SIZE - strlen(str);
    const char *str1=" ";
    for (int i = 0;i < j ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    text = " |";
    strncat (str,text,strlen(text)+1);   
    return str;
}

char *printHelpSecondColumn(char *text, char *text1){
    const char *str1=" ";
    strncat (str,str1,strlen(str1)+1);

    strncat (str,text1,strlen(text1));

    int j = TABLE_SECOND_COLUMN_SIZE - strlen(text1);
    for (int i = 0;i < j ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    text = "|";
    strncat (str,text,strlen(text)+1);   
    return str;
}

void printTableBlank(void){
        const char *str1=" ";

    str1 = printHelpFirstColumn(" ");
    sprintf(str, str1);
    str1 = printHelpSecondColumn(str," ");
    sprintf(str, str1);
    str1 = printHelpSecondColumn(str," ");
    sprintf(str, str1);
    ESP_LOGI(TAG,"%s",str);
    uartDataBackLF(str);
}

void printTableLine(char *text1,char *text2,char *text3,char *text4){
        const char *str1=" ";

    str1 = printHelpFirstColumn(text1);
    sprintf(str, str1);
    str1 = printHelpSecondColumn(str,text2);
    sprintf(str, str1);
    str1 = printHelpSecondColumn(str,text3);
    sprintf(str, str1);
    ESP_LOGI(TAG,"%s",str);
    uartDataBackLF(str);
}

/**
 * @brief Get the From Code Descriptor object
 * 
 * Format : Poid fort :
 *              0001xxxx = Input
 *              0002xxxx = Output
 *          Poid Faible :
 *              xxxx0000 = NULL
 *              xxxx01ss = HEX / ss = size of hexadecimal
 *              xxxx02ss = DEC / ss = size of decimal
 *              xxxx03ss = STR / ss = size of string   
 *  
 * @param input 
 *  * @return char* 
 */

char* getFromCodeDescriptor(uint32_t input){
    static char str1[TABLE_SIZE];
    static char str2[10];


    // Traitement du poid fort

    uint32_t p_fort = (uint32_t)(input >> 16);

    uint8_t size = (uint8_t)(input & 0xFF);

    uint8_t format = (uint8_t)(input >> 8) &0xFF;

    switch(format){
        case 0: 
            snprintf(str2, sizeof(str2), "   ");
            break;
        case 1: 
            snprintf(str2, sizeof(str2), "HEX");
            break;
    }
    
    switch(p_fort){
    case 0: 
        snprintf(str1, sizeof(str1), " ");
        break;
    
    case 1:
        //str1 = "input :    ";
        //sprintf(str1,"input : %02x",0x02);
        snprintf(str1, sizeof(str1), "input : %s%x",str2, (uint8_t)(size & 0xFF));
        break;

    case 2:
        snprintf(str1, sizeof(str1), "Outout : %s%x",str2, (uint8_t)(size & 0xFF));
        break;

    default:
    snprintf(str1, sizeof(str1), "Error ");
    //erreur de formatage
    break;
    }
    return str1;
}

void printTableCode(char *name,uint32_t input,uint32_t output){
        const char *str1=" ";

    str1 = printHelpFirstColumn(name);
    sprintf(str, str1);

    str1 = printHelpSecondColumn(str,getFromCodeDescriptor(input));
    sprintf(str, str1);

    str1 = printHelpSecondColumn(str,getFromCodeDescriptor(output));
    sprintf(str, str1);
    ESP_LOGE(TAG,"%s",str);
    uartDataBackLF(str);
}