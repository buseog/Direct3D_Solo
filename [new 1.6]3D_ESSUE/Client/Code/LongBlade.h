#ifndef LongBlade_h__
#define LongBlade_h__

#include "GameObject.h"
#include "BigHeaders.h"
#include "Export_Engine.h"

class CLongBlade :public Engine::CGameObject
{
private:
	Engine::CRenderer*		m_pRendererCom;
	Engine::CTransform*		m_pTransformCom;
	Engine::CMaterial*		m_pMtrCom;
	Engine::CStaticMesh*	m_pMeshCom;

private:
	HRESULT	ReadyComponent(void);

public:
	virtual HRESULT Initialize(void);
	virtual _int	Update(const _float& fDelta);
	virtual void	Render(void);

public:
	virtual void Free(void);

public:
	static CLongBlade* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CLongBlade(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLongBlade(void);
};

#endif // LongBlade_h__