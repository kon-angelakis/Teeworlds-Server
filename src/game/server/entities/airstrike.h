#ifndef GAME_SERVER_ENTITIES_AIRSTRIKE_H
#define GAME_SERVER_ENTITIES_AIRSTRIKE_H

#include <game/server/entity.h>

class CAirstrike : public CEntity
{
public:
	CAirstrike(CGameWorld *pGameWorld, int Owner, vec2 Pos, int Span,
		int Amount, bool Explosive, bool SoA = false);

	vec2 GetPos(float Time);
	void FillInfo(CNetObj_Projectile *pProj);

	virtual void Tick();
	virtual void TickPaused();
	virtual void Snap(int SnappingClient);

private:
	vec2 m_Direction;
    vec2 m_Pos;
	int m_Owner;
	int m_LifeSpan;
    int m_Amount;
	bool m_Explosive;
    bool m_SoA; // Start of projectile = true if called outside, references of this class = false
	int m_Weapon;
	int m_StartTick;
    int m_Damage;
    int m_SoundImpact;
};

#endif
