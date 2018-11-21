/*
 *                    Universidad de Guanajuato
 *        División de Ingenierias Campus Irapuato Salamanca
 *                Maestria en Ingenieria Eléctrica
 *                
 *                Procesamiento Digital de señales
 *                  Septiembre - Diciembre 2018
 *                
 *                  Mendoza Pinto Gustavo David
 *                  
 *                  
 *   Programa para arduino que toma muestras de una senal de audio y las c
 */


 /* --------------------------------------------- Librerias a utilizar------------------------------------------*/

 #include<LedControl.h>                    // Control de Display Led
 #include<arduinoFFT.h>                   // Libreria que contiene la funci'on de la transforda rapida de Fourier


/*------------------------------------------------------------------------------------------------------------*/
arduinoFFT FFT = arduinoFFT();            // Se contruye el objeto para la transformada de la FFT

/*------------------------------------- variables que definen los parametros de camptura ----------------------*/
#define CHANNEL A0          
const uint16_t samples = 128; // Muestras a tomar
const double samplingFrecuency = 8000; // Frecuencia maxima de que se puede muestrear 4 kHz

/*--------------------------------- Arreglos y Variables internos para el muestreo ----------------------------*/
unsigned int sampling_period_us;
unsigned long microsecond;
double vReal[samples];                //arreglo a donde guardar las muestras tomadas del convertidor analogico digital
double vImag[samples];                // arrego donde se encuentran los valores imaginarios
uint16_t Frec[] = {2,3,4,6,8,9,11,12,13,14,15,17,19,21,40,60};
/*---------------- Variables para generar eje de las frecuencias en las matrices LED -------------------*/
//uint16_t K = 0;
//uint16_t R = 0;

LedControl Display = LedControl(12,11,10,2); //CLK pin 11, CS  pin 10, DIN pin 12,

void setup() {
  Display.shutdown(0,false);// se limpian display
  Display.shutdown(1,false);
  Display.setIntensity(0,8);
  Display.setIntensity(1,8);
  Display.clearDisplay(0);
  Display.clearDisplay(1);
  sampling_period_us = round (1000000*(1.0/samplingFrecuency));
}


void loop() {
  /*Muestreo*/
  for(int i = 0; i<samples; i++){
  microsecond = micros();
  vReal[i] = analogRead(CHANNEL);
  vImag[i] = 0;
  while(micros() < (microsecond + sampling_period_us)){
    // cixlo vasio de espera para la siguiente muestra
    /*empty loop*/
    }
  }

  FFT.Windowing(vReal,samples, FFT_WIN_TYP_RECTANGLE,FFT_FORWARD); // se crea ventaneo de funcion rectangular para la FFT
  FFT.Compute(vReal,vImag, samples, FFT_FORWARD);                  // se pasa al dominio de la frecuencias
  FFT.ComplexToMagnitude(vReal, vImag, samples);

  for(uint16_t j = 0; j < 8; j++){
      if((byte)vReal[Frec[j]]<10)
         Display.setRow(1,7-j,0);
      else 
         if((byte)vReal[Frec[j]]<30)
            Display.setRow(1,7-j,1);
         else 
            if((byte)vReal[Frec[j]]<50)
               Display.setRow(1,7-j,3);
            else 
               if((byte)vReal[Frec[j]]<70)
                  Display.setRow(1,7-j,7);
               else 
                  if((byte)vReal[Frec[j]]<90)
                     Display.setRow(1,7-j,15);
                  else 
                     if((byte)vReal[Frec[j]]<110)
                        Display.setRow(1,7-j,31);
                     else 
                        if((byte)vReal[Frec[j]]<130)
                           Display.setRow(1,7-j,63);
                        else 
                           if((byte)vReal[Frec[j]]<150)
                              Display.setRow(1,7-j,127);
                           else
                              if((byte)vReal[Frec[j]]<200)
                                 Display.setRow(1,7-j,255);   

   }
   for(uint16_t j = 0; j < 8; j++){
      if((byte)vReal[Frec[8+j]]<10)
         Display.setRow(0,7-j,0);
      else 
         if((byte)vReal[Frec[8+j]]<30)
            Display.setRow(0,7-j,1);
         else 
            if((byte)vReal[Frec[8+j]]<50)
               Display.setRow(0,7-j,3);
            else 
               if((byte)vReal[Frec[8+j]]<70)
                  Display.setRow(0,7-j,7);
               else 
                  if((byte)vReal[Frec[8+j]]<90)
                     Display.setRow(0,7-j,15);
                  else 
                     if((byte)vReal[Frec[8+j]]<110)
                        Display.setRow(0,7-j,31);
                     else 
                        if((byte)vReal[Frec[8+j]]<130)
                           Display.setRow(0,7-j,63);
                        else 
                           if((byte)vReal[Frec[8+j]]<150)
                              Display.setRow(0,7-j,127);
                           else
                              if((byte)vReal[Frec[8+j]]<200)
                                 Display.setRow(1,7-j,255);   
   }

}
