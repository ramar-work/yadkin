#include "../shared.h"

struct file android_dirs[] = {
 	{ "app", 0755 }
, { "app/libs", 0755 }
, { "app/src", 0755 }
, { "app/src/androidTest", 0755 }
, { "app/src/main", 0755 }
, { "app/src/main/java", 0755 }
, { "app/src/main/java/com", 0755 }
, { "$app/src/main/java/com", 0755 }
, { "@app/src/main/java/com", 0755 }
#if 0
, { "Fapp/src/main/java/com/-/-/fragments", 0755 }
#endif
, { "app/src/main/res", 0755 }
, { "app/src/main/res/drawable", 0755 }
, { "app/src/main/res/drawable-v24", 0755 }
, { "app/src/main/res/font", 0755 }
, { "app/src/main/res/mipmap-anydpi-v26", 0755 }
, { "app/src/main/res/mipmap-hdpi", 0755 }
, { "app/src/main/res/mipmap-mdpi", 0755 }
, { "app/src/main/res/mipmap-xhdpi", 0755 }
, { "app/src/main/res/mipmap-xxhdpi", 0755 }
, { "app/src/main/res/mipmap-xxxhdpi", 0755 }
, { "app/src/main/res/values", 0755 }
, { "app/src/main/res/values-night", 0755 }
, { "app/src/test", 0755 }
, { "app/src/test/java", 0755 }
, { "app/src/test/java/com", 0755 }
, { "$app/src/test/java/com", 0755 }
, { "@app/src/test/java/com", 0755 }
, { "gradle", 0755 }
, { "gradle/wrapper", 0755 }
,	{ NULL, -1 }
};


struct file android_files[] = {
  { "$build.gradle", 0644 }
, { "$gradle.properties", 0644 }
, { "$gradlew", 0755 }
, { "$gradlew.bat", 0644 }
, { "settings.gradle", 0644 }
, { "$gradle/wrapper/gradle-wrapper.jar", 0644 }
, { "$gradle/wrapper/gradle-wrapper.properties", 0644 }
, { "app/build.gradle", 0644 }
, { "$app/proguard-rules.pro", 0644 }
, { "app/src/main/AndroidManifest.xml", 0644 }
, { "app/src/main/res/drawable/ic_launcher_background.xml", 0644 }
, { "app/src/main/res/drawable-v24/ic_launcher_foreground.xml", 0644 }
, { "app/src/main/res/mipmap-anydpi-v26/ic_launcher.xml", 0644 }
, { "app/src/main/res/mipmap-anydpi-v26/ic_launcher_round.xml", 0644 }
, { "$app/src/main/res/mipmap-hdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-hdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-mdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-mdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-xhdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-xhdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-xxhdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-xxhdpi/ic_launcher_round.webp", 0644 }
, { "$app/src/main/res/mipmap-xxxhdpi/ic_launcher.webp", 0644 }
, { "$app/src/main/res/mipmap-xxxhdpi/ic_launcher_round.webp", 0644 }
, { "app/src/main/res/values/colors.xml", 0644 }
, { "app/src/main/res/values/strings.xml", 0644 }
, { "app/src/main/res/values/themes.xml", 0644 }
, { "app/src/main/res/values-night/themes.xml", 0644 }
, { "@app/src/main/kotlin/#/#/#/MainActivity.kt", 0644 }
,	{ NULL, -1 }
};
