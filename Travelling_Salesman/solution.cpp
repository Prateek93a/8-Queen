#include <iostream>
#include <queue> 
#include <vector>
using namespace std;

class State{
    public:
    int g;
    int f;
    int totalCities;
    vector<int> citiesVisited;
    int currentCity;
    vector<int>path;
    State(int numCities){
        totalCities = numCities;
        g = 0;
        f = 0;
        for(int i=0;i<totalCities+1;i++){
            citiesVisited.push_back(-1);
        }
        currentCity = -1;
    }

};

bool hasReachedGoalState(State temp){
    for(int i=0;i<temp.totalCities;i++){
        if(temp.citiesVisited[i]==-1){
            return false;
        }
    }
    return true;
}

bool isValid(State temp, int nextCity, vector<vector<int>> cities, vector<State>closed){
    if(temp.currentCity == nextCity){
	    return false;
    }else{
	    for(int x: temp.path){
	    	if(nextCity == x){
			return false;
		}
	    }
	    return true;
    }
	for( State s: closed){
        if(s.currentCity == nextCity){
            if((s.path.size()-temp.path.size())!=1){
                return true;
            }else{
                vector<int>aux;
                vector<int>aux2;
                for(int x: s.path){
                    aux.push_back(x);
                }
                for(int x: temp.path){
                    aux2.push_back(x);
                }
                aux2.push_back(nextCity);
                if(aux==aux2){
            if(s.f>(temp.g+cities[temp.currentCity][nextCity]+cities[nextCity][0])){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return true;
                }
            }
        }
    }

    return true;
}

bool operator<(const State& p1, const State& p2) 
{ 
    return p1.f > p2.f; 
} 

priority_queue<State> applyAction(State temp, priority_queue<State>open, vector<vector<int>> cities, vector<State>closed){
    for (int i = 0; i < cities.size(); i++)
    {
        if (isValid(temp,i, cities, closed))
        {
            State nextState(cities.size());
            for(int k=0;k<5;k++){
                nextState.citiesVisited[k]= temp.citiesVisited[k];
            }
            for(int x: temp.path){
                nextState.path.push_back(x);
            }
            nextState.citiesVisited[i] = 1;
            nextState.g = temp.g + cities[temp.currentCity][i];
            nextState.f = nextState.g + cities[i][0];
            nextState.currentCity = i;
            nextState.path.push_back(i);
            open.push(nextState);

        }
    }
   
    return open;
}


int main(){
    int numCities, input;
    cout<<"Enter number cities\n";
    cin>>numCities;
    vector<vector<int>> cities;

    cout<<"Enter distances of each city from every other city(Assumption-Given edge costs represent distances between cities, hence input[i][j]=0 when i==j and input[i][j]>0 when i!=j)\n";
    // Eg-> {{0,4,1,9},{3,0,6,11},{4,1,0,2},{6,5,2,0}}
    for(int i = 0; i < numCities; i++){
        vector<int>temp;
        for(int j=0; j < numCities; j++){
            cin>>input;
            temp.push_back(input);
        }
        cities.push_back(temp);
    } 

    bool goalVisited = false;
    priority_queue <State> open;
    vector <State> closed;
    priority_queue<State>aux;
    State s(cities.size());
    s.citiesVisited[0] = 1;
    s.currentCity = 0;
    s.path.push_back(0);
    s.g = 0;
    s.f = 0;
    open.push(s);
    while(!open.empty()){
        while(!open.empty()){
            State auxi = open.top();
            open.pop();
            aux.push(auxi);
        }
        while(!aux.empty()){
            State auxip = aux.top();
            aux.pop();
            open.push(auxip);
        }
        State temp = open.top();
        open.pop();
        closed.push_back(temp);
        if(hasReachedGoalState(temp)){
            cout<<"Cost = "<<temp.g + cities[temp.currentCity][0]<<endl;
            for(int x: temp.path){
                cout<<x<<" ";
            }
            cout<<endl;
            goalVisited = true;
            break;
        }
        open = applyAction(temp,open,cities,closed);
    }
    if(!goalVisited){
        cout<<"No Goal reached"<<endl;
    }


}
