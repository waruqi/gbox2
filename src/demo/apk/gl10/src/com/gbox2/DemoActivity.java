/* //////////////////////////////////////////////////////////////////////
 * imports
 */
package com.gbox2;
import android.app.Activity;
import android.os.Bundle;

/* //////////////////////////////////////////////////////////////////////
 * DemoActivity
 */
public class DemoActivity extends Activity
{
	// view
	private DemoView demoView = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

		// init
		demoView = (DemoView)this.findViewById(R.id.DemoView);
    }

	@Override
	public void onDestroy()
	{
		// exit
		if (demoView != null) demoView.exit();
		super.onDestroy();
	}
}
