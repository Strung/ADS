#include<iostream>
#include<string>

using namespace std;

class Problem{
public:
	string name;
	int ti;
	int di;
};

int H, N, t0, time, totaltime;
void swap(int &a, int &b);
void Sequence(Problem Problem[], int list[], int low, int high);

int main(void){

	int i, j;
	Problem Problem[9];
	while(cin>>H>>N>>t0 && H>=0){
		int list[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		time = 30000;
		for(i = 0; i < N; i++)
			cin>>Problem[i].name>>Problem[i].ti>>Problem[i].di;
		Sequence(Problem, list, 0, N);
	}
	return 0;
}

void swap(int &a, int &b){
    int temp = a ;
    a = b;
    b = temp;
}

void Sequence(Problem Problem[], int list[], int low, int high){
	if(low == high){
        for(int i = 0; i <= low; i++){
            

    }
    for(int i = low; i <= high; i++){
        swap(list[i], list[low]); 
        Sequence(Problem, list, low+1, high); 
        swap(list[i], list[low]);
	}
}