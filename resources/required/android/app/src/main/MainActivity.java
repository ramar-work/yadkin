package com.[[ identifier ]].[[ app_name ]]; 

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.widget.TextView;
import android.widget.Button;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);
/*
            Button b = (Button)findViewById( R.id.my_button );
            b.setOnClickListener( new View.OnClickListener() {
                @Override
                public void onClick( View v ) {
                    clickToStart( v );
                }
            });
*/
			setContentView(R.layout.activity_main);
    }

    public void clickToStart( View v ) {
        /*
        Intent i = new Intent( this, BudgetActivity.class ); 
        startActivity( i );
        */
    }
}
