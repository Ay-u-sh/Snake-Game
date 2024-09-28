#define X 15
#define Y 25
#define EMPTY 0 
#define BOUNDARY 3
#define SNAKE 1
#define FOOD 2
typedef struct Node{
    int x;
    int y;
    struct Node* left;
    struct Node* right;
}Node;


void run();
void start();
int takeInput();

void determineSpeed();

void loadGame();
void loadPlayArea();
void loadStartingPoint();
void loadSnake();

void generateFood();
int isEating();

int moveSnake(char);
int moveSnakeLeft();
int moveSnakeRight();
int moveSnakeUp();
int moveSnakeDown();

void cleanup();

void printPlayArea();

Node* createNode(int,int);
void insertAtHead(int,int);
void removeFromEnd();