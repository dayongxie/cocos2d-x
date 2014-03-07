#include "FontJni.h"

namespace cocos2d
{
////////////////////////////////////////////////////////////////////////////////
	const char* JavaFont::className = "org/cocos2dx/lib/Cocos2dxFont";

	JavaFont::JavaFont()
	{
		JniHelper::getMethodInfo(m_methodInit, className, "<init>", "()V");
		JniHelper::getMethodInfo(m_methodSetFont, className, "setFont", "(Ljava/lang/String;IZZ)V");
		JniHelper::getMethodInfo(m_methodGetHeight, className, "getHeight", "()I");
		JniHelper::getMethodInfo(m_methodLoadCharactor, className, "loadCharactor", "(C)Z");

		m_jObject = m_methodInit.env->NewObject(m_methodInit.classID, m_methodInit.methodID);
		m_jObject = m_methodInit.env->NewGlobalRef(m_jObject);
	}

	JavaFont::~JavaFont()
	{
		m_methodInit.env->DeleteGlobalRef(m_jObject);
	}

	void JavaFont::setFont(const std::string& name, int size, bool bold, bool italic)
	{
		jstring jstrName = m_methodSetFont.env->NewStringUTF(name.c_str());
		jboolean jBold = bold ? 1 : 0;
		jboolean jItalic = italic ? 1 : 0;

		m_methodSetFont.env->CallVoidMethod(m_jObject, m_methodSetFont.methodID, jstrName, size, jBold, jItalic);
	}
	
	int JavaFont::getHeight()
	{
		return m_methodGetHeight.env->CallIntMethod(m_jObject, m_methodGetHeight.methodID);
	}

	static CCGlyph* s_glyph = NULL;
	bool JavaFont::loadCharactor(unsigned int _id, CCGlyph* _glyph)
	{
		jchar jCharactor = _id;

		s_glyph = _glyph;
		jboolean result = m_methodLoadCharactor.env->CallBooleanMethod(m_jObject, m_methodLoadCharactor.methodID, jCharactor);

		return result != 0;
	}

	extern "C"
	{
		void Java_org_cocos2dx_lib_Cocos2dxFont_onCharactorLoaded(JNIEnv*  env, jobject thiz, jintArray _pixels, jint _glyphWidth)
		{
			int size = env->GetArrayLength(_pixels);

			s_glyph->buffer.resize(size * 2, 0);
			std::fill(s_glyph->buffer.begin(), s_glyph->buffer.end(), 0);

			int* c_pixels = env->GetIntArrayElements(_pixels, NULL);
			uint16_t* dstPtr = (uint16_t*)&s_glyph->buffer[0];
			for (unsigned i = 0; i < size; ++i) {
				dstPtr[i] = c_pixels[i] >> 16;
				dstPtr[i] |= 0x00FF;
			}

			env->ReleaseIntArrayElements(_pixels, c_pixels, 0);

			s_glyph->width = _glyphWidth;
			s_glyph->height = size / _glyphWidth;
			s_glyph->advance = _glyphWidth;

		}
	}
}
