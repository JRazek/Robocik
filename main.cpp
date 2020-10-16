
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
    Vector2f point(stoi(args[0]), stoi(args[1]));
    Rectangle * movesBox = new Rectangle(new Vector2f(0, 0), max, endPoint);
    int maxShift = time/timeUsed;//without the remaining small part
    int leftForMove = time % timeUsed;
    int touches = 0;
    if(movesBox->stride->y != 0) {
        float a = (movesBox->stride->x / movesBox->stride->y);
        float x = (point.y + a*point.x)/(2*a);
        float x1 = (point.y + a * point.x + movesBox->max->x*a)/(2*a);
        float x2 = (point.y + a*point.x - movesBox->max->y)/(2*a);

        Vector2f p (x, a * x);
        Vector2f p1(x1, a * x1 - movesBox->max->x * a);
        Vector2f p2(x2, a * x2 + movesBox->max->y);
        //get the distances

        int distToPointSquared = pow(p.x - point.x, 2) + pow(p.y - point.y, 2);
        if(((pow(p.x - p1.x, 2) + pow(p.y - p1.y, 2)) - distToPointSquared >= 0 ) ||
            ((pow(p.x - p2.x, 2) + pow(p.y - p2.y, 2)) - distToPointSquared >= 0 )){
            
        }

    }
    return 0;
}