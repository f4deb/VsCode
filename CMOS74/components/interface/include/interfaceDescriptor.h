#ifndef INTERFACE_DESCRIPTOR_H
#define INTERFACE_DESCRIPTOR_H

#define INTERFACE_DESCRIPTOR_DEBUG 0

#define TABLE_SIZE 52
#define TABLE_FIRST_COLUMN_SIZE 18
#define TABLE_SECOND_COLUMN_SIZE 15
#define TABLE_THIRD_COLUMN_SIZE 16

void printDeviceLine(void);
void printDeviceStar(void);
void printHelpTitle(char *text1,char *text2,char *text3,char *text4);
char *printHelpFirstColumn(char *text);
char *printHelpSecondColumn(char *text, char *text1);
void printTableBlank(void);
void printTableBLine(char *text1,char *text2,char *text3,char *text4);



#endif