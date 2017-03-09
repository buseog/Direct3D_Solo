#ifndef Stage_h__
#define Stage_h__

#include "BigHeaders.h"
#include "Scene.h"

class CLoading;
class CStage :public Engine::CScene
{
private:
	HRESULT Ready_RenderState(void);
	HRESULT Ready_Light(void);
	HRESULT	Ready_LayerCamera(void);
	HRESULT Ready_LayerBackGround(void);
	HRESULT	Ready_LayerSkyBox(void);
	HRESULT Ready_LayerPlayer(void);

public:
	virtual HRESULT Initialize(void);
	virtual _int Update(const _float& fDelta);
	virtual void Render(void);

public:
	virtual void Free(void);

public:
	static CStage* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CStage(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CStage(void);
};

#endif // Stage_h__