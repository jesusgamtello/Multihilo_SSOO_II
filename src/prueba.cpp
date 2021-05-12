#include <queue>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <filesystem>
#include "users.cpp"

std::vector<User> f;
int main(){
    srand(time(NULL));

    int n_random = 1 + rand() % 3;
    std::cout<<"el numero random es "<<n_random<<std::endl;
    if (n_random==1){
        std::cout<<"hola"<<std::endl;
    }
    else if(n_random==2){
        std::cout<<"hola2"<<std::endl;
        
    }
    else{
        std::cout<<"hola3"<<std::endl;
    }
}
    