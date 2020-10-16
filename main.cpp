
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
    void changePos(Vector2f * shift){
        float height = max->y - min->y;
        float width = max->x - min->x;
        min->x = shift->x;
        min->y = shift->y;
        max->y = min->y + height;
        max->x = max->x + width;
    }
    bool pointBelongs(Vector2f point){
        if(min->x <= point.x && max->x >= point.x && min->y <= point.y && max->y >= point.y){
            cout<<"im here";
        }
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

    Vector2f * cycleVector = movesBox->stride;

    int maxCycles = time / timePerCycle;
    Vector2f * maxMove = new Vector2f(cycleVector->x * maxCycles, cycleVector->y * maxCycles);

    int destOriginY = 0;
    if(cycleVector->y != 0)
        destOriginY = point.y - movesBox->getSize()->y;
    int destOriginX = 0;
    if(cycleVector->x != 0)
        destOriginX = destOriginY/(cycleVector->y/cycleVector->x);

    int touches = 0;
    int timeLeft = time;
    timeLeft -= 0;
    Vector2f * neededMove = new Vector2f(destOriginX, destOriginY);
    if(maxMove->x - neededMove->x >= 0 && maxMove->x*neededMove->x >= 0
        && maxMove->y - neededMove->y >= 0 && maxMove->y*neededMove->y >= 0){
        movesBox->changePos(neededMove);
        if(movesBox->pointBelongs(point)){

        }
    }
    cout<<touches;
    return 0;
}