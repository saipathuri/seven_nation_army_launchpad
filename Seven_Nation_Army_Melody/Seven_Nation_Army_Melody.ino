// define your pitch constants
// these will be notes that can be used to make a song
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_D2  73
#define NOTE_E2  82
#define NOTE_G2  98

#define SYNC_OUT_M2     P1_6 //This has analog_write
#define RLED1 P1_0
#define RLED2 P1_3
#define YLED1 P1_5
#define YLED2 P2_0
#define GLED1 P2_1
#define GLED2 P2_2
// Connect longer leg of buzzer to pin 19 and shorter leg to GND
// on the breadboard. The buzzer will work for any GPIO pin.
// You can switch to other pins later.
int buzzerPin = 19; 

// Next we will set up an Array to store our notes in the melody
// An array is way to store data in a comma seperated structure.
// notes in the birthday melody:
int melody[] = {
  NOTE_E2, NOTE_E2, NOTE_G2,
  NOTE_E2, NOTE_D2, NOTE_C2, NOTE_B1};
   
// note durations: 4 = quarter note, 8 = eighth note, etc.:
double noteDurations[] = {
  1.5, 4, 3.4, 3.4, 3.4, 1, 1};

//the number of times the riff has been played
int repetitions = 1; 

/* In the setup function we will set our buzzer pin to 
 * output. That's all we need to do at setup. 
 */
void setup() 
{
  pinMode(buzzerPin, OUTPUT); // set buzzerPin to OUTPUT
  pinMode(SYNC_OUT_M2, OUTPUT);
  pinMode(RLED1, OUTPUT);
  pinMode(RLED2, OUTPUT);
  pinMode(YLED1, OUTPUT);
  pinMode(YLED2, OUTPUT);
  pinMode(GLED1, OUTPUT);
  pinMode(GLED2, OUTPUT);
  
  Serial.begin(9600);
}

void lightLED(int note, double length){
  if(note == NOTE_E2){
    //light a red led
    digitalWrite(RLED1, HIGH);
    digitalWrite(RLED2, HIGH);
    delay(length);
    digitalWrite(RLED1, LOW);
    digitalWrite(RLED2, LOW);
  }
  else if(note == NOTE_D2){
    //light yellow led
    digitalWrite(YLED1, HIGH);
    digitalWrite(YLED2, HIGH);
    delay(length);
    digitalWrite(YLED1, LOW);
    digitalWrite(YLED2, LOW);
  }
  else if(note == NOTE_G2){
    //light green LED
    digitalWrite(GLED1, HIGH);
    digitalWrite(GLED2, HIGH);
    delay(length);
    digitalWrite(GLED1, LOW);
    digitalWrite(GLED2, LOW);
  }
  else if(note == NOTE_C2){
    //light a certain LED
    digitalWrite(YLED1, HIGH);
    digitalWrite(YLED2, HIGH);
    digitalWrite(GLED1, HIGH);
    digitalWrite(RLED2, HIGH);
    delay(length);
    digitalWrite(YLED1, LOW);
    digitalWrite(YLED2, LOW);
    digitalWrite(GLED1, LOW);
    digitalWrite(RLED2, LOW);
  }
  else{
    //light B1 led
    digitalWrite(RLED1, HIGH);
    digitalWrite(RLED2, HIGH);
    digitalWrite(GLED1, HIGH);
    digitalWrite(GLED2, HIGH);
    digitalWrite(YLED1, HIGH);
    digitalWrite(YLED2, HIGH);
    delay(length);
    digitalWrite(YLED1, LOW);
    digitalWrite(YLED2, LOW);
    digitalWrite(RLED1, LOW);
    digitalWrite(RLED2, LOW);
    digitalWrite(GLED1, LOW);
    digitalWrite(GLED2, LOW);
  }
}

/* In the loop section we will use the tone function to 
 * enable enable the sound. Tone needs arguments for the 
 * pin of the buzzer, the note, and the note duration.
 */
void loop() 
{

  analogWrite(SYNC_OUT_M2, 255);  //Sends signal to start to M2 Launchpad
  if(repetitions > 6){
    digitalWrite(SYNC_OUT_VOCALS, 0);
  }
  Serial.print(repetitions);
  Serial.print("\n");
  if(repetitions != 7){
    for (int thisNote = 0; thisNote < 7; thisNote++) {
  
      // to calculate the note duration, take one second divided by the 
      // note type. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      double noteDuration = 400/noteDurations[thisNote];
      unsigned long duration = (long) noteDuration;
      tone(buzzerPin, melody[thisNote], duration);
      lightLED(melody[thisNote], noteDuration);
  
      int pauseBetweenNotes = noteDuration + 150; // delay between pulse
      delay(pauseBetweenNotes);
      
      noTone(buzzerPin); // stop the tone playing
    } 
    repetitions++;
  }
}
