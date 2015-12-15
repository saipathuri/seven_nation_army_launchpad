// define your pitch constants
// these will be notes that can be used to make a song

#define NOTE_C2  65
#define NOTE_G2  98
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_G5  784


#define SYNCIN  P1_4 //This has analog_read
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

int melody[] = {-1, -1, -1, -1, -1, -1, -1, -1, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_E5, -1, -1, -1, NOTE_D5, NOTE_E5, 
  NOTE_D5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_E5};
   

double noteDurations[] = {.2, .2, .2, .2, .2, .2, 1, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4,
  1, 2, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 2.4, 2.4, 2.4};
  
int repetitions = 0;
/* In the setup function we will set our buzzer pin to 
 * output. That's all we need to do at setup. 
 */
void setup() 
{
  pinMode(buzzerPin, OUTPUT); // set buzzerPin to OUTPUT
  pinMode(SYNCIN, INPUT);
  pinMode(RLED1, OUTPUT);
  pinMode(RLED2, OUTPUT);
  pinMode(YLED1, OUTPUT);
  pinMode(YLED2, OUTPUT);
  pinMode(GLED1, OUTPUT);
  pinMode(GLED2, OUTPUT);
  Serial.begin(9600);
}

void lightLED(int note, double length){
  if(note == NOTE_E5){
    //light a red led
    digitalWrite(RLED1, HIGH);
    digitalWrite(RLED2, HIGH);
    delay(length);
    digitalWrite(RLED1, LOW);
    digitalWrite(RLED2, LOW);
  }
  else if(note == NOTE_D5){
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
  if(repetitions == 0){  
    for (int thisNote = 0; thisNote < 29; thisNote++) {
  
      // to calculate the note duration, take one second divided by the 
      // note type. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      double noteDuration = 400/noteDurations[thisNote];
      unsigned long duration = (long) noteDuration;
     
      
      if(melody[thisNote] != -1){
        tone(buzzerPin, melody[thisNote], duration);
        lightLED(melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration + 150; // delay between pulse
        delay(pauseBetweenNotes);
        noTone(buzzerPin); // stop the tone playing
      }
      else if(melody[thisNote] == -1){
        delay(noteDuration);
      }  
     repetitions++;
    }
  }
}
