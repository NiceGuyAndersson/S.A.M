#include "Entities/Enemies/Enemy_2.h"

Enemy_2::Enemy_2()
{
	
}

Enemy_2::~Enemy_2()
{
	delete m_spline;
}

void Enemy_2::Update(double time)
{
	m_age += time / 2;
	if (m_age > 1.0f)
	{
		m_age = 0;
		m_spline->SetCurrPathNode(m_spline->GetCurrPathNode() + 1);
	}
	m_position = m_spline->GetPathPosition(m_age);
	m_entityBox.Center = m_position;
	m_entityBox.Extents = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void Enemy_2::Destroyed(double time)
{

}