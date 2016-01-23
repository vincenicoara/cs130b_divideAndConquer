#include <iostream>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]){
	if (argc != 2) { 
		printf("%s\n", "You must enter the number of points you want generated");
	} else {
		int numberOfRandomPairs = atoi(argv[1]);
		int min = -10000;
		int max = 10000;
	
		srand(time(NULL));
		for (int i = 0; i < numberOfRandomPairs; i++){
			printf("%.9f %.9f\n", min + (max - min)*(double)rand() / RAND_MAX
				, min + (max - min)*(double)rand() / RAND_MAX);
		}
	}
	


	return 0;
}
