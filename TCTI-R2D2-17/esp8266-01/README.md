## Team 4 Overdracht

Voor deze overdracht module maken wij gebruik van de ESP8266

De pinout van de ESP8266 is als volgt:
![ESP](ESP8266_01_PinOut.png)

Om hem aan te sluiten aan de arduino wil je het volgende doen
- RX pin van de ESP op de TX pin van de Arduino
- TX pin van de ESP op de RX pin van de Arduino
- GND aan GND
- VCC aan 3.3V
- CH_PD aan 3.3V

Zorg ervoor dat je de laatste versie hebt van bmptk in verband met de interrupts patch. Of download de [cortex.zip](https://cdn.discordapp.com/attachments/805737161335767070/827161871672410162/cortex.zip) patch en overschrijf de bestanden in bmptk/targets/cortex met de bestanden uit het cortex.zip bestand.
