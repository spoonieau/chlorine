#include <Arduino.h>

/* 
C15 PWM Throttle driver
Built for MCW1-UP Engine
Frequency need to be between 150Hz and 1000Hz
Duty cycle needs to be no less than 10% and no greater than 90% otherwise DTC
Written by Rick Spooner  
*/

//Pin setup
int led_pin = 6;
int throttle_pin = 5; 
int pot_pin = A4;

//Vars 
int output_pwm;
int led_value;
int  throttle_value;
int duty_cycle;

void setup() 
{
  //Frequency 976.56Hz
  //TCCR0B = TCCR0B & B11111000 | B00000011;


  //Frequency 244.14Hz
  //TCCR0B = TCCR0B & B11111000 | B00000100;

  Serial.begin(9600);

  //Set D6 LED and D5 PWM 
  pinMode(led_pin, OUTPUT);
  pinMode(throttle_pin, OUTPUT);
}

void loop() 
{
  //Get 10K pot
  output_pwm = analogRead(pot_pin);

  // 255 - 90% = 25.5 lower map value
  // 255 - 10% = 229.5 upper map value
  //Map needed values
  led_value = map(output_pwm, 0, 1023, 26, 229); 
  throttle_value = map(output_pwm, 0, 1023, 26, 229);
  duty_cycle = map(output_pwm, 0 ,1023, 0, 100);

  //Write outputs to D5 and D6
  analogWrite(led_pin, led_value);
  analogWrite(throttle_pin, throttle_value);
  
  Serial.println("Duty Cycle " + String(duty_cycle) + "%");
  delay(1);
}
