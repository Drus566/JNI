package app;

import java.util.List;

public class NativeLib {
    static {
        System.loadLibrary("native_lib");
    }

    public native void hello();
    public native int getRandom();
    public native void printMatrix(float[][] matrix);

    public void printNativeResult(float value1, int value2) {
        System.out.println("Java code: value1: " + value1 + " value2: " + value2);
    }
    public native MyObject processObject(MyObject obj);

    public native List<MyObject> processList(List<MyObject> myList);

}
