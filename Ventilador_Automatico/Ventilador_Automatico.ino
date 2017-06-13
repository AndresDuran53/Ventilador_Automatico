
/*
 *Ventilador Automatico: En este ejercio utilizaremos un sensor de
 *temperatura para ejecutar acciones y encender luces para
 *saber si esta frio, normal, o caliente.                   
 *Vamos a tomar una temperatura base como la normal, luego  
 *asignamos un rango dentro del que puede estar, por ejemplo
 *dos grados arriba o abajo de la base, y si se sale de ese 
 *rango, entonces encenderemos o apagaremos un ventilador y 
 *encenderemos la luz correspondiente.
*/

//Declaramos los pines del Led RGB
const int rgbRojo = 8;
const int rgbAzul = 9;
const int rgbVerde = 10;

const int pinMotor = 11; //Declaramos el pin de senal de nuestro Ventilador (Motor DC)
const int sensorPin = A0; //Declaramos el pin analogico donde leeremos el sensor de temperatura

const float baselineTemp = 24.5; //Asignamos una temperatura base
const float rangoTemp = 1.0; //Asignamos un rango que significa que tan arriba o abajo puede estar la temperatura de la base

int sensorVal; //Creamos la variable donde almacenaremos la lectura del sensor
int sumatoria; //Creamos una variable donde sumaremos los valores leidos para luego promediarlos
int promedio; //Creamos una variable donde almacenaremos el promedio de los valores leidos


void setup() {
  Serial.begin(9600);
  //Declaramos los pines de salida en una iteracion y les enviamos un LOW
  for (int pinNumber = 8; pinNumber < 12; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  
  sumatoria=0; //Iniciamos la variable de sumatoria como 0 para empezar a leer.

  //Obtenemos 10 valores mediante una iteracion antes de continuar.
  for (int i = 0;i<10;i++){
    sensorVal = analogRead(sensorPin); //Leemos nuestro sensor de temperatura
    sumatoria=sumatoria+sensorVal; //Le sumamos a la variable el valor que leimos
  }
  float promedio=(sumatoria/10); //sacamos un promedio de los 10 valores que leimos
  float voltage = (promedio / 1024.0) * 5.0; //Convertimos el promedio leido a voltios
  float temperatura = (voltage - .5) * 100; //Convertimos los voltios a grados celcius
  
  //Mostramos los valores leidos (*Opcional)
  Serial.print("Sumatoria Sin Promedio: ");
  Serial.println(sumatoria);
  Serial.print("Promedio Leido: ");
  Serial.println(promedio);
  Serial.print("Voltios: ");
  Serial.println(voltage);
  Serial.print("Grados: ");
  Serial.println(temperatura);

  //Si la temperatura es menor al rango que pusimos ejecutamos la funcion temperaturaBaja()
  if (temperatura < baselineTemp - rangoTemp) {
    temperaturaBaja();
  }
  //Si la temperatura esta dentro del rango que pusimos ejecutamos la funcion temperaturaMedia()
  else if ((temperatura >= baselineTemp - rangoTemp) && (temperatura <= baselineTemp + rangoTemp)) {
    temperaturaMedia();
  }
  //Si la temperatura es mayor al rango que pusimos ejecutamos la funcion temperaturaAlta()
  else if (temperatura > baselineTemp + rangoTemp) {
    temperaturaAlta();
  }
  delay(5);
}

//Dentro de esta funcion estan las acciones que queremos realizar si la temperatura es Baja
void temperaturaBaja(){
  digitalWrite(rgbAzul,HIGH);
  digitalWrite(rgbVerde,LOW);
  digitalWrite(rgbRojo,LOW);
  digitalWrite(pinMotor,LOW);
}

//Dentro de esta funcion estan las acciones que queremos realizar si la temperatura es Medio
void temperaturaMedia(){
  digitalWrite(rgbAzul,LOW);
  digitalWrite(rgbVerde,HIGH);
  digitalWrite(rgbRojo,LOW);
  digitalWrite(pinMotor,LOW);
}

//Dentro de esta funcion estan las acciones que queremos realizar si la temperatura es Alta
void temperaturaAlta(){
  digitalWrite(rgbAzul,LOW);
  digitalWrite(rgbVerde,LOW);
  digitalWrite(rgbRojo,HIGH);
  digitalWrite(pinMotor,HIGH);
}

