/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: mario
 *
 * Created on 20 de febrero de 2021, 1:41
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


int doMenu(){

    int opc = menuPrint();
    printf("\n\n");
    switch(opc){
        case 1: 
            printf("Caso 1 seleccionado.\n");
            
            break;
        case 2: 
            printf("Caso 2 seleccionado.\n");
            
            break;
        default:
            printf("Caso DEFAULT selected.\n");
    
    }
    
    
    return 1;
}

int menuPrint(){
    
    int opc;
    do{
        printf("\n\nOpciones\n");
        printf("\n1. Encender servidor. \n");
        printf("2. Apagar servidor. \n");
        printf("0. Salir \n");
        printf("\t Elija:\t");
        scanf("%d", &opc);
    } while (opc < 0 || opc > 2 );

    return opc;
}

int main(int argc, char** argv) {
    
    doMenu();
   

     
    //system("ls -l");
    return (EXIT_SUCCESS);
}



