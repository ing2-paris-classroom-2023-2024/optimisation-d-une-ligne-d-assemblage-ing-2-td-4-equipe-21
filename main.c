#include "main.h"

///Partie contrainte exclusion Jean

void lire_fichier (char *nomFichier, char *nomFichier2, int paires [OPERATION_MAX * 2][2], int operations [OPERATION_MAX], int* nb_paires, int* nb_operations){

    /// Ouverture du fichier exclusions
    FILE * fichier = fopen(nomFichier,"r");

    // Blindage de la bonne lecture du fichier
    if (!fichier) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    else {

        // Affectation des paires dans un tableau
        for (int i = 0; !feof (fichier); i++) {

            int op1, op2;

            // Lecture du fichier
            fscanf(fichier,"%d %d", &op1, &op2);


            // Ordonnancement de la paire : [p1 p2] avec p1 < p2
            if (op1 > op2){
                paires [i][0] = op2;
                paires [i][1] = op1;
            }

            else {
                paires [i][0] = op1;
                paires [i][1] = op2;
            }


            // Compteur du nombre de paires
            *nb_paires += 1;
        }

    }

    // Fermeture du fichier
    fclose(fichier);


    /// Ouverture du fichier operations
    FILE * fichier2 = fopen(nomFichier2,"r");

    // Blindage de la bonne lecture du fichier
    if (!fichier2) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    else {

        // Affectation des operations dans un tableau
        for (int i = 0; !feof (fichier2); i++) {

            int opA;
            float opB;

            // Lecture du fichier
            fscanf(fichier2,"%d %f", &opA, &opB);


            // Affectation au tableau d'operations
            operations [i] = opA;

            *nb_operations += 1;

        }

    }

    // Fermeture du fichier
    fclose(fichier2);

}


void trier_operations (int paires [OPERATION_MAX * 2][2], int stations [STATION_MAX][OPERATION_MAX], const int operations [OPERATION_MAX], const int* nb_paires, const int* nb_operations) {

    // Initialisation du tableau des stations
    for (int i = 0; i < STATION_MAX; i++) {
        for (int j = 0; j < *nb_operations; j++) {
            stations[i][j] = 0;
        }
    }



    // Boucle principale : on parcourt les elements du tableau d'operations
    for (int i = 0; i < *nb_operations; i++) {

        // On affecte chaque valeur a la station 1, puis on les modifie si besoin
        stations [0][i] = operations [i];

        // i represente la position de valeur
        int valeur = operations[i];

        int valeur_interdite = 0;


        // On parcourt les differentes stations
        for (int e = 0; e < STATION_MAX; e++){

            // On parcourt les elements du tableau de paires
            for (int j = 0; j < *nb_paires; j++) {
                for (int k = 0; k < 2; k++) {


                    // On affecte les valeurs interdites
                    if (valeur == paires[j][k]) {


                        if (k == 0) {
                            valeur_interdite = paires[j][1];
                        }

                        if (k == 1) {
                            valeur_interdite = paires[j][0];
                        }


                        // On deplace les valeurs interdites si elles se trouvent dans une meme station
                        for (int l = 0; l < *nb_operations; l++) {

                            if (valeur_interdite == stations[e][l]) {

                                stations[e][i] = 0;
                                stations[e + 1][i] = valeur;

                            }
                        }
                    }
                }
            }
        }
    }


    // On supprime les doublons
    for (int i = 0; i < *nb_operations; i++){
        for (int j = 0; j < STATION_MAX; j++){

            if ((stations [j][i] != 0) && stations [j + 1][i] == 0){

                stations [j + 2][i] = 0;

            }
        }
    }
}


void afficher_stations (int stations [STATION_MAX][OPERATION_MAX], const int* nb_operations){

    printf("\n\n");

    // Affichage des stations et operations
    for (int i = 0; i < STATION_MAX; i++) {

        printf("\nStation %2d :", i + 1);

        for (int j = 0; j < *nb_operations - 1; j++) {

            if (stations [i][j] != 0){

                printf(" %2d", stations [i][j]);

            }
        }
    }
}



