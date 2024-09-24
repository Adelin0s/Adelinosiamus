﻿/*
* SpeedTreeRTExample Class
*
* (c) 2003 IDV, Inc.
*
* This class is provided to illustrate one way to incorporate
* SpeedTreeRT into an OpenGL application.  All of the SpeedTreeRT
* calls that must be made on a per tree basis are done by this class.
* Calls that apply to all trees (i.e. static SpeedTreeRT functions)
* are made in the functions in main.cpp.
*
*
* *** INTERACTIVE DATA VISUALIZATION (IDV) PROPRIETARY INFORMATION ***
*
* This software is supplied under the terms of a license agreement or
* nondisclosure agreement with Interactive Data Visualization and may
* not be copied or disclosed except in accordance with the terms of
* that agreement.
*
* Copyright (c) 2001-2003 IDV, Inc.
* All Rights Reserved.
*
* IDV, Inc.
* 1233 Washington St. Suite 610
* Columbia, SC 29201
* Voice: (803) 799-1699
* Fax: (803) 931-0320
* Web: http://www.idvinc.com
*/

#pragma once
#pragma warning (disable : 4786)

///////////////////////////////////////////////////////////////////////
// Include files

#include "SpeedTreeMaterial.h"
#include <SpeedTreeRT.h>

#ifdef DIRECTX9
#include <MicrosoftDirectX/d3d9.h>
#include <MicrosoftDirectX/d3dx9.h>
#include <MicrosoftDirectX/d3d9types.h>
#else
#include <d3d8.h>
#include <d3dx8.h>
#include <d3d8types.h>
#endif
#include <vector>
#include <memory>
#include <list>

#include "../EterLib/GrpObjectInstance.h"
#include "../EterLib/GrpImageInstance.h"
#include "../EterLib/GrpCollisionObject.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete (p); (p) = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p) = NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = NULL; } }
#endif

///////////////////////////////////////////////////////////////////////
// class CSpeedTreeWrapper declaration

#pragma warning(push)
#pragma warning(disable:4100)

class CSpeedTreeWrapper : public CGraphicObjectInstance, public std::enable_shared_from_this<CSpeedTreeWrapper>
{
	typedef std::shared_ptr<CSpeedTreeWrapper> SpeedTreeWrapperPtr;
	typedef std::weak_ptr<CSpeedTreeWrapper> SpeedTreeWrapperWeakPtr;

	enum
	{
		ID = TREE_OBJECT
	};

	int GetType() const { return ID; }

	// Collision Data
protected:
	virtual void OnUpdateCollisionData(const CStaticCollisionDataVector* pscdVector);
	virtual void OnUpdateHeighInstance(CAttributeInstance* pAttributeInstance) {}
	virtual bool OnGetObjectHeight(float fX, float fY, float* pfHeight) { return false; }
	// Bounding Sphere

public:
	virtual bool GetBoundingSphere(D3DXVECTOR3& v3Center, float& fRadius);

public:
	static bool ms_bSelfShadowOn;

public:
	// methods from CGraphicObjectInstance
	virtual void SetPosition(float x, float y, float z);
	virtual void CalculateBBox();

	/*
	* Render �ÿ� �޼ҵ�, �׷��� �����䳪 Ư���� ��쿡�� ���� Render ���� �θ���
	* �� �̿ܿ��� RenderBranches, RenderFronds ���� �޼ҵ带 CSpeedTreeForest���� ȣ���Ѵ�.
	*/
	virtual void OnRender();

	virtual void OnBlendRender() {}
	virtual void OnRenderToShadowMap() {}
	virtual void OnRenderShadow() {}
	virtual void OnRenderPCBlocker();

public:
	CSpeedTreeWrapper();
	virtual	~CSpeedTreeWrapper();

	const float* GetPosition();
	static void SetVertexShaders(LPDIRECT3DVERTEXSHADER9 dwBranchVertexShader, LPDIRECT3DVERTEXSHADER9 dwLeafVertexShader);

	// geometry
	bool LoadTree(const char* pszSptFile, const BYTE* c_pbBlock = NULL, unsigned int uiBlockSize = 0, unsigned int nSeed = 1, float fSize = -1.0f, float fSizeVariance = -1.0f);
	const float* GetBoundingBox(void) const { return m_afBoundingBox; }
	void GetTreeSize(float& r_fSize, float& r_fVariance);
	UINT GetCollisionObjectCount();
	void GetCollisionObject(unsigned int nIndex, CSpeedTreeRT::ECollisionObjectType& eType, float* pPosition, float* pDimensions);

