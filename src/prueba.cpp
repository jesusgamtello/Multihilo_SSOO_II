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
    User u(1,"f",400,-1,true);
    final_result fi(1, 5,5, 5, "hola", "hola", "hola");
    final_result p(1, 5,5, 5, "j", "j", "j");
    f.push_back(u);
    f[0].set_confirmated(false);

   
   std::cout<<f[0].is_confirmated()
}
    