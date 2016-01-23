#include <iostream>
#include <iostream>
#include <cMath>
#include <cfloat>
#include <vector>
#include "divideAndConquer.h"

using namespace std;

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Please enter either \"basic\", \"brute\", or \"optimal\" following your program." << endl;
    } else if (strcmp(argv[1], "brute") == 0){
        bruteAlgorithm();
    } else if (strcmp(argv[1], "basic") == 0){
        divideAndConquer();
    } else if (strcmp(argv[1], "optimal") == 0){
        divideAndConquerOptimal();
    }
    return 0; 
}

void divideAndConquer(){
    string space = " ";
    string input = "";
    bool isDuplicate = false;
    string xCoord, yCoord;
    vector<Coord> myCoord;
    Coord tempCoord;
    Coord finalCoord;
    int i = 0, b = 0;
    
    while (getline(cin, input)){
        if (input == "") continue;
        if (input.find_first_not_of("-1234567890. ", 0) != std::string::npos) continue;
        if (input.find(space, 0) == std::string::npos) continue;
        size_t firstSpace = input.find(space);
        xCoord = input.substr(0, firstSpace);
        yCoord = input.substr(input.find_first_not_of(" ", xCoord.length() + 1));
        if (yCoord.find(space) != std::string::npos){
            int a = yCoord.find(space);
            if (yCoord.find_first_not_of(" ", a + 1) != std::string::npos){
                continue;
            }
        }
        tempCoord.x = stod(xCoord, NULL);
        tempCoord.y = stod(yCoord, NULL);
        for (std::vector<Coord>::iterator it = myCoord.begin(); it != myCoord.end(); ++it){
            if (isEqual(it->x, tempCoord.x) && isEqual(it->y, tempCoord.y)){
                isDuplicate = true;
            }
        }
        if (isDuplicate == false){
            myCoord.push_back(tempCoord);
            i++;
        } else{
            isDuplicate = false;
        }
    }
    if (myCoord.size() < 2){
        cout << "You must enter 2 or more data points." << endl;
        return;
    }
    Coord* copyMyCord = &myCoord[0];
    qsort(copyMyCord, i, sizeof(Coord), compareX);
    finalCoord = divideAndConquerRec(i, copyMyCord);
    printf("%.7f\n(%.7f, %.7f) (%.7f, %.7f)\n", finalCoord.distance, finalCoord.x, finalCoord.y, finalCoord.x1, finalCoord.y1);
}
void divideAndConquerOptimal(){
    string space = " ";
    string input = "";
    bool isDuplicate = false;
    string xCoord, yCoord;
    vector<Coord> myCoordX;
    vector<Coord> myCoordY;
    Coord tempCoord;
    Coord finalCoord;
    int i = 0, b = 0;
    
    while (getline(cin, input)){
        if (input == "") continue;
        if (input.find_first_not_of("-1234567890. ", 0) != std::string::npos) continue;
        if (input.find(space, 0) == std::string::npos) continue;
        size_t firstSpace = input.find(space);
        xCoord = input.substr(0, firstSpace);
        yCoord = input.substr(input.find_first_not_of(" ", xCoord.length() + 1));
        if (yCoord.find(space) != std::string::npos){
            int a = yCoord.find(space);
            if (yCoord.find_first_not_of(" ", a + 1) != std::string::npos){
                continue;
            }
        }
        tempCoord.x = stod(xCoord, NULL);
        tempCoord.y = stod(yCoord, NULL);
        for (std::vector<Coord>::iterator it = myCoordX.begin(); it != myCoordX.end(); ++it){
            if (isEqual(it->x, tempCoord.x) && isEqual(it->y, tempCoord.y)){
                isDuplicate = true;
            }
        }
        if (isDuplicate == false){
            myCoordX.push_back(tempCoord);
            myCoordY.push_back(tempCoord);
            i++;
        } else{
            isDuplicate = false;
        }
    }
    if (myCoordX.size() < 2){
        cout << "You must enter 2 or more data points." << endl;
        return;
    }

    sort(myCoordX.begin(), myCoordX.end(), vSortX);
    sort(myCoordY.begin(), myCoordY.end(), vSortY);

    finalCoord = divideAndConquerRecOptimal(i, myCoordX, myCoordY);
    printf("%.7f\n(%.7f, %.7f) (%.7f, %.7f)\n", finalCoord.distance, finalCoord.x, finalCoord.y, finalCoord.x1, finalCoord.y1);
}

