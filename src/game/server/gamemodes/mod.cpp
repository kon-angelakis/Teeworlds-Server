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
	m_pGameType = "HUNT";

	//m_GameFlags = GAMEFLAG_TEAMS; // GAMEFLAG_TEAMS makes it a two-team gamemode
}

void CGameControllerMOD::Tick()
{
	// this is the main part of the gamemode, this function is run every tick
	IGameController::Tick();
	StatsTick();
	KillstreakTick();	
}

void CGameControllerMOD::StatsTick()
{
	for(int i=0;i<MAX_CLIENTS;i++){
		if(GameServer()->IsClientReady(i) && GameServer()->m_apPlayers[i]->m_pCharacter
			&& GameServer()->m_apPlayers[i]->m_pCharacter->IsAlive())
		{
			DisplayStats(GameServer()->GetPlayerChar(i));
		}
	}
}

void CGameControllerMOD::DisplayStats(class CCharacter *pChr)
{
	char aBuf[64];
	switch (pChr->m_Killstreak)
	{
	case NO_KILLSTREAK:
		if(pChr->m_DamageMult != 1) //If damage ks is active
		{
			str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: DAMAGE UP ACTIVE %i ", pChr->m_Health,
														pChr->m_MaxHealth,
														pChr->m_Armor,
														pChr->m_MaxArmor,
														pChr->m_TimeToRemoveMult - Server()->Tick()/50);
			break;
		}else
		{
			str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: -", pChr->m_Health,
														pChr->m_MaxHealth,
														pChr->m_Armor,
														pChr->m_MaxArmor);
			break;
		}
	case MEDKIT:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: MEDKIT", pChr->m_Health,
													pChr->m_MaxHealth,
													pChr->m_Armor,
													pChr->m_MaxArmor);
		break;
	case DAMAGE_UP:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: DAMAGE UP", pChr->m_Health,
													pChr->m_MaxHealth,
													pChr->m_Armor,
													pChr->m_MaxArmor);
		break;
	case AIRSTRIKE:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: AIRSTRIKE", pChr->m_Health,
													pChr->m_MaxHealth,
													pChr->m_Armor,
													pChr->m_MaxArmor);
		break;
	default:
		break;
	}
	GameServer()->SendBroadcast(aBuf, pChr->GetPlayer()->GetCID());
	
}

void CGameControllerMOD::OnCharacterSpawn(class CCharacter *pChr)
{
	//IGameController::OnCharacterSpawn(pChr);
	// default health
	pChr->IncreaseHealth(pChr->m_MaxHealth);

	pChr->GiveWeapon(WEAPON_HAMMER, -1);
	pChr->GiveWeapon(WEAPON_GUN, 10);

}

int CGameControllerMOD::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	//IGameController::OnCharacterDeath(pVictim, pKiller, Weapon);
	
	int mScoreToBeAdded = 0;
	char aBufKB[64] = {}; //Killed Bounty
	pKiller->m_pCharacter->m_bScore++;
	
	// do scoreing
	if(!pKiller || Weapon == WEAPON_GAME)
		return 0;
	if(!(pKiller == pVictim->GetPlayer()))
	{
		if(!(IsTeamplay() && pVictim->GetPlayer()->GetTeam() == pKiller->GetTeam()))
		{
			if(pKiller->m_pCharacter->m_bScore >= 5) //Killer has bounty
			{
				if(pVictim->GetPlayer()->m_pCharacter->m_bScore >= 5)
				{
					mScoreToBeAdded = pKiller->m_pCharacter->m_bScore/4 + pVictim->m_bScore; // bounty kill another bounty
					str_format(aBufKB, sizeof(aBufKB), "'%s' has claimed the bounty (%ix) of '%s'", Server()->ClientName(pKiller->GetCID()),
																								pVictim->m_bScore,
																								Server()->ClientName(pVictim->GetPlayer()->GetCID()));
				}
				else
				{
					mScoreToBeAdded = pKiller->m_pCharacter->m_bScore/4;	// default bounty kill on non bounty
				}
			
				{ //Change killers clan to their bounty
					char aBuf[64];
					str_format(aBuf, sizeof(aBuf), "%ix BOUNTY", pKiller->m_pCharacter->m_bScore);
					Server()->SetClientClan(pKiller->GetCID(), aBuf);		
				}
			}
			else
			{
				if(pVictim->m_bScore >= 5){
					mScoreToBeAdded = 1 + pVictim->m_bScore;
					str_format(aBufKB, sizeof(aBufKB), "'%s' has claimed the bounty (%ix) of '%s'", Server()->ClientName(pKiller->GetCID()),
																								pVictim->m_bScore,
																								Server()->ClientName(pVictim->GetPlayer()->GetCID()));
				}
				else
				{
					mScoreToBeAdded = 1;
				}
			}

			if(pKiller->m_pCharacter->m_bScore%5==0){ // Announce it to all chat every %5 bounties
				char aBuf[64];
				str_format(aBuf, sizeof(aBuf), "'%s' has now a bounty of %i!", Server()->ClientName(pKiller->GetCID()), 
																				pKiller->m_pCharacter->m_bScore);
				GameServer()->SendChat(-1, CGameContext::CHAT_ALL, aBuf);
			}

			if(aBufKB!=nullptr)
				GameServer()->SendChat(-1, CGameContext::CHAT_ALL, aBufKB);

			pKiller->m_Score += mScoreToBeAdded;
			Server()->SetClientClan(pVictim->GetPlayer()->GetCID(), "");
			pVictim->m_bScore = 0;

		}
	}
	if(Weapon == WEAPON_SELF)
		pVictim->GetPlayer()->m_RespawnTick = Server()->Tick()+Server()->TickSpeed()*3.0f;


	pVictim->m_bScore = 0; //Reset bounty
	Server()->SetClientClan(pVictim->GetPlayer()->GetCID(), "");

	if(pKiller->m_pCharacter->m_bScore >= 5)
		CGameControllerMOD::CheckForKillstreak(pKiller->m_pCharacter);

	return 0;

}

