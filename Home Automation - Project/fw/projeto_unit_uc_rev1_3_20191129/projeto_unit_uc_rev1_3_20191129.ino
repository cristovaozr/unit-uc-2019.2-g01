/*
  ------ Projeto para cadeira uC - UNIT ------

  Autoria: Rubem Diego (rubemdiego@yahoo.com.br);

  VERSÃO: 1.3

  DATA: 29/11/2019

  Comandos a serem dados pelo programa:

  NOTE: *Esta versão terá uso do terminal. Utilização do app para mostrar variaveis de controle.

*/

#include <LiquidCrystal.h>     //Library LCD Display

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
/*Cria objeto lcd da classe LiquidCrystal
  RS     7
  Enable 6
  DB4    5
  DB5    4
  DB6    3
  DB7    2
*/

/*********************************** Dio defines  ***********************************/
//None
/*********************************** UART defines  ***********************************/

#define BAUD_RATE     9600

/*********************************** AN defines  ***********************************/

#define ANALOG_VREF               5.00
#define ANALOG_MAX_RAW_VALUE      1024.00

/*********************************** Delays defines  ***********************************/

#define init_delay            500   //Delay time for initialization on Display (ms)
#define disp_m_delay          1000  //Delay time for texts Menu (ms)

/*********************************** Global Variables ***********************************/

float temp,           //external temperature from LM35 Sensor (ºC)
      temp_f,         //external temperature from LM35 Sensor (ºF)
      volt_b,         //Voltage converted by adjusts buttons MENU
      volt_mic,       //Voltage from Noise Capture
      volt_light,     //Voltage from LDR Capture
      volt_bar = 0;   //Variable for Bargraph generator on display LCD
      
short int count_screen = 0;   //Variable for swap on screen display LCD

char command;   //Variable for commands from UART Communication

float maxtemp = -100.00,    // Variáveis que guardam a temperatura máxima e mínima
      mintemp = 100.00; 

//Array que desenha o simbolo de grau
byte a[8] = {B00110, B01001, B00110, B00000, B00000, B00000, B00000, B00000};
//Array que desenha a barra
byte b[8] = {B01110, B01110, B01110, B01110, B01110, B01110, B01110, B01110};
//Array que desenha os caracteres vazios
byte e[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};


/*********************************** Keyboard MENU ***********************************/

short int teclas()
{
  //conv. valor analogico para tensão:
  volt_b = (((analogRead(A1)) * (ANALOG_VREF)) / (ANALOG_MAX_RAW_VALUE));

  //cond. para MENU
  if (volt_b >= 4.50) return 1;
  
  //cond. para UP
  else if (volt_b < 4.00 && volt_b > 3.50) return 2;

  //cond. para DW
  else if (volt_b < 3.40 && volt_b > 2.90) return 3;

  //cond. para ESC
  else if (volt_b < 2.80 && volt_b > 2.00) return 4;

  else return 0;
}

unsigned int entrada(void)
{
  unsigned int valor;
  do
  {
    valor = teclas();
  }
  while (valor == 0);

  while (teclas());
  delay(100);
  return (valor);
}

/*********************************** Bargraph Generator for Display ***********************************/