void exclusion() {

    int paires [OPERATION_MAX * 2][2]; // Tableau de paires interdites
    int operations [OPERATION_MAX]; // Tableau des operations
    char nom_fichier [50];
    char nom_fichier2 [50];
    int nb_paires = 0; // Nombre de paires
    int nb_operations = 0; // Nombre d'operations
    int stations [STATION_MAX][OPERATION_MAX]; // Tableau des stations contenant les operations


    // Recuperation des fichiers textes
    printf("\nEntrer le nom du fichier des exclusions : ");
    gets(nom_fichier);
    fflush(stdin);

    printf("\nEntrer le nom du fichier des operations : ");
    gets(nom_fichier2);
    fflush(stdin);


    lire_fichier(nom_fichier, nom_fichier2, paires, operations, &nb_paires, &nb_operations); ///Question : nom_fichier =! nom_fichier2?

    trier_operations (paires, stations, operations, &nb_paires, &nb_operations);

    afficher_stations (stations, &nb_operations);
    fflush(stdin);


    printf("\n\n");
    system("pause");
}

void exclusionSansAffichage(){
    int paires1 [OPERATION_MAX * 2][2]; // Tableau de paires1 interdites
    int operations1 [OPERATION_MAX]; // Tableau des operations1
    char nom_fichier1 [50];
    char nom_fichier21 [50];
    int nb_paires1 = 0; // Nombre de paires1
    int nb_operations1 = 0; // Nombre d'operations1
    int stations1 [STATION_MAX][OPERATION_MAX]; // Tableau des stations1 contenant les operations1


    // Recuperation des fichiers textes
    printf("\nEntrer le nom du fichier des exclusions : ");
    gets(nom_fichier1);
    fflush(stdin);

    printf("\nEntrer le nom du fichier des operations1 : ");
    gets(nom_fichier21);
    fflush(stdin);


    lire_fichier(nom_fichier1, nom_fichier21, paires1, operations1, &nb_paires1, &nb_operations1); ///Question : nom_fichier1 =! nom_fichier21?

    trier_operations (paires1, stations1, operations1, &nb_paires1, &nb_operations1);

    afficher_stations (stations1, &nb_operations1);
    fflush(stdin);


    printf("\n\n");
    system("pause");

}

///FIN partie contrainte exclusion Jean


/// partie temps de cycle Antoine
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
        printf("rang:%d num: %d %f groupe %d tps %lf \n",operation[i].rangOperation,operation[i].numeroOperation,operation[i].dureeOperation,operation[i].groupeOperation,operation[i].sommeDureeOperationsPrecedentes);
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
    double sommeIndependante=0;
    int groupement=1;
    for(int i=0;i<operation[i].nombrelignes;i++){
        operation[i].groupeOperation=groupement;
        sommeIndependante+=operation[i].dureeOperation;
        operation[i].sommeDureeOperationsPrecedentes=sommeIndependante;
        if(somme>tempsDeCycle){
            i-=1;
            groupement+=1;//on recule de une etape des qu'on a franchi le seuil du temps cycle.
            operation[i].groupeOperation=groupement;
            printf("le temps de cycle pour la station est : %lf\n",somme-operation[i].dureeOperation);
            somme=0;
        }
        somme+=operation[i].dureeOperation;
    }
    printf("le temps de cycle pour la station est : %lf\n",somme);
}

