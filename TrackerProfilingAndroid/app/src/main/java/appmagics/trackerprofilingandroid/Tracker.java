package appmagics.trackerprofilingandroid;

import android.content.Context;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Created by SHI.yang on 2017/8/23.
 */

public class Tracker {
    static {
        System.loadLibrary("native-lib");
    }

    private int getProcessCpuRate() {

        StringBuilder tv = new StringBuilder();
        int rate = 0;

        try {
            String Result;
            Process p;
            p = Runtime.getRuntime().exec("top -n 1");

            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            while ((Result = br.readLine()) != null) {
                if (Result.trim().length() < 1) {
                    continue;
                } else {
                    String[] CPUusr = Result.split("%");
                    tv.append("USER:" + CPUusr[0] + "\n");
                    String[] CPUusage = CPUusr[0].split("User");
                    String[] SYSusage = CPUusr[1].split("System");
                    tv.append("CPU:" + CPUusage[1].trim() + " length:" + CPUusage[1].trim().length() + "\n");
                    tv.append("SYS:" + SYSusage[1].trim() + " length:" + SYSusage[1].trim().length() + "\n");

                    rate = Integer.parseInt(CPUusage[1].trim()) + Integer.parseInt(SYSusage[1].trim());
                    break;
                }
            }

        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        Log.e("shiyang", "shiyang cpu rate = " + rate);
        return rate;
    }

    enum TRACKER_TYPE{
        ARCSOFT,
        FACEPP,
        SENSETIME,
        SELF,
        ULSEE,
        ULSEE_FACERIG
    };

    public void init(int type) {
        initJNI(type);
    }

    public void init(Context context, int type, int width, int height, int format, String path, int angle) {
        getProcessCpuRate();
        switch (type) {
            case 0:
                initJNI0(context, type, width, height, format, path, angle);
//                getProcessCpuRate();
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
