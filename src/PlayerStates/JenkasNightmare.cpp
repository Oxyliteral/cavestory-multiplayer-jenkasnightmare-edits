#include "../Header.h"
#include "PlayerStates.h"
#include <Subclasses/CustomPlayer.h>

void DrawCharacter(int fx, int fy, SafeClientInterface* pInterface, float fScale)
{
	MYCHAR* pMC = pInterface->mMC;

	if ((pMC->cond & 0x80) == 0 || (pMC->cond & 2) || (((pMC->shock / 2) % 2) && !pMC->dont_flash_shock))
		return;

	// Draw player
	RECT rect = pMC->rect;
	int iHeight = (pMC->rect.bottom - pMC->rect.top);
	bool fishing = pMC->character->GetFrameFlags((PlayerAnimFrame)pMC->anim_info.curr_anim) & PlayerAnimFlags::PAF_FISHING;
	if (pMC->equip & 512)
	{
		if (!fishing)
		{
			rect.top += iHeight * 4;
			rect.bottom += iHeight * 4;
		}
	}
	else if (pMC->equip & 0x40 && (!pMC->character || !(pMC->character->GetFrameFlags((PlayerAnimFrame)pMC->anim_info.curr_anim) & PlayerAnimFlags::PAF_MIMIGA_MASK)))
	{
		if (!fishing)
		{
			rect.top += iHeight * 2;
			rect.bottom += iHeight * 2;
		}
	}
	RECT rcBubble[2] =
	{
		{56, 96, 80, 120},
		{80, 96, 104, 120},
	};

	// Increment the bubble thing
	++pMC->bubble;

	// Draw the character
	if (fScale != 1.f)
	{
		GUI_POINT pPlayerPnt
		(
			SubpixelToScreenCoord(pMC->x - pMC->view.left) - SubpixelToScreenCoord(fx),
			SubpixelToScreenCoord(pMC->y - pMC->view.top) - SubpixelToScreenCoord(fy)
		);

		GUI_POINT pPlayerBottomCenter
		(
			SubpixelToScreenCoord(pMC->x) - SubpixelToScreenCoord(fx),
			SubpixelToScreenCoord(pMC->y + pMC->view.bottom) - SubpixelToScreenCoord(fy)
		);

		pPlayerPnt = SCALE_GUI_POINT(pPlayerPnt, pPlayerBottomCenter, fScale);

		RECT rcPlayerDrawRect =
		{
			pPlayerPnt.x,
			pPlayerPnt.y,
			pPlayerPnt.x + int(PixelToScreenCoord(RECT_WIDTH(gMC.rect)) * fScale),
			pPlayerPnt.y + int(PixelToScreenCoord(RECT_HEIGHT(gMC.rect)) * fScale)
		};

		// Draw the character
		PutBitmap17(&rcPlayerDrawRect, &rect, (Surface_Ids)pMC->character->mNormalSurfaceId);

		// Don't forget the mask
		if (pMC->use_char_color)
		{
			ModBitmap((Surface_Ids)pMC->character->mMaskSurfaceId, RGB(pMC->col_r, pMC->col_g, pMC->col_b));
			PutBitmap17(&rcPlayerDrawRect, &rect, (Surface_Ids)pMC->character->mMaskSurfaceId);
			ClearBitmapMod((Surface_Ids)pMC->character->mMaskSurfaceId);
		}

		if ((pMC->equip & 0x10 && pMC->flag & 0x100) || (GetPlayerStateFlags(&gMC) & PLAYER_STATE_FLAGS::PSF_PUT_BUBBLE))
		{
			GUI_POINT pBubbleDrawPnt(SubpixelToScreenCoord(pMC->x) - PixelToScreenCoord(12) - SubpixelToScreenCoord(fx), SubpixelToScreenCoord(pMC->y) - PixelToScreenCoord(12) - SubpixelToScreenCoord(fy));

			pBubbleDrawPnt = SCALE_GUI_POINT(pBubbleDrawPnt, pPlayerBottomCenter, fScale);

			RECT rcBubbleDrawRect =
			{
				pBubbleDrawPnt.x,
				pBubbleDrawPnt.y,
				pBubbleDrawPnt.x + int(PixelToScreenCoord(RECT_WIDTH(rcBubble[(pMC->bubble / 2) % 2])) * fScale),
				pBubbleDrawPnt.y + int(PixelToScreenCoord(RECT_HEIGHT(rcBubble[(pMC->bubble / 2) % 2])) * fScale)
			};

			PutBitmap17(&rcBubbleDrawRect, &rcBubble[(pMC->bubble / 2) % 2], SURFACE_ID_CARET);
		}
	}
	else
	{
		// Draw the character
		PutBitmap3(&grcGame, SubpixelToScreenCoord(pMC->x - pMC->view.left) - SubpixelToScreenCoord(fx), SubpixelToScreenCoord(pMC->y - pMC->view.top) - SubpixelToScreenCoord(fy), &rect, (Surface_Ids)pMC->character->mNormalSurfaceId);

		// Don't forget the mask
		if (pMC->use_char_color)
			PutBitmap8(&grcGame, SubpixelToScreenCoord(pMC->x - pMC->view.left) - SubpixelToScreenCoord(fx), SubpixelToScreenCoord(pMC->y - pMC->view.top) - SubpixelToScreenCoord(fy), &rect, (Surface_Ids)pMC->character->mMaskSurfaceId, pMC->col_r, pMC->col_g, pMC->col_b);

		// Draw air tank
		if ((pMC->equip & 0x10 && pMC->flag & 0x100) || (GetPlayerStateFlags(&gMC) & PLAYER_STATE_FLAGS::PSF_PUT_BUBBLE))
			PutBitmap3(&grcGame, SubpixelToScreenCoord(pMC->x) - PixelToScreenCoord(12) - SubpixelToScreenCoord(fx), SubpixelToScreenCoord(pMC->y) - PixelToScreenCoord(12) - SubpixelToScreenCoord(fy), &rcBubble[(pMC->bubble / 2) % 2], SURFACE_ID_CARET);
	}
}


