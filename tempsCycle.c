#include "tempsCycle.h"


char *nomfichier(char nomdufichiertxt[100]){
    printf("saisir nom du fichier voulu : nom.txt\n");
    gets(nomdufichiertxt);
    fflush(stdin);
    return nomdufichiertxt;
}

int lectureNombreLignesFichier(FILE *fp,char *filename){
    printf("donner le nom du fichier liste operations\n");
    nomfichier(filename);
    fp= fopen(filename,"r");
    if (fp == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier.\n");
        exit(-1); // Code d'erreur
    }
    char ligne[100]; // Choisir une taille appropriée pour la ligne
    int nbligne=0;


    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        //printf("%s", ligne);
        nbligne+=1;
    }
    printf("le nombre de lignes est %d\n",nbligne);
    // Fermer le fichier
    fclose(fp);
    return nbligne;
}



void lectureValeursFichier(FILE *fp, int nombrelignes, t_operation *operation,char* filename){
    fp=fopen(filename,"r");
    if(fp==NULL){
        exit (-1);
    }
    for(int i=0;i<nombrelignes+0;i++){
        fscanf(fp,"%d %f",&operation[i].numeroOperation,&operation[i].dureeOperation);
        operation[i].rangOperation=i+1;
        operation[i].nombrelignes=nombrelignes;
        //printf("rang: %d\t num: %d\t %f\n",operation[i].rangOperation,operation[i].numeroOperation,operation[i].dureeOperation);
    }
    fclose(fp);
}

float lectureValeurTemps(FILE *fp,char*filename){
    float temp;
    printf("donner le nom du fichier pour le temps de cycle\n");
    filename= nomfichier(filename);
    fp=fopen(filename,"r");
    if(fp==NULL){
        exit (-1);
    }
    fscanf(fp,"%f",&temp);
    fclose(fp);
    return temp;
}

void tiret(){
    printf("-------------------\n");
}


void swap(t_operation * xp, t_operation * yp)
{
    t_operation temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//code bubblesort pris sur https://www.geeksforgeeks.org/bubble-sort/ et adapté à notre usage.

// An optimized version of Bubble Sort
void bubbleSort1(t_operation *operation, int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (operation[j].dureeOperation > operation[j + 1].dureeOperation) {
                swap(&operation[j], &operation[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}


void afficherlisteoperations(t_operation *operation){

    for(int i=0;i<operation[1].nombrelignes;i++){
        printf("rang:%d num: %d %f \n",operation[i].rangOperation,operation[i].numeroOperation,operation[i].dureeOperation);
    }
}

void afficheroperationunique(t_operation *operation,int i){
    printf("rang:%d num: %d %f groupe %d \n",operation[i].rangOperation,operation[i].numeroOperation,operation[i].dureeOperation,operation[i].groupeOperation);
}

void afficherlisteoperationsExtra(t_operation *operation){

    for(int i=0;i<operation[1].nombrelignes;i++){
        printf("rang:%d num: %d %f groupe %d \n",operation[i].rangOperation,operation[i].numeroOperation,operation[i].dureeOperation,operation[i].groupeOperation);
    }
}

void bubbleSort(t_operation *operation, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n-i; j++) {
            if (operation[j].dureeOperation < operation[j+1].dureeOperation) {
                swap(&operation[j], &operation[j+1]);
            }
        }
    }
}

void updateRangOperations(t_operation *operation){
    for(int i=0; i<operation[1].nombrelignes;i++){
        operation[i].rangOperation=i+1;
    }
    printf("les rangs ont ete mis a jour\n");
}

void updateSommeDureeOperationsPrecedentesSelonOrdre(t_operation *operation){

}


void regrouperParTempsCycleBrut(t_operation *operation, float tempsDeCycle){

    double somme=0;
    int groupement=1;
    for(int i=0;i<operation[i].nombrelignes;i++){
        operation[i].groupeOperation=groupement;
        if(somme>tempsDeCycle){
            i-=1;
            groupement+=1;//on recule de une etape des qu'on a franchi le seuil du temps cycle.
            printf("%lf\n",somme-operation[i].dureeOperation);
            somme=0;
        }
        somme+=operation[i].dureeOperation;
    }
    printf("%lf\n",somme);
}

void formerGroupesParGroupeTempsDeCycle(t_operation *operation){
    for(int i=1;i<operation[operation[1].nombrelignes].groupeOperation+1;i++){
        tiret();
        for(int j=0;j<operation[1].nombrelignes;j++){
            if(operation[j].groupeOperation==i){
                afficheroperationunique(operation,j);
            }

        }
    }

}

void remplirTableauDeGroupesParTempsDeCycle(t_operation** TabOperation,t_operation *operation,int nblignes){
    t_operation temp[nblignes+1];
    for(int i=1;i<operation[operation[1].nombrelignes].groupeOperation+1;i++){
        for(int j=0;j<operation[1].nombrelignes;j++){
            if(operation[j].groupeOperation==i){
                temp[j]=operation[j];
            }
            TabOperation[i]=temp;

        }
    }

}

int main() {
    FILE *fichier=NULL;
    FILE *fichiertemps=NULL;
    char nomdufichiertempsoperations[100];
    char nomdufichierTempsCycle[90];
    float tempsDeCycle=lectureValeurTemps(fichiertemps,nomdufichierTempsCycle);
    tiret();
    int nblignes = lectureNombreLignesFichier(fichier, nomdufichiertempsoperations);
    t_operation *listeoperations=(t_operation*)calloc((nblignes+1),sizeof(t_operation));
    //car on a besion d'un tableau de taille N+1 valeurs.
    lectureValeursFichier(fichier, nblignes, listeoperations, nomdufichiertempsoperations);
    tiret();
    afficherlisteoperations(listeoperations);
    //tiret();// pour faire un test//
    //printf("%d\t%f\nt cycle = %f s\n",listeoperations[4].numeroOperation,listeoperations[4].dureeOperation,tempsDeCycle);
    tiret();
    bubbleSort(listeoperations,nblignes);
    //afficherlisteoperations(listeoperations);
    //tiret();
    updateRangOperations(listeoperations);
    //afficherlisteoperations(listeoperations);
    //tiret();
    regrouperParTempsCycleBrut(listeoperations, tempsDeCycle);
    afficherlisteoperationsExtra(listeoperations);
    tiret();
    formerGroupesParGroupeTempsDeCycle(listeoperations);
    int nbGroupes=listeoperations[listeoperations[1].nombrelignes].groupeOperation;
    //printf("%d\n",nbGroupes);
    t_operation **tableauListesOperations=(t_operation**)calloc(nbGroupes*(nblignes+1),sizeof(t_operation));
    //tableau de listes d'operations ou la premiere case est la liste complete des operations (rangee dans un ordre quelconque).
    //remplirTableauDeGroupesParTempsDeCycle(tableauListesOperations,listeoperations,nbGroupes);
    //afficherlisteoperationsExtra(tableauListesOperations[1]);
    free(listeoperations);//vider espace memoire alloue
    free(tableauListesOperations);

    return 0;
}

///a voir ce qui est utile ou non afin de pouvoir faire fonctionner les programmes ensemble.
///coder une interface (switchcase)
///rassembler les programmes et regler les soucis de compatibilite
///mettre a jour le powerpoint