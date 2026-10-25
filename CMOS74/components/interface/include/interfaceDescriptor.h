#ifndef INTERFACE_DESCRIPTOR_H
#define INTERFACE_DESCRIPTOR_H

#include <stdbool.h>


#define INTERFACE_DESCRIPTOR_DEBUG 0

#define TABLE_SIZE 58
#define TABLE_FIRST_COLUMN_SIZE 22
#define TABLE_SECOND_COLUMN_SIZE 16
#define TABLE_THIRD_COLUMN_SIZE 16

#define INTERFACE_DESCRIPTOR_INDEX_SIZE 20

typedef struct
{
    bool isInit;        
    int index;
    char *name;
    char *command;
    char *description;   
    int *objet;
}InterfaceDescriptor;

typedef struct
{
    bool isInit;
    uint8_t indexMax;
    uint8_t indexSize;
    uint8_t currentIndex;
    InterfaceDescriptor map[INTERFACE_DESCRIPTOR_INDEX_SIZE];
}InterfaceList;


void printDeviceLine(void);
void printDeviceStar(void);
void printHelpTitle(char *text1,char *text2,char *text3,char *text4);
char *printHelpFirstColumn(char *text);
char *printHelpSecondColumn(char *text, char *text1);
void printTableBlank(void);
void printTableLine(char *text1,char *text2,char *text3,char *text4);

void printTableCode(char *name,uint16_t input,uint16_t output);


#endif