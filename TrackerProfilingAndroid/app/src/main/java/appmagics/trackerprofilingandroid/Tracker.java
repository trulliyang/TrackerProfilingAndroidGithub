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
        switch (type) {
            case 0:
                initJNI0(context, type, width, height, format, path, angle);
                break;
            case 1:
                initJNI1(context, type, width, height, format, path, angle);
                break;
            case 2:
                initJNI2(context, type, width, height, format, path, angle);
                break;
            case 3:
                initJNI3(context, type, width, height, format, path, angle);
                break;
            case 4:
                initJNI4(context, type, width, height, format, path, angle);
                break;
            case 5:
                initJNI5(context, type, width, height, format, path, angle);
                break;
            case 6:
                initJNI6(context, type, width, height, format, path, angle);
                break;
        }
    }

    public native void initJNI(int type);

    public native void initJNI0(Context context, int type, int width, int height, int format, String path, int angle);
    public native void initJNI1(Context context, int type, int width, int height, int format, String path, int angle);
    public native void initJNI2(Context context, int type, int width, int height, int format, String path, int angle);
    public native void initJNI3(Context context, int type, int width, int height, int format, String path, int angle);
    public native void initJNI4(Context context, int type, int width, int height, int format, String path, int angle);
    public native void initJNI5(Context context, int type, int width, int height, int format, String path, int angle);
    public native void initJNI6(Context context, int type, int width, int height, int format, String path, int angle);

}
