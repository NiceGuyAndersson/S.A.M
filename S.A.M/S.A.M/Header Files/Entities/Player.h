#ifndef PLAYER_H
#define PLAYER_H

#include "Entities/Entity.h"
#include "Gamelogic/Input.h"
#include "Audio/SoundManager.h"
#include <math.h>

class Player : public Entity
{
	//----------------------------Functions----------------------------------------
public:
	Player();
	~Player();
	Player(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, Input* input);
	void Update(double time);
	void Destroyed();
	//----------------------------Attributes----------------------------------------
private:
	Input* m_input;
	float m_rotAngle = 0;
};

#endif // ! PLAYER_H
