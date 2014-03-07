#include "CCNativeFont_ios.h"

namespace cocos2d
{

	CCNativeFont* CCNativeFont::create()
	{
		return new CCNativeFontIos();
	}

	CCNativeFontIos::CCNativeFontIos()
		:mFont(0)
	{
	}

	
	CCNativeFontIos::~CCNativeFontIos()
	{
	}

	void CCNativeFontIos::setFont(const std::string& _name, int _size, bool bold)
	{
		NSString* fntName = [NSString stringWithUTF8String:_name.c_str()];
		
		mFont = [UIFont fontWithName:fntName size:_size];
		if (!mFont) {
            if (!bold)
                mFont = [UIFont systemFontOfSize:_size];
            else
                mFont = [UIFont boldSystemFontOfSize:_size];
		}
        
		[mFont retain];
	}
    
    float CCNativeFontIos::getDefaultHeight()
    {
        return [mFont leading];
    }
    
	CCGlyph* CCNativeFontIos::loadCharactor(int _ch, CCGlyph* _glyph)
	{
        if (_glyph == NULL)
        {
            _glyph = new CCGlyph();
			_glyph->autorelease();
        }
        
		do {
			CGSize textSize = CGSizeZero;
			unichar _uchar = (unichar)_ch;
			NSString *s = [NSString stringWithCharacters:&_uchar length:1];

			textSize = [s sizeWithFont:mFont];

			_glyph->width = textSize.width;
			_glyph->height = textSize.height;
            _glyph->advance = textSize.width;

            unsigned pixelCount = unsigned(textSize.width * textSize.height);
			uint8_t buffer[pixelCount];
			std::fill(buffer, buffer + pixelCount, 0);
			CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceGray();

			CGContextRef context = CGBitmapContextCreate(buffer, textSize.width, textSize.height,
														 8, textSize.width, colorSpace, kCGImageAlphaNone);

			if (!context)
				break;

			CGContextSetGrayFillColor(context, 1, 1);
			CGContextTranslateCTM(context, 0.0f, textSize.height);
			CGContextScaleCTM(context, 1.0f, -1.0f);
			UIGraphicsPushContext(context);
		
			[s drawAtPoint:CGPointMake(0, 0) withFont:mFont];

			UIGraphicsPopContext();

			_glyph->buffer.resize(textSize.width * textSize.height * 2);

			uint16_t* glyphBuffer = (uint16_t*)(&_glyph->buffer[0]);
			for (unsigned i = 0; i < textSize.width * textSize.height; i++) {
				uint16_t& color = glyphBuffer[i];
				color = buffer[i];
				color |= (color << 8);
                color = color | 0x00FF;
			}

			return _glyph;
		} while(0);

		return NULL;
	}
	
}
