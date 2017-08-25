package appmagics.trackerprofilingandroid;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;


public class MainActivity extends AppCompatActivity {
    private Button mBtnYUV;
    private Button mBtnTrackerArcSoft;
    private Button mBtnTrackerFacePP;
    private Button mBtnTrackerSenseTime;
    private Button mBtnTrackerAppMagics;
    private Button mBtnTrackerULSee;
    private Button mBtnTrackerULSeeFaceRig;

    private byte[] mYuvData;
    private boolean mYuvDataHasGot = false;
    private int mYuvDataCount = 0;
    private int mYuvFrameLength = 720*1280*3/2;//1382400
    private String fileName = "mnt/sdcard/ws23.yuv";

    private Tracker mTracker;
    private File mDataDir;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        mTracker = new Tracker();

        mDataDir = getApplicationContext().getExternalFilesDir(null);
        if (null != mDataDir) {
            Log.e("shiyang", "shiyang dataDir = " + mDataDir);
        }

        mBtnYUV = (Button) findViewById(R.id.YUV);
        mBtnTrackerArcSoft = (Button) findViewById(R.id.ArcSoft);
        mBtnTrackerFacePP = (Button) findViewById(R.id.FacePP);
        mBtnTrackerSenseTime = (Button) findViewById(R.id.SenseTime);
        mBtnTrackerAppMagics = (Button) findViewById(R.id.appMagics);
        mBtnTrackerULSee = (Button) findViewById(R.id.ULSee);
        mBtnTrackerULSeeFaceRig = (Button) findViewById(R.id.ULSeeFaceRig);

        mBtnYUV.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.e("shiyang", "shiyang click btnYUV");

//                if (!mYuvDataHasGot) {
//                    Log.e("shiyang", "shiyang open yuv file");
//                    try {
//                        FileInputStream fin = new FileInputStream(fileName);
//                        int length = fin.available();
//                        mYuvData = new byte[length];
//                        fin.read(mYuvData);
//                        //                yuvData = new byte[1382400];
//                        //                fin.read(yuvData, 0, 1382400);
//                        fin.close();
//                        mYuvDataHasGot = true;
//                    } catch (Exception e) {
//                        Log.e("shiyang", "shiyang file " + fileName + " does not exist");
//                        e.printStackTrace();
//                    } finally {
//                        if (mYuvDataHasGot) {
//                            Log.e("shiyang", "shiyang file " + fileName + " exists");
//                        }
//                    }
//                } else {
//                    Log.e("shiyang", "shiyang no need to open yuv file again");
//                }
            }
        });

        mBtnTrackerArcSoft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.e("shiyang", "shiyang click btnTrackerArcSoft");
                String path = mDataDir.getAbsolutePath() + File.separator + "as/track_data.dat";
                mTracker.init(getApplicationContext(), 0, 1280, 720, 5, path, 270);
                Log.e("shiyang", "shiyang  mTracker.init over");
            }
        });

        mBtnTrackerFacePP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.e("shiyang", "shiyang click btnTrackerFacePP");
                mTracker.init(getApplicationContext(), 1, 1280, 720, 5, null, 270);
                Log.e("shiyang", "shiyang  mTracker.init over");
            }
        });

        mBtnTrackerSenseTime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.e("shiyang", "shiyang click btnTrackerSenseTime");

            }
        });

        mBtnTrackerAppMagics.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.e("shiyang", "shiyang click btnTrackerAppMagics");
                mTracker.init(getApplicationContext(), 3, 1280, 720, 5, null, 270);
                Log.e("shiyang", "shiyang  mTracker.init over");
            }
        });

        mBtnTrackerULSee.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.e("shiyang", "shiyang click btnTrackerULSee");
            }
        });

        mBtnTrackerULSeeFaceRig.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.e("shiyang", "shiyang click btnTrackerULSeeFaceRig");
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
