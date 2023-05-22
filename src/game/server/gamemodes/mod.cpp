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
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
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
	case KILLSTREAK_NO:
		if(pChr->m_DamageMult != 1) //If damage ks is active
		{
			str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: DAMAGE UP ACTIVE %i ", pChr->m_Health,
														pChr->m_MaxHealth,
														pChr->m_Armor,
														pChr->m_MaxArmor,
														(pChr->m_TimeToRemoveMult - Server()->Tick())/SERVER_TICK_SPEED + 1);
			if((pChr->m_TimeToRemoveMult - Server()->Tick()) % 50 == 0)
				PlayEmote(pChr->m_pPlayer, -1, -1, SOUND_HOOK_NOATTACH);
			break;
		}else
		{
			str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: -", pChr->m_Health,
														pChr->m_MaxHealth,
														pChr->m_Armor,
														pChr->m_MaxArmor);
			break;
		}
	case KILLSTREAK_MEDKIT:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: MEDKIT", pChr->m_Health,
													pChr->m_MaxHealth,
													pChr->m_Armor,
													pChr->m_MaxArmor);
		break;
	case KILLSTREAL_DAMAGEUP:
		str_format(aBuf, sizeof(aBuf), "Health: %i/%i | Armor: %i/%i\nPowerup: DAMAGE UP", pChr->m_Health,
													pChr->m_MaxHealth,
													pChr->m_Armor,
													pChr->m_MaxArmor);
		break;
	case KILLSTREAK_AIRSTRIKE:
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
				if(pVictim->m_bScore >= 5)
				{
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

			if(pKiller->m_pCharacter->m_bScore%5==0) // Announce it to all chat every %5 bounties
			{ 
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

		if(pChr->m_Killstreak > 2)
			return;

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

	if(aBuf != nullptr)
		GameServer()->SendChatTarget(pChr->GetPlayer()->GetCID(), aBuf);
}

int CGameControllerMOD::ActivatedKillstreak(class CCharacter *pChr)
{
	int KillStr = pChr->m_Killstreak;
	switch (KillStr)
	{
	case KILLSTREAK_MEDKIT:
		pChr->IncreaseHealth(pChr->m_MaxHealth/1.2f);
		pChr->IncreaseArmor(4);
		break;
	case KILLSTREAL_DAMAGEUP:
		pChr->m_DamageMult = 2;
		pChr->m_TimeToRemoveMult = Server()->Tick() + SecondsToTick(10); //Current tick + 10 seconds
		break;
	case KILLSTREAK_AIRSTRIKE:
		CAirstrike *cAir = new CAirstrike(pChr->m_pGameWorld, 
											pChr->m_pPlayer->m_ClientID, 
											pChr->m_Pos, 
											SecondsToTick(5), 
											AIRSTRIKE_AMOUNT, 
											true, true);

		//Other tees are surprised
		for(int i = 0; i < MAX_CLIENTS; i++)
		{
			if(GameServer()->IsClientReady(i) && GameServer()->m_apPlayers[i]->m_pCharacter
			&& GameServer()->m_apPlayers[i]->m_pCharacter->IsAlive())
				if(pChr->m_pPlayer->m_ClientID != i)
					PlayEmote(GameServer()->m_apPlayers[i], 
						EMOTICON_EXCLAMATION, 
						EMOTE_SURPRISE, 
						SOUND_CTF_GRAB_EN);
		}
		break;

	}
	pChr->m_Killstreak = KILLSTREAK_NO; //reset
	pChr->m_NextKillstreak = pChr->m_bScore + 5;

	return KillStr; //return which ks was activated

}

void CGameControllerMOD::KillstreakTick()
{
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(GameServer()->IsClientReady(i) && GameServer()->m_apPlayers[i]->m_pCharacter
			&& GameServer()->m_apPlayers[i]->m_pCharacter->IsAlive()) //If character exists
		{
			if(GameServer()->GetPlayerChar(i)->m_DamageMult != 1 
				&& Server()->Tick() % GameServer()->GetPlayerChar(i)->m_TimeToRemoveMult==0)
					GameServer()->GetPlayerChar(i)->m_DamageMult = 1; //Reset once dmg+ time is up
		}
	}
}

void CGameControllerMOD::HandleHammer(class CCharacter *pChr)
{
	char aBuf[64];
	switch (pChr->m_Killstreak)
	{
	case KILLSTREAK_NO:
		str_format(aBuf, sizeof(aBuf), "You do not have a powerup available");
		PlayEmote(pChr->m_pPlayer, EMOTICON_DROP, EMOTE_BLINK, SOUND_TEE_CRY); //sad tee noises :(
		break;
	case KILLSTREAK_MEDKIT:
		str_format(aBuf, sizeof(aBuf), "You used a 'MEDKIT'!");
		break;
	case KILLSTREAL_DAMAGEUP:
		str_format(aBuf, sizeof(aBuf), "Activated 'DAMAGE_UP'!");
		break;
	case KILLSTREAK_AIRSTRIKE:
		str_format(aBuf, sizeof(aBuf), "You deployed an 'AIRSTRIKE'!");
		break;
	default:
		break;
	}

	GameServer()->SendChatTarget(pChr->GetPlayer()->GetCID(), aBuf);
	if(pChr->m_Killstreak == KILLSTREAK_NO)
		return;
	ActivatedKillstreak(pChr);

}

void CGameControllerMOD::PlayEmote(class CPlayer *pPlayer, int Emoticon, int Emote, int Sound, bool Audible)
{

	GameServer()->SendEmoticon(pPlayer->GetCID(), Emoticon);
	pPlayer->m_pCharacter->SetEmote(Emote, Server()->Tick() + SecondsToTick(2));
	switch (Audible)
	{
	case true: //Audible by everyone
		
		GameServer()->CreateSound(pPlayer->m_pCharacter->m_Pos, Sound);
		break;
	
	case false:
		GameServer()->CreateSound(pPlayer->m_ViewPos, Sound);
		break;
	}


	
}
