## 1. local.properties  (open module setting -> sdk location)
> ndk.dir=D\:\\andr\\android-ndk-r10e

## 2.
## 3. build.gradle   (ndk module setting)
    ## One Way:
    android {
        defaultConfig {

        }
        android.ndk {
            moduleName = "NdkSample"
            cppFlags += "-std=c++11"
            cppFlags += "-fexceptions"
            cppFlags += "-I${file("src/main/jni//include")}".toString()
            ldLibs += ["android", "log"]
            stl = "gnustl_shared"
        }
        android.productFlavors {
            create("arm7") {
                ndk.abiFilters.add("armeabi-v7a")
            }
            create("arm8") {
                ndk.abiFilters.add("arm64-v8a")
            }
        }
    }
    ## Two way: (may deprecated -> add 'android.useDeprecatedNdk=true' to gradle.properties file)
    android {
        compileSdkVersion 23
        buildToolsVersion "23.0.2"

        defaultConfig {
            applicationId "cn.dcs.leef.main"
            minSdkVersion 19
            targetSdkVersion 23
            versionCode 1
            versionName "1.0"

            ndk{
                moduleName "SecondLib"
                abiFilters "armeabi", "armeabi-v7a", "x86"
                ldLibs "log", "z", "m", "EGL", "GLESv3", "dl"  // Link with these libraries! 在这里添加你原先在makefile里ldlibs所链接的库
                cFlags "-DANDROID_NDK -D_DEBUG DNULL=0"   // Define some macros
                stl "stlport_shared"                      // Use shared stlport library
            }
        }
    }

## 4 .javah *.h
### first way
javac -classpath D:/andr/adt_win/sdk/platforms/android-23/android.jar; cn/dcs/leef/jni/NativeTool.java
javah -classpath D:/andr/adt_win/sdk/platforms/android-23/android.jar; -d ../jni cn.dcs.leef.jni.NativeTool
### second way
1. make project
2. javah -d ..\jni -classpath D:\andr\adt_win\sdk\platforms\android-23\android.jar;..\..\..\build\intermediates\classes\arm7\debug cn.dcs.leef.jni.NativeTool
## 5. write & implentment *.cpp


[Build Doc]: http://tools.android.com/tech-docs/new-build-system/gradle-experimental
[ndk deprecated]: http://stackoverflow.com/questions/31979965/after-updating-android-studio-to-version-1-3-0-i-am-getting-ndk-integration-is