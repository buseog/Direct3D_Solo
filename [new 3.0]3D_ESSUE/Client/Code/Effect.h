#ifndef Effect_h__
#define Effect_h__

#include "GameObject.h"
#include "BigHeaders.h"
#include "Export_Engine.h"

class CEffect :public Engine::CGameObject
{
private:
	Engine::CTransform*			m_pTransformCom;
	Engine::CRenderer*			m_pRendererCom;
	Engine::CTexture*			m_pTextureCom;
	Engine::CTrainTex*			m_pBufferCom;
	Engine::CShader*			m_pShaderCom;
private:
	_float						m_fLiveTime;
	_float						m_fFrame;

private:
	virtual HRESULT Ready_Component(const _tchar* pName);
	void	SetUpShader(LPD3DXEFFECT pEffect);

public:
	virtual HRESULT Initialize(const _tchar* pName);
	virtual _int	Update(const _float& fDelta);
	virtual void	Render(void);

public:
	virtual void Free(void);

public:
	static CEffect* Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pName);

private:
	explicit CEffect(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CEffect(void);
};

#endif // Effect_h__