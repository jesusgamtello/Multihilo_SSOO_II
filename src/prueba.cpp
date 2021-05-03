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

int main(){
    User u(1,"f",400,-1);
    Petition p (u,"hola");

    u.set_limit_words(900);
    std::cout<<u.get_limit_words()<<std::endl;
}
    