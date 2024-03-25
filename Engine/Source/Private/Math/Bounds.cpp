#include "Math/Bounds.h"

Bounds::Bounds(GameObject* owner, Vector2 origin, Vector2 extent)
{
	m_Rect.origin = origin;
	m_Rect.extent = extent;
	m_Owner = owner;
	m_CollisionType = CT_OVERLAP;
	m_Tag = "ALL";
	m_ShouldDestroy = false;
	m_Debug = false;
}

bool Bounds::BoundsIntersect(const Bounds& boundsA, const Bounds& boundsB)
{
	Vector2 boundsAMin = boundsA.m_Rect.Min() - boundsA.m_OriginOffset;
	Vector2 boundsAMax = boundsA.m_Rect.Max() + boundsA.m_OriginOffset;
	Vector2 boundsBMin = boundsB.m_Rect.Min() - boundsB.m_OriginOffset;
	Vector2 boundsBMax = boundsB.m_Rect.Max() + boundsB.m_OriginOffset;

	bool minX = boundsBMin.x <= boundsAMax.x;
	bool maxX = boundsBMax.x >= boundsAMin.x;
	bool minY = boundsBMin.y <= boundsAMax.y;
	bool maxY = boundsBMax.y >= boundsAMin.y;
	return minX && maxX && minY && maxY;
}
