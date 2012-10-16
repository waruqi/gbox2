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
import android.graphics.Rect;
import android.opengl.GLES20;
import android.opengl.Matrix;
import android.content.pm.ConfigurationInfo;
import android.app.ActivityManager;
import android.graphics.drawable.BitmapDrawable;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.FileOutputStream;
import java.io.ByteArrayOutputStream;
import java.nio.FloatBuffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;
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
	private Context 				context 	= null;
	
	// chooser
	private DemoViewConfigChooser 	chooser 	= null;

	// init
	public DemoView(Context context, AttributeSet attrs) 
	{
		super(context, attrs);

		// init context
		this.context = context;

		// version
		int version = 0x19;

		// has gles2.0?
		ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();
        if (info.reqGlEsVersion >= 0x20000)
		{
			// enbale gles 2.0
			setEGLContextClientVersion(2);

			// version
			version = 0x20;
		}

		// init config chooser
//		setEGLConfigChooser(8, 8, 8, 8, 16, 4); //!< no multisample
//		setEGLConfigChooser(5, 6, 5, 0, 16, 4); //!< no multisample
//		setEGLConfigChooser(4, 4, 4, 4, 16, 4); //!< no multisample
//		setEGLConfigChooser(5, 5, 5, 1, 16, 4); //!< no multisample

		// @note multisample is not supported for gl 1.x now.
		// @note render bitmap is not supported for gl >= 2.0 now.
//		setEGLConfigChooser(chooser = new DemoViewConfigChooser(8, 8, 8, 8, 16, 4, 4, version)); //!< multisample: 4 samples
		setEGLConfigChooser(chooser = new DemoViewConfigChooser(5, 6, 5, 0, 16, 4, 4, version)); //!< multisample: 4 samples
//		setEGLConfigChooser(chooser = new DemoViewConfigChooser(4, 4, 4, 4, 16, 4, 4, version)); //!< multisample: 4 samples
//		setEGLConfigChooser(chooser = new DemoViewConfigChooser(5, 5, 5, 1, 16, 4, 4, version)); //!< multisample: 4 samples

		// init render
		setRenderer(new DemoRender(this, version));

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
						demo_move(event.getX(0), event.getY(0));
					}
				} 
				return true;
			}
		});
	}

	// fps
	public int fps()
	{
		return demo_tfps();
	}

	// rpt
	public int rpt()
	{
		return demo_trpt();
	}

	// key
	public void key(int key)
	{
		demo_tkey(key);
	}

	// exit
	public void exit()
	{
		// FIXME
//		demo_exit();
	}

	// render
	public class DemoRender implements GLSurfaceView.Renderer
	{
		// view
		private DemoView 	view 	= null;

		// version
		private int 		version = 0x19;

		// init
		public DemoRender(DemoView view, int version)
		{
			this.view = view;
			this.version = version;
		}

		// init surface
		public void onSurfaceCreated(GL10 gl, EGLConfig config)
		{
			// init demo
			demo_init(view.getWidth(), view.getHeight(), version);
		}

		// draw frame
		public void onDrawFrame(GL10 gl)
		{
			if (chooser != null && chooser.usesCoverageAa())
			{
				final int GL_COVERAGE_BUFFER_BIT_NV = 0x8000;
				if (version < 0x20) gl.glClear(GL_COVERAGE_BUFFER_BIT_NV);
				else GLES20.glClear(GL_COVERAGE_BUFFER_BIT_NV);
				Log.i("gbox2", "clear GL_COVERAGE_BUFFER_BIT_NV");
			}

			demo_draw();
		}

		// resize surface
		public void onSurfaceChanged(GL10 gl, int width, int height)
		{
			demo_size(width, height);
		}
	}

	// native
	private static native void 		demo_init(int width, int height, int version);
	private static native void 		demo_exit();
	private static native void 		demo_draw();
	private static native void 		demo_size(int width, int height);
	private static native void 		demo_move(float x, float y);
	private static native void 		demo_tkey(int key);
	private static native int 		demo_tfps();
	private static native int 		demo_trpt();

	// load library
	static 
	{
		System.loadLibrary("demo");
	}
}

