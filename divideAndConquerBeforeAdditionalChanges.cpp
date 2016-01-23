#include <iostream>
#include <iostream>
#include <cMath>
#include <cfloat>

using namespace std;

double bruteForce(double x[], double y[], int n);
double calcDistance(double x1, double y1, double x2, double y2);
void bruteAlgorithm();
void bruteAlgorithm2();
double min(double x, double y);
double divideAndConquerRec(int indexValue, double x[], double y[]);
double stripClosest(int size, float d, double x[], double y[]);
class Coord {
public:
    double x, y, x1, y1, distance = DBL_MAX;
    void setCoord(double x, double y){
        this->x = x;
        this->y = y;
    }
    void setClosestPair(double x, double y, double distance){
        this->x1 = x;
        this->y1 = y;
        this->distance = distance;
    }
};


int main(int argc, char *argv[]){
    // string space = " ";
    // string input = "";
    // string xCoord, yCoord;
    // double xPoints[10000];
    // double yPoints[10000];
    // int i = 0;
    
    // while (getline(cin, input)) {
    //     if (input == "") {
    //         continue;
    //     }
    //     if (input.find_first_not_of("-1234567890. ", 0) != std::string::npos){
    //         continue;
    //     }
    //     size_t firstSpace = input.find(space);
    //     if (input.find(space, firstSpace + 1) != std::string::npos){
    //         continue;
    //     }
        
    //     xCoord = input.substr(0, input.find(space));
    //     input.erase(0, input.find(space) + space.length()); //TODO: Check input so that wrong formats are not actually inputted in to the array
    //     yCoord = input;
    //     xPoints[i] = stod(xCoord, NULL);
    //     yPoints[i] = stod(yCoord, NULL);
    //     i++;
    // }
    // i--;
    // sort(xPoints, xPoints + i);
    // sort(yPoints, yPoints + i);

    // cout << "The answer is: " << divideAndConquerRec(i, xPoints, yPoints) << endl;
    bruteAlgorithm();
}


double divideAndConquerRec(int indexValue, double x[], double y[]){
    if (indexValue <= 2){
         return bruteForce(x, y, indexValue);
    }
    
    int mid = indexValue / 2;
    float midPointX = x[mid];
    float midPointY = y[mid];
    
    
    double smallLeft = divideAndConquerRec(mid, x, y);
    double smallRight = divideAndConquerRec(indexValue - mid, x+mid, y+mid);
    
    double d = min(smallLeft, smallRight);
    
    double stripX[indexValue];
    double stripY[indexValue];
    int j = 0;
    for (int i = 0; i < indexValue; i++){
        if (abs(x[i] - midPointX) < d){
            stripX[j] = x[i];
            stripY[j] = y[i];
            j++;
        }
    }
    return min(d, stripClosest(j, d, stripX, stripY));
    
}

double stripClosest(int size, float d, double x[], double y[])
{
    float min = d;
    
    sort(x, x + size);
    sort(y, y + size);
    
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (y[j] - y[i]) < min; ++j)
            if (calcDistance(x[i], y[i], x[j], y[j]) < min)
                min = calcDistance(x[i], y[i], x[j], y[j]);
    return min;
}

double min(double x, double y)
{
    return (x < y)? x : y;
}
double bruteForce(double x[], double y[], int n)
{
    double min = DBL_MAX;
    double tempMin = DBL_MAX;
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n; ++j){
            tempMin = calcDistance(x[i], y[i], x[j], y[j]);
            if (tempMin < min){
                min = tempMin;
                // *xCoord = x[i];
            }
        }
    }
    return min;
}



void bruteAlgorithm(){
    string space = " ";
    string input = "";
    string xCoord, yCoord;
    double x[10000];
    double y[10000];
    int i = 0;
    
    while (getline(cin, input)) {
        if (input == "") {
            continue;
        }
        if (input.find_first_not_of("-1234567890. ", 0) != std::string::npos){
            continue;
        }
        size_t firstSpace = input.find(space);
        if (input.find(space, firstSpace + 1) != std::string::npos){
            continue;
        }
        
        xCoord = input.substr(0, input.find(space));
        input.erase(0, input.find(space) + space.length()); //TODO: Check input so that wrong formats are not actually inputted in to the array
        yCoord = input;
        x[i] = stod(xCoord, NULL);
        y[i] = stod(yCoord, NULL);
        i++;
    }
    i--;
    
    double minDistance = DBL_MAX, minX1 = DBL_MAX, minY1 = DBL_MAX, minX2 = DBL_MAX, minY2 = DBL_MAX;
    double tempDistance;
    
    for (int a = 0; a < i; a++){
        for (int b = 0; b < i; b++){
            if ( a != b) {
                if (x[a] == 2) cout<< "bitch" << endl; //TODO: Note that invalid parameters are still an issue since "bitch" is still printed!!!!
                tempDistance = calcDistance(x[a], y[a], x[b], y[b]);
                if (tempDistance < minDistance){
                    minDistance = tempDistance;
                    minX1 = x[a];
                    minX2 = x[b];
                    minY1 = y[a];
                    minY2 = y[b];
                    cout << tempDistance << endl;
                }
            }
        }
    }
    printf("%.2f\n(%f, %f) (%f, %f)\n",minDistance, minX1, minY1, minX2, minY2);
}

double calcDistance(double x1, double y1, double x2, double y2){
    return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}
double calcDistance(Coord c1, Coord c2){
    return sqrt(pow((c2.x - c1.x), 2) + pow(c2.y - c1.y, 2));
}


void bruteAlgorithm2(){
    string space = " ";
    string input = "";
    string xCoord, yCoord;
    Coord myCoord[100000];
    Coord finalCoord;
    int i = 0;
    
    while (getline(cin, input)) {
        if (input == "") {
            continue;
        }
        if (input.find_first_not_of("-1234567890. ", 0) != std::string::npos){
            continue;
        }
        size_t firstSpace = input.find(space);
        if (input.find(space, firstSpace + 1) != std::string::npos){
            continue;
        }
        
        xCoord = input.substr(0, input.find(space));
        input.erase(0, input.find(space) + space.length()); //TODO: Check input so that wrong formats are not actually inputted in to the array
        yCoord = input;
        myCoord[i].x = stod(xCoord, NULL);
        myCoord[i].y = stod(yCoord, NULL);
        i++;
    }
    i--;
    
    double minDistance = DBL_MAX, minX1 = DBL_MAX, minY1 = DBL_MAX, minX2 = DBL_MAX, minY2 = DBL_MAX;
    double tempDistance;
    
    for (int a = 0; a < i; a++){
        for (int b = 0; b < i; b++){
            if ( a != b) {
                tempDistance = calcDistance(myCoord[a], myCoord[b]);
                if (tempDistance < finalCoord.distance){
                    finalCoord.setCoord(myCoord[a].x, myCoord[a].y);
                    finalCoord.setClosestPair(myCoord[b].x, myCoord[b].y, tempDistance);
                    cout << tempDistance << endl;
                }
            }
        }
    }
    printf("%.2f\n(%f, %f) (%f, %f)\n",finalCoord.distance, finalCoord.x, finalCoord.y, finalCoord.x1, finalCoord.y1);
}





























