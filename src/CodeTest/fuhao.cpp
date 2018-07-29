#include <stdio.h>
#include <string>

using namespace std;

int main(){

	printf("%d\n", ',');		
	printf("%d\n", '.');		
	printf("%d\n", '-');		
	printf("%d\n", '"');		
	printf("%d\n", '>');		


	string fuhao("。");
	printf("%d\n", fuhao[0]);
	printf("%ld\n", fuhao.size());

	return 0;
}
