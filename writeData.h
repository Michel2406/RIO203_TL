#ifndef WRITEDATA_H
#define WRITEDATA_H

typedef struct {
    double latitude;
    double longitude;
    char couleurFeu[20];
} JsonData;

void writeData(const char *filename, const char *updateType, const JsonData *jsonData);

#endif // WRITEDATA_H

