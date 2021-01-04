## Workshop — IoT (Organic Electronics)

> Physical Computing with Drawn, Organic Electronics
In this exercise block we are going to investigate new approaches of interaction design with smart paper to create interactive posters, books, cards, wallpapers, packagings, …
The tool shelf I send to you is pretty simple: a pencil, some wires and (the brain) an ESP32. Furthermore you need and USB Micro cabel and paper (and of course additional material, such as wires if you want to create an interactive system based on more then just one input sensor).


My little sister is learning to play the piano and usually has lessons to get better at it. Due to Corona, her exercises are very sporadic right now and soon may not be. So I thought a mini piano could be set up in a convenient place in the house so she can stay in practice.

**Concept Idea:** After activating, a specified part piece of music, which is to be practiced, is played through a speaker. Then a tone is sounded to indicate that it is the player's turn. During the exercise, red and green LEDs light up to show whether everything has been done correctly. The individual keys of the piano can be touched and are linked to the GPIOs by using wires. 

* * *


**first setup** 
<p>
  <a href="/assets/iot/connectedPiano.png" title="piano Setting">
    <img src="/assets/iot/connectedPiano.png" alt="piano Setting" />
  </a>
</p>

Ich habe mir, um das Piano mal zu testen, mit dem Bleistift einfache Tasten aufgemalt. Im ersten Schritt habe ich eine davon mit der Krokodielsklemme verbunden und einen Test Sketch geschrieben. 

<p>
  <a href="/assets/iot/ersterVersuchCode.png" title="ersterVersuchCode">
    <img src="/assets/iot/ersterVersuchCode.png" alt="ersterVersuchCode" />
  </a>
</p>

Nachdem das funktioniert hat hab ich weitere Krokodil

* * *

**test setup of "touchPiano**

Material:
⋅⋅* ESP 32
⋅⋅* [*DFPlayer Mini MP3 Player*](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#target_3)
⋅⋅* some jumper wires
⋅⋅* some alligator clips
⋅⋅* red led
⋅⋅* green led
⋅⋅* 2* 1 Ω resistor

<p>
  <a href="/assets/iot/schaltplan.png" title="Circuit diagram">
    <img src="/assets/iot/schaltplan.png" alt="Circuit diagram" />
  </a>
</p>

Here you can see the first structure "touchPiano". Created with Fritzing.
Assigned pins: 
IO 32       Button 1 / Taste 1
IO 33       Button 2 / Taste 2
IO 27       Button 3 / Taste 3
IO 14       Button 4 / Taste 4
IO 12       Button 5 / Taste 5
IO 13       Button 6 / Taste 6

IO 25       Communication to DFPlayer Mini
IO 26       Communication from DFPlayer Mini

D2          led    
D3          led

During the test setup for my "touchPiano" I noticed that the DFPlayer  is not working properly. In this case, this means that the manufacturer soldered on one spot too many. It took some time to identify the problem. I then ordered a new DFPlayer, which arrived a little later.
 
 <p>
   <a href="/assets/iot/DFPlayer.png" title="DFPlayer">
     <img src="/assets/iot/DFPlayer.png" alt="DFPlayer" />
   </a>
 </p>

With the new DFPlayer, the set-up works.


* * *


This is my final code for my piano idea.

<p>
  <a href="/assets/iot/FinalCode.png" title="final code">
    <img src="/assets/iot/FinalCode.png" alt="final code" />
  </a>
</p>

