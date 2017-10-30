/* Notes on the frame of reference
	Because it is a 4x4x4 array of positions, it can be represented by the bits of 64-bit int
	Each byte makes up two successive rows along the x dimension
	The rows stck to form the y  dimension
	They xy's then stack to form the z dimension
	
	Assuming the first part's orientation is fixed:
	There are 6 directional orientations that each piece can take.
	We will label them:
		0: x
		1: x'
		2: y
		3: y'
		4: z
		5: z'
	4 rotational arrangements for each.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char arr[4][4][4];
}piece;

void printArray(piece input);
piece spinX(piece input, int angle);
piece rotate(piece input, int direction);
piece shift(piece input, int amount, int direction);

void loop_spin(piece input);
void loop_rotate(piece input);
void loop_shiftX(piece input);
void loop_shiftY(piece input);
void loop_shiftZ(piece input);
void output(piece input);
int addPiece(unsigned long long currentPiece, int nextPieceNum);
void printInt(unsigned long long input);
void print2Ints(unsigned long long input1, unsigned long long input2);

int dimensions[10][3] = {
	{2,4,4},//0
	{2,3,4},//1
	{4,3,1},//5
	{2,2,4},//4
	{3,2,3},//2
	{1,2,4},//6
	{1,2,4},//7
	{1,3,3},//8
	{2,2,3},//3
	{2,2,2}//9
};
int pieceNum = 0;
int counter = 0;
unsigned long long possibles[10][700];	

int main(int argc, char** argv){
	//int pieceNum/*, i, j, k, l, m, n, arrayInt*/;
	piece temp;
	//file_p = fopen("data.csv", "w+");
	// Bounding dimensions of each piece (x,y,z)

	
	piece temp0 = {{//9
		{
			{'1','0','0','0'},
			{'1','1','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','1','1','1'},
			{'0','0','0','1'},
			{'0','0','1','1'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp1 = {{//8
		{
			{'0','0','0','0'},
			{'0','0','1','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'1','0','0','0'},
			{'1','0','1','0'},
			{'1','1','1','1'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp2 = {{//7
		{
			{'0','1','0','0'},
			{'0','1','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','1','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'1','1','1','0'},
			{'1','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp3 = {{//6
		{
			{'1','0','1','0'},
			{'1','1','1','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','1','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp4 = {{//6
		{
			{'1','1','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','1','0','0'},
			{'0','1','1','1'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp5 = {{//6
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'1','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'1','0','0','0'},
			{'0','0','0','0'}},
		{
			{'1','0','0','0'},
			{'1','0','0','0'},
			{'1','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'1','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp6 = {{//6
		{
			{'0','1','0','1'},
			{'1','1','1','1'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp7 = {{//6
		{
			{'1','0','1','1'},
			{'1','1','1','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp8 = {{//6
		{
			{'0','0','1','0'},
			{'1','0','1','0'},
			{'1','1','1','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};
	piece temp9 = {{//4
		{
			{'0','1','0','0'},
			{'0','1','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'1','1','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}},
		{
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'},
			{'0','0','0','0'}}
	}};	
	
	piece example[10] = {temp0,temp1,temp5,temp4,temp2,temp6,temp7,temp8,temp3,temp9};

	//Zero the int storage array called "possibles"
	for(pieceNum = 0; pieceNum < 10; pieceNum++){
		for(counter = 0; counter < 700; counter++){
			possibles[pieceNum][counter] = 0;
		}
	}
	
	for(pieceNum = 0; pieceNum < 10; pieceNum++){
		counter = 0;
		printf("Starting piece %d\n", pieceNum);
		loop_shiftX(example[pieceNum]);
		printf("Perms: %d\n",counter);
	}
	//fclose(file_p);
	if(addPiece(0llu,0) == 0){
		printf("FAIL\n");
	}
	else{
		printf("SUCCESS\n");
	}
	
	return 0;
}

int addPiece(unsigned long long currentPiece, int nextPieceNum){
	int count = 0;
	while(possibles[nextPieceNum][count] != 0){
	//	if(nextPieceNum == 0){
	//		printf("%4d",count);
	//	}
		//print2Ints(possibles[nextPieceNum][count], currentPiece);
		//printf("\n");
		if((possibles[nextPieceNum][count] & currentPiece) == 0){
			//printf("Good\n\n");
			if(nextPieceNum == 9){
				printInt(possibles[nextPieceNum][count] | currentPiece);
				printf("Piece: %d is %llu\n", nextPieceNum, possibles[nextPieceNum][count]);
				printInt(possibles[nextPieceNum][count]);
				return 1;
			}
			else{
				//printf(".");
				if(addPiece(currentPiece | possibles[nextPieceNum][count], nextPieceNum + 1) == 1){
					printf("Piece: %d is %llu\n", nextPieceNum, possibles[nextPieceNum][count]);
					printInt(possibles[nextPieceNum][count]);
					return 1;
				}
			}
		}
		//if(nextPieceNum == 0){
		//	printf("\n");
		//}
		count++;
	}
	return 0;
}

void printInt(unsigned long long input){
	int i, j, k;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			for(k = 0; k < 4; k++){
				if((1ull << (63-(k + (j * 16) + (i * 4)))) & input){
					printf("1");
				}
				else{
					printf("0");
				}
			}
			printf(" ");
		}	
		printf("\n");
	}
	return;
}

void print2Ints(unsigned long long input1, unsigned long long input2){
	int i, j, k;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			for(k = 0; k < 4; k++){
				if((1ull << (63-(k + (j * 16) + (i * 4)))) & input1){
					printf("X");
				}
				else{
					printf(".");
				}
			}
			printf(" ");
		}	
		for(j = 0; j < 4; j++){
			for(k = 0; k < 4; k++){
				if((1ull << (63-(k + (j * 16) + (i * 4)))) & input2){
					printf("O");
				}
				else{
					printf(",");
				}
			}
			printf(" ");
		}	
		printf("\n");
	}
	return;
}
void loop_shiftX(piece input){
	int k = 4-dimensions[pieceNum][0];
	loop_shiftY(input);
	while(k > 0){
		input = shift(input, 1, 0);
		loop_shiftY(input);
		k--;
	}
	return;
}
void loop_shiftY(piece input){
	int l = 4-dimensions[pieceNum][1];
	loop_shiftZ(input);
	while(l > 0){
		input = shift(input, 1, 1);
		loop_shiftZ(input);	
		l--;
	}
	return;
}
void loop_shiftZ(piece input){
	int m = 4-dimensions[pieceNum][2];
	if(pieceNum != 0){
		loop_rotate(input);
	}
	else{
		output(input);
	}	
	while(m > 0){
		input = shift(input, 1, 2);
		loop_rotate(input);
		m--;
	}
	return;
}
void loop_spin(piece input){
	int i;
	for(i = 0; i < 360; i+=90){
		output(spinX(input, i));
	}
	return;
}
void loop_rotate(piece input){
	int j;
	for(j = 0; j < 6; j++){//Ratate to the 6 different directions
		//output(rotate(input, j));
		loop_spin(rotate(input, j));
	}
	return;
}
void output(piece input){
	int n;
	unsigned long long arrayInt = 0;
	//printArray(input);
	for(n = 0; n < 64; n++){//Convert array to an integer
		// Add the 1s to the integer's binary
		if(input.arr[0][0][n] == '1'){
			arrayInt |= (1ull << (63-n));
		}
	}
	//printf("%llx\n", arrayInt);
	//printInt(arrayInt);
	//printf("\n");
	possibles[pieceNum][counter] = arrayInt;
	//printf("%llu\n",arrayInt);
	//fprintf(fp, outputFile, "%lu", arrayInt);
	counter++;
}

//Prints the array as it's layers
void printArray(piece input){
	int i, j, k;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			for(k = 0; k < 4; k++){
				printf("%c",input.arr[j][i][k]);
			}
			printf("   ");
		}
		printf("\n");
	}
	return;
}

//Spins the shape along the x axis
piece spinX(piece input, int angle){
	if(angle == 0){
		return input;
	}
	int i, j;
	char temp[4][4][4];
	for(i = 0; i < 4; i++){
		for(j = 0; j < 16; j++){
			switch(angle){
				case 90:
					temp[i][0][j] = input.arr[i][0][j/4 + 12 - (j%4)*4];
					break;
				case 180:
					temp[i][0][j] = input.arr[i][0][15-j];
					break;
				case 270:
					temp[i][0][j] = input.arr[i][0][3 - (j/4) + (j%4)*4];
					break;
				default:
					memcpy(temp, input.arr, sizeof(temp));
					i = 4;
					j = 16;
			}
		}
	}
	memcpy(input.arr, temp, sizeof(input.arr));
	return input;
}
	
//Points the shape in one of the 6 directions
piece rotate(piece input, int direction){
	if(direction == 0){
		return input;
	}
	char temp[4][4][4];
	int i;
	int lookup_xx[] = {51,50,49,48,55,54,53,52,59,58,57,56,63,62,61,60,35,34,33,32,39,38,37,36,43,42,41,40,47,46,45,44,19,18,17,16,23,22,21,20,27,26,25,24,31,30,29,28,3,2,1,0,7,6,5,4,11,10,9,8,15,14,13,12};
	int lookup_y[]  = {12,13,14,15,28,29,30,31,44,45,46,47,60,61,62,63,8,9,10,11,24,25,26,27,40,41,42,43,56,57,58,59,4,5,6,7,20,21,22,23,36,37,38,39,52,53,54,55,0,1,2,3,16,17,18,19,32,33,34,35,48,49,50,51};
	int lookup_yy[] = {48,49,50,51,32,33,34,35,16,17,18,19,0,1,2,3,52,53,54,55,36,37,38,39,20,21,22,23,4,5,6,7,56,57,58,59,40,41,42,43,24,25,26,27,8,9,10,11,60,61,62,63,44,45,46,47,28,29,30,31,12,13,14,15};
	int lookup_z[]  = {3,19,35,51,7,23,39,55,11,27,43,59,15,31,47,63,2,18,34,50,6,22,38,54,10,26,42,58,14,30,46,62,1,17,33,49,5,21,37,53,9,25,41,57,13,29,45,61,0,16,32,48,4,20,36,52,8,24,40,56,12,28,44,60};
	int lookup_zz[] = {48,32,16,0,52,36,20,4,56,40,24,8,60,44,28,12,49,33,17,1,53,37,21,5,57,41,25,9,61,45,29,13,50,34,18,2,54,38,22,6,58,42,26,10,62,46,30,14,51,35,19,3,55,39,23,7,59,43,27,11,63,47,31,15};
	
	for(i = 0; i < 64; i++)
	switch(direction){
		case 1: //x'
			temp[0][0][i] = input.arr[0][0][lookup_xx[i]];
			break;
		case 2: //y
			temp[0][0][i] = input.arr[0][0][lookup_y[i]];
			break;
		case 3: //y'
			temp[0][0][i] = input.arr[0][0][lookup_yy[i]];
			break;
		case 4: //z
			temp[0][0][i] = input.arr[0][0][lookup_z[i]];
			break;
		case 5: //z'
			temp[0][0][i] = input.arr[0][0][lookup_zz[i]];
			break;
		default: //x
			memcpy(temp, input.arr, sizeof(temp));
			i = 64;
	}
	memcpy(input.arr, temp, sizeof(input.arr));
	return input;
}

//Shifts the figure the specified number of 
//Directions for this are 0-x, 1-y, 2-z
piece shift(piece input, int amount, int direction){
	if(amount == 0){
		return input;
	}
	char temp[4][4][4];
	int i, pos;
	int stop = 64;
	for(i = 0; i < stop; i++){
		switch(direction){
			case 0:
				pos = i-(amount*16);
				break;
			case 1:
				pos = i-(amount*4);
				break;
			case 2:
				pos = i-(amount);
				break;
			default:
				pos = i;
		}
		if(pos < 0){
			temp[0][0][i] = '0';
		}else{
			temp[0][0][i] = input.arr[0][0][pos];
		}
	}
	memcpy(input.arr, temp, sizeof(input.arr));
	return input;
}
