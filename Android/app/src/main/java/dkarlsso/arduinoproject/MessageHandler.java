package dkarlsso.arduinoproject;

import android.content.Context;
import android.os.Message;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.ToggleButton;

import java.util.List;

/**
 * Created by Dag Karlsson on 05-May-17.
 */

public class MessageHandler extends android.os.Handler {

    private final List<ToggleButton> arduinoToggles;
    private final TextView temperatureText;

    public MessageHandler(final List<ToggleButton> arduinoToggles, final TextView temperatureText) {
        this.arduinoToggles = arduinoToggles;
        this.temperatureText = temperatureText;
    }

        @Override
        public void handleMessage(Message msg) {
            //Handle input messages from thread
            switch (msg.what) {
                case Constants.MESSAGE_ARDUINO_NAME:
                    for(int i=0;i<arduinoToggles.size();i++) {
                        final String arduinoName = msg.getData().getString(Constants.DATA_ARDUINO_NAME + i);
                        final boolean lightOn = msg.getData().getBoolean(Constants.DATA_ARDUINO_LIGHT_ON + i);


                        if(arduinoName != null) {
                            final ToggleButton toggleButton = arduinoToggles.get(i);

                            toggleButton.setVisibility(View.VISIBLE);
                            toggleButton.setActivated(lightOn);
                            toggleButton.setTextOff(String.format("%s\nLight is Off",arduinoName));
                            toggleButton.setTextOn(String.format("%s\nLight is On",arduinoName));

                            // Retarded fucking android java. Needed for refreshing apparently
                            toggleButton.setText(lightOn ? toggleButton.getTextOn() : toggleButton.getTextOff());
                        }
                    }

                    final float temperature = msg.getData().getFloat(Constants.DATA_TEMPERATURE);
                    temperatureText.setText(String.format("%.2f", temperature));
                    break;
        }
    }
}
