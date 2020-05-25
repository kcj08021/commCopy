#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

// FMOD: ����Ƽ, �𸮾�� ���� ��� �������� �η� ���̴� ���� ���� ����.
// ���忡 ���õ� �������̽��� ����.

class CSoundManager {
	DECLARE_SINGLETON(CSoundManager);

public:
	enum CHANNEL_ID { BGM, PLAYER, MONSTER, EFFECT, MAX_CHANNEL };

private:
	explicit CSoundManager();
	virtual ~CSoundManager();

public:
	void Initialize();
	void UpdateSound();
	void PlaySound(const wstring& wstrSoundKey, CHANNEL_ID eID);
	void PlayBGM(const wstring& wstrSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void SetVolume(CHANNEL_ID eID, float fVol);
	void Release();

private:
	void LoadSoundFile();

private:
	// FMOD_SOUND: ���� ���Ͽ� ���� ������ ���� ����ü.
	map<wstring, FMOD_SOUND*>	m_MapSound;

	// FMOD_CHANNEL: ���带 ����ϰ� �����ϴ� ����. ex) ���� ���� ��.
	FMOD_CHANNEL*	m_pChannelArr[MAX_CHANNEL];

	// FMOD_SYSTEM: FMOD_SOUND�� FMOD_CHANNEL�� �Ѱ� �����ϴ� ��ü.
	FMOD_SYSTEM*	m_pSystem;
};

#define SNDMGR CSoundManager::GetInstance()

#endif // !__SOUND_MANAGER_H__