void calculerTempsdeCycleParGroupe(t_operation* operation, int numeroGroupe,double tempsDeCycleDuGroupe){
    for(int i=0;i<operation[1].nombrelignes+1;i++){
        if(operation[i].groupeOperation==numeroGroupe){
            tempsDeCycleDuGroupe+=operation[i].dureeOperation;
        }
    }
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

void tableauDetempsDeCycleParGroupes(t_operation* operation,double* tableauTemps){

    for(int i =0;i<operation[operation[1].nombrelignes].groupeOperation;i++){
        calculerTempsdeCycleParGroupe(operation,i+1,tableauTemps[i]);
    }
}

void afficherUniqueGroupesDeTempsDeCycle(t_operation* operation, int groupe, int nombrelignes){
    printf("groupe n= %d : \n ",groupe);
    for(int j=0;j<nombrelignes+1;j++){
        if(operation[j].groupeOperation==groupe){
            printf("%d",operation[j].numeroOperation);
            printf(" ");
        }
    }
    printf("\n");
}

void afficherTousGroupesDeTempsDeCycle(t_operation* operation, int nbgroupes, int nlignes){
    for(int i=1;i<nbgroupes+1;i++){
        afficherUniqueGroupesDeTempsDeCycle(operation,i,nlignes);
        printf("\n");
    }
}

void optimiserGroupes(t_operation* operation){



}
void afficherEtAssocier_stations (int stations [STATION_MAX][OPERATION_MAX], const int* nb_operations, t_operation* operation, int nblignes){

    printf("\n\n");

    // Affichage des stations et operations
    for (int i = 0; i < STATION_MAX; i++) {

        printf("\nStation %2d :", i + 1);

        for (int j = 0; j < *nb_operations - 1; j++) {

            if (stations [i][j] != 0){

                printf(" %2d (%d %d)", stations [i][j],i,j);
                for(int p=0; p<nblignes;p++){
                    if(operation[p].numeroOperation==stations[i][j]){
                        operation[p].station=i+1;
                    }
                }



            }
        }
    }
}


void tempsCycle() {
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
    //afficherlisteoperations(listeoperations);
    //tiret();// pour faire un test//
    //printf("%d\t%f\nt cycle = %f s\n",listeoperations[4].numeroOperation,listeoperations[4].dureeOperation,tempsDeCycle);
    bubbleSort(listeoperations,nblignes);
    //afficherlisteoperations(listeoperations);
    //tiret();
    updateRangOperations(listeoperations);
    //afficherlisteoperations(listeoperations);
    //tiret();
    regrouperParTempsCycleBrut(listeoperations, tempsDeCycle);
    tiret();
    afficherlisteoperationsExtra(listeoperations);
    tiret();
    //formerGroupesParGroupeTempsDeCycle(listeoperations);
    int nbgroupes = listeoperations[listeoperations[1].nombrelignes].groupeOperation;
    //int nbGroupes=listeoperations[listeoperations[1].nombrelignes].groupeOperation;
    //printf("%d\n",nbGroupes);
    //t_operation **tableauListesOperations=(t_operation**)calloc(nbGroupes*(nblignes+1),sizeof(t_operation));
    //tableau de listes d'operations ou la premiere case est la liste complete des operations (rangee dans un ordre quelconque).
    //remplirTableauDeGroupesParTempsDeCycle(tableauListesOperations,listeoperations,nbGroupes);
    //afficherlisteoperationsExtra(tableauListesOperations[1]);
    //double *tableauTemps=(double*)calloc(listeoperations[listeoperations[1].nombrelignes].groupeOperation+1, sizeof(double ));
    //tableauDetempsDeCycleParGroupes(listeoperations,tableauTemps);
    //calculerTempsdeCycleParGroupe(listeoperations,1,tableauTemps[2]);
    //printf("%lf\n",tableauTemps[2]);
    afficherUniqueGroupesDeTempsDeCycle(listeoperations, 1, nblignes);
    tiret();
    afficherUniqueGroupesDeTempsDeCycle(listeoperations, 2, nblignes);
    tiret();


    //printf("%lf\n",calculerTempsdeCycleParGroupe(listeoperations,listeoperations[1].groupeOperation));
    free(listeoperations);//vider espace memoire alloue
    //free(tableauListesOperations);
}




/// FIN partie temps de cycle Antoine



void contrainteExclusionEttempsCycle() {
    exclusionSansAffichage();
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
    bubbleSort(listeoperations,nblignes);
    updateRangOperations(listeoperations);
    regrouperParTempsCycleBrut(listeoperations, tempsDeCycle);
    afficherlisteoperationsExtra(listeoperations);
    tiret();
    tiret();
    tiret();
    afficherUniqueGroupesDeTempsDeCycle(listeoperations, 1, nblignes);
    tiret();
    afficherUniqueGroupesDeTempsDeCycle(listeoperations, 2, nblignes);
    tiret();
    free(listeoperations);//vider espace memoire alloue
}
/// partie Loup et Chris


//
// Created by perron on 12/3/2023.
//


void dfs(int node) {
    visited[node] = true;


    for (int i = 0; i < n; i++) {
        if (strcmp(operations[node].op, operations[i].op) == 0 && !visited[i]) {
            dfs(i);
        }
    }
}

void precedence2() {

    FILE *file;
    char filename[] = "pre.txt"; // Nom du fichier texte
    int count = 0;


    // Ouverture du fichier en mode lecture
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(-1);
    }


    // Lecture des opérations uniques du fichier
    while (fscanf(file, "%s", operations[count].op) == 1 && count < MAX_OPERATIONS) {
        count++;
    }


    // Fermeture du fichier
    fclose(file);


    n = count;


    // Initialisation du tableau de visite
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }


    printf("Ordre des opérations respectant la contrainte de précédence :\n");


    // Appliquer DFS pour obtenir l'ordre des opérations uniques
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }


    // Affichage des opérations uniques dans l'ordre
    printf("%s", operations[0].op);
    for (int i = 1; i < n; i++) {
        if (strcmp(operations[i].op, operations[i - 1].op) != 0) {
            printf("\n%s", operations[i].op);
        }
    }

}

