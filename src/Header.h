#include "framework.h"

#ifndef DRECT
#define DRECT(X, Y, W, H) { X, Y, X + W, Y + H }
#endif

static RECT grcGame = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

void ShootBullet_Snake(ShootInfo* sData, int level);
void ShootBullet_PoleStar(ShootInfo* sData, int level);
void ShootBullet_FireBall(ShootInfo* sData, int level);
void ShootBullet_MachineGun(ShootInfo* sData, int level);
void ShootBullet_NormalMissile(ShootInfo* sData, int level);
void ShootBullet_SuperMissile(ShootInfo* sData, int level);
void ShootBullet_Bubblin1(ShootInfo* sData, int level);
void ShootBullet_Sword(ShootInfo* sData, int level);
void ShootBullet_Nemesis(ShootInfo* sData, int level);
void ShootBullet_Spur(ShootInfo* sData, int level);
void ShootBullet_Agility(ShootInfo* sData, int level);
void ShootBullet_Star(ShootInfo* sData, int level);

void ActBullet_Snake(BULLET* bul, int level);
void ActBullet_PoleStar(BULLET* bul, int level);
void ActBullet_FireBall(BULLET* bul, int level);
void ActBullet_MachineGun(BULLET* bul, int level);
void ActBullet_Missile(BULLET* bul, int level);
void ActBullet_Bom(BULLET* bul, int level);
void ActBullet_Bubblin1(BULLET* bul, int level);
void ActBullet_Bubblin2(BULLET* bul, int level);
void ActBullet_Bubblin3(BULLET* bul, int level);
void ActBullet_Spine(BULLET* bul, int level);
void ActBullet_Edge(BULLET* bul, int level);
void ActBullet_Drop(BULLET* bul, int level);
void ActBullet_Sword1(BULLET* bul, int level);
void ActBullet_Sword2(BULLET* bul, int level);
void ActBullet_Sword3(BULLET* bul, int level);
void ActBullet_SuperMissile(BULLET* bul, int level);
void ActBullet_SuperBom(BULLET* bul, int level);
void ActBullet_Nemesis(BULLET* bul, int level);
void ActBullet_Spur(BULLET* bul, int level);
void ActBullet_SpurTail(BULLET* bul, int level);
void ActBullet_EnemyClear(BULLET* bul, int level);
void ActBullet_Star(BULLET* bul, int level);