#include<stdio.h>

#define GRID_COLS 25; 
#define GRID_ROWS 25;
#define ALIVE='*';
#define DEAD='-';

void setCell(char *grid, int x, int y,int state){
	grid[y*GRID_COLS+x] = state;
}

char getCell(){
	return grid[y*GRID_COLS+x];
}

int main(void){
	char grid[Cols*Rows]; 
}
