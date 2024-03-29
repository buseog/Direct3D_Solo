#include "StdAfx.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr(void)
{
	m_pSystem = NULL;
	m_iVersion = 0;

	Initialize();
}

CSoundMgr::~CSoundMgr(void)
{
	Release();
}

void CSoundMgr::Initialize(void)
{
	FMOD_System_Create(&m_pSystem);

	FMOD_System_GetVersion(m_pSystem, &m_iVersion);

	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd;
	long handle;
	int iResult = 1;

	handle = _findfirst("..\\Bin\\Sound\\*.*", &fd);

	if(handle == -1)
	{
		return;
	}

	while(iResult != -1)
	{
		TCHAR szName[256] = L"";

		ZeroMemory(szName, sizeof(szName));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fd.name, strlen(fd.name), szName, 256);

		TCHAR*	pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		lstrcpy(pName, szName);

		char szFullName[256];
		strcpy_s(szFullName, "..\\bin\\sound\\");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;
		int iTemp = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if(iTemp == FMOD_OK)
			m_mapSound.insert(make_pair(pName, pSound));
		else
			Engine::Safe_DeleteArray(pName);

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);


	FMOD_System_Update(m_pSystem);

}

void CSoundMgr::PlaySound(TCHAR* pSoundKey, const _uint& iIndex)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCompare(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	if (iIndex == 0)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pPlayer);
	else if (iIndex == 1)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pPlayerEffect);
	else if (iIndex == 2)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pBoss);
	else if (iIndex == 3)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pBossEffect);
	else if (iIndex == 4)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pTemp);
	else if (iIndex == 5)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pTemp2);
	else if (iIndex == 6)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pTemp3);
	else if (iIndex == 7)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pTemp4);
	else if (iIndex == 8)
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pTemp5);

}

void CSoundMgr::PlayBGM(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCompare(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pBgm);
}

void CSoundMgr::StopBGM(TCHAR* pSoundKey)
{
	FMOD_Channel_Stop(m_pBgm);
}

void CSoundMgr::StopSoundAll(void)
{
	FMOD_Channel_Stop(m_pBgm);
	FMOD_Channel_Stop(m_pPlayerEffect);
}

void CSoundMgr::Free( void )
{
	StopSoundAll();
	map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin();
	map<TCHAR*, FMOD_SOUND*>::iterator iter_end = m_mapSound.end();

	for(iter; iter != iter_end; ++iter)
	{
		FMOD_Sound_Release(iter->second);
		delete [] (iter->first);
	}

	m_mapSound.clear();

	/*
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);*/
}

