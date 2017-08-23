package appmagics.trackerprofilingandroid;

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

    public native void initJNI(int type);
}
