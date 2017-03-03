#include "Ultrasonic.h"

Ultrasonic ultrasonic(12,13);

void setup() {
Serial.begin(9600);
}

void loop()
{

  int distanceDetails[10];
  int distance;
  int avgTot;
  double avg;
  double sem;
  double sd;
  String packet;

  int counter = 0;

  while(1) {

    sd = 0.0;
    avgTot = 0.0;
    counter += 1;
    packet = "DP|MULE|DISTANCE|0x1|";
    
    for(int i=0; i<10; i++) {
      distanceDetails[i] = ultrasonic.Ranging(CM);
      delay(50);
    }

    for(int i = 0; i < 9; i++) {
      avgTot += distanceDetails[i];
    }

    avg = avgTot/9;

    for(int i = 0; i < 10; i++) {
      if(distanceDetails[i] != 594){
        double temp = (distanceDetails[i] - avg); 
        sd += sq(temp);
      }
    }

    sd = sd / 10;
    sd = sqrt(sd);
    sem = sd / 3.1623;
    packet.concat(counter);
    packet.concat("|CM|");
    packet.concat(sd);
    packet.concat("|");
    packet.concat(sem);
    packet.concat("|");
    packet.concat(avg);
    packet.concat("|");
    for(int i = 0; i<10; i++){
      packet.concat(distanceDetails[i]);
      if(i != 9) {
        packet.concat(",");
      }
    }
    packet.concat("|");
    Serial.println(packet); 
  }
   
}





