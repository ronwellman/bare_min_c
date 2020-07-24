#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>

struct item {
	char *name;
};

struct inventory {
	size_t maxItems;   // max items
	size_t totalItems; // current items
	struct item *items;// array of pointers to items
};

typedef struct player {
	struct inventory inv;//player's inventory
	char *name;
} player_t;

player_t *
createPlayer();

bool
addItem(player_t *);

void
listItems(const player_t *);

bool
destroyPlayer(player_t **);

#endif
