package appmagics.trackerprofilingandroid;

import android.content.Context;

/**
 * Created by SHI.yang on 2017/8/23.
 */

public class Tracker {
    static {
        System.loadLibrary("native-lib");
    }

    public void init(int type) {
        initJNI(type);
    }

    public void init(Context context, int type, int width, int height, int format, String path, int angle) {
        initJNI2(context, type, width, height, format, path, angle);
    }

    public native void initJNI(int type);

    public native void initJNI2(Context context, int type, int width, int height, int format, String path, int angle);
}
