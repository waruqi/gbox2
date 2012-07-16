/* //////////////////////////////////////////////////////////////////////
 * imports
 */
package com.gbox2;
import android.app.Activity;
import android.os.Bundle;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TextView;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.GestureDetector.OnGestureListener;
import android.view.GestureDetector.OnDoubleTapListener;
import android.view.GestureDetector.SimpleOnGestureListener;
import android.view.View;
import android.util.Log;
import android.os.Handler;

/* //////////////////////////////////////////////////////////////////////
 * DemoActivity
 */
public class DemoActivity extends Activity implements Runnable
{
	// view
	private DemoView 			demoView 		= null;

	// info
	private TextView 			infoView 		= null;

	// layout
	private LinearLayout 		toolView 		= null;

	// handler
	private Handler 			handler = new Handler();

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

		// init screen
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		// init
		toolView 	= (LinearLayout)this.findViewById(R.id.Tool);
		demoView 	= (DemoView)this.findViewById(R.id.Demo);
		infoView 	= (TextView)this.findViewById(R.id.Info);

		// init handler
		handler.postDelayed(this, 1000);
    }

	// handler
	public void run() 
	{
		int fps = demoView.fps();
		int rpt = demoView.rpt();
		infoView.setText("fps: " + fps + ", rpt: " + rpt + " us");
		handler.postDelayed(this, 1000);
	}

	@Override
	public void onDestroy()
	{
		// exit
		if (demoView != null) demoView.exit();
		super.onDestroy();
	}
}
