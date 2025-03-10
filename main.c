#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* last;
} LinkedList;

typedef struct {
    char name[20];
    char symbol;
} Player;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
    } else {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return newNode;
}

LinkedList* createLinkedList() {
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    if (newList) {
        newList->head = NULL;
        newList->last = NULL;
    } else {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return newList;
}

void append(LinkedList* list, char data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->last = newNode;
    } else {
        list->last->next = newNode;
        newNode->prev = list->last;
        list->last = newNode;
    }
}

void displayBoard(LinkedList* list) {
    Node* current = list->head;
    int count = 0;
    while (current != NULL) {
        printf(" %c ", current->data);
        count++;
        if (count % 3 == 0) {
            printf("\n-----------\n");
        } else {
            printf("|");
        }
        current = current->next;
    }
}

int checkWinner(LinkedList* list, char symbol) {
    // Check rows
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == symbol && current->next != NULL && current->next->data == symbol && current->next->next != NULL && current->next->next->data == symbol) {
            return 1;
        }
        current = current->next->next->next;
    }

    current = list->head;
     while (current != NULL){
        if (current->data == symbol && current->next != NULL && current->next->next != NULL &&
            current->next->next->next != NULL && current->next->next->next->data == symbol && current->next->next->next->next != NULL &&
             current->next->next->next->next->next != NULL && current->next->next->next->next->next->next != NULL && current->next->next->next->next->next->next->data == symbol) {
            return 1;
        }
        current = current->next;
    }

    // Check diagonals
    current = list->head;
    if (current->data == symbol && current->next != NULL && current->next->next != NULL &&
        current->next->next->next != NULL && current->next->next->next->next != NULL &&
        current->next->next->next->next->data == symbol && current->next->next->next->next->next != NULL && current->next->next->next->next->next->next != NULL &&
        current->next->next->next->next->next->next->next != NULL && current->next->next->next->next->next->next->next->next != NULL &&
        current->next->next->next->next->next->next->next->next->data == symbol ) {
        return 1;
    }

    if (current->data != NULL  && current->next != NULL && current->next->next != NULL &&
        current->next->next->data == symbol && current->next->next->next != NULL && current->next->next->next->next != NULL &&
        current->next->next->next->next->data == symbol && current->next->next->next->next->next != NULL &&
        current->next->next->next->next->next->next->data == symbol && current->next->next->next->next->next->next->data != NULL
          ) {
        return 1;
    }

    return 0;
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* board = createLinkedList();
    for (int i = 0; i < 9; i++) {
        append(board, ' ');
    }

    Player playerX, playerO;
    printf("Welcome to Tic Tac Toe!\n");
    printf("Enter name for Player X: ");
    scanf("%s", playerX.name);
    playerX.symbol = 'X';

    printf("Enter name for Player O: ");
    scanf("%s", playerO.name);
    playerO.symbol = 'O';

    char choice;
    do {
        printf("Menu:\n");
        printf("1. Play\n");
        printf("2. Info\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                // Game logic
                displayBoard(board);
                printf("\n");

                Player currentPlayer = playerX;
                int movesLeft = 9;
                int gameOver = 0;

                while (movesLeft > 0 && !gameOver) {
                    int position;
                    printf("%s's turn. Enter position (1-9): ", currentPlayer.name);
                    scanf("%d", &position);
                    if (position < 1 || position > 9) {
                        printf("Invalid position! Please enter a number between 1 and 9.\n");
                        continue;
                    }

                    Node* current = board->head;
                    for (int i = 1; i < position; i++) {
                        current = current->next;
                    }

                    if (current->data == ' ') {
                        current->data = currentPlayer.symbol;
                        displayBoard(board);
                        printf("\n");
                        if (checkWinner(board, currentPlayer.symbol)) {
                            printf("%s wins!\n", currentPlayer.name);
                            gameOver = 1;
                        }
                        currentPlayer = (currentPlayer.symbol == 'X') ? playerO : playerX;
                        movesLeft--;
                    } else {
                        printf("Invalid move! Position already taken.\n");
                    }
                }

                if (!gameOver) {
                    printf("It's a draw!\n");
                }
                break;

            case '2':
                // Information
                printf("This is a simple Tic Tac Toe game.\n");
                printf("Players take turns marking spaces in a 3x3 grid.\n");
                printf("The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row wins the game.\n");
                break;

            case '3':
                // Exit
                printf("Exiting the game. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '3');
    freeLinkedList(board);

    return 0;
}
