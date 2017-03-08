#include "NaviMgr.h"
#include "NaviMesh.h"

USING(Engine)
IMPLEMENT_SINGLETON(CNaviMgr)

Engine::CNaviMgr::CNaviMgr( void )
: m_pDevice(NULL)
, m_dwIdxCnt(0)
{

}

Engine::CNaviMgr::~CNaviMgr( void )
{

}

HRESULT Engine::CNaviMgr::ReadyNaviMgr( LPDIRECT3DDEVICE9 pDevice )
{
	m_pDevice = pDevice;

	return S_OK;
}

HRESULT Engine::CNaviMgr::AddNaviMesh( const MyVec3* pVecA, const MyVec3* pVecB, const MyVec3* pVecC )
{
	CNaviMesh* pNaviMesh = Engine::CNaviMesh::Create(m_pDevice, pVecA, pVecB, pVecC, m_dwIdxCnt);
	if (pNaviMesh == NULL)
		return E_FAIL;

	++m_dwIdxCnt;

	m_vecNavi.push_back(pNaviMesh);

	return S_OK;
}

void Engine::CNaviMgr::RenderNaviMesh( void )
{
	for (_uint i = 0; i < m_vecNavi.size(); ++i)
	{
		m_vecNavi[i]->Render();
	}
}

void Engine::CNaviMgr::LinkNaviMesh( void )
{
	VECNAVI::iterator iter = m_vecNavi.begin();
	VECNAVI::iterator iter_end = m_vecNavi.end();

	if (iter == m_vecNavi.end())
		return;

	for ( ; iter != iter_end; ++iter)
	{
		VECNAVI::iterator iter_target = m_vecNavi.begin();

		while (iter_target != m_vecNavi.end())
		{
			if (iter == iter_target)
			{
				++iter_target;
				continue;
			}

			if ((*iter_target)->Compare((*iter)->GetPoint(CNaviMesh::POINT_A), (*iter)->GetPoint(CNaviMesh::POINT_B), (*iter)))
			{
				(*iter)->SetNeighbor(CNaviMesh::NEIGHBOR_AB, *iter_target);
			}
			else if ((*iter_target)->Compare((*iter)->GetPoint(CNaviMesh::POINT_B), (*iter)->GetPoint(CNaviMesh::POINT_C), (*iter)))
			{
				(*iter)->SetNeighbor(CNaviMesh::NEIGHBOR_BC, *iter_target);
			}
			else if ((*iter_target)->Compare((*iter)->GetPoint(CNaviMesh::POINT_C), (*iter)->GetPoint(CNaviMesh::POINT_A), (*iter)))
			{
				(*iter)->SetNeighbor(CNaviMesh::NEIGHBOR_CA, *iter_target);
			}

			++iter_target;
		}
	}
}

_ulong Engine::CNaviMgr::MoveOnNaviMesh( MyVec3* pPos, const MyVec3* pDir, const _ulong& dwIndex )
{
	CNaviMesh::NEIGHBORID eNeighbor;
	_ulong	dwNextIndex = dwIndex;

	if (m_vecNavi[dwIndex]->CheckPass(pPos, pDir, &eNeighbor))
	{
		const CNaviMesh* pNeighbor = m_vecNavi[dwIndex]->GetNeighbor(eNeighbor);

		if (pNeighbor == NULL)
		{

		}
		else
		{
			dwNextIndex = pNeighbor->GetIndex();
			*pPos += *pDir;
		}
	}
	else
	{
		*pPos += *pDir;
	}

	return dwNextIndex;
}

void Engine::CNaviMgr::Free( void )
{
	for_each(m_vecNavi.begin(), m_vecNavi.end(), Engine::CReleaseSingle());
	m_vecNavi.clear();
}
