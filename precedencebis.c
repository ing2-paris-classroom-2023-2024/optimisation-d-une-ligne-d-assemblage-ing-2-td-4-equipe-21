#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_OPERATIONS 100

typedef struct {
    char op[10];
} Operation;

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
    
    printf("%s\n", operations[node].op);
}

int main() {
    FILE *file;
    char filename[] = "operations.txt"; // Nom du fichier texte
    int count = 0;

    // Ouverture du fichier en mode lecture
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }

    // Lecture des opérations du fichier
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

    // Appliquer DFS pour obtenir l'ordre
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    return EXIT_SUCCESS;
}
