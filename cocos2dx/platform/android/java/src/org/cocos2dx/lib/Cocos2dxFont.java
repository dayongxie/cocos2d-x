/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.lib;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.Rect;
import android.graphics.Paint.FontMetricsInt;
import android.graphics.PorterDuff;
import android.util.Log;

public class Cocos2dxFont{
	/*
	 * The values are the same as cocos2dx/platform/CCImage.h.
	 */
	private static final int HALIGNCENTER = 3;
	private static final int HALIGNLEFT	  = 1;
	private static final int HALIGNRIGHT  = 2;
	// vertical alignment
	private static final int VALIGNTOP    = 1;
	private static final int VALIGNBOTTOM = 2;
	private static final int VALIGNCENTER = 3;
	
	private static Context context;
	
    private Bitmap bitmap;
    private Canvas canvas;
    private Paint paint;
    private FontMetricsInt metrics;

    public Cocos2dxFont()
    {
    }

	public static void setContext(Context context){
		Cocos2dxFont.context = context;
	}
	
	public void setFont(String fontName, int fontSize, boolean bold, boolean italic) {
		paint = new Paint();
		paint.setColor(Color.WHITE);
		paint.setTextSize(fontSize);
		paint.setAntiAlias(true);
		paint.setTextAlign(Paint.Align.LEFT);
		metrics = new FontMetricsInt();
		
		int style = Typeface.NORMAL;
		if (bold)
			style = style | Typeface.BOLD;
		if (italic)
			style = style | Typeface.ITALIC;

		/*
		 * Set type face for paint, now it support .ttf file.
		 */
		if (fontName.endsWith(".ttf")) {
			try {
				// Typeface typeFace =
				// Typeface.createFromAsset(context.getAssets(), fontName);
				Typeface typeFace = Cocos2dxTypefaces.get(context, fontName);
				paint.setTypeface(typeFace);
			} catch (Exception e) {
				Log.e("Cocos2dxFont", "error to create ttf type face: "
						+ fontName);

				/*
				 * The file may not find, use system font
				 */
				paint.setTypeface(Typeface.create(fontName, style));
			}
		} else {
			paint.setTypeface(Typeface.defaultFromStyle(style));
		}
		
		paint.getFontMetricsInt(metrics);
    	bitmap = Bitmap.createBitmap(getHeight(), getHeight(), Bitmap.Config.ARGB_8888);
    	canvas = new Canvas(bitmap);
	}
	
	public int getHeight()
	{
		return metrics.bottom - metrics.ascent;
	}
	
    public boolean loadCharactor(char _id) {
    	char[] text = new char[] { _id };
    	
    	int glyphWidth = (int)paint.measureText(text, 0, 1);
    	/*
    	Rect bounds = new Rect();
    	paint.getTextBounds(text, 0, 1, bounds);
    	float advances[] = {};
    	paint.getTextWidths(text, 0, 1, advances);
    	*/
    	
    	if (glyphWidth > 0)
    	{
    		// Draw text to bitmap
    		//if (bitmap.getWidth() != glyphWidth)
    		{
    			bitmap = Bitmap.createBitmap(glyphWidth, getHeight(), Bitmap.Config.ARGB_8888);
    			canvas = new Canvas(bitmap);
    		}

    		canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
    		canvas.drawText(text, 0, 1, 0, bitmap.getHeight() - metrics.bottom, paint);

    		invokeCallbackCharactorLoaded(bitmap, glyphWidth);
    		
            return true;
    	}
		
    	return false;
    }

    public void invokeCallbackCharactorLoaded(Bitmap bitmap, int glyphWidth)
    {
        int[] pixels = new int[bitmap.getWidth() * bitmap.getHeight()];
		bitmap.getPixels(pixels, 0, glyphWidth, 0, 0, glyphWidth, bitmap.getHeight());
		
		onCharactorLoaded(pixels, glyphWidth);
    }
    
    public static native void onCharactorLoaded(int[] p, int glyphWidth);
}
