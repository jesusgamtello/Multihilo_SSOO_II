#include <queue>
#include "users.cpp"
#define CLIENTS 50

void create_objects(){
    for(int i =0;i<CLIENTS;i++){
        int n_random = (rand() % 10) + 1;
        //std::cout << random<<std::endl;
        if(n_random<=2){
            Free f (3,"free",700);
        }
        else if (n_random>2)
        {
            if(n_random%2 == 0){
                Premium_credits p(2,"hey",600);
            }
            else{
                Ilimited i (4,"ilimited");      
            }
        }
        
    }
    
}
int main(){
    User u (1,"hola");
    std::cout << u.get_id() << " "<< u.get_random_word()<<std::endl;

    Premium_credits p(2,"hey",600);
    std::cout << p.get_id() << " "<< p.get_random_word()<<" "<<p.get_credits()<<std::endl;

    Free f (3,"free",700);
    std::cout << f.get_id() << " "<< f.get_random_word()<<" "<<f.get_number_of_words()<<std::endl;

    Ilimited i (4,"ilimited");
    std::cout << i.get_id() << " "<< i.get_random_word()<<std::endl;
    create_objects();
}