#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini mp3Player;

void setup() {
  Serial.begin(115200);                       // ESP 32 Ausgabe zu PC
  Serial.println("Touch Piano");              // Begrüßung

  pinMode(22, OUTPUT);                        // grüne LED => Ausgang
  pinMode(23, OUTPUT);                        // rote LED => Ausgang

  digitalWrite(22, HIGH);                     // grüne LED an
  digitalWrite(23, HIGH);                     // rote LED an

  Serial1.begin(9600, SERIAL_8N1, 26, 25);    // DFPlayer Ausgabe zu PC, Pin 26 => mp3Player kommuniziert zu ESP32, Pin 25 => ESP32 kommuniziert zu mp3Player

  delay(1000);                                // MP3-Chip braucht etwas Zeit bis er kommunizieren kann

  bool mp3PlayerOk = mp3Player.begin(Serial1);//MP3 Player wird initialisiert

  if (mp3PlayerOk == false) {                 // Falls der MP3Player nicht initialisert werden kann, wird das im Seriellen Monitor ausgegeben und der restliche Code wird nicht mehr ausgeführt. Neustart erforderlich
    Serial.println("Konnte den MP3-Player nicht initalisieren");
    digitalWrite(22, LOW);                    //Grüne LED aus

    while(0 == 0) {                           //Endlosschleife
    }
  }

  Serial.println("Ready...");                 // Das eigentliche Programm geht los
}

void loop() {
                                              // 3 Sekunden abwechselnd blinken, um den Start zu markieren (15 * 200 ms = 3000 ms)
  for (int i = 0; i < 15; i++) {
    if (i % 2 == 0) {
      digitalWrite(22, HIGH);
      digitalWrite(23, LOW);
    } else {
      digitalWrite(22, LOW);
      digitalWrite(23, HIGH);
    }

    delay(200);
  }

  digitalWrite(22, LOW);                      // grüne LED aus
  digitalWrite(23, LOW);                      // rote LED aus

  Serial.println("Go!");                      // Start des Übungsmaterials
  Serial.println();

                                              // Spiele alle Töne für jeweils 1 Sekunde ab
  for (int ton = 0; ton < 6; ton++) {
    Serial.printf("Spiele Ton %d\n", ton);    // Gibt den jeweils gespielten Ton aus

    mp3Player.playFolder(1, ton + 1);
    delay(1000);

    mp3Player.stop();
    delay(300);
  }

                                              // 1 Sekunden abwechselnd blinken (5 * 200 ms = 1000 ms)
  for (int i = 0; i < 5; i++) {
    if (i % 2 == 0) {
      digitalWrite(22, HIGH);
      digitalWrite(23, LOW);
    } else {
      digitalWrite(22, LOW);
      digitalWrite(23, HIGH);
    }

    delay(200);
  }

  digitalWrite(22, LOW);                      // grüne LED aus
  digitalWrite(23, LOW);                      // rote LED aus

  for (int ton = 0; ton < 6; ton++) {
    int taste = -1;                           // -1 ist kein Array-Element => ist somit keine Taste, die gedrückt werden kann
    
                                              // Lese solange die Touch-Pins aus, bis eine Taste gedrückt wurde
                                              // Kann sein, dass im Seriallen Monitor angezeigt wird 
    while (taste == -1) {
      delay(100);

                                              // Lese alle Tasten in ein Array
                                              // auf der Tastatur von links nach rechts = C - D - E - F - G - A
      int touches[6] = {touchRead(13), touchRead(12), touchRead(14), touchRead(27), touchRead(33), touchRead(32)}; 
                                              
      int kleinsterTouch = 1000000;           // Dieser Wert ist größer als alle mgölichen Touch-Werte, damit sichergestellt wird, dass auf jedenfall der Touch Point niedriger ist

                                              // Finde den kleinsten Wert = Touch Point. Werte die größer/gleich 20 sind, werden als nicht gedrückt ignoriert
      for (int i = 0; i < 6; i++) {
        Serial.printf("Taste %d: %d\n", i, touches[i]);

        if (touches[i] < kleinsterTouch && touches[i] < 20) {
          taste = i;
          kleinsterTouch = touches[i];
        }
      }
                                              // Gibt aus welche Taste gedrückt ist
      Serial.printf("Gedrückte Taste: %d\n", taste);
      Serial.println();
    }

                                              // SpielT den Sound der gedrückten Taste ab
    mp3Player.playFolder(1, taste + 1);

                                             // Ist die gedrückte Taste gleich dem Ton, der gerade abgespielt wurde? => LED rot oder grün
    if (taste == ton) {
      Serial.println("Richtig");
      digitalWrite(22, HIGH);
    } else {
      Serial.println("Falsch");
      digitalWrite(23, HIGH);
    }

                                              // Nutzer:in hat 1 Sekunde Zeit, um die LEDs anzusehen und zu entscheiden, welche Taste als nächstes gedrückt wird
    delay(1000);

    mp3Player.stop();                         // Ton wird gestoppt
    delay(300);                               // kurze Pause

                                              // LEDs werden wieder ausgemacht und die nächste Runde wird gestartet. (Beispiel-Töne werden wieder abgespielt)
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  }

  digitalWrite(22, HIGH);                      // grüne LED an
  digitalWrite(23, HIGH);                      // rote LED aus
  delay(5000);                                 // warten vor dem Neustart

  Serial.println();
  Serial.println("Neustart");                  // Damit im Seriellen Monitor klar ist das der Neustart gestartet wurde
}
