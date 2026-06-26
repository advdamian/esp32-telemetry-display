#include <Arduino.h>
#include <TFT_eSPI.h>
#include <BluetoothSerial.h>
#include <ELMduino.h>

TFT_eSPI tft = TFT_eSPI();
BluetoothSerial SerialBT;
ELM327 myELM327;

const String obd_name = "OBDII"; 

void setup() {
  Serial.begin(115200);
  
  // 1. Initializare Ecran
  tft.init();
  tft.invertDisplay(false); 
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK); 
  tft.setTextColor(TFT_WHITE, TFT_BLACK); 
  
  tft.drawString("Sistem Telemetrie", 10, 10, 4);
  tft.drawString("Conectare la Mazda...", 10, 50, 4);
  
  // 2. Pornire Bluetooth cu parola hardcodata
  SerialBT.begin("ESP32_Mazda", true); 
  SerialBT.setPin("1234"); // Am setat PIN-ul castigator direct!
  
  // 3. Conectare la adaptor
  if (SerialBT.connect(obd_name)) {
    tft.fillRect(10, 50, 300, 30, TFT_BLACK);
    tft.drawString("BT Conectat! Init OBD...", 10, 50, 4);
    
    myELM327.begin(SerialBT, false, 2000);
    
    tft.fillScreen(TFT_BLACK);
    tft.drawString("OBD2 GATA", 10, 10, 4);
    tft.drawString("RPM:", 10, 60, 4);
  } else {
    // Daca esueaza, se opreste aici si scrie cu rosu
    tft.fillRect(10, 50, 300, 30, TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("Eroare Conectare BT!", 10, 50, 4);
    while(1); // Bucla infinita (blocheaza placa ca sa nu ruleze degeaba)
  }
}

void loop() {
  // Cerem turatia de la motor
  float tempRPM = myELM327.rpm();

  // Daca citirea a fost un succes absolut
  if (myELM327.nb_rx_state == ELM_SUCCESS) {
    int rpm = (uint32_t)tempRPM; // Convertim in numar intreg
    
    Serial.print("RPM Mazda: ");
    Serial.println(rpm);

    // Setam text verde pe fundal negru
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    
    // TRUC DE GRAFICA: Desenam un dreptunghi negru inainte, FIX peste numerele vechi.
    // Daca turatia scade de la 1000 la 900, fara dreptunghiul asta ar ramane ultimul zero de la 1000 pe ecran.
    tft.fillRect(80, 60, 100, 30, TFT_BLACK); 
    
    // Afisam noua turatie
    tft.drawNumber(rpm, 80, 60, 4); 
  } 
  else if (myELM327.nb_rx_state != ELM_GETTING_MSG) {
    // Printam eventualele erori de protocol in Serial Monitor ca sa le urmarim, dar nu blocam ecranul
    Serial.print("Asteptare / Eroare OBD: ");
    Serial.println(myELM327.nb_rx_state);
  }
}