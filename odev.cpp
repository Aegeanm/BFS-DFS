#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include <bits/stdc++.h>
#define ROW 9 
#define COL 9 
 
using namespace std;

int counter = 0;
char array2d[ROW][COL];
bool arrayFlags[ROW][COL];
int mat[ROW][COL];
int result[300][2];

void repaintscr(){
	Sleep(500);
	system("cls");		
}

writetotxt(bool isdepth){
	
	if(isdepth){
		ofstream outfile ("DFS_result.txt");
		outfile << "K ->" ; 
		for(int i= 0; i<counter; i++){
			outfile << result[i][0]+1<< result[i][1]+1 << "->";
		}
		outfile << "X" << endl ;
		
		int a,b;
		for (a = 0; a < ROW; a++) {
			for (b = 0; b < COL; b++) {
				outfile << array2d[a][b];
			}
			outfile << endl;
		}
		outfile.close();
		cout << "\n\nResult has saved DFS_result.txt" << endl;		
	}else if(!isdepth){
		ofstream outfile ("BFS_result.txt");
		outfile << "K ->" ; 
		for(int i= 0; i<counter; i++){
			outfile << result[i][0]+1<< result[i][1]+1 << "->";
		}
		outfile << "X" << endl ;
		
		int a,b;
		for (a = 0; a < ROW; a++) {
			for (b = 0; b < COL; b++) {
				outfile << array2d[a][b];
			}
			outfile << endl;
		}
		outfile.close();
		cout << "\n\nResult has saved BFS_result.txt" << endl;			
	}else{
		cout << "\n\n.txt file cannot be created" << endl;
	}
	
}

void checkforbomb(char c, bool isdepth){
	if(c == 'X'){
		cout << "Bomb has found..." << endl;	
		cout << "K ->" ; 
		for(int i= 0; i<counter; i++){
			cout << result[i][0]+1<< result[i][1]+1 << "->";
		}
		cout << "X" ;
		writetotxt(isdepth);
		system("PAUSE");
		exit(0);
	}
}

void print(){
	int a,b;
	for (a = 0; a < ROW; a++) {
		for (b = 0; b < COL; b++) {
			cout << array2d[a][b];
		}
		cout << endl;
	}
}

void godfs(int x, int y){
	
	if(arrayFlags[x-1][y]){
		
		checkforbomb(array2d[x-1][y], true);
		arrayFlags[x-1][y] = false;
		array2d[x-1][y] = '.';
		result[counter][0] = x-1;
		result[counter][1] = y;
		counter++;
		print();
		repaintscr();	
		godfs(x-1,y);
		godfs(x,y);		
			
	}else if(arrayFlags[x][y+1]){
		
		checkforbomb(array2d[x][y+1], true);
		arrayFlags[x][y+1] = false;
		array2d[x][y+1] = '.';
		result[counter][0] = x;
		result[counter][1] = y+1;	
		counter++;
		print();
		repaintscr();		
 		godfs(x, y+1);
		godfs(x, y);
	
	}else if(arrayFlags[x+1][y]){

		checkforbomb(array2d[x+1][y],true);
		arrayFlags[x+1][y] = false;
		array2d[x+1][y] = '.';
		result[counter][0] = x+1;
		result[counter][1] = y;	
		counter++;
		print();
		repaintscr();	
		godfs(x+1, y);
		godfs(x, y);
	
	}else if(arrayFlags[x][y-1]){
	
		checkforbomb(array2d[x][y-1],true);
		arrayFlags[x][y-1] = false;
		array2d[x][y-1] = '.';
		result[counter][0] = x;
		result[counter][1] = y-1;
		counter++;
		print();
		repaintscr();	
		godfs(x, y-1);
		godfs(x, y);
		
	}else{
		array2d[x][y] = ' ';
	}
}

struct Point 
{ 
    int x; 
    int y; 
}; 
  
struct queueNode 
{ 
    Point pt; 
    int dist; 
}; 
  
 
bool isValid(int row, int col) 
{ 
    return (row >= 0) && (row < ROW) && 
           (col >= 0) && (col < COL); 
} 
  

int rowNum[] = {-1, 0, 1, 0}; 
int colNum[] = {0, 1, 0, -1}; 
  

void gobfs(int mat[][9], Point src, Point dest) 
{ 
    queue<queueNode> q; 
    queueNode s = {src, 0}; 
    q.push(s);
   
    while (!q.empty()) 
    { 
        queueNode curr = q.front(); 
        Point pt = curr.pt;
        q.pop(); 
  
        for (int i = 0; i < 4; i++) 
        { 
            int row = pt.x + rowNum[i]; 
            int col = pt.y + colNum[i]; 
              
            if (isValid(row, col) && mat[row][col] &&  
               arrayFlags[row][col]) 
            { 
                checkforbomb(array2d[row][col], false);
                arrayFlags[row][col] = false;
				array2d[row][col] = '.';
				result[counter][0] = row;
				result[counter][1] = col;
				counter++;
				print();
				repaintscr();
                queueNode Adjcell = { {row, col}, 
                                      curr.dist + 1 }; 
                q.push(Adjcell);
            } 
        } 
    }
}
	
int main() {
	
	int Kx;
	int Ky;
	int Bx;
	int By;
	char ch;
	int x =0;
	int y=0;

	fstream f("input.txt", fstream::in);
	system("color a");
	
	if (f.is_open()) {
		cout << "input.txt okundu..." << endl;
	}else{
		cout << "input.txt okunamadi..." << endl;
		exit(0);
	}

	
	while (f >> noskipws >> ch) {
		if (ch == '\n') {
			x++;
			y = 0;
		}else {
			
			array2d[x][y] = ch;
			if (ch == 'K') {
				Kx = x;
				Ky = y;
				arrayFlags[x][y] = false;
				mat[x][y] = 1;
			}else if(ch == ' '){
				arrayFlags[x][y] = true;
				mat[x][y] = 1;
			}else if(ch == 'X'){
				arrayFlags[x][y] = true;
				mat[x][y] = 1;
				Bx = x;
				By = y;
			}else{
				arrayFlags[x][y] = false;
				mat[x][y] = 0;
			}
			y++;
		}
	}
	
	while(true){
		
			char input;
			cout << "For BFS (1), for DFS (2) : ";
			cin >> input;
			system("cls");
		if(input == '1'){
			Point source = {Kx, Ky};
   			Point dest = {Bx, By}; 
    		gobfs(mat, source, dest); 
			break;
		}else if(input == '2'){
			godfs(Kx, Ky);
			break;
		}else{
			cout << "Invalid Input..."<< endl;
		}
	}
	
	f.close();
		
}
