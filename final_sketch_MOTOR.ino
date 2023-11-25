#include <Servo.h>
Servo myservo; // creating a servo object

int photoPin = A0; // Pin for the photosensitive resistor 1
int photoPin2 = A1;
int pos = 0; // stores the position of the servo motor


const int RED_PIN = 3;
const int YELLOW_PIN = 5;  // All these are PWM pins for nano arduino
const int GREEN_PIN = 11;

const int DELAY = 30000; // The delay in miliseconds


void setup(){
    pinMode( RED_PIN, OUTPUT );
    pinMode( YELLOW_PIN, OUTPUT );
    pinMode( GREEN_PIN, OUTPUT );

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);  // The default setting is off for all of the lights
    digitalWrite(YELLOW_PIN, LOW);

    myservo.attach(9); // attaching the servo motor to the respective pin
    Serial.begin(9600);

}

void loop(){
    int lightRaw = analogRead(photoPin); // This line reads the photosensitiity values, which are between 0 and 600 ish
    int light = map(lightRaw, 1023, 0, 10, 0); // Converting the light values to values between 0 and 10

    int lightRaw2 = analogRead(photoPin2); // Readint the photosensitivity values for photoresistor 2
    int light2 = map(lightRaw2, 1023, 0, 10, 0); // normalizing the values in between 0 and 10

    Serial.print(light); // Light value for photoresistor in A0
    Serial.print(", ");
    Serial.println(light2); // tHIS LINE keeps printing the light values for our reference (light, light2)



      // Analogwrite in combination with PWM pins can result in dimmer lights
    
    // NIGHT AND TRAIN (DIM)
    if (light<=5 && light2 <= 2) {
      analogWrite(GREEN_PIN, 0);// Green lights off 
      analogWrite(YELLOW_PIN, 30);// Dimmed yellow light on 
      delay(1000); //delay for 1 second 
      analogWrite(YELLOW_PIN, 0);// YELLOW light off (0)
      analogWrite(RED_PIN, 30);// Dimmed red light on 

      // As ther is a train, we are going to lower the barrier 
      for (pos = 0; pos <=100; pos+=1) {
        myservo.write(pos); // moving it by 1 degree every iteration
        delay(15);
      }

      delay(DELAY);// delay for 30 second intervals? or no delay?

      analogWrite(RED_PIN, 0);// Red lights off  and then the barrier up  

      for (pos = 100; pos >=0; pos-=1) {
        myservo.write(pos);
        delay(15);
      }

    }  

    // NIGHT AND NO TRAIN (DIM) 
    else if (light <=5 && light2 >= 2) {
      analogWrite(GREEN_PIN, 120);// Dimmed Green lights on, as green light is already on 
    } 

    // DAY AND TRAIN (BRIGHT)
    else if (light >= 5 && light2 <=2) {
      analogWrite(GREEN_PIN, 0);// Green lights off 
      analogWrite(YELLOW_PIN, 255);// Bright yellow on
      delay(1000);// delay for 1 second (delay(1000)) 
      analogWrite(YELLOW_PIN, 0);// Bright yellow off
      analogWrite(RED_PIN, 255);// Bright red on, use analog.Write and set bright red to on
      delay(DELAY);// Delay for 30 seconds intervals? or no delay? 
      analogWrite(RED_PIN, 0);// Red lights off 
    } 

    // DAY AND NO TRAIN (BRIGHT)
    else if (light>=5 && light2 >= 5) {
      analogWrite(GREEN_PIN, 255); // Bright green on 
    } 
}