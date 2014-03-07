#include "CCNativeFont_android.h"

namespace cocos2d
{

	CCNativeFont* CCNativeFont::create()
	{
		return new CCNativeFontAndroid();
	}


	/////////////////////////
	CCNativeFontAndroid::CCNativeFontAndroid()
	{
	}

	
	CCNativeFontAndroid::~CCNativeFontAndroid()
	{
	}

	void CCNativeFontAndroid::setFont(const std::string& _name, int _size, bool bold)
	{
		m_jFont.setFont(_name, _size, bold, false);
		mDefaultHeight = m_jFont.getHeight();
	}
    
    float CCNativeFontAndroid::getDefaultHeight()
    {
        return mDefaultHeight;
    }
    
	CCGlyph* CCNativeFontAndroid::loadCharactor(int _ch, CCGlyph* _glyph)
	{
        if (_glyph == NULL)
        {
            _glyph = new CCGlyph();
	    _glyph->autorelease();
        }

		do {
			if (!m_jFont.loadCharactor(_ch, _glyph))
				break;

			return _glyph;
		} while(0);

		return NULL;
	}
	
}