///partie avec revision


// Un noeud ds la liste d'adjacence
struct NoeudAdjacence {
    int destination;
    struct NoeudAdjacence* suivant;
};

//  liste d adjacence
struct ListeAdjacence {
    struct NoeudAdjacence* tete;
};

// Structure representer un graphe
struct Graphe {
    int nombreSommets;
    struct ListeAdjacence* tableau;
};

struct Station {
    int* operations;
    int nbOperations;
    int tempsCycle;
    int capaciteMax;
};

struct Operation {
    int id;
    int tempsExecution;
};


// Fonction pour creer un nouveau noeud de la liste d adjacence

struct NoeudAdjacence* creerNoeudAdjacence(int destination) {
    struct NoeudAdjacence* nouveauNoeud = (struct NoeudAdjacence*) malloc(sizeof(struct NoeudAdjacence));
    nouveauNoeud->destination = destination;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

// Fonction creation graphe de nombreSommets sommets

struct Graphe* creerGraphe(int nombreSommets) {
    struct Graphe* graphe = (struct Graphe*) malloc(sizeof(struct Graphe));
    graphe->nombreSommets = nombreSommets;

    // creer  tableau de listes d adjacence
    graphe->tableau = (struct ListeAdjacence*) malloc(nombreSommets * sizeof(struct ListeAdjacence));

    // Initialiser chaque liste d adjacence comme vide
    for (int i = 0; i < nombreSommets; ++i) {
        graphe->tableau[i].tete = NULL;
    }

    return graphe;
}

// Fonction pour lire le fichier et determiner le nbre max de sommet

int determinerNombreSommets(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    int maxSommet = 0;
    int sommet1, sommet2;
    while (fscanf(fichier, "%d %d", &sommet1, &sommet2) == 2) {
        if (sommet1 > maxSommet) maxSommet = sommet1;
        if (sommet2 > maxSommet) maxSommet = sommet2;
    }

    fclose(fichier);
    return maxSommet + 1; // +1 si les sommet commence a 0
}

// Ajoute une arret au graphe oriente

void ajouterArete(struct Graphe* graphe, int source, int destination, int oriente) {

    // Ajout de l arete source -> destination

    struct NoeudAdjacence* nouveauNoeud = creerNoeudAdjacence(destination);
    nouveauNoeud->suivant = graphe->tableau[source].tete;
    graphe->tableau[source].tete = nouveauNoeud;

    // Pour les graphe non oriente : sa ajoute l arrete inverse

    if (!oriente) {
        nouveauNoeud = creerNoeudAdjacence(source);
        nouveauNoeud->suivant = graphe->tableau[destination].tete;
        graphe->tableau[destination].tete = nouveauNoeud;
    }
}


// Une fonction pour afficher la representation de la liste d adjcence du graphe

void afficherGraphe(struct Graphe* graphe) {
    for (int v = 0; v < graphe->nombreSommets; ++v) {
        struct NoeudAdjacence* parcours = graphe->tableau[v].tete;
        printf("\n Liste d'adjacence du sommet %d\n tete ", v);
        while (parcours) {
            printf("-> %d", parcours->destination);
            parcours = parcours->suivant;
        }
        printf("\n");
    }
}

// Fonction pour lire le fichier de contraintes de precedence et construire le graphe

void lireContraintesPrecedence(const char* nomFichier, struct Graphe* graphe, int oriente) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    int source, destination;
    while (fscanf(fichier, "%d %d", &source, &destination) == 2) {
        ajouterArete(graphe, source, destination, oriente);
    }