	// rendering
	void SetupBranchForTreeType(void);
	void SetupBranchForTreeTypeShadow(void);
	void SetupFrondForTreeType(void);
	void SetupFrondForTreeTypeShadow(void);
	void SetupLeafForTreeType(void);
	void EndLeafForTreeType(void);
	void EndLeafForTreeTypeShadow(void);


	void UploadLeafTables(unsigned int uiLocation) const;


	void RenderBranches(void) const;
	void RenderFronds(void) const;
	void RenderLeaves(void) const;
	void RenderLeaves2(void) const;
	void RenderLeaves3(void) const;
	void RenderBillboards(void) const;

	// instancing
	std::list<SpeedTreeWrapperWeakPtr> GetInstances(unsigned int& nCount);
	SpeedTreeWrapperPtr InstanceOf(void) const { return m_pInstanceOf; }
	SpeedTreeWrapperPtr MakeInstance();
	void DeleteInstance(SpeedTreeWrapperPtr pInstance);
	CSpeedTreeRT* GetSpeedTree(void) const { return m_pSpeedTree; }

	// lighting
	const CSpeedTreeMaterial& GetBranchMaterial(void) const { return m_cBranchMaterial; }
	const CSpeedTreeMaterial& GetFrondMaterial(void) const { return m_cFrondMaterial; }
	const CSpeedTreeMaterial& GetLeafMaterial(void) const { return m_cLeafMaterial; }
	float GetLeafLightingAdjustment(void) const { return m_pSpeedTree->GetLeafLightingAdjustment(); }

	// wind
	void SetWindStrength(float fStrength) { m_pSpeedTree->SetWindStrength(fStrength); }
	void Advance(void);

	// utility
	LPDIRECT3DTEXTURE8 GetBranchTexture(void) const;
	void CleanUpMemory(void);

private:
	void SetupBuffers(void);
	void SetupBranchBuffers(void);
	void SetupFrondBuffers(void);
	void SetupLeafBuffers(void);
	void PositionTree(void) const;
	static bool LoadTexture(const char* pFilename, CGraphicImageInstance& rImage);
	void SetShaderConstants(const float* pMaterial) const;
	mutable UINT m_num_leaves_to_render;

private:
	// SpeedTreeRT data
	CSpeedTreeRT* m_pSpeedTree; // the SpeedTree object
	CSpeedTreeRT::STextures* m_pTextureInfo; // texture info cache
	bool m_bIsInstance; // is this an instance?
	std::vector<SpeedTreeWrapperPtr> m_vInstances; // what is an instance of us
	SpeedTreeWrapperPtr m_pInstanceOf; // which tree is this an instance of

	// geometry cache
	CSpeedTreeRT::SGeometry* m_pGeometryCache; // cache for pulling geometry from SpeedTree avoids lots of reallocation

	// branch buffers
	LPDIRECT3DVERTEXBUFFER8 m_pBranchVertexBuffer; // branch vertex buffer
	unsigned int m_unBranchVertexCount; // number of vertices in branches
	LPDIRECT3DINDEXBUFFER8 m_pBranchIndexBuffer; // branch index buffer
	unsigned short* m_pBranchIndexCounts; // number of indexes per branch LOD level

	// frond buffers
	LPDIRECT3DVERTEXBUFFER8 m_pFrondVertexBuffer; // frond vertex buffer
	unsigned int m_unFrondVertexCount; // number of vertices in frond
	LPDIRECT3DINDEXBUFFER8 m_pFrondIndexBuffer; // frond index buffer
	unsigned short* m_pFrondIndexCounts; // number of indexes per frond LOD level

	// leaf buffers
	unsigned short m_usNumLeafLods; // the number of leaf LODs
	LPDIRECT3DVERTEXBUFFER8* m_pLeafVertexBuffer; // leaf vertex buffer
	bool* m_pLeavesUpdatedByCpu; // stores which LOD's have been updated already per frame

	// tree properties
	float m_afPos[3]; // tree position
	float m_afBoundingBox[6]; // tree bounding box

	// materials
	CSpeedTreeMaterial m_cBranchMaterial; // branch material
	CSpeedTreeMaterial m_cLeafMaterial; // leaf material
	CSpeedTreeMaterial m_cFrondMaterial; // frond material

	// branch texture
	CGraphicImageInstance m_BranchImageInstance;
	CGraphicImageInstance m_ShadowImageInstance; // shadow texture object (used if shadows are enabled)
	CGraphicImageInstance m_CompositeImageInstance;

	static LPDIRECT3DVERTEXSHADER9 ms_dwBranchVertexShader;
	static LPDIRECT3DVERTEXSHADER9 ms_dwLeafVertexShader;
};

#pragma warning(pop)