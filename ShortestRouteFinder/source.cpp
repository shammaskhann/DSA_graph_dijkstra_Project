#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
using namespace std;
struct Node {
    string name;
};
struct lastRide {
    Node start;
    Node end;
};
struct Person{
    string name;
    int id;
    string password;
    vector<lastRide> lastRides;
};
struct Edge {
    Node start;
    Node end;
    int weight;
};
vector<Person> people;
vector<Node> nodes;
vector<Edge> edges;
int totalDistance = 0; 
string Area[13] = {"Nazimabad", "Liaqtabad", "Paposh" , "Nagan" ,"Highway ", "Mazar-e-Quaid", "Gulshan",  "Safoora" , "Saddar" ,"Karsaz", "Airport", "Malir", "Hadeed"};
void addNode(const string& name);
void addEdge(int startIdx, int endIdx, int weight);
void addEdge(int startIdx, int endIdx, int weight);
void displayGraph();
void initialize();
void Register();
void Login();
void mainMenu();
void personMenu(Person p);
void lastHistory(Person p);
void getShortestRoute();
vector<int> shortestRoute(int start_idx, int end_idx);

int main() {
    initialize();
    displayGraph();
    mainMenu();
    return 0;
}

void initialize() {
    addNode("Nazimabad");//0
    addNode("Liaqtabad");//1
    addNode("Paposh");//2
    addNode("Nagan");//3
    addNode("Highway");//4
    addNode("Mazar-e-Quaid");//5
    addNode("Gulshan");//6
    addNode("Safoora");//7
    addNode("Saddar");//8
    addNode("Karsaz");//9
    addNode("Airport");//10
    addNode("Malir");//11
    addNode("Hadeed");//12

    addEdge(0, 1, 5);  // Nazimabad to Liaqtabad
    addEdge(0, 2, 2);  // Nazimabad to Paposh
    addEdge(1, 2, 4);  // Liaqtabad to Paposh
    addEdge(1, 5, 8);  // Liaqtabad to Mazar-e-Quaid
    addEdge(1, 6, 7);  // Liaqtabad to Gulshan
    addEdge(1, 4, 7);   // Liaqtabad to Highway
    addEdge(2, 3, 5);  //  Paposh to Nagan
    addEdge(3, 4, 4);  // Nagan to Highway
    addEdge(6, 7, 8);  // Gulshan to Safoora
    addEdge(6, 5, 6);  // Gulshan to Mazar-e-Quaid
    addEdge(6, 9, 8);  // Gulshan to Karsaz
    addEdge(5, 8, 3);  // Mazar-e-Quaid to Saddar
    addEdge(8, 9, 10);  // Saddar to Karsaz
    addEdge(9, 10, 6);  // Karsaz to Airport
    addEdge(9, 11, 9);  // Karsaz to Malir
    addEdge(10, 11, 3);  // Airport to Malir
    addEdge(11, 12, 13);  // Malir to Hadeed
    addEdge(11, 7, 6);  // Malir to Safoora
    addEdge(7,4, 5);  // Safoora to Highway
    addEdge(12, 4, 13);  // Hadeed to Highway
}

void displayGraph() {
    for (int i = 0; i < nodes.size(); i++) {
        cout << nodes[i].name << ": ";
        for (int j = 0; j < edges.size(); j++) {
            if (edges[j].start.name == nodes[i].name) {
                cout << edges[j].end.name << "(" << edges[j].weight << "), ";
            }
        }
        cout << "\n";
    }
}

void addEdge(int startIdx, int endIdx, int weight) {
    edges.push_back({ nodes[startIdx], nodes[endIdx], weight });
    edges.push_back({ nodes[endIdx], nodes[startIdx], weight });
}

