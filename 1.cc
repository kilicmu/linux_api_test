#include<iostream>
#include<cstring>
using namespace std;

int main(){
    char buff[1024];
    // memset(buff, 0, sizeof(buff));
    strcat(buff, "hello");
    cout << sizeof(buff) << endl;
}