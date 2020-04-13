#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

enum class State {kObstacle, kEmpty, kClosed, kPath, kStart, kFinish};
const int delta[4][2] = {{0,1}, {1,0}, {-1,0}, {0,-1}}; // for expanding neighbours

std::vector<State> ParseLine(std::string &line) {

    std::vector <State> returnVec;
    std::istringstream my_stream(line);
    int i; char c;
    while(my_stream >> i >> c && c == ',') {

        if(i == 0) returnVec.push_back(State::kEmpty);
        else returnVec.push_back(State::kObstacle);
    } // end of; while0

    return returnVec;
} // end of; parseLine()

std::string CellString(State &s) {

    switch(s) {
        case State::kEmpty: return "0   ";
        case State::kStart: return "S   ";
        case State::kFinish: return "F   ";
        case State::kPath: return "p   ";
        case State::kObstacle: return "Z   ";
        default: return "0   ";
    } // end of; switch0
} // end of; cellString()

void PrintBoard(std::vector<std::vector<auto>> &board) {

    for(auto i : board){

        for(auto x : i){  std::cout << CellString(x); } // end of; for1
        std::cout << std::endl;
    } // end of; for0
} // end of; printBoard()

std::vector<std::vector<State>> ReadBoardFile(std::string path) {

    std::ifstream my_file(path);
    std::vector<std::vector<State>> board{};
    if(my_file){

        std::string line;
        while(getline(my_file, line)) {

            std::vector<State> row = ParseLine(line);
            board.push_back(row);
        } // end of; while0
    } // end of; if0

    return board;
} // end of; readBoardFile()


// A* Algorithm functions

bool Compare(std::vector<int> &first, std::vector<int> &second) {

    // f = g + h      , fvalue is being compared to sort
    if((first[2]+first[3]) > (second[2]+second[3])) return true;
    return false;
} // end of; Compare()

void CellSort(std::vector<std::vector<int>> *vec) { sort(vec->begin(), vec->end(), Compare); } // end of; cellSort()

int Heuristic(int &x1, int &y1, int &x2, int &y2) { return abs(x1-x2) + abs(y1-y2); } // end of; Heuristic()

void AddToOpen(int x, int y, int g, int h, auto &vecOpenNodes, auto &vecGrid) {

    vecOpenNodes.push_back(std::vector<int>{x, y, g, h});
    vecGrid[x][y] = State::kClosed;
} // end of; addToOpen()

bool CheckValidCell(int &x, int &y, auto &grid) {

    if((x >= 0 && x < grid.size()) && (y >= 0 && y < grid[0].size())) // checks that point is on grid
        return grid[x][y] == State::kEmpty; // checks that point not empty

    return false;
} // end of; CheckValidCell()

void ExpandNeighbours(auto &curNode, auto &openVec, auto &grid, int arr[]) {

    int curX = curNode[0], curY = curNode[1], curG = curNode[2];
    int x2, y2, g2, h2;
    for(int i=0; i<4; ++i) {

        x2 = curX + delta[i][0];
        y2 = curY + delta[i][1];
        if(CheckValidCell(x2, y2, grid)) {

            g2 = curG + 1;
            h2 = Heuristic(x2, y2, arr[0], arr[1]);
            AddToOpen(x2, y2, g2, h2, openVec, grid);
        } // end of; if0
    } // end of; for0
} // end of; ExpandNeighbours()

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> &grid, int start[2], int goal[2]) {

    std::vector<std::vector<int>> open{};
    int x = start[0];
    int y = start[1];
    int g = 0; // cost
    int h = Heuristic(x, y, goal[0], goal[1]); // heuristic value of point
    AddToOpen(x, y, g, h, open, grid);

    while(!open.empty()) {

        CellSort(&open);
        auto current = open.back();
        open.pop_back();
        x = current[0], y = current[1];
        grid[x][y] = State::kPath;
        if(x == goal[0] && y == goal[1]) {
            grid[start[0]][start[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;
            std::cout << "\nGoal has been Reached!\n";
            return grid;
        } // end of; if0

        ExpandNeighbours(current, open, grid, goal);
    } // end of; while0

    std::cout << "\nNo path found!\n";
    return std::vector<std::vector<State>>{};
} // end of; Search()


int main()
{
    int start[2] = {0, 0};
    int goal[2] = {4, 5};

    auto board = ReadBoardFile("files/1.board");
    PrintBoard(board);
    auto solution = Search(board, start, goal);
    PrintBoard(solution);

    return 0;
}
