/* //////////////////////////////////////////////////////////////////////
 * imports
 */
package com.gbox2;
import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.os.SystemClock;
import android.opengl.GLUtils;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.media.AudioManager;  
import android.media.AudioTrack;  
import android.media.AudioFormat;  
import android.view.MotionEvent;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TextView;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.view.ViewGroup;
import android.view.View;
import android.view.Gravity;
import android.os.Handler;
import android.graphics.Color;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.util.DisplayMetrics;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.WindowManager;
import android.util.AttributeSet;
import android.util.Log;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;  
import android.os.Environment;
import android.provider.MediaStore;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.os.SystemClock;
import android.app.AlertDialog;  
import android.content.DialogInterface;  
import android.content.Intent;
import android.os.Handler;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.FileOutputStream;
import java.io.ByteArrayOutputStream;
import java.nio.FloatBuffer;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import java.io.IOException;
import java.io.File;

/* //////////////////////////////////////////////////////////////////////
 * DemoView
 */
class DemoView extends GLSurfaceView
{
	// context
	private Context 			context 		= null;

	// demo
	private int 				demo 		= 0;

	// init
	public DemoView(Context context, AttributeSet attrs) 
	{
		super(context, attrs);

		// init context
		this.context = context;

		// init render
		setRenderer(new DemoRender(this));

		// init focus
		requestFocus();
		setFocusableInTouchMode(true);

		// init event
		setOnTouchListener(new View.OnTouchListener()
		{	
			// touch
			public boolean onTouch(View v, MotionEvent event) 
			{
				if (event.getAction() == MotionEvent.ACTION_MOVE) 
				{
					if (event.getPointerCount() == 1) 
					{
						if (demo != 0) demo_move(demo, event.getX(0), event.getY(0));
					}
				} 
				return true;
			}
		});
	}

	// exit
	public void exit()
	{
		if (demo != 0) demo_exit(demo);
		demo = 0;
	}

	// render
	public class DemoRender implements GLSurfaceView.Renderer
	{
		// view
		private DemoView view;

		// init
		public DemoRender(DemoView view)
		{
			this.view = view;	
		}

		// init surface
		public void onSurfaceCreated(GL10 gl, EGLConfig config)
		{
			// init demo
			demo = demo_init();
		}

		// draw frame
		public void onDrawFrame(GL10 gl)
		{
			if (demo != 0) demo_draw(demo);
		}

		// resize surface
		public void onSurfaceChanged(GL10 gl, int width, int height)
		{
			if (demo != 0) demo_size(demo, width, height);
		}
	}

	// native
	private static native int 	demo_init();
	private static native void 	demo_exit(int demo);
	private static native void 	demo_draw(int demo);
	private static native void 	demo_size(int demo, int width, int height);
	private static native void 	demo_move(int demo, float x, float y);

	// load library
	static 
	{
		System.loadLibrary("demo");
	}
}

