#include "SoundManager.h"
#include "Windows.h"
#include <sstream>
#include <iostream>

//using namespace FMOD;

SoundManager::SoundManager() {
	InitFMOD();
}

void SoundManager::MessageBoxAndShutDown(std::stringstream* _ss) {
	std::string _boxStringS(_ss->str());
	const char* _boxStringLPCSTR = _boxStringS.c_str();

	//Displays error box and quits the game
	MessageBox(NULL,
		_boxStringLPCSTR,
		"Sound Error",
		MB_ICONERROR | MB_OK);
	exit(-1);
}
void SoundManager::LoadSound(char* fileName, char* soundName, SoundFlags flags)
{
	FMOD::Sound* audio;

	//Either load into memory or as a stream
	if (flags == LOAD_MEMORY)
		m_result = m_system->createSound(fileName, FMOD_DEFAULT, 0, &audio);
	else if (flags == LOAD_STREAM)
		m_result = m_system->createStream(fileName, FMOD_DEFAULT, 0, &audio);
	else	//No mode set
	{
		MessageBox(NULL, (LPCSTR)L"No Loadmode Set", "Sound Loading Error", MB_ICONERROR | MB_OK);
		exit(-1);
	}
	
	FMODErrorCheck(m_result);

	//Add audio and sound name to their vectors
	m_sounds.push_back(audio);
	m_soundIndex.push_back(soundName);
}

void SoundManager::PlayOneShotSound(char* soundName)
{
	int _soundIndex = -1;	//Index of correct sound in the vectors
	bool found = false;

	//Go through the index vector to find index of correct sound
	for (int i = 0; i < m_soundIndex.size() && found == false; i++)
	{
		if (m_soundIndex[i] == soundName)
		{
			found = true;
			_soundIndex = i;
		}
	}

	//If the sound was found, play it!
	if (_soundIndex != -1) 
	{
		m_result = m_system->playSound(FMOD_CHANNEL_FREE, m_sounds[_soundIndex], false, 0);
		FMODErrorCheck(m_result);
	}
	
}

void SoundManager::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		//Makes an stringstream with error message and send to messagebox function
		std::stringstream _ss;
		_ss << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << "\nGame Shutting Down";
		MessageBoxAndShutDown(&_ss);
	}
}

void SoundManager::InitFMOD()
{
	//Create FMOD Interface Object
	m_result = FMOD::System_Create(&m_system);
	FMODErrorCheck(m_result);

	//Check version
	m_result = m_system->getVersion(&m_version);
	FMODErrorCheck(m_result);

	//If the user has an old version of FMOD, shut the program down
	if (m_version < FMOD_VERSION)
	{
		//Makes an stringstream with error message and send to messagebox function
		std::stringstream _ss;
		_ss << "Error! You are using an old version of FMOD " << m_version << ". This program requires " << FMOD_VERSION << "\nGame Shutting Down";
		MessageBoxAndShutDown(&_ss);
	}

	//Get number of sound cards
	m_result = m_system->getNumDrivers(&m_numDrivers);
	FMODErrorCheck(m_result);

	//If no sound cards, disable sound
	if(m_numDrivers == 0)
	{
		m_result = m_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODErrorCheck(m_result);
	}
	else	//If at least one sound card
	{ 
		//Get the capabilities of the default (0) sound card   (stereo, 5.1, 7.1 etc)
		m_result = m_system->getDriverCaps(0, &m_caps, 0, &m_speakerMode);
		FMODErrorCheck(m_result);

		//Set the speaker mode to match that in Control Panel
		m_result = m_system->setSpeakerMode(m_speakerMode);
		FMODErrorCheck(m_result);

		//Increase the buffer size if user has hardware acceleration disabled to guard agains skipping and stuttering
		if (m_caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			m_result = m_system->setDSPBufferSize(1024, 10);
			FMODErrorCheck(m_result);
		}

		//Get name of driver
		m_result = m_system->getDriverInfo(0, m_name, 256, 0);
		FMODErrorCheck(m_result);

		// SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
		// PCM floating point output seems to solve it.
		if (strstr(m_name, "SigmaTel"))
		{
			m_result = m_system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			FMODErrorCheck(m_result);
		}
	}

	//Actually initialize the FMOD system
	m_result = m_system->init(100, FMOD_INIT_NORMAL, 0);	//100 is number of virtual channel, won't probably use more than 5

	//If the selected speaker mode isn't supported by this sound card, switch it back to stereo
	if (m_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		m_result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		FMODErrorCheck(m_result);

		m_result = m_system->init(100, FMOD_INIT_NORMAL, 0);
	}
	FMODErrorCheck(m_result);
}