// Same as in vanilla
IMPLEMENT_PLAYER_STATE_DRAW(JENKASNIGHTMARE)
{
	CSM_PlayerState_DrawWeapon(iFrameX, iFrameY, pInterface, 1.0F);
	DrawCharacter(iFrameX, iFrameY, pInterface, 1.0F);
}

// Same as in vanilla
IMPLEMENT_PLAYER_STATE_ACT(JENKASNIGHTMARE)
{
	// Get speeds and accelerations
	int max_move;
	int max_dash;
	int gravity1;
	int gravity2;
	int jump;
	int dash1;
	int dash2;
	int resist;

	int a;
	int x;

	if (pMC->cond & 2)
		return;

	max_dash = physics->max_dash;
	max_move = physics->max_move;
	gravity1 = physics->gravity1;
	gravity2 = physics->gravity2;
	jump = physics->jump;
	dash1 = physics->dash1;
	dash2 = physics->dash2;
	resist = physics->resist;

	// Don't create "?" effect
	pMC->ques = 0;

	// If we can't control player, stop boosting
	if (!bKey)
		pMC->boost_sw = 0;

	// Movement on the ground
	if (pMC->flag & 8 || pMC->flag & 0x10 || pMC->flag & 0x20)
	{
		// Stop boosting and refuel
		pMC->boost_sw = 0;

		if (pMC->equip & 1)
		{
			pMC->boost_cnt = pMC->boost_max;
		}
		else if (pMC->equip & 0x20)
		{
			pMC->boost_cnt = pMC->boost_max;
		}
		else
		{
			pMC->boost_cnt = 0;
		}

		// Move in direction held
		if (bKey)
		{
			if (KEYTRG == gKeyDown && KEY == gKeyDown && (pMC->cond & 1) == 0 && (GAMEFLAGS & 4) == 0)
			{
				pMC->cond |= 1;
				pMC->ques = 1;
			}
			else if (KEY == gKeyDown)
			{

			}
			else
			{
				if (KEY & gKeyLeft && pMC->xm > -max_dash)
					pMC->xm -= dash1;
				if (KEY & gKeyRight && pMC->xm < max_dash)
					pMC->xm += dash1;

				if (KEY & gKeyLeft)
					pMC->direct = 0;
				if (KEY & gKeyRight)
					pMC->direct = 2;
			}
		}

		// Friction
		if (!(pMC->cond & 0x20))
		{
			if (pMC->xm < 0)
			{
				if (pMC->xm > -resist)
					pMC->xm = 0;
				else
					pMC->xm += resist;
			}
			if (pMC->xm > 0)
			{
				if (pMC->xm < resist)
					pMC->xm = 0;
				else
					pMC->xm -= resist;
			}
		}
	}
	else
	{
		// Start boosting
		if (bKey)
		{
			if (pMC->equip & 0x21 && KEYTRG & gKeyJump && pMC->boost_cnt)
			{
				// Booster 0.8
				if (pMC->equip & 1)
				{
					pMC->boost_sw = 1;
					if (pMC->ym > 0x100)
						pMC->ym /= 2;
				}

				// Booster 2.0
				if (pMC->equip & 0x20)
				{
					if (KEY & gKeyUp)
					{
						pMC->boost_sw = 2;
						pMC->xm = 0;
						pMC->ym = -0x5FF;
					}
					else if (KEY & gKeyLeft)
					{
						pMC->boost_sw = 1;
						pMC->ym = 0;
						pMC->xm = -0x5FF;
					}
					else if (KEY & gKeyRight)
					{
						pMC->boost_sw = 1;
						pMC->ym = 0;
						pMC->xm = 0x5FF;
					}
					else if (KEY & gKeyDown)
					{
						pMC->boost_sw = 3;
						pMC->xm = 0;
						pMC->ym = 0x5FF;
					}
					else
					{
						pMC->boost_sw = 2;
						pMC->xm = 0;
						pMC->ym = -0x5FF;
					}
				}
			}

			// Move left and right
			if (KEY & gKeyLeft && pMC->xm > -max_dash)
				pMC->xm -= dash2;
			if (KEY & gKeyRight && pMC->xm < max_dash)
				pMC->xm += dash2;

			if (KEY & gKeyLeft)
				pMC->direct = 0;
			if (KEY & gKeyRight)
				pMC->direct = 2;
		}

		// Slow down when stopped boosting (Booster 2.0)
		if (pMC->equip & 0x20 && pMC->boost_sw && (!(KEY & gKeyJump) || !pMC->boost_cnt))
		{
			if (pMC->boost_sw == 1)
				pMC->xm /= 2;
			else if (pMC->boost_sw == 2)
				pMC->ym /= 2;
		}

		// Stop boosting
		if (!pMC->boost_cnt || !(KEY & gKeyJump))
			pMC->boost_sw = 0;
	}

	// Jumping
	if (bKey)
	{
		// Look up and down
		if (KEY & gKeyUp)
			pMC->up = TRUE;
		else
			pMC->up = FALSE;

		if (KEY & gKeyDown && (pMC->flag & 8) == 0)
			pMC->down = TRUE;
		else
			pMC->down = FALSE;

		if (KEYTRG & gKeyJump
			&& (pMC->flag & 8 || pMC->flag & 0x10 || pMC->flag & 0x20))
		{
			if (pMC->flag & 0x2000)
			{
				// Another weird empty case needed for accurate assembly
			}
			else
			{
				pMC->ym = -jump;
				PlaySoundObject2D(pMC->x, pMC->y, 0, true, 15, 1);
			}
		}
	}

	// Stop interacting when moved
	if (bKey && (gKeyShot | gKeyJump | gKeyUp | gKeyRight | gKeyLeft) & KEY)
		pMC->cond &= ~1;

	// Booster losing fuel
	if (pMC->boost_sw && pMC->boost_cnt)
		--pMC->boost_cnt;

	// Wind / current forces
	if (pMC->flag & 0x1000)
		pMC->xm -= 0x88;
	if (pMC->flag & 0x2000)
		pMC->ym -= 0x80;
	if (pMC->flag & 0x4000)
		pMC->xm += 0x88;
	if (pMC->flag & 0x8000)
		pMC->ym += 0x55;

	// Booster 2.0 forces and effects
	if (pMC->equip & 0x20 && pMC->boost_sw)
	{
		if (pMC->boost_sw == 1)
		{
			// Go up when going into a wall
			if (pMC->flag & 5)
				pMC->ym = -0x100;

			// Move in direction facing
			if (!pMC->direct)
				pMC->xm -= 0x20;
			if (pMC->direct == 2)
				pMC->xm += 0x20;

			// Boost particles (and sound)
			if (KEYTRG & gKeyJump || pMC->boost_cnt % 3 == 1)
			{
				if (!pMC->direct)
					SetCaret(pMC->x + 0x400, pMC->y + 0x400, 7, 2);
				if (pMC->direct == 2)
					SetCaret(pMC->x - 0x400, pMC->y + 0x400, 7, 0);

				PlaySoundObject2D(pMC->x, pMC->y, 0, true, 113, 1);
			}
		}
		else if (pMC->boost_sw == 2)
		{
			// Move upwards
			pMC->ym -= 0x20;

			// Boost particles (and sound)
			if (KEYTRG & gKeyJump || pMC->boost_cnt % 3 == 1)
			{
				SetCaret(pMC->x, pMC->y + 0xC00, 7, 3);
				PlaySoundObject2D(pMC->x, pMC->y, 0, true, 113, 1);
			}
		}
		else if (pMC->boost_sw == 3 && (KEYTRG & gKeyJump || pMC->boost_cnt % 3 == 1))
		{
			// Boost particles (and sound)
			SetCaret(pMC->x, pMC->y - 0xC00, 7, 1);
			PlaySoundObject2D(pMC->x, pMC->y, 0, true, 113, 1);
		}
	}
	// Upwards wind/current
	else if (pMC->flag & 0x2000)
	{
		pMC->ym += gravity1;
	}
	// Booster 0.8
	else if (pMC->equip & 1 && pMC->boost_sw && pMC->ym > -0x400)
	{
		// Upwards force
		pMC->ym -= 0x20;

		if (!(pMC->boost_cnt % 3))
		{
			SetCaret(pMC->x, pMC->hit.bottom / 2 + pMC->y, 7, 3);
			PlaySoundObject2D(pMC->x, pMC->y, 0, true, 113, 1);
		}

		// Bounce off of ceiling
		if (pMC->flag & 2)
			pMC->ym = 0x200;
	}
	// Gravity while jump is held
	else if (pMC->ym < 0 && bKey && KEY & gKeyJump)
	{
		pMC->ym += gravity2;
	}
	// Normal gravity
	else
	{
		pMC->ym += gravity1;
	}

	// Keep player on slopes
	if (!bKey || !(KEYTRG & gKeyJump))
	{
		if (pMC->flag & 0x10 && pMC->xm < 0)
			pMC->ym = -pMC->xm;
		if (pMC->flag & 0x20 && pMC->xm > 0)
			pMC->ym = pMC->xm;
		if (pMC->flag & 8 && pMC->flag & 0x80000 && pMC->xm < 0)
			pMC->ym = 0x400;
		if (pMC->flag & 8 && pMC->flag & 0x10000 && pMC->xm > 0)
			pMC->ym = 0x400;
		if (pMC->flag & 8 && pMC->flag & 0x20000 && pMC->flag & 0x40000)
			pMC->ym = 0x400;
	}

	// Limit speed
	if (pMC->flag & 0x100 && !(pMC->flag & (0x8000 | 0x4000 | 0x2000 | 0x1000)))
		max_move = pMC->physics_underwater.max_move;	// Underwater or in wind
	else
		max_move = pMC->physics_normal.max_move;	// Normal conditions

	if (pMC->xm < -max_move)
		pMC->xm = -max_move;
	if (pMC->xm > max_move)
		pMC->xm = max_move;
	if (pMC->ym < -max_move)
		pMC->ym = -max_move;
	if (pMC->ym > max_move)
		pMC->ym = max_move;

	// Water splashing
	if (!pMC->ignore_water && !pMC->sprash && pMC->flag & 0x100)
	{
		int dir;
		if (pMC->flag & 0x800)
			dir = 2;
		else
			dir = 0;

		if ((pMC->flag & 8) == 0 && pMC->ym > 0x200)
		{
			for (a = 0; a < 8; a++)
			{
				x = pMC->x + (Random(-8, 8) * 0x200);
				SetNpChar(73, x, pMC->y, pMC->xm + Random(-0x200, 0x200), Random(-0x200, 0x80) - pMC->ym / 2, dir, 0, 0);
			}

			PlaySoundObject2D(pMC->x, pMC->y, 0, true, 56, 1);
		}
		else
		{
			if (pMC->xm > 0x200 || pMC->xm < -0x200)
			{
				for (a = 0; a < 8; a++)
				{
					x = pMC->x + (Random(-8, 8) * 0x200);
					SetNpChar(73, x, pMC->y, pMC->xm + Random(-0x200, 0x200), Random(-0x200, 0x80), dir, 0, 0);
				}

				PlaySoundObject2D(pMC->x, pMC->y, 0, true, 56, 1);
			}
		}

		pMC->sprash = 1;
	}

	if (!(pMC->flag & 0x100))
		pMC->sprash = 0;

	// Spike damage
	if ((pMC->flag & 0x400) && (!CaveNet_Client_IsConnected() || CaveNet_Server_IsHosting()))
		pInterface->DamagePlayer(10);

	// Change position
	if (pMC->xm > resist || pMC->xm < -resist)
		pMC->x += pMC->xm;

	pMC->y += pMC->ym;
}

