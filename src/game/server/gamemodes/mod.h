/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_MOD_H
#define GAME_SERVER_GAMEMODES_MOD_H
#include <game/server/gamecontroller.h>
#include <game/server/player.h>
#include <game/server/entities/character.h>

// you can subclass GAMECONTROLLER_CTF, GAMECONTROLLER_TDM etc if you want
// todo a modification with their base as well.
class CGameControllerMOD : public IGameController
{
	friend class CPlayer;
	friend class CCharacter;

	void DisplayStats(class CPlayer *pPlayer);
	void StatsTick();


public:
	enum Killstreaks{
		KS_NoKS = -1,
		KS_HEAL = 0,
		KS_DAMAGE = 1,
		KS_AIRSTRIKE = 2,
	};

	CGameControllerMOD(class CGameContext *pGameServer);


	void OnCharacterSpawn(class CCharacter *pChr);
	int OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon);
	
	bool IsFriendlyFire(int ClientID1, int ClientID2) { return true; }
	void CheckForKillstreak(class CPlayer *pPlayer);

	void CallKillstreak(class CPlayer *pPlayer, int Killstreak);
	
	virtual void Tick();
    // add more virtual functions here if you wish
};

#endif
