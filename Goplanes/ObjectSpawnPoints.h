#ifndef OBJECT_SPAWN_POINTS_INCLUDE_H
#define OBJECT_SPAWN_POINTS_INCLUDE_H

typedef struct
{
    unsigned short			x;
	unsigned short			y;
    unsigned short          objectType;
} ObjectSpawnPoint;

typedef struct
{
    unsigned short          numObjectSpawnPoints;
    const ObjectSpawnPoint* objectSpawnPoints;
} ObjectSpawnPoints;

#endif
