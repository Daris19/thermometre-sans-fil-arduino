# thermometre-sans-fil-arduino
Projet de thermomètre sans fil utilisant Arduino, capteur de température, module UCA Education Board et affichage sur écran Oled et effet sonore  avec essaie d'envoie sur smartphone via wifi ou Bluetooth.
Ce projet a été conçu dans le cadre de notre cours de Communication sans fil du terrestre au spatial, et son but principal est de mesurer la température et l’humidité ambiantes, puis de les afficher de manière claire et intuitive à la fois sur un petit écran OLED et via une bande de LED colorées.
Ce type de dispositif peut être utilisé dans une serre, une chambre d'enfant, ou un atelier, pour alerter visuellement en cas de température anormale.


Matériel utilisé
Pour réaliser ce projet, j’ai utilisé :
Une carte UCA Education Board compatible Arduino (ou une carte Arduino Uno),
Un écran OLED SSD1306 de 128×64 pixels,
Et, pour l’alimentation et la programmation, un câble USB relié à un ordinateur.


Fonctionnement général
Une fois le système allumé :
Le capteur mesure la température et l'humidité toutes les deux secondes.
Ces données sont :
Affichées sur l’écran OLED sous forme de texte et de barres graphiques,
Et envoyées vers une bande LED qui change de couleur en fonction de la température.
Le but est de permettre une lecture rapide des conditions ambiantes, même de loin, grâce aux couleurs.


Interprétation des couleurs sur la bande LED
Voici comment la couleur des LED change selon la température :
Si la température est inférieure à 22°C, toutes les LEDs deviennent bleues : cela indique qu’il fait froid.
Si la température est entre 22 et 27°C, elles passent au vert, ce qui est une plage normale.
Au-dessus de 27°C, les LEDs deviennent rouges pour signaler un excès de chaleur.
C’est une façon simple de rendre l’information visuelle sans avoir besoin de lire précisément les chiffres.

Partie logicielle – Programme Arduino
Le programme est avec l’environnement Arduino IDE.
FastLED.h pour gérer la bande LED.
Le code lit les mesures, les affiche, puis les transforme en barres horizontales sur l’écran OLED et couleurs dynamiques sur les LEDs.

Situation concrète d’utilisation
Imaginons une serre de jardin :
La température ne doit pas dépasser 30°C, sinon les plantes risquent de souffrir.
Grâce à ce thermomètre, le jardinier peut jeter un coup d'œil rapide :
S’il voit les LEDs en vert, tout va bien.  S’il voit du rouge, il doit aérer la serre.
Ce type de système peut aussi être utilisé dans une chambre d’enfant, un laboratoire, ou un atelier de fabrication.

Conclusion
Ce projet m’a permis de mettre en œuvre plusieurs compétences :
Lecture de capteurs,
Communication I2C,
Affichage graphique,
Pilotage d’un système lumineux,
Et tructuration d’un programme Arduino.
