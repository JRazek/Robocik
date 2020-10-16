
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
    Vector2f * size;
    Vector2f * firstStride;
    int endingPivot;
    Rectangle(Vector2f * min, Vector2f * max, Vector2f * stride, int endingPivot){
        this->min = min;
        this->max = max;
        this->size = new Vector2f(max->x - min->x, max->y - min->y);
        this->firstStride = stride;
        this->endingPivot = endingPivot;
    }
    Vector2f * getNStride(int n){
        n %= 4;
        Vector2f * strideN;
        switch (endingPivot) {
            case 0:
                if(n == 0) strideN = new Vector2f(firstStride->x,firstStride->y);
                else if(n == 1) strideN = new Vector2f(firstStride->y,firstStride->x);
                else if(n == 2) strideN = new Vector2f(-firstStride->x,-firstStride->y);
                else if(n == 3) strideN = new Vector2f(-firstStride->y,-firstStride->x);
                break;
            case 1:
                n %= 2;
                if(n == 0) strideN = new Vector2f(firstStride->x,firstStride->y);
                else if(n == 1) strideN = new Vector2f(-firstStride->x,-firstStride->y);
                break;
            case 2:
                if(n == 0) strideN = new Vector2f(firstStride->x,firstStride->y);
                else if(n == 1) strideN = new Vector2f(-firstStride->y,firstStride->x);
                else if(n == 2) strideN = new Vector2f(-firstStride->x,-firstStride->y);
                else if(n == 3) strideN = new Vector2f(firstStride->y,-firstStride->x);
                break;
            case 3:
                strideN = firstStride;
                break;
        }
        return strideN;
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
    bool pointBelongs(Vector2f point){
        return (min->x <= point.x && max->x >= point.x && min->y <= point.y && max->y >= point.y);
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
    int endingPivot;
    for(int i = 0; i < movesCount; i ++){
        int move = stoi(args[i]);
        if(timePerCycle + move + 1 > time){
            endingPivot = pivot;
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
        if(i == movesCount -1)
            endingPivot = pivot;
    }
    getline(cin, line);
    args = split(line, ' ');
    Vector2f point(stoi(args[0]), stoi(args[1]));
    Vector2f * firstStride = new Vector2f(endPoint->x, endPoint->y);
    Rectangle * movesBox = new Rectangle(new Vector2f(0,0), max, firstStride, endingPivot);

    return 0;
}