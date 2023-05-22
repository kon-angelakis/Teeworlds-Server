#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>

#include "airstrike.h"

CAirstrike::CAirstrike(CGameWorld *pGameWorld, int Owner, vec2 Pos, int Span,
		int Amount, bool Explosive, bool SoA)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_PROJECTILE)
{
	m_Direction = vec2(0,1); //airstrike goes down
	m_Pos = Pos + vec2(0, AIRSTRIKE_HEIGHT);
	m_Owner = Owner;
	m_LifeSpan = Span;
    m_Amount = Amount;
	m_Explosive = Explosive;
    m_SoA = SoA;
	m_Weapon = WEAPON_GRENADE;
	m_StartTick = Server()->Tick();
    m_Damage = 1;
    m_SoundImpact = SOUND_PICKUP_ARMOR;

    for(int i = -m_Amount/2; i <= m_Amount/2; i++)
    {
        if(m_SoA) //This gets only called on the main airstrike not its references created below
           new CAirstrike(pGameWorld, m_Owner, 
                m_Pos + vec2(i * AIRSTRIKE_SPACING, AIRSTRIKE_HEIGHT - abs(i * AIRSTRIKE_HEIGHT)), 
                m_LifeSpan, m_Amount, true);
    }
    if(!m_SoA)
	    GameWorld()->InsertEntity(this);
}

vec2 CAirstrike::GetPos(float Time)
{
	float Curvature = GameServer()->Tuning()->m_GrenadeCurvature;
	float Speed = GameServer()->Tuning()->m_GrenadeSpeed;

	return CalcPos(m_Pos, m_Direction, Curvature, Speed, Time);
}


void CAirstrike::Tick()
{
	float Pt = (Server()->Tick()-m_StartTick-1)/(float)Server()->TickSpeed();
	float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
	vec2 PrevPos = GetPos(Pt);
	vec2 CurPos = GetPos(Ct);
	CCharacter *OwnerChar = GameServer()->GetPlayerChar(m_Owner);
	CCharacter *TargetChr = GameServer()->m_World.IntersectCharacter(PrevPos, CurPos, 6.0f, CurPos, OwnerChar);

	GameServer()->CreateSound(CurPos, m_SoundImpact);

	if(m_Explosive)
		GameServer()->CreateExplosion(CurPos, m_Owner, WEAPON_HAMMER, false);

	m_LifeSpan--;
    if(m_LifeSpan < 0)
        GameServer()->m_World.DestroyEntity(this);
}

void CAirstrike::TickPaused()
{
	++m_StartTick;
}

void CAirstrike::FillInfo(CNetObj_Projectile *pProj)
{
	pProj->m_X = (int)m_Pos.x;
	pProj->m_Y = (int)m_Pos.y;
	pProj->m_VelX = (int)(m_Direction.x*100.0f);
	pProj->m_VelY = (int)(m_Direction.y*100.0f);
	pProj->m_StartTick = m_StartTick;
	pProj->m_Type = m_Weapon;
}

void CAirstrike::Snap(int SnappingClient)
{
	float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();

	if(NetworkClipped(SnappingClient, GetPos(Ct)))
		return;

	CNetObj_Projectile *pProj = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_ID, sizeof(CNetObj_Projectile)));
	if(pProj)
		FillInfo(pProj);
}