// Same as in vanilla
IMPLEMENT_PLAYER_STATE_ANIM(JENKASNIGHTMARE)
{
	PlayerAnimation iAnimType = PlayerAnimation::ANIMATION_IDLE;

	if (!(pMC->cond & 2))
	{
		if ((*pInterface->mKeyTrg) & gKeyShot)
		{
			if (pMC->flag & 8)
			{
				// On ground
				if (pMC->cond & 1)
					iAnimType = PlayerAnimation::ANIMATION_IDLE_SHOOT;
				else if ((KEY & gKeyUp) && ((gKeyRight | gKeyLeft) & KEY) && bKey)
					iAnimType = PlayerAnimation::ANIMATION_IDLE_LOOK_UP_SHOOT;
				else if (((gKeyRight | gKeyLeft) & KEY) && bKey)
					iAnimType = PlayerAnimation::ANIMATION_WALK_SHOOT;
				else if ((KEY & gKeyUp) && bKey)
					iAnimType = PlayerAnimation::ANIMATION_IDLE_LOOK_UP_SHOOT;
				else
					iAnimType = PlayerAnimation::ANIMATION_IDLE_SHOOT;
			}
			else if (pMC->up)
			{
				if (pMC->ym > 0) // Fall
					iAnimType = PlayerAnimation::ANIMATION_FALL_LOOK_UP_SHOOT;
				else // Jump
					iAnimType = PlayerAnimation::ANIMATION_JUMP_LOOK_UP_SHOOT;
			}
			else if (pMC->down)
			{
				if (pMC->ym > 0) // Fall
					iAnimType = PlayerAnimation::ANIMATION_FALL_LOOK_DOWN_SHOOT;
				else // Jump
					iAnimType = PlayerAnimation::ANIMATION_JUMP_LOOK_DOWN_SHOOT;
			}
			else
			{
				if (pMC->ym > 0) // Fall
					iAnimType = PlayerAnimation::ANIMATION_FALL_SHOOT;
				else // Jump
					iAnimType = PlayerAnimation::ANIMATION_JUMP_SHOOT;
			}
		}
		else if (pMC->flag & 8)
		{
			// On ground
			if (pMC->cond & 1)
				iAnimType = PlayerAnimation::ANIMATION_SEARCH;
			else if ((KEY & gKeyUp) && ((gKeyRight | gKeyLeft) & KEY) && bKey)
				iAnimType = PlayerAnimation::ANIMATION_WALK_LOOK_UP;
			else if (((gKeyRight | gKeyLeft) & KEY) && bKey)
				iAnimType = PlayerAnimation::ANIMATION_WALK;
			else if ((KEY & gKeyUp) && bKey)
				iAnimType = PlayerAnimation::ANIMATION_IDLE_LOOK_UP;
			else
				iAnimType = PlayerAnimation::ANIMATION_IDLE;
		}
		else if (pMC->up)
		{
			if (pMC->ym > 0) // Fall
				iAnimType = PlayerAnimation::ANIMATION_FALL_LOOK_UP;
			else // Jump
				iAnimType = PlayerAnimation::ANIMATION_JUMP_LOOK_UP;
		}
		else if (pMC->down)
		{
			if (pMC->ym > 0) // Fall
				iAnimType = PlayerAnimation::ANIMATION_FALL_LOOK_DOWN;
			else // Jump
				iAnimType = PlayerAnimation::ANIMATION_JUMP_LOOK_DOWN;
		}
		else
		{
			if (pMC->ym > 0) // Fall
				iAnimType = PlayerAnimation::ANIMATION_FALL;
			else // Jump
				iAnimType = PlayerAnimation::ANIMATION_JUMP;
		}
	}
	return iAnimType;
}