/*
Name: Raju Khadka
Maximum Power Point Tracker
Project Lab 2
Texas Tech University 

For this system, MSP430 is integrated with the LabVIEW program, 
so that the sampling of datas and calculation can be performed easily. 
The microcontroller is coded using IAR Embedded System and the code is 
written to sense the analog voltage of the battery, voltage from the 
solar panel, and current from the solar panel.  And finally the sensed
 data are sent to the labVIEW through the USB.


*/

#include <msp430f5529.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


char *big_string;
char Current1[6];
char Current2[6];
char Current3[6];
  
int counter=0;
int senddata=0;
int value1;
int value2;
int value3;

float C_value1;
float C_value2;
float C_value3;



int V1;
int V2;
int V3;


void Select_ADC(void);
void S_UART(void);

void ADC_Value1(int);
void ADC_Value2(int);
void ADC_Value3(int);

void Initialize_Timer(void);
void Serial(void);

void Select_ADC(void)
{
  //configure A0,A1,A2 pin for function mode
  P6SEL |= BIT0|BIT1|BIT2;
  REFCTL0 &= ~REFMSTR;  //enables reference generator
  ADC12CTL0 = ADC12SHT0_9|ADC12MSC|ADC12REFON|ADC12REF2_5V|ADC12ON;
  ADC12CTL1 = ADC12SHP|ADC12CONSEQ_1;
   
  ADC12MCTL0 = ADC12SREF_1|ADC12INCH_0;
  ADC12MCTL1 = ADC12SREF_1|ADC12INCH_1;
  ADC12MCTL2 = ADC12SREF_1|ADC12INCH_2|ADC12EOS;
  ADC12IE = ADC12IE2;
  
      
  ADC12CTL0 |= ADC12ENC+ADC12SC;
  senddata = 1;

 
}

void S_UART(void)
{
  P4SEL |=0X30;                 //p4.4,5 = USCI_A! TXD/RXD 0011 0000
  UCA1CTL1 |= UCSWRST;           // state machine in reset
  UCA1CTL1 |=UCSSEL_1;          // select 32768 Hz
  UCA1BR0 =3;                   // 9600 Baud Rate
  UCA1BR1 =0X00;                // select 32768 Hz
  UCA1MCTL =0X06;               // Modulation UCBRSx=3, UCBRFx=3
  
  UCA1CTL0=0X00;
  UCA1CTL1 &= ~UCSWRST;         //Reset or putting USCI in opereation mode
}


void ADC_Value1 (int Data1)
  {
    Current1[0] = (Data1/1000)+48;
    Current1[1] = '.';
    Current1[2] = ((Data1%1000)/100)+48;
    Current1[3] = ((Data1%1000%100)/10)+48;
    Current1[4] = ((Data1%1000%100%10))+48;
    Current1[5]=' ';

  }
void ADC_Value2 (int Data2)
  {  
    Current2[0] = (Data2/1000)+48;
    Current2[1] = '.';
    Current2[2] = ((Data2%1000)/100)+48;
    Current2[3] = ((Data2%1000%100)/10)+48;
    Current2[4] = ((Data2%1000%100%10))+48;
    Current2[5]= ' ';
    
  }

void ADC_Value3 (int Data3)
  {

    Current3[0] = (Data3/1000)+48;
    Current3[1] = '.';
    Current3[2] = ((Data3%1000)/100)+48;
    Current3[3] = ((Data3%1000%100)/10)+48;
    Current3[4] = ((Data3%1000%100%10))+48;
    Current3[5]=' ';
  }   

void Initialize_Timer(void)
{
TA0CTL = TASSEL_1|MC_1+ID_0; //counts to TA0CCR0, and source from ACLK
TA0CCR0 = 32768-1; //5 seconds count=5000/0.03 (Tperiod of ACLK = 0.03)
TA0CCTL0 = CCIE; 
}
  

void Serial(void)
{
    senddata =0;
  volatile int i=0;
   for(i = 0;i<strlen(big_string);i++) //send until end of data
  {
    UCA1TXBUF = big_string[i];
    while (UCA1STAT&UCBUSY);
  }
    UCA1TXBUF =0X0a;
    while (UCA1STAT&UCBUSY);
    UCA1TXBUF =0X0d;
    while (UCA1STAT&UCBUSY);  

}

int main(void)
{
  WDTCTL =WDTPW +WDTHOLD;                        //stop watchdog timer
  
  Initialize_Timer();
  Select_ADC();                                 //Enable ADC pin    
  S_UART();  //Initialize UART
 __enable_interrupt();
  while(1)
  {
    
  
  }                     
}

#pragma vector= TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{ 
  counter++;
  if(counter == 5)
  {
    ADC12CTL0 |= ADC12ENC|ADC12SC;
    senddata=1;
    counter =0;
  }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
 
  switch (__even_in_range(ADC12IV,ADC12IV_ADC12IFG15))
  {
 case ADC12IV_ADC12IFG2:
    ADC12CTL0 &= ~ADC12ENC;
    value1 = ADC12MEM0 & 0x0FFF;         // Keep only 12bits
    value2 = ADC12MEM1 & 0x0FFF;
    value3 = ADC12MEM2 & 0x0FFF;
         
    C_value1=((value1*2.5)/4095);
    V1=C_value1*1000;
    //sprintf(Current1, "%f", C_value1);
    
    C_value2=((value2*2.5)/4095);
    V2=C_value2*1000;
    
    C_value3=((value3*2.5)/4095);
    V3=C_value3*1000;
    
    
    ADC_Value1(V1);                  //convert from decimal to ASCII                    
    ADC_Value2(V2);
    ADC_Value3(V3);
    
    
  big_string=(char*)malloc(18* sizeof(char)); 
  
  strcpy(big_string,Current1);
    
    Serial();
   free(big_string);
  
    
    break;
  default : break;
  }
}
