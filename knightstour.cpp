#include<bits/stdc++.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

static int rowPath[] = {-2, -2, -1, -1, 1, 1, 2, 2};
static int colPath[] = {-1 , 1, -2,  2, -2, 2, -1, 1};

bool isValid(char board[8][8], int row, int col){
    if(row>=0 && row<8 && col >= 0 && col<8 && board[row][col]=='0'){
        return true;
    }return false;
}

void printsolution(char board[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            cout<< board[i][j] << "\t";
        }cout<< endl<<endl;
    }
}

bool knightstour(char board[8][8], int row, int col, int move){
    if(move == 64){
        return true;
    }else{
        for(int i=0;i<8;i++){
            int newRow = row + rowPath[i];
            int newCol = col + colPath[i];
            if(isValid(board, newRow, newCol)){
                move++;
                board[newRow][newCol] = 'K';
                system("clear");
                printsolution(board);
                cout<< "cells occupied : " << move << endl;
                sleep(1);
                if(knightstour(board,newRow, newCol, move)){
                    return true;
                }board[newRow][newCol] = '0';
                move--;
            }
        }
    }return false;
}
int main(){
    
    char board[8][8];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            board[i][j] = '0';
        }
    }
    board[0][0] = 'K';
    if(knightstour(board,0,0,1)){
        cout<<"Knight's Tour competed succesfully !"<< endl;
    }
    return 0;
}