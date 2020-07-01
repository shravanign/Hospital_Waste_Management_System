#include "CTBot.h"         
#define  msg_sender_id  456019330
CTBot myBot;
String ssid = "smile";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "123456789";

String token = "1161500489:AAFPeMNyDkVhipgFAxzT0OZX1PAoKP6_Afo";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN

const int rs = 5, en = 4, d4 = 0, d5 = 2, d6 = 14, d7 = 12;

uint8_t led = D0;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)    
char Start_buff[70]; 
int i,z;             
char ch;
int str_len;
String message="";
int A=0,B=0,C=0,D=0; //For 4 RFID Tags
char textmessage[20];
TBMessage msg;
void MESSAGE_SEND();
void WAITING();
void setup() 
{
    // initialize the Serial
    Serial.begin(9600);
    Serial.println("Starting TelegramBot...");

    // connect the ESP8266 to the desired access point
    myBot.wifiConnect(ssid, pass);

    // set the telegram bot token
    myBot.setTelegramToken(token);

    // check if all things are ok
    if (myBot.testConnection())
        Serial.println("\ntestConnection OK");
    else
        Serial.println("\ntestConnection NOK");
  
   TEST();
}

void loop() 
{  
    RFID_CHECKING();     
}

void RFID_CHECKING()
{ 
   
 Serial.println("SHOW DEVICE");
 while(1)
 {
    if(Serial.available()>0)
    {    
      message=Serial.readString();
      int str_len = message.length() + 1;
      char textmessage[12];
      message.toCharArray(textmessage,str_len);
      Serial.println(textmessage);
      textmessage[12]='\0';
      if((strcmp(textmessage,"3A001966D194"))== 0)
      {     
          //For Syringes
          Serial.print("MEDICAL DEVICE: Syringe USED COUNT:");
          Serial.println(A);
          A++; 
          delay(1000);
           
          if(A>1)
          {
            Serial.println("MEDICAL DEVICE: SYRINGE USAGE COMPLETED..");
            myBot.sendMessage(msg_sender_id, "MEDICAL DEVICE:SYRINGE USAGE COMPLETED..");
            A=0;
          }
      }
      
      if((strcmp(textmessage,"3A001ABA0B91"))==0)
      {      
          //FOR BLOOD LANCET
          if(B!=0)
             Serial.print("MEDICAL DEVICE: Blood Lancet IS IT STERILIZED: NO");
          else
             Serial.print("MEDICAL DEVICE: Blood Lancet IS IT STERILIZED: YES");
          B++;
          delay(1000);
           
          if(B>1)
          {    
            Serial.println("  MEDICAL DEVICE:BLOOD LANCET NOT STERILIZED..");
            myBot.sendMessage(msg_sender_id, "MEDICAL DEVICE:BLOOD LANCET NOT STERILIZED..");
            B=0;
          }
      }
      
      if((strcmp(textmessage,"3A00194A355C"))==0)
      { 
          //FOR FORCEPS
          if(C!=0)
             Serial.print("MEDICAL DEVICE: Forceps IS IT STERILIZED: NO");
          else
             Serial.print("MEDICAL DEVICE: Forceps IS IT STERILIZED: YES");
          C++; 
          delay(1000);
           
          if(C>1)
          {
            Serial.println("   MEDICAL DEVICE:FORCEPS NOT STERILIZED..");
            myBot.sendMessage(msg_sender_id, "MEDICAL DEVICE:FORCEPS NOT STERILIZED..");
            C=0;
          }
      }
      
      if((strcmp(textmessage,"3A00190A361F"))==0)
      {    
          //Blood Storage Bottle 
          Serial.print("MEDICAL DEVICE:Storage Bottle USED COUNT:");
          Serial.println(D);
          D++;
          delay(1000);
           
          if(D>1)
          {     
            Serial.println("MEDICAL DEVICE:STORARGE BOTTLE USAGE COMPLETED..");
            myBot.sendMessage(msg_sender_id, "MEDICAL DEVICE:STORAGE BOTTLE USAGE COMPLETED..");
            D=0;
          }
      }
    }
 }
}

void MESSAGE_SEND()
{
   myBot.sendMessage(msg_sender_id, "SEND START TO CONTINUE");  
}

void TEST()
{
  String ssid = "smile";     // REPLACE mySSID WITH YOUR WIFI SSID
  String pass = "123456789";

  String token = "1161500489:AAFPeMNyDkVhipgFAxzT0OZX1PAoKP6_Afo"; 
  
  uint8_t led = D0;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)                            

  TBMessage msg;
  
    // initialize the Serial
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");

    // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

    // set the telegram bot token
  myBot.setTelegramToken(token);

    // check if all things are ok
  if (myBot.testConnection())
      Serial.println("\ntestConnection OK");
  else
      Serial.println("\ntestConnection NOK");
    // set the pin connected to the LED to act as output pin
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH); // turn off the led (inverted logic!)
   //myBot.sendMessage(msg_sender_id, "HOSPITAL WASTE MANAGEMENT SYSTEM"); 
  MESSAGE_SEND();
  
  while(1) {
    // a variable to store telegram message data
    // if there is an incoming message...
    if (myBot.getNewMessage(msg)) {

        if (msg.text.equalsIgnoreCase("START")) {              // if the received message is "LIGHT ON"...
            digitalWrite(led, HIGH);                               // turn on the LED (inverted logic!)
            myBot.sendMessage(msg.sender.id, "WELCOME TO HOSPITAL MANAGEMENT SYSTEM... ");  // notify the sender
            Serial.println(msg.sender.id);
          //WAITING();
          RFID_CHECKING();
        }
         else {                                                    // otherwise...
            // generate the message for the sender
            String reply;
            reply = (String)"Welcome " + msg.sender.username + (String)". Try START";
            myBot.sendMessage(msg.sender.id, reply);             // and send it
            
        }
    }
    // wait 500 milliseconds
    delay(500);
} 
}
