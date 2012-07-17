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
import android.widget.Button;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.GestureDetector.OnGestureListener;
import android.view.GestureDetector.OnDoubleTapListener;
import android.view.GestureDetector.SimpleOnGestureListener;
import android.view.View;
import android.view.View.OnClickListener;
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

	// button
	private Button 				qButton 		= null;
	private Button 				wButton 		= null;
	private Button 				mButton 		= null;
	private Button 				fButton 		= null;
	private Button 				sButton 		= null;
	private Button 				pButton 		= null;

	// layout
	private LinearLayout 		toolView 		= null;

	// handler
	private Handler 			handler 		= new Handler();

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

		// init screen
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		// init
		toolView 	= (LinearLayout)this.findViewById(R.id.ToolLayout);
		demoView 	= (DemoView)this.findViewById(R.id.Demo);
		infoView 	= (TextView)this.findViewById(R.id.Info);
		qButton 	= (Button)this.findViewById(R.id.Q);
		wButton 	= (Button)this.findViewById(R.id.W);
		mButton 	= (Button)this.findViewById(R.id.M);
		fButton 	= (Button)this.findViewById(R.id.F);
		sButton 	= (Button)this.findViewById(R.id.S);
		pButton 	= (Button)this.findViewById(R.id.P);
		qButton.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v) 
			{
				demoView.key('q');
			}
		});
		wButton.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v) 
			{
				demoView.key('w');
			}
		});
		mButton.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v) 
			{
				demoView.key('m');
			}
		});
		fButton.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v) 
			{
				demoView.key('f');
			}
		});
		sButton.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v) 
			{
				demoView.key('s');
			}
		});
		pButton.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v) 
			{
				demoView.key('p');
			}
		});

		// init event
		infoView.setOnTouchListener(new View.OnTouchListener()
		{	
			// touch
			public boolean onTouch(View v, MotionEvent event) 
			{
				if (event.getAction() == MotionEvent.ACTION_DOWN) 
				{
					if (toolView.getVisibility() == View.VISIBLE) toolView.setVisibility(View.INVISIBLE);
					else toolView.setVisibility(View.VISIBLE);
				}
				return false;
			}
		});

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
