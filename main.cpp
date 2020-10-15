
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
    void moveToY(int y){
        int diffY = max->y-min->y;
        int diffX = max->x-min->x;
        this->min->y = y;
        this->min->x = y*stride->x/stride->y;
        this->max->y = min->y + diffY;
        this->max->x = min->x + diffX;
        cout<<"";
    }
    void moveNTimes(int n ){
        int newY = min->y + stride->y;
        moveToY(newY);
    }
    Vector2I * getMinPos(){
        return min;
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
    int maxShift = time / timeUsed;
    movesBox->moveNTimes(maxShift);

    int touches = 0;
    if(movesBox->getMinPos()->x <= point.x && movesBox->getMaxPos()->x >= point.x){
        Vector2I * checkingPoint = new Vector2I(movesBox->getMinPos()->x, movesBox->getMinPos()->y);
        for(int i = 0; i < moves.size(); i ++){
            int move = moves.at(i);
            Vector2I * prevPoint = new Vector2I(checkingPoint->x, checkingPoint->y);
            switch (pivot) {
                case 0:
                    checkingPoint->y += move;
                    break;
                case 1:
                    checkingPoint->x += move;
                    break;
                case 2:
                    checkingPoint->y -= move;
                    break;
                case 3:
                    checkingPoint->x -= move;
                    break;
            }
            if((prevPoint->y <= point.y && checkingPoint->y >= point.y) || (prevPoint->y >= point.y && checkingPoint->y <= point.y) ||
                    (prevPoint->x <= point.x && checkingPoint->x >= point.x) || (prevPoint->x >= point.x && checkingPoint->x <= point.x)){
                touches ++;
            }
            pivot += 1;
            pivot %= 4;
        }
    }
    cout<<touches;
    return 0;
}