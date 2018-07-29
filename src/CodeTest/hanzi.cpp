#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

int main(){
	string hanzi;
	while(cin >> hanzi){
		cout << hanzi << endl;
		cout << hanzi.size() << endl;
		printf("%d\n", hanzi[0] & 0xff);	
		printf("%x\n", hanzi[1]);	
		printf("%x\n", hanzi[2]);	
	}

	return 0;
}
