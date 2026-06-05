#ifndef SEVEN_SEGMENTS_H
#define SEVEN_SEGMENTS_H

#include <stdint.h>

#define SEVEN_SEGMENTS_DEBUG 0

void initSevenSegments(void);

void writeSegments(char *str);

#endif