//Login.java - A standard login activity
package [[ identifier ]].[[ app_name ]];

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

//These should be selectable, but Android Studio
//can fill them in if it needs to 
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

//Not sure if this is always the best bet...
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import java.util.HashMap;
import java.util.Map;


public class [[ class_name ]] extends AppCompatActivity {

	//Error strings should be here... maybe...

	//Form fields for name and password
	EditText f_username, f_password;

	//Form field names for setting JSON fields
	final String n_username = "username", n_password = "password";

	//Endpoint for sending login requests
	final String api_endpoint = "";

	//Error messages can be up here
	final String error_auth = "User info is bad somehow.";

	//Store the token too (if one is returned)
	String token = null;

	//Keep track of subsequent requests
	final String r_tag = "[[ eid ]]";
	
	//Some way to manage multiple web requests
	RequestQueue queue = null;


	//A basic onCreate method
	@Override
	protected void onCreate ( Bundle b ) {
		super.onCreate( b );
		setContentView( R.layout.[[ ]] );
		f_username = ( EditText )findViewById( R.id.[[ uid ]] );
		f_password = ( EditText )findViewById( R.id.[[ pwid ]] );
	}


	//A basic onStop method
	@Override
	protected void onStop() {
		super.onStop();
		//Cancel any Volley requests...
	}


	@Override
	protected void onResume( Bundle b ) {
		super.onResume();
		//Do any data saving here if needed
		//Also, write stuff somewhere for recovery purposes...
		Toast.makeText( ctx, "Orientation changed.", Toast.LENGTH_LONG ).show();
	}


	//A basic Login method
	public void login ( View v ) {
		String username, password;
		Context ctx = null; 

		//Initialize things
		username = f_username.getText().toString();
		password = f_password.getText().toString();
		getApplicationContext();
		queue = Volley.newRequestQueue( this );
		JSONObject obj = new JSONObject();
		JsonObjectRequest r = null;

		//Do some validation (are these items existent?, are they long enough?)
		if ( username.length() < 4 || password.length() < 4 ) {
			//These are very stupid checks... and do absolutely nothing...
			Toast.makeText( ctx, error_auth, Toast.LENGTH_LONG ).show();
		}	

		//Add the username and password	
		obj.put( n_username, username );
		obj.put( n_password, password );

		//Make a JSON request somewhere...
		r = new JsonObjectRequest(
			Request.Method.POST
		, api_endpoint
		,	obj

			//Handle successful responses
		, new Response.Listener<JSONObject>() {
				//Need to pass the token and other data to the intent...	
				@Override	
				public void onResponse () {
					//Need to relay the message back (and handle the code somehow)
				}
			}

			//Handle unsuccessful responses
		, new Response.ErrorListener() {
				@Override	
				public void onErrorResponse ( VolleyError err ) {
					//Need to relay the message back (and handle the code somehow)
				}
			}
		);

		//Place the request
		queue.add( r );
	}
}
