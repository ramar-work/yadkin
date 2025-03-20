// MainActivity.java - Write your own stuff in here to get started...
package com.[[ identifier ]].[[ app_name ]]; 

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview


// Import themes with this.  Never been so simple
import com.example.kotlintestapp.ui.theme.KotlinTestAppTheme


// Not referencing a Theme will help simplify this even further 
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
						/*
            KotlinTestAppTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = "Android",
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
						*/
						Surface( modifier = Modifier.fillMaxSize(), color = MaterialTheme.colorScheme.background ) {
							Greeting( name = "John", modifier = Modifier.padding( 16.dp, 32.dp ) )
						}
        }
    }
}


@Composable
fun GreetingText(message: String, from: String, modifier: Modifier = Modifier) {
	Column (
		modifier = modifier,
		verticalArrangement = Arrangement.Center
	) {
		Text(
			text = message,
			fontSize = 100.sp,
			lineHeight = 116.sp,
		)
		Text(
			text = from,
			fontSize = 36.sp
		)
	}
}


// TODO: This is a good base widget.  Perhaps show some other info?
@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}


// Depending on how you build, this MIGHT not be necessary
@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    KotlinTestAppTheme {
        Greeting("Android")
    }
}
