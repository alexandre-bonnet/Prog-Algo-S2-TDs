#include <iostream>
#include <unordered_set>
#include <fstream>

enum Direction{UP,DOWN,LEFT,RIGHT};
struct Position;
Position dirToPos(Direction dir);

struct Position{
    int x;
    int y;

    Position(int xPos, int yPos) : x(xPos), y(yPos) {}

    Position& operator+=(Position const& a) {
        x += a.x;
        y += a.y;
        return *this;
    }

    Position& operator+=(Direction const& dir) {
        Position a = dirToPos(dir);
        x += a.x;
        y += a.y;
        return *this;
    }
};

bool operator==(Position const& a, Position const& b) {
    return a.x == b.x && a.y == b.y;
}

namespace std {
    template <>
    struct hash<Position>{
        std::size_t operator()(const Position& pos) const {
            std::size_t h1 = std::hash<int>{}(pos.x);
            std::size_t h2 = std::hash<int>{}(pos.y);
            return h1 ^ h2;
        }
    };
}

struct Input_Structure{
    Position guardPos{-1,-1};
    Direction guardDir;
    std::unordered_set<Position> obstacles;
    int width = 0;
    int height = 0;
};

struct WalkResult {
    Position final_position;
    size_t steps_taken;
    std::unordered_set<Position> visited_positions;
    WalkResult(Position pos, size_t steps,std::unordered_set<Position> visited_pos) :
     final_position(pos), steps_taken(steps),visited_positions(visited_pos) {}
};

Position dirToPos(Direction dir){
    switch(dir) {
         case Direction::UP :
            return Position{0,-1};
        case Direction::DOWN :
            return Position{0,1};
        case Direction::LEFT :
            return Position{-1,0};
        case Direction::RIGHT :
            return Position{1,0};
      }
}



std::ostream& operator<<(std::ostream& os, Position const& b) {
    return os << '(' << b.x << ", " << b.y << ')';
}

Position operator+(Position a, Position const& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Position operator+(Position a, Direction const& dir) {
    Position b = dirToPos(dir);
        a.x += b.x;
        a.y += b.y;
    return a;
}

Direction turn_right(Direction const& dir){
    switch(dir) {
         case Direction::UP :
            return Direction::RIGHT;
        case Direction::DOWN :
            return Direction::LEFT;
        case Direction::LEFT :
            return Direction::UP;
        case Direction::RIGHT :
            return Direction::DOWN;
      }
}

Input_Structure parse_input(std::istream& input_stream) {
    Input_Structure input;
    int y = 0;

    for (std::string line{}; std::getline(input_stream, line, '\n') && line != ""; ) {
        input.width = int(line.size());
        for (int x = 0; x < int(line.size()); x++) {
            char c = line[x];
            Position pos{x, y};

            if (c == '#'){
                input.obstacles.insert(pos);
            } else if (c == '^'){
                input.guardPos = pos;
                input.guardDir = UP;
            } else if (c == 'v') {
                input.guardPos = pos;
                input.guardDir = DOWN;
            } else if (c == '<') {
                input.guardPos = pos;
                input.guardDir = LEFT;
            } else if (c == '>') {
                input.guardPos = pos;
                input.guardDir = RIGHT;
            }
        }
        ++y;
    } input.height = y;
    if (input.guardPos==Position{-1,-1}){
        std::cout<<"Guard not found"<<std::endl;
    }
    return input;
}

bool is_inside(Position const& a, int width, int height) {
    return (a.x >= 0 && a.x < width) && (a.y >= 0 && a.y < height);
}


WalkResult simulation(Input_Structure input){
    Position pos = input.guardPos;
    Direction dir = input.guardDir;
    size_t steps{0};
    std::unordered_set<Position> visited_positions;
    visited_positions.insert(pos);
    while (true) {
        Position next = pos + dir;
        if (!is_inside(next, input.width, input.height)) {
            pos = next;
            break;
        }
        if (input.obstacles.find(next) != input.obstacles.end()) {
            dir = turn_right(dir);
        } else {
            pos = next;
            steps++;
            visited_positions.insert(pos);
        }
    }return WalkResult(pos,steps,visited_positions);
}


int main() {
    std::ifstream file("../src/input_guard_patrol.txt");

    WalkResult output = simulation(parse_input(file));

    std::cout << "Position finale : " << output.final_position << '\n';
    std::cout << "Nombre de pas : " << output.steps_taken << '\n';
    std::cout << "Nombre de positions visitees : " << output.visited_positions.size() << '\n';
}