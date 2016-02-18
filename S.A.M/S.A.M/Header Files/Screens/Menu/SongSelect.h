#ifndef _SONGSELECT_H
#define _SONGSELECT_H

#include "../Screen.h"
#include "../../Gamelogic/Stats.h"
#include "../SongElement.h"
#include "../../Audio/SoundManager.h"

class SongSelect : public Screen
{
private:
	SongSelect() {}
	~SongSelect();

public:
	SongSelect(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats, SoundManager* soundManager);
	void Update(double time);
	void Render();

private:
	vector<SongElement*> m_songElements;
	SoundManager* m_soundManager;
};
#endif