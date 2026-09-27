#include "DataModInterface.h"
#include "Header.h"
#include "framework.h"

#include "CSMAPI_begincode.h"
extern CAVESTORY_MOD_API int gStageNo;
extern CAVESTORY_MOD_API TEXT_SCRIPT gTS;
#include "CSMAPI_endcode.h"
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ShootBullet_None(ShootInfo* sData, int level)
{
}

void DrawSkip()
{
	// This will set the surface that we want to draw on. Passing 'SURFACE_ID_RENDERER_TEXTURE' here tells the rendering pipeline that we want to draw directly to the screen.
	CacheSurface::SetSurfaceID(SURFACE_ID_RENDERER_TEXTURE);
	CacheSurface::DrawBitmapBox(
		new GUI_RECT(16, 16, GUI_POINT(200, 50)),
		GUI_SourceRects::rc_FRAME_EscapeBox,
		CacheSurface::BitmapBoxType::BMPBOX_TYPE_BOTH,
		SURFACE_ID_GUI
	);
	CacheSurface::DrawClippedText(GUI_POINT(24, 24), FontHandle("Courier New", 5, 10), "Press the <Map> key to skip text,",
		CSM_RGBA(255, 255, 255, 255), -1, true, new GUI_POINT(200, 50), 1, CSM_RGBA(0, 0, 0, 150));
	CacheSurface::DrawClippedText(GUI_POINT(24, 36), FontHandle("Courier New", 5, 10), "<NOD, <CLR, and <FAC TSC.",
		CSM_RGBA(255, 255, 255, 255), -1, true, new GUI_POINT(200, 50), 1, CSM_RGBA(0, 0, 0, 150));
	CacheSurface::DrawClippedText(GUI_POINT(24, 48), FontHandle("Courier New", 5, 10), "<Inventory> key to hide this.",
		CSM_RGBA(255, 255, 255, 255), -1, true, new GUI_POINT(200, 50), 1, CSM_RGBA(0, 0, 0, 150));
}

void OnEventFunc()
{
	if (CSM_CaveNet_ConnectedAsClient())
	{
		if (!CSM_CaveNet_IsHosting())
		{
			return;
		}
	}
	char pLocBuffer[256];
	char* pLocPtr = pLocBuffer;
	BOOL clear = false;
	while (gTS.p_read < gTS.size)
	{
		if ((pLocPtr - pLocBuffer) >= sizeof(pLocBuffer) - 1)
			break;

		if (gTS.data[gTS.p_read] == '<') {
			char tsc[4];
			memcpy(tsc, gTS.data + gTS.p_read + 1, sizeof(tsc));
			tsc[3] = 0;
			BOOL cancel = true;
			if (strcmp(tsc, "NOD") == 0) {
				cancel = false;
			}
			else if (strcmp(tsc, "CLR") == 0) {
				clear = true;
				cancel = false;
			}
			else if (strcmp(tsc, "FAC") == 0) {
				cancel = false;
			}
			/* MAY CAUSE PROBLEMS
			else if (strcmp(tsc, "WAI") == 0) {
				cancel = false;
			}
			*/
			if (cancel)
				break;
		}
		*pLocPtr++ = gTS.data[gTS.p_read];
		++gTS.p_read;
	}

	*pLocPtr++ = 0;
	if (clear)
		DisplayCustomTextToScript("<CLR");
	// Clear NOD if we're in NOD mode. Mode of 0 means stopping TSC?
	if (gTS.mode == 2)
		gTS.mode = 1;
}

void OnPreDrawHUDFunc()
{
	if (gTS.current_event == 0)
		return;
	if (gTS.p_read == 0)
		return;
	if (*GetCurrentTextScriptConfig()->GameFlags & 2) {
		return;
	}
	static BOOL skipDraw = false;
	if (GetInput(CSM_KEY_DESC_KEYTRG) & GetKeybind(CSM_KEYBIND_DESC::CSM_KEYBIND_DESC_INVENTORY))
	{
		skipDraw = ~skipDraw;
	}
	if (!skipDraw)
	{
		DrawSkip();
	}
	if (GetInput(CSM_KEY_DESC_KEY) & GetKeybind(CSM_KEYBIND_DESC::CSM_KEYBIND_DESC_MAP))
	{
		OnEventFunc();
	}
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
	CSM_SetHook_OnPreDrawHUD(*OnPreDrawHUDFunc);
	return 0;
}

void DataModInterface::OnShutdown()
{
	delete this;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------