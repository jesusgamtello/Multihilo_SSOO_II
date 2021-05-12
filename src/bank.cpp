

#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <iostream>
#include <stdlib.h>
#include "main.cpp"
#include "users.cpp"




std::condition_variable x;
std::condition_variable y;
std::mutex sem;
std::mutex sem2;
int credits = 100;


void buscar(int numero_palabras){

std::unique_lock<std::mutex> c(sem);

for (int i=0 ; i<numero_palabras ; i++){
    x.wait(c,[numero_palabras]{return (credits!=0);});
    credits=credits-1;
    if (credits==0){
        y.notify_one();
    }

}
}

void add_cash(int numero ){
    std::unique_lock<std::mutex> c2(sem2);

    while(1){
        y.wait(c2,[numero]{return (credits==0);});
        std::cout <<credits<< std::endl;
        credits=numero+credits;
        std::cout <<"metiendo dinero"<< std::endl;
        std::this_thread::sleep_for (std::chrono::milliseconds(4000));
        x.notify_one();
    }
}

int main(){
    std::cout <<credits<< std::endl;

    std::thread hilo (buscar,1000);
    std::thread hilo2(add_cash,234);
    //std::thread hilo3(hallo);
    

    hilo.join();

    std::cout <<credits<< std::endl;


    return 0;

}


    /*srand(time(NULL));
    int n_random = 1 + rand() % (11 - 1);
    if(n_random<=2){
        std::cout << n_random<<std::endl;
        Free f (3,"free", WORDS_FREE);
    }
    else if (n_random>2)
    {
        if(n_random%2 == 0){
            Premium_credits p(2,"hey",TOKENS);
        }
        else{
            Ilimited i (4,"ilimited");      
        }
    }*/
        