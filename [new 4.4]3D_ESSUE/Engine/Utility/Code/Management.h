#ifndef Management_h__
#define Management_h__

#include "Engine_BigHeaders.h"
#include "Base.h"

BEGIN(Engine)

class CScene;
class CRenderer;
class CLayer;
class ENGINE_DLL CManagement :public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	CScene*		m_pScene;
	CRenderer*	m_pRenderer;

public:
	HRESULT InitManagement(void);
	_int	Update(const _float& fDelta);
	void	Render(void);

public:
	HRESULT	SetScene(CScene* pScene);
	CLayer*	GetLayer(const _tchar* LayerKey);
	CRenderer* GetRenderer(void) { return m_pRenderer; }

public:
	virtual void Free(void);

private:
	explicit CManagement(void);
	virtual ~CManagement(void);
};

END
#endif // Management_h__