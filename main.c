#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void start(int rows, int cols, int countIters);
char *create(int rows, int cols);
double getRandomDoubleInRange(double min, double max);
void display(int rows, int cols, const char* grid, int generation);
int countNeighbours(int cols, int x, int y, const char*grid);
char* newGen(int rows, int cols, char * prevGen);

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int rows=  atoi(argv[1]);
    if(rows <= 0 ){
        printf("Rows must be greater than 0");
        return -1;
    }
    int cols = atoi(argv[2]);
    if(cols <= 0){
        printf("Cols must be greater than 0");
        return -1;
    }
    int countIters = atoi(argv[3]);
    if(countIters <= 0){
        printf("Count of game iterations must be greater than zero !");
        return -1;
    }
    rows+=2;
    cols+=2;
    start(rows,cols, countIters);
    return 0;
}

/**
 * Display the game status / grid
 * @param rows < count of rows in the game grid
 * @param cols < count of columns in the game grid
 * @param grid < the grid, just a pointer to the first element of the array with cell status - alive/dead
 * @param generation < counter of current generation
 */
void display(int rows, int cols, const char* grid, int generation){
    printf("\n\n\n\n\nGeneration %d\n", generation);
    for(int y = 1; y < rows -1; y++){
        for(int x = 1; x < cols -1; x++){
            printf(" %c", *(grid + y*cols + x));
        }
        printf("\n");
    }
}

/**
 * Function to count near neighbours. This function made to create new alive cells
 * @param cols < count columns
 * @param x < this is absolutely X coordinate axis of the cell
 * @param y < this is absolutely Y coordinate axis of the cell
 * @param grid < the pointer of the first cell/first element of grid
 * @return
 */
int countNeighbours (int cols, int x, int y, const char* grid){
    int count = 0;
    int pivot = y*cols + x;
    for(int i = -1; i < 2 ; i++){
        for(int j = -1; j < 2; j++){
            char c = *(grid+ pivot + (i*cols) + j);
            if(c == '#') count++;
        }
    }
    return count;
}

/**
 * Checking game status. If game matrix on the next step is particulary simular to current matrix -> game will stop
 * @param cols
 * @param rows
 * @param lastGen < pointer to the previous grid
 * @param newGen < pointer to the next grid
 * @return
 */
int checkIfNotChanged(int cols, int rows, const char * lastGen, const char* newGen){
    for(int y = 1 ; y < rows -1 ; y++){
        for(int x=  1; x < cols -1; x++){
            char fromPrev = *(lastGen + y*cols + x);
            char fromNext = *(newGen + y*cols +x );
            if(fromNext != fromPrev) return 1;
        }
    }
    return 0;
}

/**
 * Calculate newGen function
 * @param rows
 * @param cols
 * @param prevGen < pointer to the previous grid
 * @return
 *
 * in that function we check the main rules of the game. There are them:
 * Место действия игры — размеченная на клетки плоскость, которая может быть безграничной, ограниченной или замкнутой.
    Каждая клетка на этой поверхности имеет восемь соседей, окружающих её, и может находиться в двух состояниях: быть «живой» (заполненной) или «мёртвой» (пустой).

    - Распределение живых клеток в начале игры называется первым поколением. Каждое следующее поколение рассчитывается на основе предыдущего по таким правилам:
    в пустой (мёртвой) клетке, с которой соседствуют три живые клетки, зарождается жизнь;
    если у живой клетки есть две или три живые соседки, то эта клетка продолжает жить; в противном случае (если живых соседей меньше двух или больше трёх) клетка умирает («от одиночества» или «от перенаселённости»).

    Игра прекращается, если
    - на поле не останется ни одной «живой» клетки;
    - конфигурация на очередном шаге в точности (без сдвигов и поворотов) повторит себя же на одном из более ранних шагов (складывается периодическая конфигурация)
    - при очередном шаге ни одна из клеток не меняет своего состояния (предыдущее правило действует на один шаг назад, складывается стабильная конфигурация)
   Игрок не принимает активного участия в игре. Он лишь расставляет или генерирует начальную конфигурацию «живых» клеток, которые затем изменяются согласно правилам. Несмотря на простоту правил, в игре может возникать огромное разнообразие форм.
 */
char * newGen(int rows, int cols, char*prevGen){
    char* steppedSimulation = calloc(rows*cols, sizeof(int));
    if(steppedSimulation == NULL) return NULL;
    for(int y = 1; y < rows -1; y++){
        for(int x = 1; x < cols-1; x++) {
            int live = countNeighbours(cols, x, y, prevGen);
            char cell = *(prevGen + y * cols + x);
            if (cell == '#') live--;
            *(steppedSimulation + y*cols + x) = cell;
            if (live < 2) {
                *(steppedSimulation + y * cols + x) = '.';
            }
            else if ((live == 2 || live == 3) && cell == '#') {
                *(steppedSimulation + y * cols + x) = '#';
            } else if (live > 3 && cell == '#') {
                *(steppedSimulation + y * cols + x) = '.';
            } else if (live == 3 && cell == '.') {
                *(steppedSimulation + y * cols + x) = '#';
            }
        }
    }
    return  steppedSimulation;
}

/**
 * Start game !
 * @param rows
 * @param cols
 * @param countIters < count the iterations. this parameter defines game ending
 */
void start(int rows, int cols, int countIters) {
    puts("Lets play in life");
    char* simulation = create(rows, cols);
    if(simulation == NULL) return;
    int gen = 0;
    display(rows, cols, simulation, gen);
    while(1){
        char* newSim = newGen(rows, cols, simulation);
        if(newSim == NULL) return;
        if(checkIfNotChanged(cols, rows, simulation, newSim) == 0){
            printf("Seems like simulation is looped!");
            break;
        }
        free(simulation);
        simulation = newSim;
        if(gen == countIters)
        {
            printf("The game is over due to the expiration of generations");
            return;
        }else gen++;

        display(rows, cols, simulation, gen);
        Sleep(1000);
    }
}

double getRandomDoubleInRange(double min, double max){
    return ((double) rand()/RAND_MAX) * (max-min) + min;
}

/**
 * Create the game grid
 * @param rows < count rows
 * @param cols  < count cols
 * @return
 *
 * This function with 0.35 chance make cells alive of the grid
 *
 */
char* create(int rows, int cols){
    char* grid = (char*) calloc(rows*cols, sizeof(int));
    if(grid == NULL){
        return NULL;
    }
    for(int y = 1; y < rows-1; y++){
        for(int x = 1; x < cols-1; x++){
            if(getRandomDoubleInRange(0.0, 1.0)<= 0.35){
                *(grid+ y*cols+x) = '#';
            }else{
                *(grid+ y*cols+x) = '.';
            }
        }
    }
    return grid;
}

