#ifndef WRITEDATA_H
#define WRITEDATA_H

typedef struct {
    double latitude;
    double longitude;
    char *color;
} JsonData;

extern JsonData * dataToSend;


void writeData(const char *filename, const char *updateType, JsonData *jsonData);

#endif // WRITEDATA_H

