#include <iostream>
#include "users.cpp"

int main(){
    User u (1, "f", 500, -1);

    Petition p(u,"hola");

    std::cout<< p.get_user().get_limit_words() <<" "<<p.get_random_word()<<std::endl;
}
    