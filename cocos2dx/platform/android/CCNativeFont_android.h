#ifndef __CC_NATIVE_FONT_ANDROID_H__
#define __CC_NATIVE_FONT_ANDROID_H__

#include "platform/CCNativeFont.h"
#include <jni/FontJni.h>

namespace cocos2d
{
	class CCNativeFontAndroid :
		public CCNativeFont
	{
	public:
		CCNativeFontAndroid();
		~CCNativeFontAndroid();

		virtual void setFont(const std::string& name, int size, bool bold);
		virtual CCGlyph* loadCharactor(int _ch, CCGlyph* _glyph);
        virtual float getDefaultHeight();
	private:
		JavaFont m_jFont;
		float mDefaultHeight;
	};

}

#endif //__CC_NATIVE_FONT_ANDROID_H__
