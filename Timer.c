#include<xc.h>
#define _XTAL_FREQ 4000000
// CONFIG
#pragma config FOSC = HS       
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config CP = ON          

unsigned short i=0,ss=0,mm=0,s1=0,m1=0,o=0,t=0,h=0,th=0,j=0,k=0,count=0,countm=45,a=0,b=0,l=0,l1=0,l2=0,l3=0,e=0,s=0;

unsigned short mask(unsigned short num) {  //returns Hexa value of number
  switch (num) {
    case 0 : return 0x81;
    case 1 : return 0xCF;
    case 2 : return 0x92;
    case 3 : return 0x86;
    case 4 : return 0xCC;
    case 5 : return 0xA4;
    case 6 : return 0xA0;
    case 7 : return 0x8F;
    case 8 : return 0x80;
    case 9 : return 0x8C;
  } //case end
}
void thousands()
{
    RC7=0;
    RC6=1;
    RC5=1;
    RC4=1;
}
void hundreds()
{
    RC7=1;
    RC6=0;
    RC5=1;
    RC4=1;
}
void tens()
{
    RC7=1;
    RC6=1;
    RC5=0;
    RC4=1;
}
void ones()
{
    RC7=1;
    RC6=1;
    RC5=1;
    RC4=0;
}
void ledonoff()  //on off led after 1 second
{
    RC2=1;
    __delay_ms(2);
    RC2=0;
    __delay_ms(2);
}
void cal()
{
    o = s1%10;  // Extract Ones Digit
    t = (s1/10)%10; // Extract Tens Digit
    h = m1%10;  // Extract hundreds Digit
    th = (m1/10)%10; // Extract thousands Digit
   
    
}
void display()
{
    for (j = 0; j<=115; j++)
    {
        if(s1==0 && m1==0)
        {
           break; 
        }
        if(s1%2==0)
            RC2=1;
        else
            RC2=0;
        if(m1==0 && s1<=30 && s1%2==0)
            RC3=1;
        else RC3=0;
        RC1=1;
     ones();
     PORTB=mask(o);
     __delay_ms(2);
     tens();
     PORTB=mask(t);
     __delay_ms(2);
     hundreds();
     PORTB=mask(h);
     __delay_ms(2);
     thousands();
     PORTB=mask(th);
     __delay_ms(2);
     a=check();
     if(a==1||a==12)
             {s1=0;
             m1=1;
             cal();
             for (l = 0; l<=80; l++)
             {
              ones();
              PORTB=mask(o);
              __delay_ms(2);
              tens();
              PORTB=mask(t);
              __delay_ms(2);
              hundreds();
              PORTB=mask(h);
              __delay_ms(2);
              thousands();
              PORTB=mask(th);
               __delay_ms(2);
             }
            countm=0;
             count=60;
             }
     else  if(a==3)
             {s1=0;
             m1=3;
             cal();
             for (l1 = 0; l1<=80; l1++)
             {
              ones();
              PORTB=mask(o);
              __delay_ms(2);
              tens();
              PORTB=mask(t);
              __delay_ms(2);
              hundreds();
              PORTB=mask(h);
              __delay_ms(2);
              thousands();
              PORTB=mask(th);
               __delay_ms(2);
             }
            countm=2;
             count=60;
             }
     else if(a==5)
             {s1=0;
             m1=5;
             cal();
             for (l2 = 0; l2<=80; l2++)
             {
              ones();
              PORTB=mask(o);
              __delay_ms(2);
              tens();
              PORTB=mask(t);
              __delay_ms(2);
              hundreds();
              PORTB=mask(h);
              __delay_ms(2);
              thousands();
              PORTB=mask(th);
               __delay_ms(2);
             }
            countm=4;
             count=60;
             }
     else if(a==10)
             {s1=0;
             m1=10;
             cal();
             for (l3 = 0; l3<=80; l3++)
             {
              ones();
              PORTB=mask(o);
              __delay_ms(2);
              tens();
              PORTB=mask(t);
              __delay_ms(2);
              hundreds();
              PORTB=mask(h);
              __delay_ms(2);
              thousands();
              PORTB=mask(th);
               __delay_ms(2);
             }
            countm=9;
             count=60;
             }
     else if (a==11)
     {
        
         countm=0;
         count=1;
                
     }
     
   
         
    
     
    }
    
}

int check()
{
    if(RA0==0)
    {
       b=1; 
    }else if(RA1==0)
    {
       b=3; 
    }else if(RA2==0)
    {
       b=5; 
    }else if(RA3==0)
    {
       b=10; 
    }
    else if(RA4==0)
    {
        b=11;
        
    }
   
    else b=0;
    return b;
}
void countdown()
{ 
     do
     {
     for(count=59;count>=0;count--) 
     {
         
         if((count<=59)&&(count>=0))
         {
         
         s1=count;
         m1=countm;
         cal();
         display();
         
         }
      
          
         else
             break;
     }
     
     if(countm==0)
         break;
     countm--;
    }while(countm>=0);
    RC3=0; 
    RC1=0;
    PORTB=0xFF;
}
    

void process()
{  e=0;
    while(1)
    {
        e++;
        if(e<=10000)
            RC2=1;
        else if(e>10000&&e<=20000)
            RC2=0;
            
        if(e==20001)
            e=0;
        
        
        if(RA0==0)
        {    
             s1=0;
             m1=1;
             cal();
             display();
             countm=0;
             countdown();
        }
        if(RA1==0)
        {
             s1=0;
             m1=3;
             cal();
             display();
             countm=2;
             countdown();
        }
        if(RA2==0)
        {
             s1=0;
             m1=5;
             cal();
             display();
             countm=4;
             countdown();
        }
        if(RA3==0)
        {
             s1=0;
             m1=10;
             cal();
             display();
             countm=9;
             countdown();
        }
        if(RA4==0)
        {
             s1=0;
             m1=1;
             cal();
             while(1)
             {
             ones();
     PORTB=mask(o);
     __delay_ms(2);
     tens();
     PORTB=mask(t);
     __delay_ms(2);
     hundreds();
     PORTB=mask(h);
     __delay_ms(2);
     thousands();
     PORTB=mask(th);
     __delay_ms(2);
              if(RA4==1)
                  break;
             }
             countm=0;
             countdown();
              }
        
    }

}
void main()
{
    TRISB=0;
    RB0=RB1=RB2=RB3=RB4=RB5=RB6=0;
    TRISC=0;
    TRISA0=1;  //A0 button is input
    TRISA1=1;  //A1 button is input
    TRISA2=1;  //A2 button is input
    TRISA3=1;  //A3 button is input
    TRISA4=1;  //A4 button is input
    RC1=RC2=RC3=0;
    RC4=RC5=RC6=RC7=1;
    ADCON1=0x06;
    RA0=1; //A0 is off
    RA1=1; //A1 is off
    RA2=1; //A2 is off
    RA3=1; //A3 is off
    RA4=1; //A4 is off
    for(i=0;i<45;i++)
    {    RC2=1;
         thousands();
         PORTB=mask(8);
         __delay_ms(2);
         hundreds();
         PORTB=mask(8);
         __delay_ms(2);
         tens();
         PORTB=mask(8);
         __delay_ms(2);
         ones();
         PORTB=mask(8);
         __delay_ms(2);
    }
    PORTB=0xFF;
    process();
}