void CGameControllerMOD::CheckForKillstreak(class CCharacter *pChr)
{

	char aBuf[64]={};
	if(pChr->m_bScore % pChr->m_NextKillstreak == 0)
	{
		pChr->m_Killstreak++;
		pChr->m_NextKillstreak += 5;

		switch (pChr->m_Killstreak)
		{
		case 0:
			str_format(aBuf, sizeof(aBuf), "You got a 'MEDKIT'. Use it with your hammer.");
			break;
		case 1:
			str_format(aBuf, sizeof(aBuf), "You got 'DAMAGE UP'. Use it with your hammer.");
			break;
		case 2:
		str_format(aBuf, sizeof(aBuf), "You got an 'AIRSTRIKE'. Use it with your hammer.");
			break;
		default:
			break;
		}

	}

	if(pChr->m_Killstreak > AIRSTRIKE) //No more killsteak powers
		pChr->m_Killstreak = AIRSTRIKE;

	if(aBuf != nullptr)
		GameServer()->SendChatTarget(pChr->GetPlayer()->GetCID(), aBuf);
}

void CGameControllerMOD::ActivateKillstreak(class CCharacter *pChr, int KillStr)
{
	switch (KillStr)
	{
	case MEDKIT:
		pChr->IncreaseHealth(pChr->m_MaxHealth/1.3f);
		pChr->m_Armor = pChr->m_MaxArmor;
		break;
	case DAMAGE_UP:
		pChr->m_DamageMult = 2;
		pChr->m_TimeToRemoveMult = Server()->Tick() + 50 * 10; //Current tick + 10 second(*50 ticks/s)
		break;
	case AIRSTRIKE:

		break;
	default:
		break;
	}
	pChr->m_Killstreak = NO_KILLSTREAK; //reset
	pChr->m_NextKillstreak = pChr->m_bScore + 5;
}

void CGameControllerMOD::KillstreakTick()
{
	for(int i=0;i<MAX_CLIENTS;i++){
		if(GameServer()->IsClientReady(i) && GameServer()->m_apPlayers[i]->m_pCharacter
			&& GameServer()->m_apPlayers[i]->m_pCharacter->IsAlive())
		{
			if(GameServer()->GetPlayerChar(i)->m_DamageMult != 1 
				&& Server()->Tick() % GameServer()->GetPlayerChar(i)->m_TimeToRemoveMult==0)
					GameServer()->GetPlayerChar(i)->m_DamageMult = 1;	
		}
	}
}

void CGameControllerMOD::FireHammer(class CCharacter *pChr){
	char aBuf[64];
	switch (pChr->m_Killstreak)
	{
	case NO_KILLSTREAK:
		str_format(aBuf, sizeof(aBuf), "You do not have a powerup available");
		break;
	case MEDKIT:
		str_format(aBuf, sizeof(aBuf), "Activated 'MEDKIT'!");
		break;
	case DAMAGE_UP:
		str_format(aBuf, sizeof(aBuf), "Activated 'DAMAGE_UP'!");
		break;
	case AIRSTRIKE:
		str_format(aBuf, sizeof(aBuf), "Activated 'AIRSTRIKE'!");
		break;
	default:
		break;
	}

	GameServer()->SendChatTarget(pChr->GetPlayer()->GetCID(), aBuf);
	if(pChr->m_Killstreak == NO_KILLSTREAK)
		return;
	ActivateKillstreak(pChr, pChr->m_Killstreak);

}