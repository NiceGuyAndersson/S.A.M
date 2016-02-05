#ifndef BULLET_E_H
#define BULLET_E_H
#include "Bullet.h"

class Bullet_e : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_e();
	Bullet_e(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Bullet(SoundManager, MapWidth, MapLength, Position) {}
	~Bullet_e();
	void Update(double time);
	void Destroyed();

	//Variables
private:
protected:
public:

};

#endif