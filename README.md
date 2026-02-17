# flora x midi

**setup**

- Install Arduino IDE
- Add adafruit libraries to "additional board manager urls" — `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json`
- Install board: `Adafruit ADR Boards`
- Install board: `Adafruit TeeOnArdu`
- Install library: [Bounce2](https://github.com/thomasfredericks/Bounce2)
- Modify **Adafruit TeeOnArdu**
  - edit `~/Library/Arduino15/packages/TeeOnArdu/hardware/avr/1.0.3/platform.txt`
  - change the value of `recipe.ar.pattern` ~ line 64
  - to `recipe.ar.pattern="{compiler.path}{compiler.ar.cmd}" {compiler.ar.flags} "{archive_file_path}" "{object_file}"`
- Set the board: `Flora (TeensyCore)`
- Set USB to Serial: `Tools > USB Type > Serial`
- Unplug & replug the device
- Set USB to MIDI: `Tools > USB Type > MIDI`
- Try to run the code…

**links**

- [Pinout](https://learn.adafruit.com/getting-started-with-flora/flora-pinout-diagram)
- [MIDI drum code](https://learn.adafruit.com/midi-drum-glove/code)
- [MIDI notes table](https://inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies)
- [MIDI control codes](https://midi.org/midi-1-0-control-change-messages)
- [TeeOnArdu source](https://github.com/adafruit/TeeOnArdu)
- [Flora examples](https://learn.adafruit.com/getting-started-with-flora/blink-onboard-led)
- [USB MIDI API](https://www.pjrc.com/teensy/td_midi.html)
- [core.a fix/modification](https://arduino.github.io/arduino-cli/1.4/platform-specification/#recipes-to-build-the-corea-archive-file)
- [TeeOnArdu PR](https://github.com/adafruit/TeeOnArdu/pull/3)
- [ATMEGA Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Summary.pdf)

**notes**

- On the device I tested there were issues using some of the pins, 
  there might be underlying collisions or issues with the board itself?