    fclose(fichier);
}

void trouverSommetSansPredecesseurs(struct Graphe* graphe, int* sansPredecesseur) {
    for (int i = 0; i < graphe->nombreSommets; i++) {
        sansPredecesseur[i] = 1;  // Initialiser tous les sommets  n ayant pas de predecesseurs
    }

    for (int i = 0; i < graphe->nombreSommets; i++) {
        struct NoeudAdjacence* temp = graphe->tableau[i].tete;
        while (temp != NULL) {
            sansPredecesseur[temp->destination] = 0;  // Marquer les sommets ayant des predecessurs
            temp = temp->suivant;
        }
    }
}


void BFS(struct Graphe* graphe, int sommetDepart, int* visite, int* ordreBFS, int* indexOrdre){

    // creation d une file d attente pour le BFS
    int* file = (int*) malloc(graphe->nombreSommets * sizeof(int));
    int tete = 0, queue = 0;

    // Ajout du sommet de depart a la file et sa marque comme visiter
    file[queue++] = sommetDepart;
    visite[sommetDepart] = 1;

    while (tete < queue) {
        int sommetActuel = file[tete++];
        ordreBFS[(*indexOrdre)++] = sommetActuel;

        // Affichage du sommet actuel
        printf("Visite du sommet %d\n", sommetActuel);

        struct NoeudAdjacence* temp = graphe->tableau[sommetActuel].tete;
        while (temp) {
            int adj = temp->destination;
            if (!visite[adj]) {
                file[queue++] = adj;
                visite[adj] = 1;  //noeud devient visiter
                printf("Ajout du sommet %d a la file\n", adj);
            }
            temp = temp->suivant;
        }
    }

    free(file);
}

struct Station* initialiserStations(int nombreStations) {
    struct Station* stations = malloc(nombreStations * sizeof(struct Station));
    for (int i = 0; i < nombreStations; i++) {
        stations[i].operations = malloc(TAILLE_INITIALE_OPERATIONS * sizeof(int));
        stations[i].nbOperations = 0;
        stations[i].tempsCycle = 0;
        stations[i].capaciteMax = TAILLE_INITIALE_OPERATIONS;
    }
    return stations;
}
// Fonction pour redimensionner le tableau des operation d une station

void redimensionnerOperations(struct Station* station, int nouvelleTaille) {
    int* temp = realloc(station->operations, nouvelleTaille * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Erreur de réallocation mémoire.\n");
        exit(EXIT_FAILURE);

    }
    station->operations = temp;
    station->capaciteMax = nouvelleTaille;
}

void repartirOperations(struct Graphe* graphe, struct Station* stations, int nbStations, int* tempsOperation1, int* ordreBFS, int indexOrdre) {
    int sommetsEnOrdreBFS[graphe->nombreSommets];

    for (int i = 0; i < graphe->nombreSommets; i++) {
        int operation = sommetsEnOrdreBFS[i];
        bool operationPlacee = false;

        for (int j = 0; j < nbStations && !operationPlacee; j++) {

            if (stations[j].tempsCycle + tempsOperation1[operation] <= TEMPS_CYCLE_MAX) {
                // verifier si on peut encore ajouter une operation
                if (stations[j].nbOperations == stations[j].capaciteMax) {
                    redimensionnerOperations(&stations[j], stations[j].capaciteMax * 2); // si la capacite max est atteinte alor sa la double
                }
                stations[j].operations[stations[j].nbOperations++] = operation;
                stations[j].tempsCycle += tempsOperation1[operation];
                operationPlacee = true;
            }
        }

        if (!operationPlacee) {
            // si pa de station dispo pour acceuillir une operation
            printf("Erreur : Aucune station existante ne peut accueillir l'opération %d.\n", operation);
            // Code pour ce probleme:
        }
    }
}

