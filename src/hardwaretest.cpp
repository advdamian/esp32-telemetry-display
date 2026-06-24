#include <Arduino.h>
#include "BluetoothSerial.h"
#include "ELMduino.h"

BluetoothSerial SerialBT;
ELM327 diagnoza;

uint8_t elmMac[6] ={}; //mac address of elm
void setup(){
    Serial.begin(115200);
    Serial.println("ESP32 Pornit");
    SerialBT.begin("ESP32_OBD2", true);
    Serial.println("Bluetooth pornit, astept conexiune...");

    if(!SerialBT.connect(elmMac)){
        Serial.println("Conexiune esuata. Verifica daca adaptorul este in priza OBD");
        while(1);
    }
    Serial.println("Conexiune reusita cu ELM327");
    Serial.println("Se asteapta raspuns de la ELM327...");
    if(!diagnoza.begin(SerialBT, false, 2000)){
        Serial.println("Adaptorul a fost gasit dar nu raspunde la comenzi.");
        while(1);
    }
    Serial.println("Comunicare OBD2 activa.");
    float tempApa = diagnoza.engineCoolantTemp();
    if(diagnoza.nb_rx_state == ELM_SUCCESS){
        Serial.print("Temperatura apa: ");
        Serial.print(tempApa);
        Serial.println("°C");
    }else if(diagnoza.nb_rx_state == ELM_GETTING_MSG){
        Serial.println("Eroare la citirea temperaturii apei.");
    }
    delay(1000); 
}