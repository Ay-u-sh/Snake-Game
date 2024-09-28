#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include "SnakeGame.h"


int play_area[X][Y],Fx=!FOOD,Fy=!FOOD,score,startX,startY;
char default_direction = 'd';

Node* head = NULL;
Node* tail = NULL;

void run(){
    score = 1;
    while(1){
        printf("\n\n\n\n     SNAKE GAME\n");
        printf("1. Press p to play\n");
        printf("2. Press q to quit\n");
        printf("\tby Ayush Bhande\n");
        printf("Enter your choice:");
        char choice;
        scanf(" %c",&choice);
        if(choice == 'p') start();
        else break;
    }
    return;
}

void start(){
    loadGame();
    printf("\n\n\n\nGame Instruction\n");
    printf("To quit the game press q\n");
    printf("To move the snake enter characters\n1. w for up\n2. s for down\n3. a for right\n4. d for left\n\n");
    sleep(8);
    while (1) {
        printPlayArea();
        int result = takeInput();
        if(result == 0) break;
        else if(result == 1){
            printf("\nGame Over\n\n\n\n");
            break;
        }
        else determineSpeed();
    }
    cleanup();
}

int takeInput(){
    if (kbhit()) {
        char input = getch();
        if (input == 'r' || input == 'q')
            return 0;
        else{ 
            int x = input + default_direction;
            if(x != 234 && x != 197) default_direction = input;
        } 
    }
    if (!moveSnake(default_direction)) return 1;
    printPlayArea();
    return 2; 
}


void loadGame(){
    loadPlayArea();
    loadStartingPoint();
    loadSnake();
    generateFood();
}

void loadPlayArea(){
    for(int i=0;i<X;i++){
        for(int j=0;j<Y;j++){ 
            if(i == 0 || i == X-1 || j == 0 || j == Y-1) play_area[i][j] = BOUNDARY;
            else play_area[i][j] = EMPTY;
        }
    }
}

void loadStartingPoint(){
    srand(time(NULL));
    startX = rand()%(X-1);
    startY = rand()%(Y-1);

    if(!startX) startX++;
    if(!startY) startY++;
    play_area[startX][startY] = SNAKE;
    return;
}

void loadSnake(){
    score = 1;
    head = createNode(startX,startY);
    tail = head;
}

void generateFood(){
    srand(time(NULL));
    do{
        Fx = rand()%(X-1);
        Fy = rand()%(Y-1);
        if(!Fx) Fx++;
        if(!Fy) Fy++;
    }while(play_area[Fx][Fy]);
    play_area[Fx][Fy] = FOOD;

}

void cleanup(){
    if(!head) return;
    Node* temp = head->right;
    while(temp){
        temp->left->right = NULL;
        free(temp->left);
        temp = temp->right;
    }
    if(tail) free(tail);
    head = NULL;
    tail = NULL;

    loadPlayArea();
    score = 1;
}

int isEating(){
    if(head->x == Fx && head->y == Fy){
        generateFood();
        return 1;
    }
    return 0;
}




int moveSnake(char move){
    int result = 0;
    if(move == 'w')  result = moveSnakeUp();
    else if(move == 's') result = moveSnakeDown();
    else if(move == 'a') result =  moveSnakeLeft();
    else if(move == 'd') result = moveSnakeRight();
    if(!result) return result;
    score++;
    if(!isEating()){
        play_area[tail->x][tail->y] = EMPTY;
        removeFromEnd();
        score--;
    }
    play_area[head->x][head->y] = SNAKE;
    return result;
}

int moveSnakeLeft(){
    int y = head->y - 1;
    if(tail->x == head->x && tail->y == y);
    else if(y == 0 || play_area[head->x][y] == SNAKE) return 0;
    insertAtHead(head->x,y);
    return 1;
}

int moveSnakeRight(){
    int y = head->y+1;
    if(tail->x == head->x && tail->y == y);
    else if(y == Y-1 || play_area[head->x][y] == SNAKE) return 0;
    insertAtHead(head->x,y);      
    return 1;
}

int moveSnakeDown(){
    int x = head->x + 1; 
    if(tail->x == x && tail->y == head->y);
    else if(x == X-1 || play_area[x][head->y] == SNAKE) return 0;
    insertAtHead(x,head->y);
    return 1;
}

int moveSnakeUp(){
    int x = head->x-1;
    if(tail->x == x && tail->y == head->y);
    else if(x == 0 || play_area[x][head->y] == SNAKE) return 0;
    insertAtHead(x,head->y);
    return 1;
}




void printPlayArea(){
    system("cls");
    for(int i=0;i<X;i++){
        for(int j=0;j<Y;j++){
            if(i == 0 || i == X-1 || j == 0 || j == Y-1) printf("# ");
            else{
                if(head->x == i && head->y == j){ 
                    if(default_direction == 'd') printf("> ");
                    else if(default_direction == 's') printf("v ");
                    else if(default_direction == 'a') printf("< ");
                    else printf("^ ");
                }
                else if(play_area[i][j] == SNAKE) printf("+ ");
                else if(play_area[i][j] == FOOD) printf("F ");
                else printf("  ");
            }
        }
        printf("\n");
    }
    printf("Your score is %d\n",score);
    printf("Where to move:");
}





void determineSpeed(){
    if(score<2) usleep(1*100000);
    else if(score>=2 && score<=5) usleep(1*10000);
    else usleep(1*10000);
}




Node* createNode(int x,int y){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) return NULL;
    newNode->x = x;
    newNode->y = y;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void insertAtHead(int x,int y){
    Node* newNode = createNode(x,y);
    newNode->right = head;
    head->left = newNode;
    head = newNode;
}

void removeFromEnd(){
    Node* temp = tail;
    tail = tail->left;
    tail->right = NULL;
    temp->left = NULL;
    free(temp);
}

int main(){
    run();
    return 0;
}