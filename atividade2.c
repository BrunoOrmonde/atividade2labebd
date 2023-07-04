#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Cria um novo nó com um determinado dado
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for new node.\n");
        exit(-1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insere um nó na árvore de busca binária
Node* insertNode(Node* root, int data) {
    if(root == NULL) {
        root = createNode(data);
    }
    else if(data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Encontra o mínimo valor na árvore
Node* findMin(Node* root) {
    while(root->left != NULL) root = root->left;
    return root;
}

// Remove um nó da árvore de busca binária
Node* deleteNode(Node* root, int data) {
    if(root == NULL) return root;
    else if(data < root->data) root->left = deleteNode(root->left, data);
    else if(data > root->data) root->right = deleteNode(root->right, data);
    else {
        // Caso 1: Sem filho
        if(root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        // Caso 2: Um filho
        else if(root->left == NULL) {
            Node* temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL) {
            Node* temp = root;
            root = root->left;
            free(temp);
        }
        // Caso 3: Dois filhos
        else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

// Imprime a árvore em ordem
void printInOrder(Node* root) {
    if(root == NULL) return;
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

// Imprime a árvore em pré-ordem
void printPreOrder(Node* root) {
    if(root == NULL) return;
    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// Imprime a árvore em pós-ordem
void printPostOrder(Node* root) {
    if(root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

int main() {
    int K, N;
    char op;
    Node* root = NULL;

    // Lê o valor de K
    scanf("%d", &K);

    // Lê as operações até encontrar 0
    while (scanf(" %c", &op), op != '0') {
        if (op == '+') {
            scanf("%d", &N);
            if (N <= K) {
                root = insertNode(root, N);
                printf("0\n");
            } else {
                printf("E\n0\n");
            }
        } else if (op == '-') {
            scanf("%d", &N);
            root = deleteNode(root, N);
            printf("0\n");
        } else if (op == '=') {
            scanf("%d", &N);
            if (N == 1) {
                printInOrder(root);
                printf("\n");
            }
            else if (N == 2) {
                printPreOrder(root);
                printf("\n");
            }
            else if (N == 3) {
                printPostOrder(root);
                printf("\n");
            }
            printf("0\n");
        }
    }

    return 0;
}
