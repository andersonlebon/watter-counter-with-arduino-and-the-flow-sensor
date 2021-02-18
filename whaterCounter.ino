  /*
  YF‐ S201 Water Flow Sensor
  Water Flow Sensor output processed to read in litres/hour
  Adaptation Courtesy: hobbytronics.co.uk
  */
  volatile int flow_frequency; // Measures flow sensor pulses
  // Calculated litres/hour
  int pontetionmeter = A0;
  int price;
  int ledPin = 9;
  float vol = 0.0,l_minute;
  unsigned char flowsensor = 3; // Sensor Input
  unsigned long currentTime;
  unsigned long cloopTime;
  #include <LiquidCrystal.h>
  LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
  void flow () // Interrupt function
{
   flow_frequency++;
}
void setup()
{   
   analogRead(pontetionmeter);
   pinMode(ledPin, OUTPUT);
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   lcd.begin(16, 2);
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Water Flow Meter");
   delay(500);
   lcd.setCursor(0,1);
   lcd.print("By Janvier");
   delay(500);
   currentTime = millis();
   cloopTime = currentTime;
}
void loop (){
   
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000)){
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print(l_minute);
      lcd.print(" L/M");
      l_minute = l_minute/60;
      lcd.setCursor(0,1);
      vol = vol +l_minute;
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print(" Mc");
      lcd.print(" P:");
      price = vol*0.7;
      lcd.print(price);
      lcd.print("$");        
      flow_frequency = 0; // Reset Counter
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");
    }
    else {
      Serial.println(" flow rate = 0 ");
      lcd.clear();
      if (price >=10){
          digitalWrite(ledPin, HIGH);          
          if(analogRead(pontetionmeter) >= 1000){
            vol = 0;
            price = 0;
            Serial.println(analogRead(pontetionmeter));
          }
        } 
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print( flow_frequency );
      lcd.print(" L/M");
      lcd.setCursor(0,7);
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print("Mc");
      lcd.print(" P:");
      lcd.print(price);
      lcd.print("$");
    }
   } 
   
    
     
}
