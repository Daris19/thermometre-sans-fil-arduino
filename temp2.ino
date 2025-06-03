#include <Wire.h>                     // Communication I2C (écran OLED, capteur)
#include "SHTSensor.h"               // Capteur de température et humidité SHTC3
#include <FastLED.h>                 // Contrôle de la bande LED WS2811
#include <Adafruit_GFX.h>           // Bibliothèque graphique (texte, dessin)
#include <Adafruit_SSD1306.h>       // Bibliothèque pour écran OLED SSD1306

// === Paramètres pour la bande LED ===
#define LED_PIN     4               // Broche de données connectée à la bande LED
#define NUM_LEDS    21              // Nombre de LEDs WS2811
#define BRIGHTNESS  64              // Luminosité globale (0 à 255)
#define LED_TYPE    WS2811          // Type de LED
#define COLOR_ORDER GRB             // Ordre des couleurs dans chaque LED
CRGB leds[NUM_LEDS];                // Tableau contenant l'état de chaque LED

// === Paramètres pour l'écran OLED ===
#define SCREEN_WIDTH 128            // Largeur de l'écran en pixels
#define SCREEN_HEIGHT 64            // Hauteur de l'écran en pixels
#define OLED_RESET    -1            // Pas de broche RESET utilisée
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === Divers ===
#define UPDATES_PER_SECOND 100      // Vitesse de mise à jour des LEDs
SHTSensor sht;                      // Objet pour le capteur SHTC3

void setup() {
  Serial.begin(115200);             // Démarrage de la communication série
  Wire.begin();                     // Initialisation du bus I2C

  // === Initialisation de l'écran OLED ===
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Écran OLED non détecté"));
    while (1);                      // Bloque le programme si aucun écran n'est trouvé
  }
  display.clearDisplay();           // Efface l'écran
  display.setTextSize(1);           // Taille du texte
  display.setTextColor(SSD1306_WHITE); // Couleur du texte (blanc)
  display.setCursor(0, 0);
  display.println("Initialisation...");
  display.display();                // Affiche le message

  // === Initialisation des LEDs ===
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
         .setCorrection(TypicalLEDStrip); // Correction de couleur standard
  FastLED.setBrightness(BRIGHTNESS);      // Réglage de la luminosité

  // === Initialisation du capteur SHTC3 ===
  sht.init();                           // Démarrage du capteur
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // Précision moyenne
}

void loop() {
  // === Lecture de température et humidité ===
  sht.readSample();                      // Demande une nouvelle mesure
  float temp = sht.getTemperature();     // Récupère la température en °C
  float hum  = sht.getHumidity();        // Récupère l’humidité en %

  // === Affichage des données sur le port série (debug) ===
  Serial.print(F("[SHTC3] T:"));
  Serial.print(temp);
  Serial.print(F(" Cº  /   H: "));
  Serial.print(hum);
  Serial.println(F(" %"));

  // === Conversion en largeur de barres pour l'affichage graphique ===
  int tempBarWidth = map(temp, 20, 35, 0, SCREEN_WIDTH); // 20–35°C → 0–128 px
  int humBarWidth  = map(hum, 0, 100, 0, SCREEN_WIDTH);  // 0–100% → 0–128 px

  // === Affichage OLED graphique + texte ===
  display.clearDisplay();                  // Efface l'écran
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp, 1);
  display.println(" C");
  display.drawRect(0, 12, SCREEN_WIDTH, 8, SSD1306_WHITE);      // Cadre température
  display.fillRect(0, 12, tempBarWidth, 8, SSD1306_WHITE);      // Remplissage

  display.setCursor(0, 24);
  display.print("Hum:  ");
  display.print(hum, 1);
  display.println(" %");
  display.drawRect(0, 36, SCREEN_WIDTH, 8, SSD1306_WHITE);      // Cadre humidité
  display.fillRect(0, 36, humBarWidth, 8, SSD1306_WHITE);       // Remplissage

  display.display();                        // Met à jour l’écran

  // === Couleurs LED selon température (3 zones) ===
  // Répartition : 0–6 (rouge), 7–13 (vert), 14–20 (bleu) 🧠 Idée générale : Définir des plages de température, par exemple : 
  //🟦 < 22°C → BLEU (froid) 
 // 🟩 22 à 27°C → VERT (température normale)//
//🟥 > 27°C → ROUGE (chaleur)//

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < 7) {
      leds[i] = CRGB::Red;
    } else if (i < 14) {
      leds[i] = CRGB::Green;
    } else {
      leds[i] = CRGB::Blue;
    }
  }

  FastLED.show();                            // Met à jour les LEDs
  FastLED.delay(1000 / UPDATES_PER_SECOND);  // Attente pour éviter scintillement

  delay(2000); // Pause de 2 secondes avant la prochaine mesure
}
