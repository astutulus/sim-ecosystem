#pragma once

#include <vector>

#include "EntityClasses.h"

int getScreenWidth();
int getScreenHeight();
void CreateScreenBuffer();

void WipeScreenBuffer();
void PaintEntity(Entity*);
void PaintStats(Animal*);
void PaintToScreen();