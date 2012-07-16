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
import android.opengl.GLU;  
import android.view.GestureDetector;
import android.view.MotionEvent;
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

	// exit
	public void exit()
	{
		demo_exit();
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
			demo_init();
		}

		// draw frame
		public void onDrawFrame(GL10 gl)
		{
			demo_draw();
		}

		// resize surface
		public void onSurfaceChanged(GL10 gl, int width, int height)
		{
			demo_size(width, height);
		}
	}

	// native
	private static native void 		demo_init();
	private static native void 		demo_exit();
	private static native void 		demo_draw();
	private static native void 		demo_size(int width, int height);
	private static native void 		demo_move(float x, float y);
	private static native int 		demo_tfps();
	private static native int 		demo_trpt();

	// load library
	static 
	{
		System.loadLibrary("demo");
	}
}