void afficherResultats(struct Station* stations, int nbStations) {
    for (int i = 0; i < nbStations; ++i) {
        printf("Station %d: ", i);
        for (int j = 0; j < stations[i].nbOperations; ++j) {
            printf("%d ", stations[i].operations[j]);
        }
        printf("\n");
    }
}


void precedence() {

    // trouver le nombre de sommets a partir du fichier

    int nombreSommets = determinerNombreSommets("precedences.txt");
    if (nombreSommets == -1) {
        fprintf(stderr, "Erreur lors de la lecture du fichier.\n");
        exit(-1);
    }

    // creer le graphe

    struct Graphe* graphe = creerGraphe(nombreSommets);
    lireContraintesPrecedence("precedences.txt", graphe, 1);
    afficherGraphe(graphe);

    // Initialiser les variables necessaire

    int* sansPredecesseur = (int*) calloc(nombreSommets, sizeof(int));
    int* visite = (int*) calloc(nombreSommets, sizeof(int));
    int* ordreBFS = (int*) malloc(nombreSommets * sizeof(int));
    int indexOrdre = 0;

    // Initialiser les temps d opération

    int tempsOperation[nombreSommets];
    for (int i = 0; i < nombreSommets; i++) {
        tempsOperation[i] = 10;
    }

    // Calcul du nbre total de temps d operation

    int tempsTotalOperation = 0;
    for (int i = 0; i < nombreSommets; i++) {
        tempsTotalOperation += tempsOperation[i];
    }

    // executer le BFS a partir de chaque sommet qui na pas de predecessur

    for (int i = 0; i < nombreSommets; i++) {
        if (!sansPredecesseur[i]) {
            BFS(graphe, i, visite, ordreBFS, &indexOrdre);
        }
    }
    // Estimation du nbre de stations

    int nombreStations = tempsTotalOperation / TEMPS_CYCLE_MAX;
    if (tempsTotalOperation % TEMPS_CYCLE_MAX != 0) {
        nombreStations++;
    }

    // Initialiser les stations

    struct Station* stations = initialiserStations(nombreStations);

    // Répartir les operations

    repartirOperations(graphe, stations, nombreStations, tempsOperation, ordreBFS, indexOrdre);

    // Afficher les resultats

    afficherResultats(stations, nombreStations);

    // liberation de la memoire
    free(sansPredecesseur);
    free(visite);
    free(ordreBFS);

}

////FIN partie Loup et Chris


///construire l'interface dans le main

int main(){
    int selection=0;
    while(selection==0){
        printf("bienvenue dans notre programme d'optimisation, veuillez choisir un programme:\n");
        printf("1 contrainte exclusion \n 2 contrainte precedence \n 3 temps de cycle \n 4 contrainte exclusion et temps cycle \n 5 contrainte exclusion et de precedence \n 6 contrainte precedence2 et temps de cycle \n");
        fflush(stdin);
        scanf("%d",&selection);
    }
    switch (selection) {
        case 1:
            tiret();
            fflush(stdin);
            exclusion();
            break;
        case 2:
            tiret();
            fflush(stdin);
            precedence();
            break;
        case 3:
            tiret();
            fflush(stdin);
            tempsCycle();
            break;
        case 4:
            tiret();
            fflush(stdin);
            contrainteExclusionEttempsCycle();
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            exit(-1);
            break;
    }
    return 1;
}




///a voir ce qui est utile ou non afin de pouvoir faire fonctionner les programmes ensemble.
///coder une interface (switchcase)
///rassembler les programmes et regler les soucis de compatibilite
///mettre a jour le powerpoint