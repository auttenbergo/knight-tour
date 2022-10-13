#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

const int n = 15;
const int MAX_SOLUTIONS = 100;
int board[n][n];

struct Location {
    int x;
    int y;
    bool operator==(const Location&) const;
};

bool Location::operator==(const Location& l) const {
    return x == l.x && y == l.y;
}

Location createLocation(int x, int y) {
    Location l;
    l.x = x;
    l.y = y;
    return l;
}

void fillBoardWithZeros() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
}

string locationToString(Location l) {
    string rv = "(" + to_string(l.x) + "," + to_string(l.y) + ")";
    return rv;
}


void printWay(vector<Location>& way) {
    for (int i = 0; i < way.size(); i++) {
        Location current = way[i];
        cout << locationToString(current) << " ";
    }
    cout << endl;
}

bool inBounds(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n)
        return false;
    return true;
}
bool inBounds(Location l) {
    return inBounds(l.x, l.y);
}

int countPossibleTransitions(Location curr) {
    int rv = 0;

    Location ul1 = createLocation(curr.x - 2, curr.y - 1);
    Location ul2 = createLocation(curr.x - 1, curr.y - 2);

    Location ur1 = createLocation(curr.x - 2, curr.y + 1);
    Location ur2 = createLocation(curr.x - 1, curr.y + 2);

    Location dl1 = createLocation(curr.x + 1, curr.y - 2);
    Location dl2 = createLocation(curr.x + 2, curr.y - 1);

    Location dr1 = createLocation(curr.x + 1, curr.y + 2);
    Location dr2 = createLocation(curr.x + 2, curr.y + 1);

    if (inBounds(ul1) && board[ul1.x][ul1.y] == 0) rv++;
    if (inBounds(ul2) && board[ul2.x][ul2.y] == 0) rv++;
    if (inBounds(ur1) && board[ur1.x][ur1.y] == 0) rv++;
    if (inBounds(ur2) && board[ur2.x][ur2.y] == 0) rv++;
    if (inBounds(dl1) && board[dl1.x][dl1.y] == 0) rv++;
    if (inBounds(dl2) && board[dl2.x][dl2.y] == 0) rv++;
    if (inBounds(dr1) && board[dr1.x][dr1.y] == 0) rv++;
    if (inBounds(dr2) && board[dr2.x][dr2.y] == 0) rv++;


    return rv;
}

bool compareLocationsHeuristic(Location l1, Location l2) {
    return countPossibleTransitions(l1) < countPossibleTransitions(l2);
}
bool compareLocations(Location l1, Location l2) {
    if (l1.x == l2.x)
        return l1.y < l2.y;
    return l1.x < l2.y;
}

vector<Location> getMoves(Location curr) {
    vector<Location> rv;

    Location ul1 = createLocation(curr.x - 2, curr.y - 1);
    Location ul2 = createLocation(curr.x - 1, curr.y - 2);

    Location ur1 = createLocation(curr.x - 2, curr.y + 1);
    Location ur2 = createLocation(curr.x - 1, curr.y + 2);

    Location dl1 = createLocation(curr.x + 1, curr.y - 2);
    Location dl2 = createLocation(curr.x + 2, curr.y - 1);

    Location dr1 = createLocation(curr.x + 1, curr.y + 2);
    Location dr2 = createLocation(curr.x + 2, curr.y + 1);

    if (inBounds(ul1) && board[ul1.x][ul1.y] == 0) rv.push_back(ul1);
    if (inBounds(ul2) && board[ul2.x][ul2.y] == 0) rv.push_back(ul2);
    if (inBounds(ur1) && board[ur1.x][ur1.y] == 0) rv.push_back(ur1);
    if (inBounds(ur2) && board[ur2.x][ur2.y] == 0) rv.push_back(ur2);
    if (inBounds(dl1) && board[dl1.x][dl1.y] == 0) rv.push_back(dl1);
    if (inBounds(dl2) && board[dl2.x][dl2.y] == 0) rv.push_back(dl2);
    if (inBounds(dr1) && board[dr1.x][dr1.y] == 0) rv.push_back(dr1);
    if (inBounds(dr2) && board[dr2.x][dr2.y] == 0) rv.push_back(dr2);

    sort(rv.begin(), rv.end(), compareLocationsHeuristic);

    return rv;
}
void findWay(Location curr,vector<vector<Location>>& ways, vector<Location>& way,int& usedCount) {

    if (ways.size() >= MAX_SOLUTIONS)
        return;

    if (usedCount == n * n) {
        //sort(way.begin(), way.end(),compareLocations);
        if (!count(ways.begin(), ways.end(), way))
            ways.push_back(way);
        return;
    }

    vector<Location> moves = getMoves(curr);
    if (moves.size() == 0)
        return;
    

    for (int i = 0; i < moves.size(); i++) {
        
        Location next = moves[i];

        board[next.x][next.y] = 1;
        usedCount++;
        way.push_back(next);

        findWay(next,ways,way,usedCount);

        board[next.x][next.y] = 0;
        usedCount--;
        way.pop_back();
    }
}


int main() {

    int startX = 5;
    int startY = 5;
    Location start = createLocation(startX,startY);

    fillBoardWithZeros();
    board[start.x][start.y] = 1;

    int usedCount = 1;

    vector<Location> way;
    vector<vector<Location>> ways;
    findWay(start,ways, way, usedCount);
    cout << "Starting location: " << locationToString(start) << " | Possible Ways: "<<ways.size()<<endl;
    for (int i = 0; i < ways.size(); i++) {
        cout << "Way N" << i + 1 <<" :" << endl;
        printWay(ways[i]);
    }
    

    return 0;

}