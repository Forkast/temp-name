#ifndef MAP_HOLDER_H
#define MAP_HOLDER_H

typedef struct MapHolder
{
	int ** map;
	int width;
	int height;
} MapHolder;

/**
 * Konstruktor
 */
MapHolder * MH_createMapHolder();

/**
 * Destruktor
 */
void MH_destroyMapHolder(MapHolder ** MH);

/**
 * Zwraca wartość pixela w (x, y)
 */
int MH_getPixel(const MapHolder * MH, int x, int y);
int MH_getWidth(const MapHolder * MH);
int MH_getHeight(const MapHolder * MH);

#endif /* MAP_HOLDER_H */