Coord divideAndConquerRec(int n, Coord c[]){
    if (n <= 3){
        return bruteForce(c, n);
    }
    
    int mid = n / 2;
    Coord midC = c[mid];
    
    
    Coord smallLeft = divideAndConquerRec(mid, c);
    Coord smallRight = divideAndConquerRec(n - mid, c + mid);
    
    double d = min(smallLeft.distance, smallRight.distance);
    
    Coord smallestRecursive;
    if (d == smallLeft.distance){
        smallestRecursive = smallLeft;
    } else {
        smallestRecursive = smallRight;
    }
    
    Coord* stripC = new Coord[n];
    
    int j = 0;
    for (int i = 0; i < n; i++){
        if (abs(c[i].x - midC.x) < d){
            stripC[j].x = c[i].x;
            stripC[j].y = c[i].y;
            j++;
        }
    }
//    double finalMin = min(d, stripClosest(j, d, stripX, stripY));
    Coord possibleMin = stripClosest(j, d, stripC);
    delete []stripC;
    if (possibleMin.distance <  smallestRecursive.distance){
        return possibleMin;
    } else {
        return smallestRecursive;
    }
}

Coord divideAndConquerRecOptimal(int n, vector<Coord> cX, vector<Coord> cY){
    if (n <= 3){
        return bruteForce(cX, n);
    }
    
    int mid = n / 2;
    Coord midC = cX[mid];

    vector <Coord> Cyl;
    vector <Coord> Cyr; 

    for (int i = 0; i < n; i++)
    {
      if (cY[i].x <= midC.x)
         Cyl.push_back(cY[i]);
      else
         Cyr.push_back(cY[i]);
    }

    
    Coord smallLeft = divideAndConquerRecOptimal(mid, cX, Cyl);
    Coord smallRight = divideAndConquerRecOptimal(n - mid, *(cX[0] + mid*sizeof(Coord)), Cyr);

    double d = min(smallLeft.distance, smallRight.distance);
    
    Coord smallestRecursive;
    if (d == smallLeft.distance){
        smallestRecursive = smallLeft;
    } else {
        smallestRecursive = smallRight;
    }
    
    Coord* stripC = new Coord[n];
    
    int j = 0;
    for (int i = 0; i < n; i++){
        if (abs(cY[i].x - midC.x) < d){
            stripC[j].x = cY[i].x;
            stripC[j].y = cY[i].y;
            j++;
        }
    }

    Coord possibleMin = stripClosestOptimal(j, d, stripC);
    delete []stripC;
    if (possibleMin.distance <  smallestRecursive.distance){
        return possibleMin;
    } else {
        return smallestRecursive;
    }
}

Coord stripClosest(int size, double min, Coord c[]){
    Coord finalCoord;
    double tempDistance;
    qsort(c, size, sizeof(Coord), compareY);
    for (int i = 0; i < size; i++){
        for (int j = i + 1; j < size && (c[j].y - c[i].y < min); j++){
            tempDistance = calcDistance(c[i], c[j]);
            if (tempDistance < min){
                finalCoord.setCoord(c[i].x, c[i].y);
                finalCoord.setClosestPair(c[j].x, c[j].y, tempDistance);
                min = tempDistance;
            }
        }
    }
    return finalCoord;
}

Coord stripClosestOptimal(int size, double min, Coord c[]){
    Coord finalCoord;
    double tempDistance;
    
    for (int i = 0; i < size; i++){
        for (int j = i + 1; j < size && (c[j].y - c[i].y < min); j++){
            tempDistance = calcDistance(c[i], c[j]);
            if (tempDistance < min){
                finalCoord.setCoord(c[i].x, c[i].y);
                finalCoord.setClosestPair(c[j].x, c[j].y, tempDistance);
                min = tempDistance;
            }
        }
    }
    return finalCoord;
}

