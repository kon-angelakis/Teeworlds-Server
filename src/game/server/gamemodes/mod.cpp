/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>

#include <game/server/entities/character.h>
#include <game/server/player.h>


#include "mod.h"

CGameControllerMOD::CGameControllerMOD(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	// Exchange this to a string that identifies your game mode.
	// DM, TDM and CTF are reserved for teeworlds original modes.
	m_pGameType = "Hunt";

	//m_GameFlags = GAMEFLAG_TEAMS; // GAMEFLAG_TEAMS makes it a two-team gamemode
}

void CGameControllerMOD::Tick()
{
	// this is the main part of the gamemode, this function is run every tick
	IGameController::Tick();
	StatsTick();
	
}

void CGameControllerMOD::StatsTick()
{
	for(int i=0;i<MAX_CLIENTS;i++){
		if(GameServer()->IsClientReady(i) && GameServer()->m_apPlayers[i]->m_pCharacter
			&& GameServer()->m_apPlayers[i]->m_pCharacter->IsAlive())
		{
			DisplayStats(GameServer()->GetPlayerChar(i)->GetPlayer());
		}
	}
}


void CGameControllerMOD::DisplayStats(class CPlayer *pPlayer)
{
	char aBuf[64];
	switch (pPlayer->m_Killstreak)
	{
	case -1:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup:- ", pPlayer->m_pCharacter->m_Health,
													pPlayer->m_MaxHealth,
													pPlayer->m_pCharacter->m_Armor,
													pPlayer->m_MaxArmor);
		break;
	case 0:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: HEAL", pPlayer->m_pCharacter->m_Health,
													pPlayer->m_MaxHealth,
													pPlayer->m_pCharacter->m_Armor,
													pPlayer->m_MaxArmor);
		break;
	case 1:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: DAMAGE+", pPlayer->m_pCharacter->m_Health,
													pPlayer->m_MaxHealth,
													pPlayer->m_pCharacter->m_Armor,
													pPlayer->m_MaxArmor);
		break;
	case 2:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: AIRSTRIKE", pPlayer->m_pCharacter->m_Health,
													pPlayer->m_MaxHealth,
													pPlayer->m_pCharacter->m_Armor,
													pPlayer->m_MaxArmor);
		break;
	default:
		break;
	}
	GameServer()->SendBroadcast(aBuf, pPlayer->m_ClientID);
	
}

void CGameControllerMOD::OnCharacterSpawn(class CCharacter *pChr)
{
	//IGameController::OnCharacterSpawn(pChr);
	// default health
	pChr->IncreaseHealth(pChr->GetPlayer()->m_MaxHealth/3);
	pChr->GetPlayer()->m_bScore = 0; //(Re)Spawned player has no bounty points

	pChr->GiveWeapon(WEAPON_HAMMER, -1);
	pChr->GiveWeapon(WEAPON_GUN, 10);

}

int CGameControllerMOD::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	//IGameController::OnCharacterDeath(pVictim, pKiller, Weapon);
	
	int mScoreToBeAdded = 0;
	char aBufKB[64] = {}; //Killed Bounty
	pKiller->m_bScore++;
	
	// do scoreing
	if(!pKiller || Weapon == WEAPON_GAME)
		return 0;
	if(!(pKiller == pVictim->GetPlayer()))
	{
		if(!(IsTeamplay() && pVictim->GetPlayer()->GetTeam() == pKiller->GetTeam()))
		{
			if(pKiller->m_bScore >= 5) //Killer has bounty
			{
				if(pVictim->GetPlayer()->m_bScore >= 5)
				{
					mScoreToBeAdded = pKiller->m_bScore/4 + pVictim->GetPlayer()->m_bScore; // bounty kill another bounty
					str_format(aBufKB, sizeof(aBufKB), "'%s' has claimed the bounty (%ix) of '%s'", Server()->ClientName(pKiller->GetCID()),
																								pVictim->GetPlayer()->m_bScore,
																								Server()->ClientName(pVictim->GetPlayer()->GetCID()));
				}
				else
				{
					mScoreToBeAdded = pKiller->m_bScore/4;	// default bounty kill on non bounty
				}
			
				{ //Change killers clan to their bounty
					char aBuf[64];
					str_format(aBuf, sizeof(aBuf), "%ix BOUNTY", pKiller->m_bScore);
					Server()->SetClientClan(pKiller->GetCID(), aBuf);		
				}
			}
			else
			{
				if(pVictim->GetPlayer()->m_bScore >= 5){
					mScoreToBeAdded = 1 + pVictim->GetPlayer()->m_bScore;
					str_format(aBufKB, sizeof(aBufKB), "'%s' has claimed the bounty (%ix) of '%s'", Server()->ClientName(pKiller->GetCID()),
																								pVictim->GetPlayer()->m_bScore,
																								Server()->ClientName(pVictim->GetPlayer()->GetCID()));
				}
				else
				{
					mScoreToBeAdded = 1;
				}
			}

			if(pKiller->m_bScore%5==0){ // Announce it to all chat every %5 bounties
				char aBuf[64];
				str_format(aBuf, sizeof(aBuf), "'%s' has now a bounty of %i!", Server()->ClientName(pKiller->GetCID()), 
																				pKiller->m_bScore);
				GameServer()->SendChat(-1, CGameContext::CHAT_ALL, aBuf);
			}

			if(aBufKB!=nullptr)
				GameServer()->SendChat(-1, CGameContext::CHAT_ALL, aBufKB);

			pKiller->m_Score += mScoreToBeAdded;
			Server()->SetClientClan(pVictim->GetPlayer()->GetCID(), "");
			pVictim->GetPlayer()->m_bScore = 0;

		}
	}
	if(Weapon == WEAPON_SELF)
		pVictim->GetPlayer()->m_RespawnTick = Server()->Tick()+Server()->TickSpeed()*3.0f;


	pVictim->GetPlayer()->m_bScore = 0; //Reset bounty
	Server()->SetClientClan(pVictim->GetPlayer()->GetCID(), "");

	if(pKiller->m_bScore >= 5)
		CGameControllerMOD::CheckForKillstreak(pKiller);

	return 0;

}

void CGameControllerMOD::CheckForKillstreak(class CPlayer *pPlayer)
{
	char aBuf[64]={};
	switch (pPlayer->m_bScore)
	{
	case 5:
		str_format(aBuf, sizeof(aBuf), "You got (HEAL). Use it with your hammer.");
		pPlayer->m_Killstreak = KS_HEAL;
		break;
	case 10:
		str_format(aBuf, sizeof(aBuf), "You got (DAMAGE+). Use it with your hammer.");
		pPlayer->m_Killstreak = KS_DAMAGE;
		break;
	case 15:
		str_format(aBuf, sizeof(aBuf), "You got (AIRSTRIKE). Use it with your hammer.");
		pPlayer->m_Killstreak = KS_AIRSTRIKE;
		break;
	default:
		break;
	}
	if(aBuf != nullptr)
		GameServer()->SendChatTarget(pPlayer->GetCID(), aBuf);
}
