

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TEMPS_CYCLE_MAX 100000
#define TAILLE_INITIALE_OPERATIONS 10000


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


void repartirOperations(struct Graphe* graphe, struct Station* stations, int nbStations, int* tempsOperation, int* ordreBFS, int indexOrdre) {
    int sommetsEnOrdreBFS[graphe->nombreSommets];


    for (int i = 0; i < graphe->nombreSommets; i++) {
        int operation = sommetsEnOrdreBFS[i];
        bool operationPlacee = false;


        for (int j = 0; j < nbStations && !operationPlacee; j++) {
            if (stations[j].tempsCycle + tempsOperation[operation] <= TEMPS_CYCLE_MAX) {
                // verifier si on peut encore ajouter une operation
                if (stations[j].nbOperations == stations[j].capaciteMax) {
                    redimensionnerOperations(&stations[j], stations[j].capaciteMax * 2); // si la capacite max est atteinte alor sa la double
                }
                stations[j].operations[stations[j].nbOperations++] = operation;
                stations[j].tempsCycle += tempsOperation[operation];
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




int main() {


    // trouver le nombre de sommets a partir du fichier


    int nombreSommets = determinerNombreSommets("precedences.txt");
    if (nombreSommets == -1) {
        fprintf(stderr, "Erreur lors de la lecture du fichier.\n");
        return -1;
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




    return 0;
}
