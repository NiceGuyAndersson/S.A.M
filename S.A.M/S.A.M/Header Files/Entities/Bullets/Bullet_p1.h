#ifndef BULLET_P1_H
#define BULLET_P1_H
#include "Entities\Bullets\Bullet.h"

class Bullet_p1 : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_p1();
	Bullet_p1(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color);
	~Bullet_p1();
	void Update(double time);
	void Destroyed(double time);

	//Variables
private:
protected:
public:

};

#endif