public class MyActivity extends Activity {
     protected void onCreate(Bundle icicle) {
         super.onCreate(icicle);

         setContentView(R.layout.content_layout_id);

         final CheckBox checkBox = (CheckBox) findViewById(R.id.checkbox_id);
         if (checkBox.isChecked()) {
             checkBox.setChecked(false);
         }
     }
 }
