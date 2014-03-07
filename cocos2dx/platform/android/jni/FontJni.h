#ifndef __FONT_JNI_H__
#define __FONT_JNI_H__

#include "JniHelper.h"
#include "platform/CCNativeFont.h"

namespace cocos2d
{
	class JavaFont
	{
	public:
		JavaFont();
		~JavaFont();

		void setFont(const std::string& name, int size, bool bold, bool italic);
		int getHeight();
		bool loadCharactor(unsigned int _id, CCGlyph* _glyph);

	private:
		static const char* className;
		jobject m_jObject;
		cocos2d::JniMethodInfo m_methodInit;
		cocos2d::JniMethodInfo m_methodSetFont;
		cocos2d::JniMethodInfo m_methodGetHeight;
		cocos2d::JniMethodInfo m_methodLoadCharactor;
		cocos2d::JniMethodInfo m_methodGetCharactor;
	};
}

#endif // __FONT_JNI_H__
