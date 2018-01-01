/*
 * Atmospheric CO2 Level..............400ppm
 * Average indoor co2.............350-450ppm
 * Maxiumum acceptable co2...........1000ppm
 * Dangerous co2 levels.............>2000ppm
 */




#define anInput     A0  //analog feed from MQ135

void setup(){
  
  
  pinMode(anInput,INPUT);
  Serial.begin(9600);
  
  
  }

void loop(){

int co2now[10];//int array for co2 readings
int co2raw=0;  //int for raw value of co2
int co2comp = 0;   //int for compensated co2 
int co2ppm = 0;    //int for calculated ppm
int sum=0;
for (int x=0;x<10;x++){


  co2now[x]=analogRead(A0);
  delay(200);
  sum=sum+co2now[x];
}

co2raw=sum/10;
co2ppm=map(co2raw,0,1023,400,5000);
Serial.println(co2ppm);



}

