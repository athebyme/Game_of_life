#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void start(int rows, int cols);
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
    rows+=2;
    cols+=2;
    start(rows,cols);
    return 0;
}

void display(int rows, int cols, const char* grid, int generation){
    printf("\n\n\n\n\nGeneration %d\n", generation);
    for(int y = 1; y < rows -1; y++){
        for(int x = 1; x < cols -1; x++){
            printf(" %c", *(grid + y*cols + x));
        }
        printf("\n");
    }
}

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

void start(int rows, int cols) {
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
        ++gen;
        display(rows, cols, simulation, gen);
        Sleep(1000);
    }
}

double getRandomDoubleInRange(double min, double max){
    return ((double) rand()/RAND_MAX) * (max-min) + min;
}

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

