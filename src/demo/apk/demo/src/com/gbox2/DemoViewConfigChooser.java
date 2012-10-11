/* //////////////////////////////////////////////////////////////////////
 * imports
 */
package com.gbox2;
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;
import android.opengl.GLSurfaceView;
import android.util.Log;

// DemoViewConfigChooser
public class DemoViewConfigChooser implements GLSurfaceView.EGLConfigChooser 
{
	// tag
	static private final String 	kTag = "gbox2";

	// value
	private int[] 					mValue;

	// UsesCoverageAa
	private boolean 				mUsesCoverageAa = false;

	// pixfmt
	private int 					r = 8;
	private int 					g = 8;
	private int 					b = 8;
	private int 					a = 8;

	// depth
	private int 					depth = 16;

	// stencil
	private int 					stencil = 4;

	// multisample
	private int 					multisample = 4;

	// version
	private int 					version = 0x19;

	// init
	public DemoViewConfigChooser(int r, int g, int b, int a, int depth, int stencil, int multisample, int version)
	{
		// init pixfmt
		this.r = r;
		this.g = g;
		this.b = b;
		this.a = a;

		// init depth
		this.depth = depth;

		// init stencil
		this.stencil = stencil;

		// init multisample
		this.multisample = multisample;

		// init version
		this.version = version;
	}

	@Override
	public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display)
	{
		// EGL_OPENGL_ES1_BIT or EGL_OPENGL_ES2_BIT
		int render = version < 0x20? 1 : 4;

		// try to find a normal configuration first.	
		int[] configSpec = 
		{
			EGL10.EGL_RED_SIZE, r
		,	EGL10.EGL_GREEN_SIZE, g
		,	EGL10.EGL_BLUE_SIZE, b
		,	EGL10.EGL_ALPHA_SIZE, a
		,	EGL10.EGL_DEPTH_SIZE, depth
		,	EGL10.EGL_STENCIL_SIZE, stencil
		,	EGL10.EGL_RENDERABLE_TYPE, render 
		,	EGL10.EGL_SAMPLE_BUFFERS,  1
		,	EGL10.EGL_SAMPLES, multisample
		,	EGL10.EGL_NONE
		};
		mValue = new int[1];
		if (!egl.eglChooseConfig(display, configSpec, null, 0, mValue))
		{
			throw new IllegalArgumentException("eglChooseConfig failed");
		}
		int numConfigs = mValue[0];

		// No normal multisampling config was found. Try to create a
		// converage multisampling configuration, for the nVidia Tegra2.
		// See the EGL_NV_coverage_sample documentation.
		if (numConfigs <= 0 && multisample > 1) 
		{
			final int EGL_COVERAGE_BUFFERS_NV = 0x30E0;
			final int EGL_COVERAGE_SAMPLES_NV = 0x30E1;

			configSpec = new int[]
			{
				EGL10.EGL_RED_SIZE, r
			,	EGL10.EGL_GREEN_SIZE, g
			,	EGL10.EGL_BLUE_SIZE, b
			,	EGL10.EGL_ALPHA_SIZE, a
			,	EGL10.EGL_DEPTH_SIZE, depth
			,	EGL10.EGL_STENCIL_SIZE, stencil
			,	EGL10.EGL_RENDERABLE_TYPE, render
			,	EGL_COVERAGE_BUFFERS_NV, 1
			,	EGL_COVERAGE_SAMPLES_NV, multisample
			,	EGL10.EGL_NONE
			};

			if (!egl.eglChooseConfig(display, configSpec, null, 0, mValue)) 
			{
				throw new IllegalArgumentException("2nd eglChooseConfig failed");
			}
			numConfigs = mValue[0];

			// Give up, try without multisampling.
			if (numConfigs <= 0)
			{
				configSpec = new int[]
				{
					EGL10.EGL_RED_SIZE, r
				,	EGL10.EGL_GREEN_SIZE, g
				,	EGL10.EGL_BLUE_SIZE, b
				,	EGL10.EGL_ALPHA_SIZE, a
				,	EGL10.EGL_DEPTH_SIZE, depth
				,	EGL10.EGL_STENCIL_SIZE, stencil
				,	EGL10.EGL_RENDERABLE_TYPE, render
				,	EGL10.EGL_NONE
				};

				if (!egl.eglChooseConfig(display, configSpec, null, 0, mValue)) 
				{
					throw new IllegalArgumentException("3rd eglChooseConfig failed");
				}
				numConfigs = mValue[0];

				if (numConfigs <= 0)
				{
					throw new IllegalArgumentException("No configs match configSpec");
				}
			}
			else 
			{
				mUsesCoverageAa = true;
				Log.i(kTag, "mUsesCoverageAa");
			}
		}

		// Get all matching configurations.
		EGLConfig[] configs = new EGLConfig[numConfigs];
		if (!egl.eglChooseConfig(display, configSpec, configs, numConfigs, mValue)) 
		{
			throw new IllegalArgumentException("data eglChooseConfig failed");
		}

		// CAUTION! eglChooseConfigs returns configs with higher bit depth
		// first: Even though we asked for rgb565 configurations, rgb888
		// configurations are considered to be "better" and returned first.
		// You need to explicitly filter the data returned by eglChooseConfig!
		int index = -1;
		for (int i = 0; i < configs.length; ++i)
		{
			if (findConfigAttrib(egl, display, configs[i], EGL10.EGL_RED_SIZE, 0) == r)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
		{
			Log.i(kTag, "Did not find sane config, using first");
		}
		EGLConfig config = configs.length > 0 ? configs[index] : null;
		if (config == null)
		{
			throw new IllegalArgumentException("No config chosen");
		}
		return config;
	}

	private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue)
	{
		if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) 
		{
			return mValue[0];
		}
		return defaultValue;
	}

	public boolean usesCoverageAa() 
	{
		return mUsesCoverageAa;
	}
}
