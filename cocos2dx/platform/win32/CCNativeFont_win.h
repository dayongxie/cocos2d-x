#ifndef __CC_NATIVE_FONT_WIN_H__
#define __CC_NATIVE_FONT_WIN_H__

#include "platform/CCNativeFont.h"
#include <windef.h>

namespace cocos2d
{
	class CCNativeFontWin :
		public CCNativeFont
	{
	public:
		CCNativeFontWin();
		~CCNativeFontWin();

		virtual void setFont(const std::string& name, int size, bool bold);
		virtual CCGlyph* loadCharactor(int _ch, CCGlyph* _glyph);
        virtual float getDefaultHeight();
	private:
		HDC m_MemDC;
		HFONT m_Font;
		TEXTMETRIC m_TextMetric;
	};

}

#endif //__CC_NATIVE_FONT_WIN_H__
