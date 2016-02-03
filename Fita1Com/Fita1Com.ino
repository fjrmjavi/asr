#include <string.h>
#include <stdio.h>

char cadena[10];boolean flag=false;
char num=0;int pos=0;int hora=0;
int num2=0;int led=0;
int muestra[10];int mostra;int valor=0;
int contmuestra=0;int prueba=0;int hola=0;
int w=0;
//------------------------------------------------------------------------------
void salida(void)// RUTINA PARA CUANDO TE INDICAN QUE QUIERES UNA SALIDA FUNCIONA!!!
{
  int poss=2;int num1=0;
  num1=((cadena[poss]-'0')*10);
  poss++;
  num2=((cadena[poss]-'0')+num1);
  led=num2;
  if(led>13){
    Serial.println("AS1Z");
  }
  else{
    pinMode(led,OUTPUT);
    poss++; 
    if (cadena[poss]=='1' || cadena[poss]=='0')
    { 
      digitalWrite(led, (cadena[poss]-'0'));
      poss = 0;num1=0;
      Serial.println("AS0Z");
    } 
    else {
     Serial.println("AS1Z");
     cadena[10]='0';
     poss = 0;num1=0;
    }     
   }
  return;
}
//------------------------------------------------------------------------------
void entrada(void)// RUTINA PARA CUANDO TE DICEN QUE ES ENTRADA  FUNCIONA!!!
{
    int pose=2;int num1=0;
  num1=((cadena[pose]-'0')*10);
  pose++;
  num2=((cadena[pose]-'0')+num1);
  led=num2;
  if(led>13){
    Serial.println("AE10Z ");
  }
  else{
    pinMode(led,INPUT);
    num2=digitalRead(led);
    Serial.print("AE0");
    Serial.print(num2);
    Serial.println("Z");
    pose=2;num1=0;
  }      
  return;
}
//-------------------------------------------------------------------------

void mediavariable(void)// CAMBIAR EL NÚMERO DE MUESTRAS
{
 
  if(cadena[2]<='9'){
  Serial.println("AV0Z");
  }
  
  else{
  Serial.println("AV1Z");
  }
  
}
//-----------------------------------------------------------------------------

void convertidor(void)
{
  if (flag==false){
  Serial.println("AC20000Z");
  }  
  else{
    if (cadena[2]!='Z'){
      Serial.println("AC10000Z ");
    }
    else{
      Serial.print("AC0");
      if (mostra<1000 && mostra>0){
      Serial.print("0");
      }
      else if (mostra == 0){
      Serial.print("000");
      }
      Serial.print(mostra);
      Serial.println("Z");
    }
  }
}
//------------------------------------------------------------------------------
void marcha(void)
{
  if(cadena[2]=='0'){
  flag=false;
  Serial.println("AM0Z");
  }
  else if(cadena[2]=='1'){
  flag=true;
  Serial.println("AM0Z");
  }
  else if(cadena[2]!='1'||cadena[2]!='0'){
  Serial.println("AM1Z");}
}
//-----------------------------------------------------------------------
void media (void)
{
       
      
       
       int z=0;int g=0;    
       for(z=0;z<w;z++){
       g=g+muestra[z];
       }
       mostra=g/w; 
}
//------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)//ACTIVAR LAS INTERRUPCIONES DE COMPARACIÓN DEL TIMER1. 
{
hora++;
if(hora>=9)	
  {
        hora=0;
	muestra[valor%w]= analogRead(A5);
        media();
        contmuestra++;
        valor++;
        prueba=!prueba;
        digitalWrite(13,prueba);
      if(contmuestra>=w)
      {
        hola=!hola;
        digitalWrite(12,hola);
        contmuestra=0;
        valor=0;
      }
}
}
//------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  noInterrupts(); //resetear las interrupciones del timer1
  TCCR1A=0;
  TCCR1B=0;
  TCNT1=0;
  
  OCR1A=31250; //EL TOPE DE LO QUE CUENTA EL TIMER
  TCCR1B|=(1<<WGM12); //CTC MODE
  TCCR1B|=(1<<CS12);// prescaler de 1024
  TCCR1B|=(1<<CS10);
  TIMSK1|=(1<<OCIE1A);// ACTIVAR LA INTERRUPCIÓN DE COMPARAR. 
  interrupts();
}
//-----------------------------------------------------------
void loop() { 
  do
  { 
    num=Serial.read();    
  }while(num!='A');   
  cadena[pos]='A';
  pos++;
//espero hasta que el primer caracter sea A  
  while (num!='Z'){  
    if (Serial.available() > 0) {
      num=Serial.read();
      cadena[pos]=num;
       pos++;
      if(num=='Z'){
        break;}    
    }
    delay(5);
  }
// almacena los caracteres de la consola en el array
  switch (cadena[1]){
    case 'S':{//---------------------------------------- SALIDAS
      salida();   
      num=0;num2=0;       
      delay(50);
      for(num=0;num<10;num++)
      {
        cadena[num]='0';
      }
      num=0;num2=0;led=0;pos=0;
    }
    break;
    case 'E':{//---------------------------------------  ENTRADAS
      entrada();   
      num=0;num2=0;       
      delay(50);
      for(num=0;num<10;num++)
      {
        cadena[num]='0';
      }
      num=0;num2=0;led=0;pos=0;
    }
    break;
    case 'C':{//---------------------------------------  CONVERTIDOR
      convertidor();   
      num=0;
      delay(50);
      for(num=0;num<10;num++)
      {
        cadena[num]='0';
      }
      num=0;num2=0;led=0;pos=0;
    }
    break;
    case 'M':{//---------------------------------------  MARCHA
      marcha();   
      num=0;num2=0;       
      delay(50);
      for(num=0;num<10;num++)
      {
        cadena[num]='0';
      }
      num=0;num2=0;led=0;pos=0;
    }
    break;
    case 'V':{//---------------------------------------  MEDIA VARIABLE
      mediavariable();
      w=cadena[2]-'0';
      num=0;num2=0; 
      delay(50);
      for(num=0;num<10;num++)
      {
        cadena[num]='0';
      }
      num=0;num2=0;led=0;pos=0;
    }
    break;
  } 
}

/*

-Capacitat de poder canviar el nombre de mostres amb el que es calcula la mitjana. 

-Definir un nou missatge que permeti enviar el nombre de mostres per fer la mitjana
-Modificar el codi per rebre aquest missatge
-Modificar el codi per tal que el nombre de mostres per fer la mitjana sigui variable

*/


