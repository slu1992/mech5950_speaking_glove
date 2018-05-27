/******************************************************************************
Flex_Sensor_Example.ino
Example sketch for SparkFun's flex sensors
  (https://www.sparkfun.com/products/10264)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining a flex sensor with a 47k resistor.
- The resistor should connect from A0 to GND.
- The flex sensor should connect from A0 to 3.3V
As the resistance of the flex sensor increases (meaning it's being bent), the
voltage at A0 should decrease.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int FLEX_PIN_1 = A0; // Pin connected to voltage divider output
const int FLEX_PIN_2 = A1;
const int FLEX_PIN_3 = A2;
const int FLEX_PIN_4 = A3;
const int FLEX_PIN_5 = A4;

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV_0 = 37500.0; // Measured resistance of 2.2k resistor
const float R_DIV_1 = 67500.0; // Measured resistance of 2.2k resistor
const float R_DIV_2 = 52500.0; // Measured resistance of 2.2k resistor
const float R_DIV_3 = 67500.0; // Measured resistance of 2.2k resistor
const float R_DIV_4 = 67500.0; // Measured resistance of 2.2k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE_0 = 37300.0; // resistance when straight
const float STRAIGHT_RESISTANCE_1 = 37300.0; // resistance when straight
const float STRAIGHT_RESISTANCE_2 = 37300.0; // resistance when straight
const float STRAIGHT_RESISTANCE_3 = 37300.0; // resistance when straight
const float STRAIGHT_RESISTANCE_4 = 37300.0; // resistance when straight

const float BEND_RESISTANCE_0 = 85000.0; // resistance at 90 deg
const float BEND_RESISTANCE_1 = 90000.0; // resistance at 90 deg
const float BEND_RESISTANCE_2 = 88000.0; // resistance at 90 deg
const float BEND_RESISTANCE_3 = 80000.0; // resistance at 90 deg
const float BEND_RESISTANCE_4 = 80000.0; // resistance at 90 deg

float angle_1_old = 0;
float angle_2_old = 0;
float angle_3_old = 0;
float angle_4_old = 0;
float angle_5_old = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN_1, INPUT);
  pinMode(FLEX_PIN_2, INPUT);
  pinMode(FLEX_PIN_3, INPUT);
  pinMode(FLEX_PIN_4, INPUT);
  pinMode(FLEX_PIN_5, INPUT);
}

void loop() 
{
    
  float threshold_time = 3200; //ms
  float threshold_angle = 5; //degree
  
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC_1 = analogRead(FLEX_PIN_1);
  int flexADC_2 = analogRead(FLEX_PIN_2);
  int flexADC_3 = analogRead(FLEX_PIN_3);
  int flexADC_4 = analogRead(FLEX_PIN_4);
  int flexADC_5 = analogRead(FLEX_PIN_5);
  
  float flexV_1 = flexADC_1 * VCC / 1023.0;
  float flexV_2 = flexADC_2 * VCC / 1023.0;
  float flexV_3 = flexADC_3 * VCC / 1023.0;
  float flexV_4 = flexADC_4 * VCC / 1023.0;
  float flexV_5 = flexADC_5 * VCC / 1023.0;
  
  float flexR_1 = R_DIV_0 * (VCC / flexV_1 - 1.0);
  float flexR_2 = R_DIV_1 * (VCC / flexV_2 - 1.0);
  float flexR_3 = R_DIV_2 * (VCC / flexV_3 - 1.0);
  float flexR_4 = R_DIV_3 * (VCC / flexV_4 - 1.0);
  float flexR_5 = R_DIV_4 * (VCC / flexV_5 - 1.0);
  //Serial.println("Resistance: " + String(flexR_1) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle_1 = map(flexR_1, STRAIGHT_RESISTANCE_0, BEND_RESISTANCE_0, 0, 90.0);
  float angle_2 = map(flexR_2, STRAIGHT_RESISTANCE_1, BEND_RESISTANCE_1, 0, 90.0);
  float angle_3 = map(flexR_3, STRAIGHT_RESISTANCE_2, BEND_RESISTANCE_2, 0, 90.0);
  float angle_4 = map(flexR_4, STRAIGHT_RESISTANCE_3, BEND_RESISTANCE_3, 0, 90.0);
  float angle_5 = map(flexR_5, STRAIGHT_RESISTANCE_4, BEND_RESISTANCE_4, 0, 90.0);
  
  //Serial.println("hit: flexR_1 -> " + String(angle_1) + " flexR_2 -> " + String(angle_2)+ " flexR_3 -> " + String(angle_3)+ " flexR_4 -> " + String(angle_4)+ " flexR_5 -> " + String(angle_5));
  //Serial.println();

  angle_1_old = angle_1;
  angle_2_old = angle_2;
  angle_3_old = angle_3;
  angle_4_old = angle_4;
  angle_5_old = angle_5;
  
  delay(threshold_time);
  
  flexADC_1 = analogRead(FLEX_PIN_1);
  flexADC_2 = analogRead(FLEX_PIN_2);
  flexADC_3 = analogRead(FLEX_PIN_3);
  flexADC_4 = analogRead(FLEX_PIN_4);
  flexADC_5 = analogRead(FLEX_PIN_5);
  
  flexV_1 = flexADC_1 * VCC / 1023.0;
  flexV_2 = flexADC_2 * VCC / 1023.0;
  flexV_3 = flexADC_3 * VCC / 1023.0;
  flexV_4 = flexADC_4 * VCC / 1023.0;
  flexV_5 = flexADC_5 * VCC / 1023.0;
  
  flexR_1 = R_DIV_0 * (VCC / flexV_1 - 1.0);
  flexR_2 = R_DIV_1 * (VCC / flexV_2 - 1.0);
  flexR_3 = R_DIV_2 * (VCC / flexV_3 - 1.0);
  flexR_4 = R_DIV_3 * (VCC / flexV_4 - 1.0);
  flexR_5 = R_DIV_4 * (VCC / flexV_5 - 1.0);

  angle_1 = map(flexR_1, STRAIGHT_RESISTANCE_0, BEND_RESISTANCE_0, 0, 90.0);
  angle_2 = map(flexR_2, STRAIGHT_RESISTANCE_1, BEND_RESISTANCE_1, 0, 90.0);
  angle_3 = map(flexR_3, STRAIGHT_RESISTANCE_2, BEND_RESISTANCE_2, 0, 90.0);
  angle_4 = map(flexR_4, STRAIGHT_RESISTANCE_3, BEND_RESISTANCE_3, 0, 90.0);
  angle_5 = map(flexR_5, STRAIGHT_RESISTANCE_4, BEND_RESISTANCE_4, 0, 90.0);

  int state = 0;
  
  //Serial.println("angle_1_old: " + String(angle_1_old) + " - angle_1: " + String(angle_1) +" = "+ String(abs(angle_1_old-angle_1)));
  //Serial.println("angle_2_old: " + String(angle_2_old) + " - angle_2: " + String(angle_2) +" = "+ String(abs(angle_2_old-angle_2)));
  //Serial.println("angle_3_old: " + String(angle_3_old) + " - angle_3: " + String(angle_3) +" = "+ String(abs(angle_3_old-angle_3)));
  //Serial.println("angle_4_old: " + String(angle_4_old) + " - angle_4: " + String(angle_4) +" = "+ String(abs(angle_4_old-angle_4)));
  //Serial.println("angle_5_old: " + String(angle_5_old) + " - angle_5: " + String(angle_5) +" = "+ String(abs(angle_5_old-angle_5)));
  //Serial.println();
  
  if(abs(angle_1_old-angle_1)<threshold_angle&&abs(angle_2_old-angle_2)<threshold_angle&&abs(angle_3_old-angle_3)<threshold_angle&&abs(angle_4_old-angle_4)<threshold_angle&&abs(angle_5_old-angle_5)<threshold_angle){
    state = 1;
  }else{
    state = 0;
  }

  if(state == 1){
    //Serial.println("bend: flexR_1 -> " + String(angle_1) + " flexR_2 -> " + String(angle_2)+ " flexR_3 -> " + String(angle_3)+ " flexR_4 -> " + String(angle_4)+ " flexR_5 -> " + String(angle_5));
    Serial.println("[" + String(angle_1) + ", " + String(angle_2)+ ", " + String(angle_3)+ ", " + String(angle_4)+ ", " + String(angle_5) +"]");
    Serial.println();
    state = 0;
  }

}
