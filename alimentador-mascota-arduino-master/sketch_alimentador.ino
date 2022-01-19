#include <Servo.h>
#include "RTClib.h"
#include <Wire.h>

char *horas[]={
    "3:20",
    "3:25",
    "3:35"
};
  
long nhoras = (sizeof(horas)/sizeof(char *));
bool h12;
bool PM;
RTC_DS1307 Clock;
Servo servoMotor;
byte year, month, date, DoW, hour, minute, second;

void setup() {
  Wire.begin();
    Clock.begin();
  Clock.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  Serial.begin(9600);
}
void loop() {
    delay(1000);
    DateTime now = Clock.now();
    if(deboGirar()==1)
      girar();
}


void girar(){
    servoMotor.attach(9);
    int i;
  for (i=0;i<3;i++){
    servoMotor.write(0);
    delay(1000);
    servoMotor.write(90);
    delay(500);
  }
  servoMotor.detach();
}

int deboGirar(){
  String h = "";
  String m = "";
  for(int i=0;i<nhoras;i++){
    h= getValue(horas[i], ':', 0);
    m= getValue(horas[i], ':', 1);
    DateTime now = Clock.now();
    // recuperamos las horas, minutos y segundos para realizar la comparación
    hour = now.hour();
    minute = now.minute();
    second = now.second();
    Serial.println(hour);
    if(int(hour)==atoi(h.c_str()) && int(minute)==atoi(m.c_str()) && int(second)==0)
    //if(true)   
      return 1;
   }
 return 0;  
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
//@el_guie
