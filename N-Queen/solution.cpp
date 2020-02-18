#include <iostream>
#include <queue> 
using namespace std;

class State{
    public:
    int cost;
    int numQueens;
    vector<vector<int>>arr;
    bool isVisited;
    int nextRow;
    State(int numQ){
        numQueens = numQ;
        cost = 0;
        isVisited = false;
        nextRow = 0;
        for(int i=0;i<numQueens;i++){
            vector<int>temp;
            for(int j=0;j<numQueens;j++){
                temp.push_back(0);
            }
            arr.push_back(temp);
        }
    }
    void printState(){
        cout<<endl;
        for(int i=0;i<numQueens;i++){
            for(int j=0;j<numQueens;j++){
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
};

bool isValid(vector<vector<int>>board, int row, int column, int numQueens)
{
    int count = 0;
    for (int i = 0; i < numQueens; i++)
    {
        if (board[i][column] == 1)
        {
            count++;
        }
    }
    if (count > 1)
    {
        return false;
    }
    count = 0;
    for (int i = 0; i < numQueens; i++)
    {
        if (board[row][i] == 1)
        {
            count++;
        }
    }
    if (count > 1)
    {
        return false;
    }
    count = 0;

    int c1 = column;
    int r1 = row;
    int c2 = column - 1;
    int r2 = row - 1;
    count = 0;
    for (; c1 < numQueens && r1 < numQueens; c1++, r1++)
    {
        if (board[r1][c1] == 1)
        {
            count++;
        }
    }
    for (; c2 >= 0 && r2 >= 0; c2--, r2--)
    {
        if (board[r2][c2] == 1)
        {
            count++;
        }
    }
    if (count > 1)
    {
        return false;
    }

    c1 = column;
    r1 = row;
    c2 = column + 1;
    r2 = row - 1;
    count = 0;
    for (; c1 >= 0 && r1 < numQueens; c1--, r1++)
    {
        if (board[r1][c1] == 1)
        {
            count++;
        }
    }
    for (; c2 < numQueens && r2 >= 0; c2++, r2--)
    {
        if (board[r2][c2] == 1)
        {
            count++;
        }
    }
    if (count > 1)
    {
        return false;
    }

    return true;
}

bool isGoalState(State temp){
    return temp.nextRow == temp.numQueens;
}

priority_queue<State> applyAction(State temp, priority_queue<State>open, int numQueens){
    int row = temp.nextRow;
    int cost = temp.cost;
    vector<vector<int>> board;
    for(int i=0;i<numQueens;i++){
        vector<int>tempBoard;
        for(int j=0;j<numQueens;j++){
            tempBoard.push_back(temp.arr[i][j]);
        }
        board.push_back(tempBoard);
    }

    for (int i = 0; i < numQueens; i++)
    {
        board[row][i] = 1;
        if (isValid(board, row, i, numQueens))
        {
            State nextState(numQueens);
            for(int k=0;k<numQueens;k++){
                for(int l=0;l<numQueens;l++){
                    nextState.arr[k][l] = board[k][l];
                }
            }
            nextState.cost = cost+1;
            nextState.nextRow = row+1;
            open.push(nextState);
        }
        board[row][i] = 0;
    }
    return open;
}

bool operator<(const State& p1, const State& p2) 
{ 
    return p1.cost < p2.cost; 
} 

int main(){
    priority_queue <State> open;
    int numQueens;
    cout<<"Enter number of queens\n";
    cin>>numQueens;
    State s(numQueens);
    bool hasReachedGoalState = false;
    open.push(s);
    while(!open.empty()){
        State temp = open.top();
        temp.printState();
        open.pop();
        if(isGoalState(temp)){
            hasReachedGoalState = true;
            cout<<"Cost = "<<temp.cost<<endl;
            break;
        }
        open = applyAction(temp,open,numQueens);
    }
    if(!hasReachedGoalState){
        cout<<"No Solution Exits"<<endl;
    }

    return 0;
}