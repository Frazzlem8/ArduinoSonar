#include <Servo.h>  //This includes the servo motors libray to access it's functions
#include <LiquidCrystal.h> //Load Liquid Crystal Library                                                      

LiquidCrystal LCD_board(3,4,5,12,13,6,7);  //defining each lcd ports  //FROM LEFT TO RIGHT //RS=3,R/W=4,E=4,D3=12,D4=13,D5=6,D6=7
const int Echo = 9;  //setting echo pin for the sensor at 9
const int Trig = 10; //setting the trigpin for sonar sensor at 10  
const int Buzzer = 2;  //The buzzer signal pin set to 2
int Distance; //declare distance and converts to an int
long Duration; //declare time duration using long which is an extended time variable 
Servo ServoMotor; // defining servo as myServo 
void setup() { 
     Serial.begin(9600);  
     pinMode(Trig, OUTPUT); // setting the trig pin to output data   
     pinMode(Echo, INPUT); // setting the echo pin as input 
     pinMode(Buzzer, OUTPUT); // buzz pin is output to control buzzering
     LCD_board.setCursor(0,0);  //starts the cursor to upper left corner, column 0, row 0 to print the text
     LCD_board.begin(16,2); //This means 2 lines of 16 on the lcd board (16x2=32) meaning it allows 32 charcters on screen
     LCD_board.print("Target Locked:");  //Prints the message "Target Locked" on the top line  
     ServoMotor.attach(11); // defining the servo signal pin to 11
}   
void loop() {  
  //SERVO AND SONAR CALCULATIONS
   for(int i=0;i<=180;i++){    //set i to 0 when i is less than or equal to 180 append; allows the servo motor to rotate 180 degrees 
     ServoMotor.write(i);  //i is the value being written tothe servo 
     delay(30);   //speed in which it writes to the serial manager
     Distance = CalcDistance();  //Assigning distance to calculateDistance();
     Serial.print(i);   //prints each angle in the serial manager
     Serial.print("°");
     Serial.print("Degrees");
     Serial.print(" ");        //aestic , for clearer reading in serial monitor
     Serial.print(Distance);   //prints the distance in serial manager
     Serial.print("cm");       
     Serial.print(" ");
     Serial.print("Distance ||"); 
     Serial.print(" ");                                                                    
     
     LCD_board.setCursor(0,1);  //Setting the location of the first text column 0 row 1
     LCD_board.print("                "); //This stops the LCD changing to "cmm" only solution i could find
     LCD_board.setCursor(0,1);   //Set Cursor again to first column of second row
     LCD_board.print(Distance); //Print the distance on LCD 
     LCD_board.print(" cm");  //This prints the cm next to the number of LCD
     //delay(150); //could use this to slow the cycle down
  
    //BUZZER
    if (Distance <= 40 && Distance >= 0) {  // if distance is less than 40cm and greater than 0
      digitalWrite(Buzzer, LOW); //Dont buzz if > 40cm // sets buzzer to zero volts 
    } else {
      digitalWrite(Buzzer, HIGH); //Buzz if < 40cm
    }
    //delay(300);  //delays the buzz as its extremely load and annoying
 }  
 //repeats the previous loop however for rotating the other way
   for(int i=180;i>0;i--){ //when i =180 while i is greater than 0 deppend until 0
     ServoMotor.write(i);  
     delay(30);  
     Distance = CalcDistance();  
     Serial.print(i);   //prints each angle in the serial manager
     Serial.print("°");   //serial monitor display
     Serial.print("Degrees");   //serial monitor
     Serial.print(" ");        //aestic , for clearer reading in seriel monitor
     Serial.print(Distance);   //prints the distance in serial manager
     Serial.print("cm");       
     Serial.print(" ");
     Serial.print("Distance ||"); 
     Serial.print(" ");  
     
     LCD_board.setCursor(0,1);  //Set cursor to first column of second row
     LCD_board.print("                "); //Print blanks to clear the row
     LCD_board.setCursor(0,1);   //Set Cursor again to first column of second row
     LCD_board.print(Distance); //Print measured distance
     LCD_board.print(" cm");  //This prints the cm next to the number of LCD
     //delay(150); //could use this to slow the servo spin
     
     }  
 }  
 int CalcDistance(){   //
 digitalWrite(Trig, LOW);  //sets trigpin to low sets pin to 0 volts //no signal sent out
 delayMicroseconds(2);   //delays 3 milliseconds
 digitalWrite(Trig, HIGH);   //turns trigpin to high for 10 micro seconds, set to 5v  //trig sends pulse out
 delayMicroseconds(10);  //delay 10 milliseconds
 digitalWrite(Trig, LOW);  //Back to low //turns connection off
 Duration = pulseIn(Echo, HIGH);   //send the data back power to 5v //produce a pulse and the time it took is duration
 Distance= Duration*0.034/2;  //simple equation for calculation of distance distance == speed of sound in cm (0.034/2)
 return Distance;  //returns the distance
 }
