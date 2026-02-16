/* merged different examples for Teensy by Paul Stoffregen
   to test MIDI IN & OUT
   
   This example code is in the public domain.
*/
#include <Bounce2.h>

const int channel = 1;
const int led = 7;

elapsedMillis msec = 0;

// Send a MIDI control signal based on an analog PIN, but not too often
class Stretchy {
private:
  uint8_t note;
  uint8_t pin;
  unsigned long interval;
  Bounce button;

  int previous = -1;

public:
  Stretchy(uint8_t note, uint8_t pin, unsigned long interval = 50) : note(note), pin(pin), interval(interval) {};

  void setup() {
    pinMode(this->pin, INPUT_PULLUP);
  }

  void update(elapsedMillis msec) {
    // only check the analog inputs 50 times per second,
    // to prevent a flood of MIDI messages
    if (msec < this->interval) return;

    msec = 0;
    int newValue = analogRead(this->pin) / 8;
    
    // only transmit MIDI messages if analog input changed
    if (newValue != this->previous) {
      usbMIDI.sendControlChange(this->note, newValue, channel);
      this->previous = newValue;
    }
  }
};

// Trigger a MIDI note press/release based on a PIN
class Trigger {
private:
  uint8_t note;
  uint8_t pin;
  unsigned long interval;
  uint8_t velocity;
  Bounce button;

public:
  Trigger(uint8_t note, uint8_t pin, uint8_t velocity = 70, unsigned long interval = 5)
    : note(note), pin(pin), velocity(velocity), button(pin, interval) {};

  void setup() {
    pinMode(this->pin, INPUT_PULLUP);
  }

  void update() {
    this->button.update();

    if (this->button.fallingEdge()) {
      digitalWrite(led, HIGH);
      usbMIDI.sendNoteOn(this->note, this->velocity, channel);
    }
    if (this->button.risingEdge()) {
      digitalWrite(led, LOW);
      usbMIDI.sendNoteOff(this->note, 0, channel);
    }
  }
};

// https://learn.adafruit.com/getting-started-with-flora/flora-pinout-diagram

// https://midi.org/midi-1-0-control-change-messages
Stretchy pan(10, A10);

// https://inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
Trigger c4(60, A1);
Trigger d4(62, A0);
Trigger e4(64, SDA);
Trigger f4(65, SCL);
Trigger g4(67, A10);
Trigger a5(48, A11);
Trigger b5(48, A7);
Trigger c5(48, A9);

void setup() {
  pan.setup();

  c4.setup();
  d4.setup();
  e4.setup();
  f4.setup();
  g4.setup();
  a5.setup();
  b5.setup();
  c5.setup();

  pinMode(led, OUTPUT);

  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
}

void loop() {
  pan.update(msec);
  
  c4.update();
  d4.update();
  e4.update();
  f4.update();
  g4.update();
  a5.update();
  b5.update();
  c5.update();

  while(usbMIDI.read()); // Discard incoming MIDI messages
}
