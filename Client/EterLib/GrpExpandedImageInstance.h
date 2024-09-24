#pragma once

#include "GrpImageInstance.h"

#ifdef ENABLE_WIKI
typedef struct tagExpandedRECT
{
	LONG	left_top;
	LONG	left_bottom;
	LONG	top_left;
	LONG	top_right;
	LONG	right_top;
	LONG	right_bottom;
	LONG	bottom_left;
	LONG	bottom_right;
} ExpandedRECT, * PEXPANDEDRECT;
#endif

class CGraphicExpandedImageInstance : public CGraphicImageInstance
{
public:
	static DWORD Type();
	static void DeleteExpandedImageInstance(CGraphicExpandedImageInstance* pkInstance)
	{
		pkInstance->Destroy();
		ms_kPool.Free(pkInstance);
	}

	enum ERenderingMode
	{
		RENDERING_MODE_NORMAL,
		RENDERING_MODE_SCREEN,
		RENDERING_MODE_COLOR_DODGE,
		RENDERING_MODE_MODULATE,
	};

public:
	CGraphicExpandedImageInstance();
	virtual ~CGraphicExpandedImageInstance();

	void Destroy();

	void SetDepth(float fDepth);
	void SetOrigin();
	void SetOrigin(float fx, float fy);
	void SetRotation(float fRotation);
	void SetScale(float fx, float fy);
	void SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
	void SetRenderingMode(int iMode);
	void OnRenderCoolTime(float fCoolTime);
	void RenderCoolTime(float fCoolTime);
#ifdef ENABLE_WIKI
	void SetRenderBox(RECT& renderBox);
	DWORD GetPixelColor(DWORD x, DWORD y);
	int GetRenderWidth();
	int GetRenderHeight();

	void SetExpandedRenderingRect(float fLeftTop, float fLeftBottom, float fTopLeft, float fTopRight, float fRightTop, float fRightBottom, float fBottomLeft, float fBottomRight);
	void iSetRenderingRect(int iLeft, int iTop, int iRight, int iBottom);
	void iSetExpandedRenderingRect(int iLeftTop, int iLeftBottom, int iTopLeft, int iTopRight, int iRightTop, int iRightBottom, int iBottomLeft, int iBottomRight);
	void SetTextureRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
#endif

protected:
	void Initialize();

	void OnRender();
	void OnSetImagePointer();

	BOOL OnIsType(DWORD dwType);

protected:
	float m_fDepth;
	D3DXVECTOR2 m_v2Origin;
	D3DXVECTOR2 m_v2Scale;
	float m_fRotation;
#ifdef ENABLE_WIKI
	ExpandedRECT m_RenderingRect;
	RECT m_TextureRenderingRect;
	RECT m_renderBox;
	DWORD* m_pColorMap;
#else
	RECT m_RenderingRect;
#endif
	int m_iRenderingMode;

#ifdef ENABLE_WIKI
private:
	void SaveColorMap();
#endif

public:
	static void CreateSystem(UINT uCapacity);
	static void DestroySystem();

	static CGraphicExpandedImageInstance* New();
	static void Delete(CGraphicExpandedImageInstance* pkImgInst);

	static CMemoryPool<CGraphicExpandedImageInstance> ms_kPool;
};

//martysama0134's 7f12f88f86c76f82974cba65d7406ac8