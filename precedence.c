//
// Created by perron on 12/3/2023.
//


#include "pre.h"
Operation operations[MAX_OPERATIONS];
bool visited[MAX_OPERATIONS];
int n;


void dfs(int node) {
    visited[node] = true;


    for (int i = 0; i < n; i++) {
        if (strcmp(operations[node].op, operations[i].op) == 0 && !visited[i]) {
            dfs(i);
        }
    }
}


#include "pre.h"
int main() {
    Operation operations[MAX_OPERATIONS];
    bool visited[MAX_OPERATIONS];
    int n;
    FILE *file;
    char filename[] = "pre.txt"; // Nom du fichier texte
    int count = 0;


    // Ouverture du fichier en mode lecture
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
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


    return EXIT_SUCCESS;
}


/*
#include "pre.h"


Operation operations[MAX_OPERATIONS];
bool visited[MAX_OPERATIONS];
int n;


void dfs(int node) {
   visited[node] = true;


   for (int i = 0; i < n; i++) {
       if (strcmp(operations[node].op2, operations[i].op1) == 0 && !visited[i]) {
           dfs(i);
       }
   }


   printf("%s %s\n", operations[node].op1, operations[node].op2);
}


int main() {
   FILE *file;
   char filename[] = "pre.txt"; // Nom du fichier texte
   int count = 0;


   // Ouverture du fichier en mode lecture
   file = fopen(filename, "r");
   if (file == NULL) {
       perror("Erreur lors de l'ouverture du fichier");
       return EXIT_FAILURE;
   }


   // Lecture des opérations du fichier
   while (fscanf(file, "%s %s", operations[count].op1, operations[count].op2) == 2 && count < MAX_OPERATIONS) {
       count++;
   }


   // Fermeture du fichier
   fclose(file);


   n = count;


   // Initialisation du tableau de visite
   for (int i = 0; i < n; i++) {
       visited[i] = false;
   }


   printf("Ordre des opérations respectant la contrainte de précédence (DFS) :\n");


   // Appliquer DFS pour obtenir l'ordre
   for (int i = 0; i < n; i++) {
       if (!visited[i]) {
           dfs(i);
       }
   }


   return EXIT_SUCCESS;
}
*/

