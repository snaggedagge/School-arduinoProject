package dkarlsso.arduinoproject.model;

import java.util.List;

public class ArduinosStatusDTO {

    private List<ArduinoDTO> arduinos;

    private float temperature;

    public List<ArduinoDTO> getArduinos() {
        return arduinos;
    }

    public void setArduinos(List<ArduinoDTO> arduinos) {
        this.arduinos = arduinos;
    }

    public float getTemperature() {
        return temperature;
    }

    public void setTemperature(float temperature) {
        this.temperature = temperature;
    }
}
