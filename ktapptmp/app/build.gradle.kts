/* this is about as simple as it can get */
plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.android)
    alias(libs.plugins.kotlin.compose)
}

android {

		// TBD
    compileSdk = 34

		// TBD
    namespace 'com.[[ identifier ]].[[ app_name ]]'

		// TBD
    defaultConfig {

				// TBD
        applicationId "com.[[ identifier ]].[[ app_name ]]"

				// TBD
        minSdk = 24

				// TBD
        targetSdk = 34

				// TBD
        versionCode = 1

				// TBD
        versionName = "1.0"

				// TBD
        //testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }

    compileOptions {

				// TBD: Changing this on the fly is VERY helpful
        sourceCompatibility = JavaVersion.VERSION_11

				// TBD: Changing this on the fly is VERY helpful
        targetCompatibility = JavaVersion.VERSION_11

    }

    kotlinOptions {
				// TBD: Changing this on the fly is VERY helpful
        jvmTarget = "11"
    }

    buildFeatures {
				// TBD: My guess is that the Compose compiler won't know what to do if this is not here
        compose = true
    }
}

dependencies {

    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.lifecycle.runtime.ktx)
    implementation(libs.androidx.activity.compose)
    implementation(platform(libs.androidx.compose.bom))
    implementation(libs.androidx.ui)
    implementation(libs.androidx.ui.graphics)
    implementation(libs.androidx.ui.tooling.preview)
    implementation(libs.androidx.material3)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
    androidTestImplementation(platform(libs.androidx.compose.bom))
    androidTestImplementation(libs.androidx.ui.test.junit4)
    debugImplementation(libs.androidx.ui.tooling)
    debugImplementation(libs.androidx.ui.test.manifest)
}
