#ifndef BULLET_P3_H
#define BULLET_P3_H
#include "Entities\Bullets\Bullet.h"

class Bullet_p3 : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_p3();
	Bullet_p3(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color);
	~Bullet_p3();
	void Update(double time);
	void Destroyed(double time);

	//Variables
private:
	float m_rotationValue;
protected:
public:

};

#endif