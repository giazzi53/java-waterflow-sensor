float vazao; //Variável para armazenar o valor em L/min
float media=0; //Variável para tirar a média a cada 1 minuto
int contaPulso; //Variável para a quantidade de pulsos
int i=0; //Variável para contagem

#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "24d6fecc78b74ce39ed55c8a09f0823f";
char ssid[] = "SEGJC";
char pass[] = "42645283";
String user = "Guilherme Giazzi";
String deviceId = "18-FE-34-68-F1-A9";
String description = "Pia da cozinha";

String userList[] = {"João da Silva", "Matheus Augusto", "Felipe Rocha", "Guilherme Henrique"};
String deviceIdList[] = {"00-AA-01-BB-CC", "11-BB-02-CC-DD", "22-CC-03-D, D-EE", "33-DD-04-EE-FF"};
String descriptionList[] = {"Pia do banheiro", "Filtro de água", "Máquina de lavar roupas", "Mangueira do jardim"};

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(10, 11); // RX, TX
BlynkTimer timer; // Announcing the timer

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

void setup()
{
  Serial.begin(9600);

  delay(10);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  pinMode(2, INPUT);
  attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) para trabalhar como interrupção
  timer.setInterval(10000L, myTimerEvent);
}

void loop()
{
  contaPulso = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  //cli();      //Desabilita interrupção
  
  vazao = contaPulso / 5.5; //Converte para L/min
  media=media+vazao; //Soma a vazão para o calculo da media
  i++;
  
  if(i==10)
  {
    media = media/10; //Tira a media dividindo por 60
    /*media = 0; //Zera a variável media para uma nova contagem
    i=0; //Zera a variável i para uma nova contagem*/
    
    Blynk.run();
    timer.run(); // running timer every minute
  }
}


void myTimerEvent()
{
  //sensorData = analogRead(A0);
  int randomNumber = random(0,4);
  float randomMedia = random(0,36);
  //Serial.println(media);
  Blynk.virtualWrite(V5, randomMedia);
  Blynk.virtualWrite(V6, userList[randomNumber]);
  Blynk.virtualWrite(V7, deviceIdList[randomNumber]);
  Blynk.virtualWrite(V8, descriptionList[randomNumber]);
  media = 0; //Zera a variável media para uma nova contagem
  i=0; //Zera a variável i para uma nova contagem
}

void incpulso ()
{ 
  contaPulso++; //Incrementa a variável de contagem dos pulsos
} 
