#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_OPERATIONS 100

typedef struct {
    int op1;
    int op2;
} OperationPair;

OperationPair operations[MAX_OPERATIONS];
int inDegree[MAX_OPERATIONS] = {0};
bool visited[MAX_OPERATIONS] = {false};
int n;

void topologicalSort() {
    int queue[MAX_OPERATIONS];
    int front = 0, rear = 0;

    // Initialisation de la file avec les opérations initiales
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
            visited[i] = true;
        }
    }

    while (front < rear) {
        int node = queue[front++];

        // Afficher l'opération ici ou stocker l'ordre dans une autre structure de données
        printf("%d %d\n", operations[node].op1, operations[node].op2);

        for (int i = 0; i < n; i++) {
            if (operations[i].op1 == operations[node].op2 && !visited[i]) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = true;
                }
            }
        }
    }
}

int main() {
    FILE *file;
    char filename[] = "file.txt"; // Nom du fichier texte
    int count = 0;

    // Ouverture du fichier en mode lecture
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }

    // Lecture des opérations du fichier
    while (fscanf(file, "%d %d", &operations[count].op1, &operations[count].op2) == 2 && count < MAX_OPERATIONS) {
        inDegree[count] = 0;
        count++;
    }

    // Fermeture du fichier
    fclose(file);

    n = count;

    // Compter les degrés entrants pour chaque opération
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (operations[j].op1 == operations[i].op2) {
                inDegree[j]++;
            }
        }
    }

    printf("Ordre des opérations respectant la contrainte de précédence :\n");
    topologicalSort();

    return EXIT_SUCCESS;
}
