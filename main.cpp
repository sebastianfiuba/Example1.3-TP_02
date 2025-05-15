#include "mbed.h"
#include "arm_book_lib.h"
//#include "gpio_api.h"


int main()
{
    /*

        Explicar por que es conveninete 
       DigitalIn gasDetector(D2);
       gasDetector.mode(PullDown);
    */

    gpio_t gasDetector;
    gpio_init_in_ex(&gasDetector, D2, PullDown);



    gpio_t overTempDetector;
    gpio_init_in_ex(&overTempDetector, D3, PullDown);

    gpio_t alarmOffButton;


    gpio_init_in(&alarmOffButton, BUTTON1);

    gpio_t alarmLed;


    gpio_init_out_ex(&alarmLed, LED1, OFF);
    /*
    DigitalIn overTempDetector(D3);
    DigitalIn alarmOffButton(BUTTON1);

    DigitalOut alarmLed(LED1);


    overTempDetector.mode(PullDown);
    */

    //alarmLed = OFF;

    bool alarmState = OFF;

    bool print_msg_1 = true;
    bool print_msg_2 = true;
    bool print_msg_3 = true;
    bool print_msg_4 = true;
    bool print_msg_5 = true;

    while (true) {

        if ( gpio_read(&alarmOffButton) ) {
            if(print_msg_3){
                printf("La alarma esta apagada por el boton\n");
                print_msg_1 = true;
                print_msg_2 = true;
                print_msg_3 = false;
                print_msg_4 = true;
                print_msg_5 = true;


            }       
            alarmState = OFF;   
        }
        else {
            if ( gpio_read(&gasDetector) || gpio_read(&overTempDetector) ) {
                alarmState = ON;
                
                    if(gpio_read(&overTempDetector)){
                        if (gpio_read(&gasDetector) == 1) {
                            if(print_msg_5){
                                printf("La alarma esta prendida, se detecta gas y se paso la temperatura\n");       
                                print_msg_5 = false;
                                print_msg_4 = true;                   
                                print_msg_3 = true;
                                print_msg_2 = true; 
                                print_msg_1 = true; 
                            }
                                
                        } 
                        else{
                            if(print_msg_4){
                                printf("La alarma esta prendida y solo se paso la temperatura\n");
                                print_msg_5 = true;
                                print_msg_4 = false;                   
                                print_msg_3 = true;
                                print_msg_2 = true; 
                                print_msg_1 = true;  


                            }
                                

                        }
                        
                        
                    }
                    else{
                        if(print_msg_1){
                            printf("La alarma esta prendida y solo se detecta gas\n");
                            print_msg_5 = true;
                            print_msg_4 = true;                   
                            print_msg_3 = true;
                            print_msg_2 = true; 
                            print_msg_1 = false;  
             
                    }
                  
                }
            }
            else {

                if(print_msg_2){
                    printf("La alarma esta apagada y no se detecta nada\n");
                    print_msg_1 = true;
                    print_msg_2 = false;
                    print_msg_3 = true;
                    print_msg_4 = true;
                    print_msg_5 = true;
                }       
                alarmState = OFF;
            }
           
        }
        gpio_write(&alarmLed, alarmState);
    }
}