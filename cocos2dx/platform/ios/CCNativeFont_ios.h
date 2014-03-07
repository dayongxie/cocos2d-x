#ifndef __CC_NATIVE_FONT_IOS_H__
#define __CC_NATIVE_FONT_IOS_H__

#include "platform/CCNativeFont.h"
#include <UIKit/UIKit.h>

namespace cocos2d
{
	class CCNativeFontIos :
		public CCNativeFont
	{
	public:
		CCNativeFontIos();
		~CCNativeFontIos();

		virtual void setFont(const std::string& name, int size, bool bold);
		virtual CCGlyph* loadCharactor(int _ch, CCGlyph* _glyph);
        virtual float getDefaultHeight();
	private:
		id mFont;
	};

}

#endif //__CC_NATIVE_FONT_IOS_H__
