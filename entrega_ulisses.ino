#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>
#include <Servo.h>

String sinais, url, endereco;

#define SERVO 6 // Porta Digital 6 definida para o servo motor
#define dht_dpin A1 // A1 - sensor de umidade/temperatura do ar 

dht DHT; //Inicializa o sensor de temperatura e umidade relativa do solo

// variaveis para sensor de umidade do solo
int umidade;
int i;

float sensor1 = 0;
float sensor2 = 0;
float sensor3 = 0;


unsigned long time; // variavel temporal - tempo que arduino esta ligado
Servo s; // variavel para o servo motor
int pos; // posicao para o servo motor

//Configuracoes da shield ethernet MAC e IP
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 199 }; // Define o endereço IP do arduino
byte servidor[] = { 192, 168, 0, 103 }; // Define o endereço IP do servidor

// Porta de comunicacao pela internet
EthernetServer server(80);
EthernetClient cliente;

String readString; //parametro de leitura da pag HTML
int Pin = 7;  //Pino digital onde será ligado e desligado o dispositivo 1.
int Pin1 = 4; //Pino digital onde será ligado e desligado o dispositivo 2.
int Pin2 = 8; //Pino digital onde será ligado e desligado o dispositivo 3.
int Pin3 = 11; //Pino digital onde será ligado e desligado o dispositivo 4.

void setup(){

   pinMode(Pin, OUTPUT); // Define o Pino 7 como saída.
   pinMode(Pin1, OUTPUT); // Define o Pino 4 como saída.
   pinMode(Pin2, OUTPUT); // Define o Pino 8 como saída.
   pinMode(Pin3, OUTPUT); // Define o Pino 8 como saída.
    
   Ethernet.begin(mac, ip); // Inicia MAC e IP    
   //  Inicia o servidor
   server.begin();
   Serial.begin(9600);// inicia leitura no sensor de temp. umidade
   s.attach(SERVO);
   s.write(0);
   delay(1000);//Aguarda 1 seg antes de acessar as informações do sensor    
    
}
void loop(){

  DHT.read11(dht_dpin); //acessa o sensor DHT11 

  float sensor1 = DHT.humidity;// variavel umidade relativa do ar tipo float
  float sensor2 = DHT.temperature;// variavel temperatura do ar tipo float

  sinais = String(sensor1) + "|" + String(sensor2);
  Serial.println(sinais);
   
   Serial.print("Umidade = ");
   Serial.print(sensor1);
   Serial.print(" %  ");
   Serial.print("Temperatura = ");
   Serial.print(sensor2);
   Serial.println(" Celsius  "); 

  umidade = analogRead(A0);// entrada para o sensor de umidade do solo - A0
  int Porcento = map(umidade, 1023, 0, 0, 100);// // sensor de umidade do solo
  float sensor3 = Porcento; // variavel umidade relativa do solo tipo float
  
  //sensor umidade relativa do solo - dados
  Serial.print("h% (solo) = ");
  Serial.print(sensor3);
  Serial.println(" % ");

   time = millis();
   Serial.println("TEMPO DE MONITORIAMENTO");
   Serial.print("T(min) = ");
   Serial.println((time/1000)/60);
   Serial.print("T(s) = ");
   Serial.println(time/1000);
   Serial.print("T(ms) = ");
   Serial.println(time);
   Serial.println("=========================");
   Serial.println(Ethernet.localIP());

   Serial.print("GET /arduino/salvardados.php?");
   Serial.print("sensor1=");
   Serial.print(sensor1);
   Serial.print("&sensor2=");
   Serial.print(sensor2);
   Serial.print("&sensor3=");
   Serial.println(sensor3); 

   
   delay(2000);  

    //programcao para WEB
    EthernetClient client = server.available();
    if (client) {
     while (client.connected()) {
       if (client.available()) {
         char c = client.read();
        if (readString.length() < 100) {
           readString += c;
         }
         if (c == '\n') {
           client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println();                   

           // Início do código HTML.

           client.println("<HTML>");
           client.println("<BODY>");
           client.println("<H1>APP - ANDROID</H1>");

               client.println("<hr />");
               client.println("<br />");               

                     
                   //client.println("GET /http://192.168.0.103/arduino/salvardados.php?sensor1=37.00&sensor2=26.00&sensor3=8.00 HTTP/1.1");
                   cliente.print("GET /192.168.0.199/arduino/salvardados.php?");
                   cliente.print("sensor1=");
                   cliente.print(sensor1);
                   cliente.print("&sensor2=");
                   cliente.print(sensor2);
                   cliente.print("&sensor3=");
                   cliente.println(sensor3);       
                 
                   
                   client.print("GET /http://192.168.0.103/arduino/salvardados.php?");
                   client.print("sensor1=");
                   client.print(sensor1);
                   client.print("&sensor2=");
                   client.print(sensor2);
                   client.print("&sensor3=");
                   client.println(sensor3); 
                                             
                  
                   client.println("<br />"); 
                   client.println("<br />"); 
                   client.println("UMIDADE (AR) [%]  ==>");
                   client.println(sensor1);                   
                   client.println("<br />"); 
                   client.println("TEMPERATURA  [C]  ==>");
                   client.println(sensor2);
                   client.println("<br />");
                   client.print("UMIDADE (SOLO)      ==>");
                   client.print(sensor3);
                   client.println(" % ");
                   client.println("<br />");
                   client.println("IP - SERVIDOR     ==>");
                   client.println(Ethernet.localIP());
                   client.println("<br />");
                   client.print("T(S) DE OPERACAO ==> ");
                   client.println(time/1000);  
  
              //client.print("<meta http-equiv='refresh' content=60 URL='http://192.168.0.199/'>");
                                       
              client.println("</BODY>");
              client.println("</HTML>");

           delay(1);
           client.stop();

             if(readString.indexOf("android/Abre") > 0)
           {
             s.write(90);
             delay(15);  // posicao aberta (90 graus).
           }
              if(readString.indexOf("android/Fecha") > 0)
           {
              s.write(0);
              delay(15);  // posicao aberta (0 graus)
           }           
           if(readString.indexOf("android/LedOn") > 0)
           {
           digitalWrite(Pin, HIGH);
           digitalWrite(Pin2, HIGH);            
           } 
           if(readString.indexOf("android/LedOff") > 0)
           {
           digitalWrite(Pin, LOW);
           digitalWrite(Pin2, LOW);  
           }
           if(readString.indexOf("android/LedOn1") > 0)
           {
           digitalWrite(Pin1, HIGH);
           digitalWrite(Pin, LOW);
           digitalWrite(Pin2, LOW);    
           }
           if(readString.indexOf("android/LedOff1") > 0)
           {
           digitalWrite(Pin1, LOW);
           digitalWrite(Pin, LOW);
           digitalWrite(Pin2, LOW);                   
           }         

                                  
                readString="";
        }
      }
    }
  }
}
