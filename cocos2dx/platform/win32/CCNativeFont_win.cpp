#include "CCNativeFont_win.h"
#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "CCEGLView.h"

namespace cocos2d
{

	CCNativeFont* CCNativeFont::create()
	{
		CCNativeFontWin * pRet = new CCNativeFontWin();
		if (pRet)
		{
			pRet->autorelease();
			return pRet;
		}

		CC_SAFE_DELETE(pRet);
		return NULL;
	}

	CCNativeFontWin::CCNativeFontWin()
		:m_MemDC(NULL),
		m_Font(NULL)
	{
	}

	
	CCNativeFontWin::~CCNativeFontWin()
	{
		if (m_Font != NULL)
		{
			::DeleteObject(m_Font);
			m_Font = NULL;
		}

		// 清理 GDI 相关的资源
		if (m_MemDC != NULL)
		{
			::DeleteDC(m_MemDC);
			m_MemDC = NULL;
		}
	}

	void CCNativeFontWin::setFont(const std::string& _name, int _size, bool bold)
	{
		HDC hDC = ::GetDC(NULL);
		m_MemDC = ::CreateCompatibleDC(hDC);
		if (m_MemDC == NULL)
		{
			CCLOGERROR("字体兼容DC创建失败");
			return;
		}

		::ReleaseDC(NULL,hDC);

		// 字体模式
		::SetMapMode(m_MemDC, MM_TEXT);
		::SetTextColor(m_MemDC, RGB(255,255,255));
		::SetBkColor(m_MemDC, RGB(0,0,0));

		HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		LOGFONTA    tNewFont = {0};

		GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);

		if (!_name.empty())
		{
			// create font from ttf file
			int nFindttf = _name.find(".ttf");
			int nFindTTF = _name.find(".TTF");

			std::string fontName = _name;
			if (nFindttf >= 0 || nFindTTF >= 0)
			{
				std::string fontPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(_name.c_str());
				int nFindPos = fontName.rfind("/");
				fontName = &fontName[nFindPos+1];
				nFindPos = fontName.rfind(".");
				fontName = fontName.substr(0, nFindPos);
				strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());

				if(AddFontResourceA(fontPath.c_str()))
				{
					SendMessage(cocos2d::CCEGLView::sharedOpenGLView()->getHWnd(), WM_FONTCHANGE, 0, 0);
				}
			}

			tNewFont.lfCharSet = DEFAULT_CHARSET;
			strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());
		}

		tNewFont.lfHeight = -_size;
		tNewFont.lfQuality = ANTIALIASED_QUALITY;
		tNewFont.lfItalic = FALSE;
		if (bold)
			tNewFont.lfWeight = 700;
		else
			tNewFont.lfWeight = 400;

		m_Font = CreateFontIndirectA(&tNewFont);

		if (! m_Font)
		{
			m_Font = hDefFont;
			CCLOGERROR("字体创建失败");
			return;
		}

		::SelectObject(m_MemDC, m_Font);

		::GetTextMetrics(m_MemDC, &m_TextMetric);
	}
    
    float CCNativeFontWin::getDefaultHeight()
    {
        return m_TextMetric.tmHeight;
    }
    
	CCGlyph* CCNativeFontWin::loadCharactor(int _ch, CCGlyph* _glyph)
	{
        if (_glyph == NULL)
        {
            _glyph = new CCGlyph();
			_glyph->autorelease();
        }

		GLYPHMETRICS _GM;
		MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};
		std::vector<uint8_t> pixels;

		memset(&_GM, 0, sizeof(GLYPHMETRICS));

		// 字模格式
		uint32_t nLen = ::GetGlyphOutlineW(m_MemDC, _ch, GGO_GRAY8_BITMAP, &_GM, 0, NULL, &mat2);

		do {
			// 获取数据
			_glyph->buffer.resize(_GM.gmBlackBoxX * _GM.gmBlackBoxY * 2, 0);

			if (nLen > 0)
			{
				pixels.resize(nLen);
				// 字符轮廓
				::GetGlyphOutlineW(m_MemDC, _ch, GGO_GRAY8_BITMAP, &_GM, nLen, &pixels[0], &mat2);

				// 位图调整
				LONG nSrcPitch = ((_GM.gmBlackBoxX + 3) >> 2) << 2;
				LONG nDstPitch = _GM.gmBlackBoxX;

				uint8_t* lpSrc = &pixels[0];
				uint16_t* lpDst = (uint16_t*)&_glyph->buffer[0];

				// 拷贝数据
				for (unsigned y = 0; y < _GM.gmBlackBoxY; ++y)
				{
					for (unsigned x = 0; x < _GM.gmBlackBoxX; ++x)
					{
						// 按字节计算
						uint16_t gray = lpSrc[x] << 2;
						if (gray != 0) {
							if (gray > 255) gray = 255;
							lpDst[x] = (gray << 8) | 0x00FF;
						}
						else
						{
							lpDst[x] = 0x00FF;
						}
					}
					lpSrc += nSrcPitch;
					lpDst += nDstPitch;
				}
			}
			else
			{
				std::fill(_glyph->buffer.begin(), _glyph->buffer.end(), 0x00);
			}

			_glyph->width = _GM.gmBlackBoxX;
			_glyph->height = _GM.gmBlackBoxY;
			_glyph->bearingX = _GM.gmptGlyphOrigin.x;
			_glyph->bearingY =  m_TextMetric.tmAscent - _GM.gmptGlyphOrigin.y;
			_glyph->advance = _GM.gmCellIncX;

			return _glyph;
		} while(0);

		return NULL;
	}
	
}
