

#ifndef DUCK_H_
#define DUCK_H_

#include <stdbool.h>

void duckInit (int difficulty);
void duckUpdate (void);
bool duckIsHit (int hunterPos);
void duckHitAnimation(int hunterPos);
void duckCounter (int shotDownCount);
bool duckIsGameOver(void);

#endif /* DUCK_H_ */
