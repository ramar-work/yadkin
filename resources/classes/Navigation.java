package com.[[ identifier ]].[[ app_name ]];

import androidx.appcompat.app.AppCompatActivity;

import android.widget.AdapterView;
import android.widget.ListView;
import android.view.View;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class [[ class_name ]] extends AppCompatActivity {

    @Override
    protected void onCreate( Bundle b ) {
        super.onCreate( b );
        setContentView( R.layout.[[ layout_name ]] );

        Class<?>[] activities = {
                SearchActivity.class
                , Favorites.class
                , About.class
        };

        AdapterView.OnItemClickListener icl = new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Toast.makeText( [[ class_name ]].this, "Index: " + i, Toast.LENGTH_LONG ).show();
                Intent intent = new Intent( [[ class_name ]].this, activities[ i ] );
                startActivity( intent );
            }
        };

        //ListView lv = findViewById( R.id.nav_options );
        //lv.setOnItemClickListener( icl );
    }
}
