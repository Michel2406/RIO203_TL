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

void updateGPSData(const char*, const JsonData *);
void updateColorData(const char *filename, const JsonData *jsonData);

#endif // WRITEDATA_H