void addNode(const string& name) {
    nodes.push_back({ name });
}
void lastHistory(Person p){

    for(int i = 0; i < p.lastRides.size(); i++){
        cout << p.lastRides[i].start.name << " to " << p.lastRides[i].end.name << "\n";
    }
    return;
}
void personMenu(Person p){
    int choice;
    do{
        cout << "> 1. View last Travel Route\n";
        cout << "> 2. Get Shorted Route\n";
        cout << "> 3. Show Map \n";
        cout << "> 4. Exit\n";
        cin >> choice;
        switch(choice){
            case 1:
                getShortestRoute();
                break;
            case 2:
                lastHistory(p);
            case 3:
                displayGraph();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice\n";
        }
    }while(choice != 4);
} 
vector<int> shortestRoute(int start_idx, int end_idx) {
    vector<int> dist(nodes.size(), numeric_limits<int>::max());
    vector<int> prev(nodes.size(), -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start_idx] = 0;
    pq.push({0, start_idx});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int i = 0; i < edges.size(); i++) {
            if (edges[i].start.name == nodes[u].name) {
                int v = -1;
                for (int j = 0; j < nodes.size(); j++) {
                    if (nodes[j].name == edges[i].end.name) {
                        v = j;
                        break;
                    }
                }
                int weight = edges[i].weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    vector<int> path;
    for (int at = end_idx; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    totalDistance = dist[end_idx];  

    return path;
}
void getShortestRoute(){
    int start_idx, end_idx;
    cout << "Enter your current location: \n";
    for(int i = 0; i < 13; i++){
        cout << i+1 << ". " << Area[i] << "\n";
    };
    int start;
    cout << "> Input: ";
    cin >> start;
    switch(start){
        case 1:
            start_idx = 0;
            break;
        case 2:
            start_idx = 1;
            break;
        case 3:
            start_idx = 2;
            break;
        case 4:
            start_idx = 3;
            break;
        case 5:
            start_idx = 4;
            break;
        case 6:
            start_idx = 5;
            break;
        case 7:
            start_idx = 6;
            break;
        case 8:
            start_idx = 7;
            break;
        case 9:
            start_idx = 8;
            break;
        case 10:
            start_idx = 9;
            break;
        case 11:
            start_idx = 10;
            break;
        case 12:
            start_idx = 11;
            break;
        case 13:
            start_idx = 12;
            break;
        default:
            cout << "Invalid choice\n";
    }
    cout << "Enter your destination: \n";
    for(int i = 0; i < 13; i++){
        cout << i+1 << ". " << Area[i] << "\n";
    };
    int end;
    cout << "> Input: ";
    cin >> end;
    switch(end){
        case 1:
            end_idx = 0;
            break;
        case 2:
            end_idx = 1;
            break;
        case 3:
            end_idx = 2;
            break;
        case 4:
            end_idx = 3;
            break;
        case 5:
            end_idx = 4;
            break;
        case 6:
            end_idx = 5;
            break;
        case 7:
            end_idx = 6;
            break;
        case 8:
            end_idx = 7;
            break;
        case 9:
            end_idx = 8;
            break;
        case 10:
            end_idx = 9;
            break;
        case 11:
            end_idx = 10;
            break;
        case 12:
            end_idx = 11;
            break;
        case 13:
            end_idx = 12;
            break;
        default:
            cout << "Invalid choice\n";
    }
    vector<int> path = shortestRoute(start_idx, end_idx);
    cout << "- - - - - - - - - - \n";
    cout << "Shortest Route To Your Destination : ";
    for (int i = 0; i < path.size(); i++) {
        cout << nodes[path[i]].name;
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << "\n";
    cout << "- - - - - - - - - - \n";
    cout << "Total distance: " << totalDistance << " Km \n";
    cout << "- - - - - - - - - - \n";
    cout << "Enjoy your ride\n";
    cout << "- - - - - - - - - - \n";
}
void Login(){
    int id;
    string password;
    cout << "- - - - - - - - - - \n";
    cout << "> Login In\n";
    cout << "- - - - - - - - - - \n";
    cout << "Enter your id: ";
    cin >> id;
    cout << "Enter your password: ";
    cin >> password;
    cout << "- - - - - - - - - - \n";
    for(int i = 0; i < people.size(); i++){
        if(people[i].id == id && people[i].password == password){
            personMenu(people[i]);
            return;
        }
    }

    cout << "Invalid id or password\n";
    cout << "- - - - - - - - - - \n";
    return;
}
void Register()
{
    Person p;
    cout << "- - - - - - - - - - \n";
    cout << "> Register Yourself \n";
    cout << "- - - - - - - - - - \n";
    cout << "> Enter your name: ";
    cin >> p.name;
    cout << "> Enter your id: ";
    cin >> p.id;
    cout << "> Enter your password: ";
    cin >> p.password;
    cout << "- - - - - - - - - - \n";
    people.push_back(p);
    return;
}
void mainMenu(){
    do{
        cout << "> Welcome To Rehnuma  \n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        int choice;
        cin >> choice;
        switch(choice){
            case 1:
                Register();
                break;
            case 2:
                Login();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout << "Invalid choice\n";
        }
    }while(true);
}