#include "Entities/Enemies/Enemy_3.h"

Enemy_3::Enemy_3()
{
	m_score = m_health;
}

Enemy_3::~Enemy_3()
{

}

void Enemy_3::Update(double time)
{
	m_age += time / 2;
	if (m_age > 1.0f)
	{
		m_age = 0;
		m_spline->SetCurrPathNode(m_spline->GetCurrPathNode() + 1);
	}
	m_position = m_spline->GetPathPosition(m_age);
	m_entityBox.Center = m_position;
	m_size = XMFLOAT3(m_scale.x * 1.5, m_scale.y * 2.5, m_scale.z * 1.5);	//used to set size of explosion		y is not used
	m_entityBox.Extents = XMFLOAT3(m_scale.x * 7, 0, m_scale.z * 14);
}

void Enemy_3::Destroyed(double time)
{

}