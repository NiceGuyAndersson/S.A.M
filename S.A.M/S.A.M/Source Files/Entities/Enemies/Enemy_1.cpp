#include "Entities/Enemies/Enemy_1.h"

Enemy_1::Enemy_1()
{
	m_score = m_health;
}

Enemy_1::~Enemy_1()
{
	delete m_spline;
}

void Enemy_1::Update(double time)
{
	m_age += time/2;
	if (m_age > 1.0f)
	{
		m_age = 0;
		m_spline->SetCurrPathNode(m_spline->GetCurrPathNode() + 1);
	}
	m_position = m_spline->GetPathPosition(m_age);
	m_entityBox.Center = m_position;
	m_size = XMFLOAT3(m_scale.x / 2.0, m_scale.y, m_scale.z / 2.0);	//used to set size of explosion
	m_entityBox.Extents = XMFLOAT3(m_scale.x, 0, m_scale.z);
}

void Enemy_1::Destroyed(double time)
{
	//PlaySound of DEATH


}