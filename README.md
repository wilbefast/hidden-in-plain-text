Hidden In Plain Text
====================

A few days before leaving for Exile game jam my 6 year old laptop [started playing up](https://vine.co/v/MnQi7aB0wBd "A Vine clip").

By the time I'd arrived it [had pretty much had it](https://vine.co/v/MrmgraKLm9h "Another Vine clip").

Basically whenever I started X Server (graphical mode) the computer would freeze with pretty patterns on screen. However I realised that if I stayed in text mode the OS would just shrug off these glitches and continue to work: I just needed to lean on 'Return' til the screen cleared. 
Thus [Hidden In Plain Text](https://vine.co/v/MrDmttA6J00 "Yet another Vine clip") was born, written in C using [nano](http://www.nano-editor.org/ "Nano editor website") and the [libcaca](http://caca.zoy.org/wiki/libcaca "Libcaca website") ASCII rendering library.

I implemented various things that weren't really used in the end, such as:
* Perlin Noise
* HSL to RGB conversion
* A 2-Player synchronous game

The latter was scrapped because I couldn't seem to get enough simultaneous key-press events out of the library to make it work. The command-line can only do so much...

Long story short I *really* enjoyed myself, and I got to be on of only two people I think not using Unity 3D, which makes me feel terribly smug and superior :P
