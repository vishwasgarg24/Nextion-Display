#include "Nextion.h"
#include "DHT.h"
 
NexProgressBar j0 = NexProgressBar(0, 6, "j0");
NexText txt_temp  = NexText(0, 3, "t0");
NexText txt_umid  = NexText(0, 5, "t2");
NexDSButton bt0   = NexDSButton(0, 7, "bt0");
 
 
//  Configuracao do modulo DHT11
#define DHTPIN 2 
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);
 
 
// Variaveis
int temp = 0;
int temp_perc = 0;
char buffer[100] = {0};
char buffer2[100] = {0};
int led = 13;
uint32_t dual_state;
 
 
void setup(void){
    nexInit();
    pinMode(led, OUTPUT);  
}
 
 
void loop(void){
    // Atualiza os valores do Nextion
    j0.setValue(temp_perc);
    txt_temp.setText(buffer);
    txt_umid.setText(buffer2);
 
    // sensor DHT
    int temp = dht.readTemperature();
    int umid = dht.readHumidity();
 
    // Conversion of integer values ​​to string
    memset(buffer, 0, sizeof(buffer));
    itoa(temp, buffer, 10);
    memset(buffer2, 0, sizeof(buffer2));
    itoa(umid, buffer2, 10);
 
    // Conversao da temperatura para percentual (0 a 50)
    temp_perc=(temp/0.5);
 
    // Faz a leitura do valor do botao
    bt0.getValue(&dual_state);
    if(dual_state>0) {
        digitalWrite(led, HIGH);
    } else {
        digitalWrite(led, LOW);
    }
}
