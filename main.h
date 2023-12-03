//
// Created by abouv on 02/12/2023.
//

////Fichier Header regroupant tous les sous programmes

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING_2_TD_4_EQUIPE_21_MAIN_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING_2_TD_4_EQUIPE_21_MAIN_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>

#define OPERATION_MAX 50
#define STATION_MAX 10

typedef struct operation{
    int numeroOperation;//nomenclature operation
    float dureeOperation;//duree operation
    int rangOperation;//rang dans l'ordre de l'operation (variable)
    int operationMarquee;//si besoin de marquage
    int groupeOperation;//Groupe dans lequel appartient l'operation
    int nombrelignes;//constant donne le nb d'operations dans la liste donnee
    double sommeDureeOperationsPrecedentes;//donne le temps en amont de cette operation (depend du rang)
}t_operation;




#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING_2_TD_4_EQUIPE_21_MAIN_H
