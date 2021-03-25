#include "Ucglib.h"  // Include Ucglib library to drive the display
#include <Wire.h>
#include "SparkFunBME280.h"

#include <SoftwareSerial.h>


SoftwareSerial softSerial(2, 3); // RX, TX
String SSID = "palu";  // SSID du réseau Wi-Fi
String PASS = "+menfouu"; // Mot de passe Wi-Fi

BME280 mySensor; // Capteur


// Create display and define the pins:
Ucglib_ST7735_18x128x160_HWSPI ucg(8, 10, 9);  // (A0=8, CS=10, RESET=9)
// The rest of the pins are pre-selected as the default hardware SPI for Arduino Uno (SCK=13 and SDA=11)


int Variable1;  // Create a variable to have something dynamic to show on the display


void setup(void)  // Start of setup
{
  softSerial.begin(115200);
  
  Serial.begin(9600); // demarrage du port série a 9600 bauds
  mySensor.setI2CAddress(0x76);
  Wire.begin(); //connexion bus I2c en tant que maître ou esclave
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
  
    // Display setup:

    // Select a type of text background:
    //ucg.begin(UCG_FONT_MODE_TRANSPARENT);  // It doesn't overwrite background, so it's a mess for text that changes
    ucg.begin(UCG_FONT_MODE_SOLID);  // It writes a background for the text. This is the recommended option

    ucg.clearScreen();  // Clear the screen

    // Set display orientation:
    ucg.setRotate180();  // Put 90, 180 or 270, or comment to leave default

    // Set text orientation:
    // It only alters the text, not the entire display
    //ucg.setPrintDir(0);  // 0, 1, 2 or 3 to change orientation of text. If not specify, orientation is 0




    ucg.setFont(ucg_font_7x14B_tf);





    // We are going to print on the display everything that is static on the setup, to leave the loop free for dynamic elements:


    // Write to the display the text "World":
    ucg.setColor(0, 0, 0, 255);  // Set color (0,R,G,B)
    ucg.setPrintPos(10,15);  // Set position (x,y)
    ucg.print("Altitude :");  // Print text or value

    ucg.setColor(0, 255, 255, 255);  // Set color (0,R,G,B)
    ucg.setPrintPos(10,65);  // Set position (x,y)
    ucg.print("Temperature :");  // Print text or value

    ucg.setColor(0, 255, 0, 0);  // Set color (0,R,G,B)
    ucg.setPrintPos(10,115);  // Set position (x,y)
    ucg.print("Pression :");  // Print text or value


    // Draw rectangle:
    ucg.setColor(255, 255, 255);  // Set color (0,R,G,B)
    ucg.drawFrame(20, 20, 100, 30);  // Start from top-left pixel (x,y,wigth,height)

    // Draw rectangle:
    ucg.setColor(255, 255, 255);  // Set color (0,R,G,B)
    ucg.drawFrame(20, 70, 100, 30);  // Start from top-left pixel (x,y,wigth,height)

    // Draw rectangle:
    ucg.setColor(255, 255, 255);  // Set color (0,R,G,B)
    ucg.drawFrame(20, 120, 100, 30);  // Start from top-left pixel (x,y,wigth,height)




  startconnexion();
}  // End of setup





void loop(void)  // Start of loop
{

    String url_altitude = String(mySensor.readFloatAltitudeMeters()); // conversion en string
    String url_pression = String(mySensor.readFloatPressure()/100);
    String url_temperature = String(mySensor.readTempC());

    String url = "?temp="+url_temperature+"&press="+url_pression+"&alt="+url_altitude; // prépare les valeur qui vont etre envoyé par l'URL


    sendValueUrl(url); // appel de la fonction avec en attribut l'url préparée


    setvalue();


}  // End of loop

void startconnexion() {
  //IP de votre serveur web a changer selon votre réseau";
  String host = "192.168.104.172";
  delay(100);
  // on va se connecter à un réseau existant, donc on passe en mode station
  softSerial.println("AT+CWMODE=1");
  receiveValue(1000);
  delay(1000);
  // on se connecte au réseau
  softSerial.println("AT+CWJAP=\""+SSID+"\",\""+PASS+"\"");
  receiveValue(1000);
  delay(10000);
  // mode "connexions multiples"
  softSerial.println("AT+CIPMUX=1");
  receiveValue(1000);
  
  delay(3000);
  // on se connecte à notre serveur en TCP sur le port 80
  softSerial.println("AT+CIPSTART=4,\"TCP\",\""+host+"\",80");
  delay(1000);

 
}
void sendValueUrl(String value) {
  //IP de votre serveur web a changer selon votre réseau";
  String host = "192.168.104.172";
  delay(100);

  String request = "GET /meteo/main.php"+value+" HTTP/1.0\r\n";

  // chemin de et nom du fichier qui recevra les données
  
  request       += "Host:"+host+"\r\n";
  // on donne la taille de la requête qu'on va envoyer, en ajoutant 2 car
  // println ajouter 2 caractères à la fin "\r" et "\n"
  softSerial.println("AT+CIPSEND=4,"+String(request.length()+2));
  delay(500);
  // on envoie la requete
  softSerial.println(request);
  delay(3000);

  // on ferme la connexion
  softSerial.println("AT+CIPCLOSE=4");
 
}

void receiveValue(const int timeout)
{
    String reponse = "";
    long int time = millis();
    while( (time+timeout) > millis())
    {
        while(softSerial.available())
        {
            char c = softSerial.read();
            reponse+=c;
        }
    }
    Serial.print(reponse);
}

void setvalue() {


    // We are going to print on the display everything that is dynamic on the loop, to refresh continuously:

    // Write to the display the Variable1 with left text alignment:
    ucg.setFont(ucg_font_logisoso18_tf);  // Set font
    ucg.setColor(0, 0, 0, 255);  // Set color (0,R,G,B)
    ucg.setColor(1, 0, 0, 0);  // Set color of text background (1,R,G,B)
    ucg.setPrintPos(35,45);  // Set position (x,y)
    ucg.print(mySensor.readFloatAltitudeMeters());  // Print text or value

    // Write to the display the string with right text alignment:
    ucg.setFont(ucg_font_logisoso18_tf);  // Set font
    ucg.setColor(0, 255, 255, 255);  // Set color (0,R,G,B)
    ucg.setColor(1, 0, 0, 0);  // Set color of text background (1,R,G,B)
    ucg.setPrintPos(45,95);  // Set position (x,y)
   // ucg.print(string);  // Print text or value
    ucg.print(mySensor.readTempC());

    ucg.setFont(ucg_font_logisoso18_tf);  // Set font
    ucg.setColor(0, 255, 0, 0);  // Set color (0,R,G,B)
    ucg.setColor(1, 0, 0, 0);  // Set color of text background (1,R,G,B)
    ucg.setPrintPos(35,145);  // Set position (x,y)
   // ucg.print(string);  // Print text or value
    ucg.print(mySensor.readFloatPressure()/100);
}
