package dkarlsso.arduinoproject.connection;

import android.util.Log;

import org.apache.commons.lang3.StringUtils;
import org.springframework.http.ResponseEntity;
import org.springframework.http.client.HttpComponentsClientHttpRequestFactory;
import org.springframework.web.client.RestTemplate;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import dkarlsso.arduinoproject.model.ArduinoDTO;
import dkarlsso.arduinoproject.model.ArduinosStatusDTO;

public class ArduinoConnector {
    private static final String URL_ARDUINOS = "arduinos";

    private static final String URL_STATUS = "status";

    private static final String URL_TURN_LIGHT_ON = "lights?";

    private static final String FORMAT_REQUEST_PARAM_TURN_LIGHT_ON = "%d=%b";

    public final Map<Integer, ArduinoDTO> arduinoIdMap = new HashMap<>();

    private final RestTemplate restTemplate = new RestTemplate();

    private final RestTemplate dropFastTemplate;

    private final String arduinoURL;

    public ArduinoConnector(final String arduinoURL) {

        HttpComponentsClientHttpRequestFactory httpRequestFactory = new HttpComponentsClientHttpRequestFactory();
        httpRequestFactory.setReadTimeout(500);

        dropFastTemplate = new RestTemplate(httpRequestFactory);
        this.arduinoURL = arduinoURL + "/";
    }

    public void turnOnAllLights(final boolean turnOnAllLights) throws IOException {
        String URL = arduinoURL + URL_TURN_LIGHT_ON;
        boolean firstParam = true;


        final List<ArduinoDTO> arduinos = new ArrayList<>();
        arduinos.addAll(arduinoIdMap.values());

        // Debugging purposes
        if(arduinos.isEmpty()) {
            for(int i=1;i<3;i++) {
                final ArduinoDTO arduinoDTO = new ArduinoDTO();
                arduinoDTO.setId(i);
                arduinoDTO.setLightOn(turnOnAllLights);
                arduinos.add(arduinoDTO);
            }
        }

        for (ArduinoDTO arduino : arduinoIdMap.values()) {
            if(!firstParam) {
                URL += "&";
            }
            URL += String.format(FORMAT_REQUEST_PARAM_TURN_LIGHT_ON, arduino.getId(), turnOnAllLights);
            firstParam = false;
        }

        Log.e("YES", URL);
        ResponseEntity<Void> response = dropFastTemplate.getForEntity(URL, Void.class);
        verifyResponse(response);
    }

    public void turnLightOn(int id, final boolean turnLightOn) throws IOException {
        final String URL = arduinoURL + URL_TURN_LIGHT_ON + String.format(FORMAT_REQUEST_PARAM_TURN_LIGHT_ON, arduinoIdMap.get(id).getId(), turnLightOn);

        ResponseEntity<Void> response = dropFastTemplate.getForEntity(URL, Void.class);
        verifyResponse(response);
    }

    /**
     * This does not retriev the full information DTO, only the names and id's
     * @return
     */
    public List<ArduinoDTO> getArduinos() throws IOException {
        ResponseEntity<ArduinosStatusDTO> response = restTemplate.getForEntity(arduinoURL + URL_ARDUINOS, ArduinosStatusDTO.class);
        verifyResponse(response);

        addArduinoMappings(response.getBody().getArduinos());
        return response.getBody().getArduinos();
    }


    /**
     * This does not retriev the full information DTO, only the names and id's
     * @return
     */
    public ArduinosStatusDTO getArduinoStatus() throws IOException {
        ResponseEntity<ArduinosStatusDTO> response = restTemplate.getForEntity(arduinoURL + URL_STATUS, ArduinosStatusDTO.class);
        verifyResponse(response);
        addArduinoMappings(response.getBody().getArduinos());
        return response.getBody();
    }

    private void addArduinoMappings(final List<ArduinoDTO> arduinos) {

        final Iterator<ArduinoDTO> iterator = arduinos.iterator();
        while(iterator.hasNext()) {
            final ArduinoDTO arduinoDTO = iterator.next();
            if(StringUtils.isBlank(arduinoDTO.getName()) || arduinoDTO.getId() < 1) {
                iterator.remove();
            }
        }

        for(int i=0;i<arduinos.size();i++) {
            arduinoIdMap.put(i, arduinos.get(i));
        }
    }

    private void verifyResponse(ResponseEntity<?> responseEntity) throws IOException {
        if(responseEntity.getStatusCode().value() == 200 && !responseEntity.hasBody()) {
            throw new IOException("Data could not be retrieved");
        }
        else if(!responseEntity.getStatusCode().is2xxSuccessful()) {
            throw new IOException("Arduino call was unsuccessful");
        }
    }

}
