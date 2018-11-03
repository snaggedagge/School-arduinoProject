package dkarlsso.arduinoproject;

import android.os.Bundle;
import android.os.Message;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.ToggleButton;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;

import dkarlsso.arduinoproject.connection.ArduinoConnector;
import dkarlsso.arduinoproject.model.ArduinosStatusDTO;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MyActivity";

    private ArduinoConnector arduinoConnector;

    private MessageHandler mHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        int SDK_INT = android.os.Build.VERSION.SDK_INT;
        if (SDK_INT > 9)
        {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
            StrictMode.setThreadPolicy(policy);
        }
        else if (SDK_INT > 8)
        {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
                    .permitAll().build();
            StrictMode.setThreadPolicy(policy);
            //your codes here
        }



        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        final ToggleButton btnArduinoOne = findViewById(R.id.button);
        final ToggleButton btnArduinoTwo = findViewById(R.id.button2);
        final Button allBtn = findViewById(R.id.button3);


        final TextView temperature = findViewById(R.id.actualTempText);

        final List<ToggleButton> arduinoButtons = Arrays.asList(btnArduinoOne, btnArduinoTwo);

        for(Button button : arduinoButtons) {
            button.setVisibility(View.GONE);
        }


        mHandler = new MessageHandler(arduinoButtons, temperature);
        arduinoConnector= new ArduinoConnector("http://192.168.43.87");

        /* Disgusting code yeah i know. I added ID mappings to connector class but this class just doesnt seem to give a shit  ¯\_(ツ)_/¯   */

        btnArduinoOne.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    btnArduinoOne.setActivated(!btnArduinoOne.isActivated());
                    btnArduinoOne.refreshDrawableState();
                    arduinoConnector.turnLightOn(0, btnArduinoOne.isActivated());
                } catch (Exception e) {
                    Log.e("YES", e.getMessage(), e);
                }
            }
        });

        /* Disgusting code yeah i know. I added ID mappings to connector class but this class just doesnt seem to give a shit  ¯\_(ツ)_/¯   */
        btnArduinoTwo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    btnArduinoTwo.setActivated(!btnArduinoTwo.isActivated());
                    btnArduinoTwo.refreshDrawableState();
                    arduinoConnector.turnLightOn(1, btnArduinoTwo.isActivated());
                } catch (Exception e) {
                    Log.e("YES", e.getMessage(), e);
                }
            }
        });

        /* Disgusting code yeah i know. I added ID mappings to connector class but this class just doesnt seem to give a shit  ¯\_(ツ)_/¯   */
        allBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    allBtn.setActivated(!allBtn.isActivated());
                    arduinoConnector.turnOnAllLights(false);
                } catch (Exception e) {
                    Log.e("YES", e.getMessage(), e);
                }
            }
        });

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    while(true) {
                        final ArduinosStatusDTO arduinosStatus = arduinoConnector.getArduinoStatus();

                        Message msg = mHandler.obtainMessage(Constants.MESSAGE_ARDUINO_NAME);
                        Bundle bundle = new Bundle();
                        bundle.putFloat(Constants.DATA_TEMPERATURE, arduinosStatus.getTemperature());

                        for(int i=0;i<arduinosStatus.getArduinos().size();i++) {
                            bundle.putString(Constants.DATA_ARDUINO_NAME + i, arduinosStatus.getArduinos().get(i).getName());
                            bundle.putBoolean(Constants.DATA_ARDUINO_LIGHT_ON + i, arduinosStatus.getArduinos().get(i).isLightOn());
                        }
                        msg.setData(bundle);
                        mHandler.sendMessage(msg);
                        Thread.sleep(10000);
                    }
                } catch (Exception e) {
                    Log.e("YES", e.getMessage(), e);
                }
            }
        }).start();

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
