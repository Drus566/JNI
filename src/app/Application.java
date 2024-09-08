package app;

import java.util.ArrayList;
import java.util.List;

public class Application {
    public static void main(String[] args) {
        System.out.println("Welcome to the Java Application!");

        NativeLib nl = new NativeLib();
        nl.hello();
        int random = nl.getRandom();
        System.out.println("Get random " + random);

        float[][] floatArray = new float[3][4];

        // Заполнение массива значениями
        for (int i = 0; i < floatArray.length; i++) {
            for (int j = 0; j < floatArray[i].length; j++) {
                floatArray[i][j] = (i + 1) * (j + 1) * 1.5f; // Пример заполнения
            }
        }
        nl.printMatrix(floatArray);

        MyObject my_obj = nl.processObject(new MyObject(13, "Таня"));
        System.out.println("New ID: " + my_obj.id + ", Name: " + my_obj.name);

        List<MyObject> myList = new ArrayList<>();
        myList.add(new MyObject(1, "Иван"));
        myList.add(new MyObject(2, "Наташа"));

        // Вызов нативного метода и получение нового списка
        List<MyObject> newList = nl.processList(myList);

//        System.out.println(newList.isEmpty());
        // Вывод нового списка
        for (MyObject obj : newList) {
            System.out.println("ID: " + obj.id + ", Name: " + obj.name);
        }


    }
}
