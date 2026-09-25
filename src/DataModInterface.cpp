#define _TEXT_SCRIPT_FILE_

#include "DataModInterface.h"
#include "Header.h"
#include "framework.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ShootBullet_None(ShootInfo* sData, int level)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int DataModInterface::OnInit()
{
	CSM_RegisterWeapon(0, ShootBullet_None);
	CSM_RegisterWeapon(1, ShootBullet_Snake);
	CSM_RegisterWeapon(2, ShootBullet_PoleStar);
	CSM_RegisterWeapon(3, ShootBullet_FireBall);
	CSM_RegisterWeapon(4, ShootBullet_MachineGun);
	CSM_RegisterWeapon(5, ShootBullet_NormalMissile);
	CSM_RegisterWeapon(7, ShootBullet_Bubblin1);
	CSM_RegisterWeapon(9, ShootBullet_Sword);
	CSM_RegisterWeapon(10, ShootBullet_SuperMissile);
	CSM_RegisterWeapon(12, ShootBullet_Nemesis);
	CSM_RegisterWeapon(13, ShootBullet_Spur);
	CSM_RegisterWeapon(14, ShootBullet_Agility);
	CSM_RegisterWeapon(15, ShootBullet_Star);
	CSM_RegisterWeapon(16, ShootBullet_None);
	CSM_RegisterBullet(3, ActBullet_Snake);
	CSM_RegisterBullet(4, ActBullet_Snake);
	CSM_RegisterBullet(5, ActBullet_Snake);
	CSM_RegisterBullet(6, ActBullet_PoleStar);
	CSM_RegisterBullet(7, ActBullet_PoleStar);
	CSM_RegisterBullet(8, ActBullet_PoleStar);
	CSM_RegisterBullet(9, ActBullet_FireBall);
	CSM_RegisterBullet(10, ActBullet_FireBall);
	CSM_RegisterBullet(11, ActBullet_FireBall);
	CSM_RegisterBullet(12, ActBullet_MachineGun);
	CSM_RegisterBullet(13, ActBullet_MachineGun);
	CSM_RegisterBullet(14, ActBullet_MachineGun);
	CSM_RegisterBullet(15, ActBullet_Missile);
	CSM_RegisterBullet(16, ActBullet_Missile);
	CSM_RegisterBullet(17, ActBullet_Missile);
	CSM_RegisterBullet(18, ActBullet_Bom);
	CSM_RegisterBullet(19, ActBullet_Bom);
	CSM_RegisterBullet(20, ActBullet_Bom);
	CSM_RegisterBullet(21, ActBullet_Bubblin1);
	CSM_RegisterBullet(22, ActBullet_Bubblin2);
	CSM_RegisterBullet(23, ActBullet_Bubblin3);
	CSM_RegisterBullet(24, ActBullet_Spine);
	CSM_RegisterBullet(25, ActBullet_Edge);
	CSM_RegisterBullet(26, ActBullet_Drop);
	CSM_RegisterBullet(27, ActBullet_Sword1);
	CSM_RegisterBullet(28, ActBullet_Sword2);
	CSM_RegisterBullet(29, ActBullet_Sword3);
	CSM_RegisterBullet(30, ActBullet_SuperMissile);
	CSM_RegisterBullet(31, ActBullet_SuperMissile);
	CSM_RegisterBullet(32, ActBullet_SuperMissile);
	CSM_RegisterBullet(33, ActBullet_SuperBom);
	CSM_RegisterBullet(34, ActBullet_SuperBom);
	CSM_RegisterBullet(35, ActBullet_SuperBom);
	CSM_RegisterBullet(36, ActBullet_Nemesis);
	CSM_RegisterBullet(37, ActBullet_Nemesis);
	CSM_RegisterBullet(38, ActBullet_Nemesis);
	CSM_RegisterBullet(39, ActBullet_Spur);
	CSM_RegisterBullet(40, ActBullet_Spur);
	CSM_RegisterBullet(41, ActBullet_Spur);
	CSM_RegisterBullet(42, ActBullet_SpurTail);
	CSM_RegisterBullet(43, ActBullet_SpurTail);
	CSM_RegisterBullet(44, ActBullet_SpurTail);
	CSM_RegisterBullet(45, ActBullet_Nemesis);
	CSM_RegisterBullet(46, ActBullet_EnemyClear);
	CSM_RegisterBullet(47, ActBullet_Star);
	return 0;
}

void DataModInterface::OnShutdown()
{
	delete this;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------