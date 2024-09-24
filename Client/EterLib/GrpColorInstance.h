#pragma once

#include "GrpColor.h"
#include "Pool.h"

class CGraphicColorInstance
{
	public:
		CGraphicColorInstance();
		virtual ~CGraphicColorInstance();

		void Clear();

		void SetColorReference(const CGraphicColor& c_rSrcColor);
		void BlendColorReference(DWORD blendTime, const CGraphicColor& c_rDstColor);

		void Update();

		const CGraphicColor& GetCurrentColorReference() const;

	protected:
		DWORD GetCurrentTime();

	protected:
		CGraphicColor m_srcColor;
		CGraphicColor m_dstColor;
		CGraphicColor m_curColor;

		DWORD m_baseTime;
		DWORD m_blendTime;
};

typedef CMemoryPool<CGraphicColorInstance> TGraphicColorInstancePool;
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
