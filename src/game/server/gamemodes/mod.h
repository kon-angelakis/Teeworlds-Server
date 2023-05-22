/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_MOD_H
#define GAME_SERVER_GAMEMODES_MOD_H
#include <game/server/gamecontroller.h>
#include <game/server/player.h>
#include <game/server/entities/character.h>
#include <game/server/entity.h>
#include <game/server/entities/projectile.h>
#include <game/server/entities/airstrike.h>


//==HUNT
#define IsControllerHunt(GameServer) (*((int*)GameServer->GameType()) == 0x544e5548)
#define SecondsToTick(sec) (int)(SERVER_TICK_SPEED * sec)

#define AIRSTRIKE_HEIGHT -600
#define AIRSTRIKE_AMOUNT 15 //Better be an odd number so it splits in half(center: player)
#define AIRSTRIKE_SPACING 110



// you can subclass GAMECONTROLLER_CTF, GAMECONTROLLER_TDM etc if you want
// todo a modification with their base as well.
class CGameControllerMOD : public IGameController
{
private:
	friend class CPlayer;
	friend class CCharacter;

	void DisplayStats(class CCharacter *pChr);
	void StatsTick();


public:

	enum Killstreaks{
		KILLSTREAK_NO = -1,
		KILLSTREAK_MEDKIT = 0,
		KILLSTREAL_DAMAGEUP = 1,
		KILLSTREAK_AIRSTRIKE = 2,
	};

	CGameControllerMOD(class CGameContext *pGameServer);

	void OnCharacterSpawn(class CCharacter *pChr);
	int OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon);
	
	bool IsFriendlyFire(int ClientID1, int ClientID2) { return false; }

	void CheckForKillstreak(class CCharacter *pChr);
	int ActivatedKillstreak(class CCharacter *pChr);
	void KillstreakTick();

	void HandleHammer(class CCharacter *pChr); //Returns what killstreak is active
	void HandleGrenade();
	void HandleRifle();
	void HandleNinja();

	void PlayEmote(class CPlayer *pPlayer, int Emoticon = -1, int Emote = -1, int Sound = -1, bool Audible = false);
	
	virtual void Tick();
    // add more virtual functions here if you wish
};






#endif
