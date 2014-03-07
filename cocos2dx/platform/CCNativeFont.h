#ifndef __CC_NATIVE_FONT_H__
#define __CC_NATIVE_FONT_H__

#include <vector>
#include <string>
#include <cocoa/CCObject.h>
#include <CCStdC.h>

namespace cocos2d
{
	class CC_DLL CCGlyph :
		public CCObject
	{
	public:
		CCGlyph(
				float _width = 0.0f,
				float _height = 0.0f,
				float _advance = 0.0f,
				float _bearingX = 0.0f,
				float _bearingY = 0.0f)
			:width(_width),
			 height(_height),
			 advance(_advance),
			 bearingX(_bearingX),
			 bearingY(_bearingY)
		{
		}

		float width;
		float height;
		float advance;
		float bearingX;
		float bearingY;

        std::vector<uint8_t> buffer;
	};

	class CC_DLL CCNativeFont : 
		public CCObject
	{
	public:
		static CCNativeFont* create();

		virtual void setFont(const std::string& name, int size, bool bold) = 0;
		virtual CCGlyph* loadCharactor(int _ch, CCGlyph* _glyph) = 0;
        virtual float getDefaultHeight() = 0;
	};
}

#endif //  __CC_NATIVE_FONT_H__
