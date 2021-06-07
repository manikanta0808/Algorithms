#include<bits/stdc++.h>
#include<unistd.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
using namespace std;

void printsolution(vector<vector<char>> board){
    int n = board.size();
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
            cout<< board[i][j]<< "\t";
        }cout<< endl<<endl<<endl;
    }
}
bool place(vector<vector<char>> board, int row, int col){
    int i , j;
    int n = board.size();
    //checking column
    for(j=0;j<row;j++){
        if(board[j][col] == 'Q')
            return false;
    }
    // checking right upper diagonal
    for(i=row,j = col;i>=0 && j<n ; i--,j++){
        if(board[i][j]=='Q'){
            return false;
        }
    }
    //checking left upper diagonal
    for(i=row,j = col;i>=0 && j>=0 ; i--,j--){
        if(board[i][j]=='Q'){
            return false;
        }
    }
    return true;
}
bool nqueen(vector<vector<char>> &board, int row){
    int n = board.size();
    if(row>=n)
        return true;
    else{
        for(int col=0;col<n;col++){
            if(place(board,row,col)){
                board[row][col] = 'Q';
                if(nqueen(board, row+1))
                    return true;
                board[row][col] = '.';
            }
        }
    }
    return false;
}

int main(){

    int n;// you can change the number of queens
    cout<<"Enter queens:";cin>>n;
    vector<vector<char>> Board(n, vector<char> (n,'.'));
    if(nqueen(Board,0))
        printsolution(Board);
    else
        cout<<" No solution"<<endl;
    
    return 0;
}