Coord bruteForce(Coord c[], int n){
    double tempMin = DBL_MAX;
    Coord finalCoord;
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n; ++j){
            tempMin = calcDistance(c[i], c[j]);
            if (tempMin < finalCoord.distance){
                finalCoord.setCoord( c[i].x, c[i].y);
                finalCoord.setClosestPair(c[j].x, c[j].y, tempMin);
            }
        }
    }
    return finalCoord;
}
Coord bruteForce(vector<Coord> c, int n){
    double tempMin = DBL_MAX;
    Coord finalCoord;
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n; ++j){
            tempMin = calcDistance(c[i], c[j]);
            if (tempMin < finalCoord.distance){
                finalCoord.setCoord( c[i].x, c[i].y);
                finalCoord.setClosestPair(c[j].x, c[j].y, tempMin);
            }
        }
    }
    return finalCoord;
}

void bruteAlgorithm(){
    string space = " ";
    string input = "";
    bool isDuplicate = false;
    string xCoord, yCoord;
    vector<Coord> myCoord;
    Coord tempCoord;
    Coord finalCoord;
    int i = 0, b = 0;
    
    while (getline(cin, input)){
        if (input == "") continue;
        if (input.find_first_not_of("-1234567890. ", 0) != std::string::npos) continue;
        if (input.find(space, 0) == std::string::npos) continue;
        size_t firstSpace = input.find(space);
        xCoord = input.substr(0, firstSpace);
        yCoord = input.substr(input.find_first_not_of(" ", xCoord.length() + 1));
        if (yCoord.find(space) != std::string::npos){
            int a = yCoord.find(space);
            if (yCoord.find_first_not_of(" ", a + 1) != std::string::npos){
                continue;
            }
        }

        tempCoord.x = stod(xCoord, NULL);
        tempCoord.y = stod(yCoord, NULL);

        for (std::vector<Coord>::iterator it = myCoord.begin(); it != myCoord.end(); ++it){
            if (isEqual(it->x, tempCoord.x) && isEqual(it->y, tempCoord.y)){
                isDuplicate = true;
            }
        }
        if (isDuplicate == false){
            myCoord.push_back(tempCoord);
            i++;
        } else{
            isDuplicate = false;
        }
    }
    if (myCoord.size() < 2){
        cout << "You must enter 2 or more data points." << endl;
        return;
    }
    double tempDistance;
    
    for (int a = 0; a < i; a++){
        for (int b = 0; b < i; b++){
            if ( a != b) {
                tempDistance = calcDistance(myCoord[a], myCoord[b]);
                if (tempDistance < finalCoord.distance){
                    finalCoord.setCoord(myCoord[a].x, myCoord[a].y);
                    finalCoord.setClosestPair(myCoord[b].x, myCoord[b].y, tempDistance);
                }
            }
        }
    }
    printf("%.7f\n(%.7f, %.7f) (%.7f, %.7f)\n",finalCoord.distance, finalCoord.x, finalCoord.y, finalCoord.x1, finalCoord.y1);
}

double calcDistance(Coord c1, Coord c2){
    return sqrt(pow((c2.x - c1.x), 2) + pow(c2.y - c1.y, 2));
}

int compareX(const void* a, const void* b)
{
    Coord*p1 = (Coord*)a,  *p2 = (Coord*)b;
    if (isEqual(p1->x, p2->x))
        return (p1->y - p2->y);
    else {
        return (p1->x - p2->x);
    }
}
int compareY(const void* a, const void* b)
{
    Coord*p1 = (Coord*)a,  *p2 = (Coord*)b;
    if (isEqual(p1->y, p1->y))
        return (p1->x - p2->x);
    else {
        return (p1->y - p2->y);
    }
}
bool isEqual(double a, double b){
    if ( abs(abs(a)-abs(b)) <= 0.00000001 ){
        return true;
    } else {
        return false;
    }
}
bool vSortX(const Coord a, const Coord b){
    if (abs(a.x) < abs(b.x)) 
        return true;
    else if (abs(a.x) == abs(b.x)){
        if (abs(a.y) < abs(b.y))
            return true;
    } else{
        return false;
    }
}
bool vSortY(const Coord a, const Coord b){
        if (abs(a.y) < abs(b.y)) 
        return true;
    else if (abs(a.y) == abs(b.y)){
        if (abs(a.x) < abs(b.x))
            return true;
    } else{
        return false;
    }
}
// bool sortByY(const Coord &a, const Coord &b){
//     return a.y < b.y;
// }
// bool sortByX(const Coord &a, const Coord &b){
//     return a.x < b.x;
// }















