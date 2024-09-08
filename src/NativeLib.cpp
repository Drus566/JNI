#include "app_NativeLib.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>


JNIEXPORT void JNICALL Java_app_NativeLib_hello(JNIEnv * env, jobject thisObject) {
    std::cout << "Hello" << std::endl;

    jclass cls_awesome_lib = env -> GetObjectClass(thisObject);
    jmethodID mid_compare = env->GetMethodID(
        cls_awesome_lib,
        "printNativeResult",
        "(FI)V"
    );

    // call method
    env->CallVoidMethod(
        thisObject,
        mid_compare,
        2.0,
        3
    );
}

JNIEXPORT jint JNICALL Java_app_NativeLib_getRandom(JNIEnv *, jobject) {
      std::srand(std::time(nullptr));
      int randomValue = std::rand();
      return randomValue;
}

JNIEXPORT void JNICALL Java_app_NativeLib_printMatrix(JNIEnv *env, jobject obj, jobjectArray matrix) {
    std::cout << "C++ code: print jobjectArray:" << std::endl;
    int sizeFirstArr = env->GetArrayLength(matrix);

    for (int i = 0; i < sizeFirstArr; i++) {
        jfloatArray secondArr = (jfloatArray) env->GetObjectArrayElement(matrix, i);
        jfloat *elements = env->GetFloatArrayElements(secondArr, 0);
        int sizeSecondArr = env->GetArrayLength(secondArr);

        for (int k = 0; k < sizeSecondArr; k++) {
            float value = elements[k];
            std::cout << value << ", ";
        }

        std::cout << std::endl;

        env->ReleaseFloatArrayElements(secondArr, elements, 0);
        env->DeleteLocalRef(secondArr);
    }
}


//JNIEXPORT void JNICALL Java_app_NativeLib_processObject (JNIEnv *env, jobject obj, jobject myObject) {
//    // Получаем класс MyObject
//    jclass myObjectClass = env->GetObjectClass(myObject);
//
//    // Получаем поле id
//    jfieldID idField = env->GetFieldID(myObjectClass, "id", "I");
//    jint id = env->GetIntField(myObject, idField);
//
//    // Получаем поле name
//    jfieldID nameField = env->GetFieldID(myObjectClass, "name", "Ljava/lang/String;");
//    jstring nameString = (jstring)env->GetObjectField(myObject, nameField);
//
//    // Преобразуем jstring в std::string
//    const char *nameChars = env->GetStringUTFChars(nameString, 0);
//    std::string name(nameChars);
//    env->ReleaseStringUTFChars(nameString, nameChars);
//
//    // Выводим информацию
//    std::cout << "ID: " << id << ", Name: " << name << std::endl;
//}

JNIEXPORT jobject JNICALL Java_app_NativeLib_processObject (JNIEnv *env, jobject obj, jobject myObject) {
    // Получаем класс MyObject
    jclass myObjectClass = env->GetObjectClass(myObject);

    // Получаем поле id
    jfieldID idField = env->GetFieldID(myObjectClass, "id", "I");
    jint id = env->GetIntField(myObject, idField);

    // Получаем поле name
    jfieldID nameField = env->GetFieldID(myObjectClass, "name", "Ljava/lang/String;");
    jstring nameString = (jstring)env->GetObjectField(myObject, nameField);

    // Преобразуем jstring в std::string
    const char *nameChars = env->GetStringUTFChars(nameString, 0);
    std::string name(nameChars);
    env->ReleaseStringUTFChars(nameString, nameChars);

    // Выводим информацию
    std::cout << "ID: " << id << ", Name: " << name << std::endl;

    // Создание нового объекта MyObject
    jmethodID constructor = env->GetMethodID(myObjectClass, "<init>", "(ILjava/lang/String;)V");
    jstring newNameString = env->NewStringUTF("New таня"); // Пример изменения имени
    jobject newObject = env->NewObject(myObjectClass, constructor, id + 1, newNameString);

    // Освобождаем локальную ссылку на newNameString
    env->DeleteLocalRef(newNameString);

    // Освобождаем локальную ссылку на myObjectClass
    env->DeleteLocalRef(myObjectClass);

    // Возвращаем новый объект
    return newObject;
}

JNIEXPORT jobject JNICALL Java_app_NativeLib_processList(JNIEnv *env, jobject obj, jobject myList) {
    // Получаем класс ArrayList
    jclass listClass = env->GetObjectClass(myList);

    // Получаем метод size() для получения размера списка
    jmethodID sizeMethod = env->GetMethodID(listClass, "size", "()I");
    jint size = env->CallIntMethod(myList, sizeMethod);

    // Получаем метод get(int index) для получения элемента списка
    jmethodID getMethod = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");

    // Создаем новый список для возврата
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jobject newList = env->NewObject(arrayListClass, arrayListConstructor);

    // Получаем метод add(Object o) для добавления элементов в новый список
    jmethodID addMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    // Обрабатываем каждый элемент списка
    for (jint i = 0; i < size; i++) {
        jobject myObject = env->CallObjectMethod(myList, getMethod, i);

        // Получаем класс MyObject
        jclass myObjectClass = env->GetObjectClass(myObject);

        // Получаем поле id
        jfieldID idField = env->GetFieldID(myObjectClass, "id", "I");
        jint id = env->GetIntField(myObject, idField);

        // Получаем поле name
        jfieldID nameField = env->GetFieldID(myObjectClass, "name", "Ljava/lang/String;");
        jstring nameString = (jstring)env->GetObjectField(myObject, nameField);

        // Преобразуем jstring в std::string
        const char *nameChars = env->GetStringUTFChars(nameString, 0);
        std::string name(nameChars);
        env->ReleaseStringUTFChars(nameString, nameChars);

        // Создаем новый объект MyObject с измененными данными
        jmethodID constructor = env->GetMethodID(myObjectClass, "<init>", "(ILjava/lang/String;)V");
        jstring newNameString = env->NewStringUTF((name + " - modified").c_str());
        jobject newObject = env->NewObject(myObjectClass, constructor, id + 1, newNameString);

        // Добавляем новый объект в новый список
//        env->CallBooleanMethod(newList, addMethod, newObject);

        // Освобождаем локальные ссылки
        env->DeleteLocalRef(myObject);
        env->DeleteLocalRef(nameString);
        env->DeleteLocalRef(newNameString);
        env->DeleteLocalRef(newObject);
        env->DeleteLocalRef(myObjectClass);
    }

    // Освобождаем локальную ссылку на listClass
    env->DeleteLocalRef(listClass);
    env->DeleteLocalRef(arrayListClass);

    // Возвращаем новый список
    return newList;
}

