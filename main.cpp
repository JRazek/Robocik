
#include <iostream>

#include <vector>
#include <cmath>

using namespace std;
struct Vector2f{
    float x;
    float y;
    Vector2f(float x, float y){
        this->x = x;
        this->y = y;
    }
};
struct Rectangle{
    Vector2f * min;
    Vector2f * max;
    Vector2f * stride;
    Rectangle(Vector2f * min, Vector2f * max, Vector2f * stride){
        this->min = min;
        this->max = max;
        this->stride = stride;
    }

    Vector2f * getMinPos(){
        return min;
    }
    Vector2f * getSize(){
        return new Vector2f(abs(min->x - max->x), abs(min->y - max->y));
    }
    Vector2f * getMaxPos(){
        return max;
    }
    void shit(Vector2f * shift){
        float height = max->y-min->y;
        float width = max->x-min->x;
        min->x = shift->x;
        max->y = shift->y;
        max->y = min->y + height;
        max->x = max->x + width;
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
    Vector2f * max = new Vector2f(0, 0);
    Vector2f * endPoint = new Vector2f(0, 0);
    int timePerCycle = 0;
    for(int i = 0; i < movesCount; i ++){
        int move = stoi(args[i]);
        if(timePerCycle + move + 1 > time){
            break;
        }
        moves.push_back(move);
        timePerCycle += move + 1;
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
    Vector2f point(stoi(args[0]), stoi(args[1]));
    Rectangle * movesBox = new Rectangle(new Vector2f(0, 0), max, endPoint);

    Vector2f *shiftVector = nullptr;
    if(movesBox->stride->x != 0 && movesBox->stride->y != 0) {
        float a = (movesBox->stride->y / movesBox->stride->x);
        float x = (point.y + a*point.x)/(2*a);
        float x1 = (point.y + a * point.x + movesBox->max->x*a)/(2*a);
        float x2 = (point.y + a*point.x - movesBox->max->y)/(2*a);

        Vector2f p (x, a * x);
        Vector2f p1(x1, a * x1 - movesBox->max->x * a);
        Vector2f p2(x2, a * x2 + movesBox->max->y);
        //get the distances
        float distToPointSquared = pow(p.x - point.x, 2) + pow(p.y - point.y, 2);
        float dToP1 = (pow(p.x - p1.x, 2) + pow(p.y - p1.y, 2));
        float dToP2 = (pow(p.x - p2.x, 2) + pow(p.y - p2.y, 2));
        if((point.x >= p.x && distToPointSquared <= dToP1) || (point.x <= p.x && distToPointSquared <= dToP2)){
            //vector of movement as shift to pos
            shiftVector = new Vector2f(point.y/a, point.y);
        }

    }
    else if(movesBox->stride->x == 0 && movesBox->stride->y != 0){
        if((point.x >= 0 && movesBox->max->x >= point.x) || (point.x <= 0 && movesBox->max->x <= point.x)){
            shiftVector = new Vector2f(0, point.y);
        }
    }
    else if(movesBox->stride->y == 0 && movesBox->stride->x != 0){
        if((point.y >= 0 && movesBox->max->y >= point.y) || (point.y <= 0 && movesBox->max->y <= point.y)){
            shiftVector = new Vector2f(point.x, 0);
        }
    }
    else{
        if(((point.y >= 0 && movesBox->max->y >= point.y) || (point.y <= 0 && movesBox->max->y <= point.y)) &&
            ((point.x >= 0 && movesBox->max->x >= point.x) || (point.x <= 0 && movesBox->max->x <= point.x))){
            shiftVector = new Vector2f(0, 0);
        }
    }
    int leftForMove = time % timePerCycle;
    int maxCycles = time / timePerCycle;
    int touches = 0;
    if(shiftVector != nullptr){
        Vector2f * maxVectorMove = new Vector2f(movesBox->stride->x * maxCycles, movesBox->stride->y * maxCycles);
        if(maxVectorMove->x >= shiftVector->x && maxVectorMove->y >= shiftVector->y){
            movesBox->shit(shiftVector);
            cout<<"ok";
        }
    }else{
        cout<<0;
    }
    return 0;
}