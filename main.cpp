
#include <iostream>

#include <vector>
using namespace std;
struct Vector2I{
    int x;
    int y;
    Vector2I(int x, int y){
        this->x = x;
        this->y = y;
    }
};
struct Rectangle{
    Vector2I * min;
    Vector2I * max;
    Vector2I * stride;
    Rectangle(Vector2I * min, Vector2I * max, Vector2I * stride){
        this->min = min;
        this->max = max;
        this->stride = stride;
    }

    Vector2I * getMinPos(){
        return min;
    }
    Vector2I * getSize(){
        return new Vector2I(abs(min->x - max->x), abs(min->y - max->y));
    }
    Vector2I * getMaxPos(){
        return max;
    }
};
vector<string> split(string str, char divider){
    vector<string> result;

    string currWord = "";
    for(int i = 0; i < str.size(); i ++){
        currWord+=str[i];
        if(str[i] == divider || str.size()-1 == i){
            result.push_back(currWord);
            currWord = "";
        }
    }
    return result;
}

int main() {
    string line;
    getline(cin, line);
    vector<string> args = split(line, ' ');
    int movesCount = stoi(args[0]);
    int time = stoi(args[1]);
    int pivot = 0;

    vector<int> moves;
    getline(cin, line);
    args = split(line, ' ');
    Vector2I * max = new Vector2I(0,0);
    Vector2I * endPoint = new Vector2I(0,0);
    int timeUsed = 0;
    for(int i = 0; i < movesCount; i ++){
        int move = stoi(args[i]);
        if(timeUsed + move + 1 > time){
            break;
        }
        moves.push_back(move);
        timeUsed += move + 1;
        switch (pivot) {
            case 0:
                endPoint->y += move;
                break;
            case 1:
                endPoint->x += move;
                break;
            case 2:
                endPoint->y -= move;
                break;
            case 3:
                endPoint->x -= move;
                break;
        }
        if(endPoint->x > max->x){
            max->x = endPoint->x;
        }
        if(endPoint->y > max->y){
            max->y = endPoint->y;
        }
        pivot += 1;
        pivot %= 4;
    }
    getline(cin, line);
    args = split(line, ' ');
    Vector2I point(stoi(args[0]), stoi(args[1]));
    Rectangle * movesBox = new Rectangle(new Vector2I(0, 0), max, endPoint);
    int maxShift = time/timeUsed;//without the remaining small part
    int leftForMove = time % timeUsed;
    int touches = 0;
    if(movesBox->stride->y != 0) {
        float a = (((float) movesBox->stride->x) / ((float) movesBox->stride->y));
        int x = (point.y+a*point.x)/2*a;
        int x1 = (point.y + a * point.x + movesBox->max->x)/2*a;
        int x2 = (point.y + a * point.x - movesBox->max->y)/2*a;;
        Vector2I p (x,  a*x);
        Vector2I p1(x1, a*x1 - max->x);
        Vector2I p2(x2, a*x2 + max->y);
        //get the distances
    }
    return 0;
}