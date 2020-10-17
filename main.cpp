
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
    Vector2f * firstStride;
    int endingPivot;
    Rectangle(Vector2f * min, int firstMoveEndingPivot){
        this->min = min;
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
    static Vector2f * rotateStrideByPivot(int pivot, Vector2f * stride){
        pivot %= 4;
        switch (pivot) {
            case 0: return stride;
            case 1: return new Vector2f(stride->y, stride->x);
            case 2: return new Vector2f(-stride->x, -stride->y);
            case 3: return new Vector2f(-stride->y, -stride->x);
        }
    }
    Vector2f * getMinPos(){
        return min;
    }
    void move(Vector2f * v){
        this->min->x += v->x;
        this->min->y += v->y;
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
bool isInt(float n){
    return ((int)n == n);
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
    //Vector2f * max;
    int pivot = 0;
    Vector2f * firstCycleEndPoint;//this in this case is the stride of the first cycle

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
                firstCycleEndPoint = new Vector2f(x, y);
               // max = new Vector2f(maxX, maxY);
            }
        }
    }
    getline(cin, line);
    args = split(line, ' ');
    Vector2f * subjectPoint = new Vector2f(stoi(args[0]), stoi(args[1]));

    int endingPivot = (movesCount) % 4;//pivot that is the start of the next cycle
    Rectangle * movesBox = new Rectangle(new Vector2f(0,0), endingPivot);

    int cyclesToLoop = 1;   //starting with 1 so it wont take the first one.
                            // The result of loop is the index a[n] that is the pivot
    while(movesBox->getNCycleStartingPivot(cyclesToLoop) != 0 && cyclesToLoop++);

    int timePerLoop = timePerCycle * cyclesToLoop;
    Vector2f * cycleLoopStride = new Vector2f(0,0);
    for(int i = 0; i < cyclesToLoop; i ++){
        int p = movesBox->getNCycleStartingPivot(i);
        Vector2f * currVectorRotatedByPivot = movesBox->rotateStrideByPivot(p, firstCycleEndPoint);
        cycleLoopStride = new Vector2f(cycleLoopStride->x + currVectorRotatedByPivot->x, cycleLoopStride->y + currVectorRotatedByPivot->y);
    }
    //now time to check where the maximum x and y that our path has

    //need the point after the loop to get and get the loop stride vector.
    //From that the point where u can teleport to and if the givenTime is enough for such thing.
    cout<<timePerLoop<<"\n";

    int touches = 0;
    if(cycleLoopStride->x != 0 && cycleLoopStride->y != 0){
        float a = cycleLoopStride->y/cycleLoopStride->x;
        Vector2f * destinedPointWithYEqualToPoint = new Vector2f(subjectPoint->y/a, subjectPoint->y - cycleLoopStride->y);
    }
    else if(cycleLoopStride->x == 0 && cycleLoopStride->y != 0){

    }
    else if(cycleLoopStride->y == 0 && cycleLoopStride->x != 0){

    }
    else{

    }

    return 0;
}