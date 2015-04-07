
#include <SerialGSM.h> //Inclui a biblioteca SerialGSM.h
#include <SoftwareSerial.h> //Inclui a biblioteca SoftwareSerial.h
#include <string.h>
SerialGSM cel(2,3); //Configura os pinos 2 e 3 para se trabalhar como Rx e Tx via Software
String SMS; //Variável para o armazenamento da SMS recebida
String numeroRemetente; //Variável para o armazenamento do número do remetente da SMS
String numeroPermitido = "+55129812755"; //Variável que define o número do celular que o sistema irá responder
String numeroPermitido2 = "\"012981275534\"";
boolean sendonce=true; //Variável boleana utilizada pela biblioteca SerialGSM.h
String lat="latitude",lon="longitude";


void setup() {
  
  Serial.begin(9600); //Incializa a Serial(Hardware) com um Baud Rate de 9600
  cel.begin(9600); //Incializa a Serial(Software) com um Baud Rate de 9600
  cel.Verbose(true); //Função de configuração da biblioteca SerialGSM.h
  cel.Boot(); //Função de inicialização do Módulo SM5100B
  cel.DeleteAllSMS(); //Função para deletar todas as SMS do chip
  cel.FwdSMS2Serial(); //Função utilizada para enviar as SMS para a Serial
Serial.println(">>>>> Celular Shield Inicializado <"); //Mensagem de início da aplicação
  Serial.println(); //Pula linha
   delay(10000); //Delay de 2 segundos   
}

void loop() {
  
  if (cel.ReceiveSMS()) //Se o chip no Celular Shield receber uma SMS
  {
    Serial.println(); //Pula linha
    Serial.println(); //Pula linha
    Serial.println(); //Pula linha
    Serial.println(); //Pula linha
    Serial.println("~~NOVA MENSAGEM RECEBIDA~~"); //Imprime na serial "NOVA MENSAGEM RECEBIDA"
    Serial.println(); //Pula linha
Serial.print("REMETENTE: "); //Imprime na serial a palavra "REMETENTE:"
    Serial.println(cel.Sender()); //Imprime o número do remetente que a SMS foi enviada
numeroRemetente = cel.Sender(); //Armazena na variável numeroRemetente o número do remetente
SMS = cel.Message();
if(SMS!="receber"){
   Serial.println("Não Permitido");
}else{
  
if(numeroRemetente != numeroPermitido) //Se o número do remetente não for o mesmo que o número permitido
    {
      Serial.println("Não Permitido"); //Imprime a mensagem "Não Permitido" e não executa nada
    }
else //Senão, o número é o permitido e executará os comandos
    {
      Serial.print("MENSAGEM: "); //Imprime na serial a palavra "MENSAGEM:"
      Serial.println(cel.Message()); //Imprime a mensagem que foi recebida
      SMS = cel.Message(); //Guarda na mensagem na variável SMS
      
      cel.println("AT+CMGF=1");
      delay(1000);
      cel.println("AT+CMGS="+numeroPermitido2);
      delay(1000);
      cel.println("As coordenadas sao: "+lat+", "+lon);
      delay(5000);
      cel.write(0x1A);
      delay(1000);
}
}

  }
  
}
