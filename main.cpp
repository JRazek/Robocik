
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
    Rectangle(Vector2f * min, Vector2f * max, int firstMoveEndingPivot){
        this->min = min;
        this->max = max;
        this->size = new Vector2f(max->x - min->x, max->y - min->y);
       // this->firstStride = stride;
        this->endingPivot = firstMoveEndingPivot;
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
    int getNCycleStartingPivot(int n){
        switch (endingPivot) {
            case 0: return 0;
            case 1: return n%4;
            case 2: return (n%2)*2;
            case 3: return 3 - (n+3)%4;
        }
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
    void move(Vector2f * v){
        this->min->x += v->x;
        this->max->x += v->x;
        this->min->y += v->y;
        this->max->y += v->y;
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
    long int movesCount = stoll(args[0]);
    long int givenTime = stoll(args[1]);

    getline(cin, line);
    args = split(line, ' ');
    /**
     * counting the time per cycle here
     */
    int timePerCycle = 0;  //remember that the last cycle will take movesCount -1
                                    // as the pivot wont be needed in the end
    Vector2f * max;
    int pivot = 0;
    Vector2f * cycleEndPoint;//this in this case is the stride of the first cycle
    {
        int x = 0;
        int y = 0;
        int maxX = 0;
        int maxY = 0;
        for (int i = 0; i < movesCount; i++) {
            int currMove = stoi(args[i]);
            timePerCycle += currMove + 1;
            switch (pivot) {
                case 0:
                    y += currMove;
                    break;
                case 1:
                    x += currMove;
                    break;
                case 2:
                    y -= currMove;
                    break;
                case 3:
                    x -= currMove;
                    break;
            }
            if (x > maxX)
                maxX = x;
            if (y > maxY)
                maxY = y;
            pivot += 1;
            pivot %= 4;
            if (i == (movesCount - 1)) {
                cycleEndPoint = new Vector2f(x, y);
                max = new Vector2f(maxX, maxY);
            }
        }
    }


    int endingPivot = (movesCount) % 4;//pivot that is the start of the next cycle
    Rectangle * movesBox = new Rectangle(new Vector2f(0,0), max, endingPivot);

    int cyclesToLoop = 1;   //starting with 1 so it wont take the first one.
                            // The result of loop is the index a[n] that is the pivot
    while(movesBox->getNCycleStartingPivot(cyclesToLoop) != 0 && cyclesToLoop++);

    int timePerLoop = timePerCycle * cyclesToLoop;
    Vector2f * cycleLoopStride = ?

    //need the point after the loop to get and get the loop stride vector.
    //From that the point where u can teleport to and if the givenTime is enough for such thing.
    cout<<timePerLoop<<"\n";


    return 0;
}