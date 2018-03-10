#include "map_holder.h"
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

MapHolder * MH_createMapHolder()
{
	MapHolder * MH = malloc(sizeof *MH);
	MH->width = SCREEN_WIDTH;
	MH->height = SCREEN_HEIGHT;
	MH->map = malloc(MH->width * sizeof *(MH->map));
	for (int i = 0; i < MH->width; i++) {
		*(MH->map + i) = malloc(MH->height * sizeof *(*MH->map));
		for (int j = 0; j < MH->height; j++) {
			MH->map[i][j] = ((i + 10) * (j + 10)) %(256*256*256) ;
		}
	}
	return MH;
}

void MH_destroyMapHolder(MapHolder ** MH)
{
	for (int i = 0; i < (*MH)->width; i++) {
		free(*((*MH)->map + i));
	}
	free((*MH)->map);
	free(*MH);
}

int MH_getPixel(const MapHolder * MH, int x, int y)
{
	return MH->map[x][y];
}

int MH_getWidth(const MapHolder * MH)
{
	return MH->width;
}

int MH_getHeight(const MapHolder * MH)
{
	return MH->height;
}
