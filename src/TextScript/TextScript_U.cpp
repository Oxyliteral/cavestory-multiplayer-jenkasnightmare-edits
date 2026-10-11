#define _TEXT_SCRIPT_FILE_

#include "../Header.h"
#include <CavestoryModAPI.h>
#include <Subclasses/ModTextScriptCommand.h>

#include <CSMAPI_begincode.h>

ModTextScriptCommand* ModTextScriptCommand::first = NULL;

void SetEquipFlagPlayer(CaveNet::DataStructures::NetPlayer* pPlayer, int argument, bool isAdding)
{
	if (isAdding)
	{
		pPlayer->m_Player.npc.equip |= argument;
	}
	else
	{
		pPlayer->m_Player.npc.equip &= ~argument;
	}
}

void SetEquipFlag(TextScriptTarget target, int argument, bool isAdding)
{
	if (CaveNet_Server_IsHosting())
	{
		switch (target)
		{
		case TextScriptTarget::TS_TARGET_EVERYONE:
		{
			for (int i = 0; i < CaveNet_Server_ClientGroup_GetClientCount(); i++)
			{
				CaveNet::DataStructures::NetClient* pClient = CaveNet_Server_ClientGroup_GetClient(i);
				CaveNet::DataStructures::NetPlayer* pPlayer = pClient->GetPlayer();
				if (!pPlayer)
					continue;
				SetEquipFlagPlayer(pPlayer, argument, isAdding);
			}
			break;
		}
		case TextScriptTarget::TS_TARGET_EXECUTOR_TEAM:
		{
			if (TGetClient && TGetClient->GetTeam())
			{
				CaveNet::DataStructures::NetTeam* pTeam = TGetClient->GetTeam();

				for (int i = 0; i < pTeam->GetMemberCount(); i++)
				{
					CaveNet::DataStructures::NetClient* pClient = pTeam->GetMember(i);
					CaveNet::DataStructures::NetPlayer* pPlayer = pClient->GetPlayer();
					if (!pPlayer)
						continue;
					SetEquipFlagPlayer(pPlayer, argument, isAdding);
				}
				break;
			}
		}
		case TextScriptTarget::TS_TARGET_EXECUTOR:
		{
			if (!TGetPlayer)
				break;
			SetEquipFlagPlayer(TGetPlayer, argument, isAdding);
			break;
		}
		}
	}
	else if (CaveNet_Client_IsConnected())
	{
		switch (target)
		{
		case TextScriptTarget::TS_TARGET_EVERYONE:
		{
			for (int i = 0; i < CaveNet_Client_ClientGroup_GetClientCount(); i++)
			{
				CaveNet::DataStructures::NetClient* pClient = CaveNet_Client_ClientGroup_GetClient(i);
				if (!pClient->GetPlayer())
					continue;
				SetEquipFlagPlayer(pClient->GetPlayer(), argument, isAdding);
			}

			break;
		}
		case TextScriptTarget::TS_TARGET_EXECUTOR_TEAM:
		{
			if (TGetClient && TGetClient->GetTeam())
			{
				CaveNet::DataStructures::NetTeam* pTeam = TGetClient->GetTeam();

				for (int i = 0; i < pTeam->GetMemberCount(); i++)
				{
					CaveNet::DataStructures::NetClient* pClient = pTeam->GetMember(i);
					if (!pClient->GetPlayer())
						continue;
					SetEquipFlagPlayer(pClient->GetPlayer(), argument, isAdding);
				}

				break;
			}
		}
		case TextScriptTarget::TS_TARGET_EXECUTOR:
		{
			if (!TGetClient || !TGetPlayer)
			{
				if (isAdding)
				{
					gMC.equip |= argument;
				}
				else
				{
					gMC.equip &= ~argument;
				}
				break;
			}
			SetEquipFlagPlayer(TGetPlayer, argument, isAdding);

		}
		}
	}
	else
	{
		if (isAdding)
		{
			gMC.equip |= argument;
		}
		else
		{
			gMC.equip &= ~argument;
		};
	}
}

DEFINE_TEXTSCRIPT_COMMAND(U, I, A, "Use Item, to Add equip flag.", "Set an equip flag, this is supposed to replace USE TSC.", "Equip flag")
{
	// READ the args
	x = GetTextScriptNo(gTS.p_read + 4);
	gTS.p_read += 8;
	SetEquipFlag(gTS.target, x, true);
}

DEFINE_TEXTSCRIPT_COMMAND(U, I, R, "Use Item, to Remove equip flag.", "Set an equip flag, this is supposed to replace USE TSC.", "Equip flag")
{
	// READ the args
	x = GetTextScriptNo(gTS.p_read + 4);
	gTS.p_read += 8;
	SetEquipFlag(gTS.target, x, false);
}

#include <CSMAPI_endcode.h>