void bargraph()
{ 
  if (volt_bar >= 0.32)
  {
    lcd.setCursor(0, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.write(3);
  }
  if (volt_bar >= 0.64)
  {
    lcd.setCursor(1, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(1, 1);
    lcd.write(3);
  }
  if (volt_bar >= 1.28)
  {
    lcd.setCursor(2, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(2, 1);
    lcd.write(3);
  }
  if (volt_bar >= 1.60)
  {
    lcd.setCursor(3, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(3, 1);
    lcd.write(3);
  }
  if (volt_bar >= 1.92)
  {
    lcd.setCursor(4, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(4, 1);
    lcd.write(3);
  }
  if (volt_bar >= 2.24)
  {
    lcd.setCursor(5, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(5, 1);
    lcd.write(3);
  }
  if (volt_bar >= 2.56)
  {
    lcd.setCursor(6, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(6, 1);
    lcd.write(3);
  }
  if (volt_bar >= 2.88)
  {
    lcd.setCursor(7, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(7, 1);
    lcd.write(3);
  }
  if (volt_bar >= 3.20)
  {
    lcd.setCursor(8, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(8, 1);
    lcd.write(3);
  }
  if (volt_bar >= 3.52)
  {
    lcd.setCursor(9, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(9, 1);
    lcd.write(3);
  }
  if (volt_bar >= 3.84)
  {
    lcd.setCursor(10, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(10, 1);
    lcd.write(3);
  }
  if (volt_bar >= 4.16)
  {
    lcd.setCursor(11, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(11, 1);
    lcd.write(3);
  }
  if (volt_bar >= 4.48)
  {
    lcd.setCursor(12, 1);
    lcd.write(2);
  } 
  else
  {
    lcd.setCursor(12, 1);
    lcd.write(3);
  }
  if (volt_bar >= 4.80)
  {
    lcd.setCursor(13, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(13, 1);
    lcd.write(3);
  }
  if (volt_bar >= 5.00)
  {
    lcd.setCursor(14, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(14, 1);
    lcd.write(3);
  }
  if (volt_bar >= 5.00)
  {
    lcd.setCursor(15, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(15, 1);
    lcd.write(3);
  }
}

/*********************************** Screen 3: Noise ***********************************/

void screen_3()
{ 
    lcd.home();
    lcd.print("Noise:");

    lcd.setCursor(8, 0);
    lcd.print(volt_mic);
    lcd.setCursor(15, 0);
    lcd.print("%");

    volt_bar = volt_mic;
    bargraph();
}

/*********************************** Screen 2: Light ***********************************/

void screen_2()
{
    lcd.home();
    lcd.print("Light:");

    lcd.setCursor(8, 0);
    lcd.print(volt_light);
    lcd.setCursor(15, 0);
    lcd.print("%");

    volt_bar = volt_light;
    bargraph();
}

/*********************************** Screen 1: Temperature ***********************************/

short int screen_1()
{
  lcd.home();
  lcd.print("Temperature:");

  lcd.setCursor(5, 1); //Coloca o cursor na coluna 5, linha 1
  lcd.write(1); //Escreve o simbolo de grau

  //lcd.createChar(1, a);
  lcd.setCursor(14, 1); //Coloca o cursor na coluna 14, linha 1
  lcd.write(1); //Escreve o simbolo de grau

  //Convert temperature °C in °F

  temp_f = (((9.00 * temp) + 160.00) / 5.00);
  
  lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.setCursor(6, 1);
  lcd.print("C");
  
  lcd.setCursor(9, 1);
  lcd.print(temp_f);
  lcd.setCursor(15, 1);
  lcd.print("F");
}

/*********************************** SETUP Arduino***********************************/

void setup()
{
  
  pinMode(A0, INPUT); //Analogic Signal from LM35 Sensor Temp
  pinMode(A1, INPUT); //Analogic Signal from Keyboard Menu
  pinMode(A2, INPUT); //Analogic Signal from Light Sensor LDR
  pinMode(A3, INPUT); //Analogic Signal from Mic with Op amplifier

  Serial.begin(BAUD_RATE);  //Uart Configuration

  lcd.begin(16, 2);   //Inicializa display de 2 linhas x 16 colunas

  lcd.home();         //Posiciona cursor no canto superior esquerdo
  lcd.clear();

  //Executa uma pequena inicialização com contagem regressiva
  
  lcd.print("Ready");
  delay(init_delay);
  lcd.setCursor(5, 0);
  lcd.print(".");
  delay(init_delay);
  lcd.setCursor(6, 0);
  lcd.print(".");
  delay(init_delay);
  lcd.setCursor(7, 0);
  lcd.print(".");

  lcd.clear();

  //Mensagem informação Versão de Firmware:
  
  lcd.print("----- UNIT -----");
  lcd.setCursor(5, 1);
  lcd.print("2019.2");
  delay(init_delay);
  lcd.clear();

  //Criação dos Caracteres especiais no LCD Display
  
  lcd.createChar(1, a);
  lcd.createChar(2, b);
  lcd.createChar(3, e);
}
/*********************************** Program MAIN ***********************************/

void loop()
{
  short int aux = 0;
  
  aux = teclas();

  temp = (((analogRead(A0)) * (ANALOG_VREF) * 100.00) / (ANALOG_MAX_RAW_VALUE));

  volt_mic = (((analogRead(A2)) * (ANALOG_VREF)) / (ANALOG_MAX_RAW_VALUE));

  volt_light = (((analogRead(A3)) * (ANALOG_VREF)) / (ANALOG_MAX_RAW_VALUE));

  //Save max. temperature
  if(temp > maxtemp)  maxtemp = temp;
   
  //Save min. temperature
  if(temp < mintemp)  mintemp = temp;
  
  //Max. and Min. Temp. When push UP on Keyboard Menu;
  if (aux == 2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("M:");
    lcd.setCursor(2, 0);
    lcd.print(maxtemp);
    lcd.setCursor(0, 1);
    lcd.print("m:");
    lcd.setCursor(2, 1);
    lcd.print(mintemp);
    
    lcd.setCursor(7, 0); //Coloca o cursor na coluna 7, linha 0
    lcd.write(1); //Escreve o simbolo de grau

    lcd.setCursor(7, 1); //Coloca o cursor na coluna 7, linha 1
    lcd.write(1); //Escreve o simbolo de grau

    lcd.setCursor(8, 0);
    lcd.print("C");

    lcd.setCursor(8, 1);
    lcd.print("C");
    
    delay(1000);
    lcd.clear();
  }

  //Mudança de informaçãoes no display LCD quando press. MENU
  
  if (aux == 1)
  { 
      if(count_screen <= 2) count_screen++;
      lcd.clear();
      delay(200);
  }
     
  if (count_screen == 3) count_screen = 0;     
  
  if (count_screen == 0) screen_1();
  if (count_screen == 1) screen_2();
  if (count_screen == 2) screen_3();

  delay(10);
  
  //Commands for variables reading by Uart
  
  if(Serial.available()>0)
  {
    command = Serial.read();
    
    if(command == 'a')
    { 
      Serial.println(temp);
    }
    
    else if(command == 'b')
    {
      Serial.println(temp_f);
    }

    else if(command == 'c')
    {
      Serial.println(maxtemp);      
    }
    
    else if(command == 'd')
    {
      Serial.println(mintemp);      
    }

    else if(command == 'e')
    {
      Serial.println(volt_light);       
    }

    else if(command == 'f')
    {
      Serial.println(volt_mic);      
    }
  }
}
