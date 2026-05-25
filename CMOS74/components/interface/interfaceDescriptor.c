#include <stdio.h>
#include <string.h>
#include "interfaceDescriptor.h"
#include "interface.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"


#define TAG "Interface Descriptor"


    char str[50] = "TOTO";

void printDeviceLine(void){
    sprintf(str,"|" );
    const char *str1="-";
    for (int i = 0;i < TABLE_SIZE ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    str1="|";
    strncat (str,str1,strlen(str1)+1);
    ESP_LOGE(TAG,"%s",str);
    uartDataBack(str);
}

void printDeviceStar(void){
    sprintf(str,"|" );
    const char *str1="*";
    for (int i = 0;i < TABLE_SIZE ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    str1="|";
    strncat (str,str1,strlen(str1)+1);
    ESP_LOGE(TAG,"%s",str);
    uartDataBack(str);
}


void printHelpTitle(char *text1,char *text2,char *text3,char *text4){
    sprintf (str,"| " );
    strncat (str,text1,strlen(text1));
    strncat (str,text2,strlen(text2));
    strncat (str,text3,strlen(text3));
    strncat (str,text4,strlen(text4));
    const char *str1=" ";

    int j = TABLE_SIZE - strlen(str);

    for (int i = 0;i < j ; i++){
        strncat (str,str1,strlen(str1)+1);
    }
    text1 = " |";
    strncat (str,text1,strlen(text1)+1);
    ESP_LOGE(TAG,"%s",str);
    uartDataBack(str);
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
    ESP_LOGE(TAG,"%s",str);
    uartDataBack(str);
}

void printTableBLine(char *text1,char *text2,char *text3,char *text4){
        const char *str1=" ";

    str1 = printHelpFirstColumn(text1);
    sprintf(str, str1);
    str1 = printHelpSecondColumn(str,text2);
    sprintf(str, str1);
    str1 = printHelpSecondColumn(str,text3);
    sprintf(str, str1);
    ESP_LOGE(TAG,"%s",str);
    uartDataBack(str);
}