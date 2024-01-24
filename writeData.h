#ifndef WRITEDATA_H
#define WRITEDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char *color;
} JsonData;


void writeData(const char *, const char *, JsonData *);
void updateGPSData(FILE *, const JsonData *);

#endif // WRITEDATA_H

