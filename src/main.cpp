#include <queue>
#include "users.cpp"
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <iostream>

#define CLIENTS 10
#define TOKENS 500
#define WORDS_FREE 500

//std::queue<User> queue_users;
std::vector<int> v_free;
std::vector<int> limited;
std::vector<int> premium;
int contador = 0;
int buffer=0;
std::mutex m;
void create_objects(){
    
    
}
/*User random_type(int id ){
    int n_random = 1 + rand() % 3;
    if (n_random==1){
        User u(id, "", "f", WORDS_FREE, 0);
        return u;
    }
    else if(n_random==2){
        User u(id, "", "l", 0, TOKENS);/////
        return u;
    }
    else{
        User u(id,"","p",0,0); 
        return u;
    }
}*/
void create_client_free(int id){

    Free f (id,"free",WORDS_FREE); 
    std::cout << "Soy el cliente "<< f.get_id()<< " limite de palabras:"<< f.get_number_of_words()<< std::endl;
    v_free.push_back(id);
    
}
void create_client_limited(int id){
    Premium_credits p(id,"",TOKENS);
    std::cout << "Soy el cliente "<< p.get_id()<< " Creditos :"<< p.get_credits()<< std::endl;
    limited.push_back(id);
}
void create_client_premium(int id){
    Ilimited i (id,"");
    std::cout << "Soy el cliente "<< i.get_id()<< " Soy ilimitado"<< std::endl;
    premium.push_back(id);

}
void attend(int id){
    std::cout<<"ATENDIENDO..."<< id<< std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(4000));
    m.lock();
    std::cout<<"termino..."<< id<< std::endl;
    buffer=buffer-1;
    m.unlock();
}
void initialize_search(){

    while(1){
        if(buffer!=4){
            int n_random = 1 + rand() % (11 - 1);
            if(n_random<=2){
                if (v_free.size()!=0){
                m.lock();
                buffer=buffer+1;
                m.unlock();
                std::thread hilo(attend,v_free.at((v_free.size()-1)));
                hilo.detach();
                v_free.pop_back();
                }
            }   
            else if (n_random>2)
            {
            if(n_random%2 == 0){
                if (limited.size()!=0){
                m.lock();
                buffer=buffer+1;
                m.unlock();
                std::thread hilo(attend,limited.at((limited.size()-1)));
                limited.pop_back();
                hilo.detach();
                }

            }
            else{
                if (premium.size()!=0){
                    m.lock();
                    buffer=buffer+1;
                    m.unlock();
                    std::thread hilo(attend,premium.at((premium.size()-1)));
                    premium.pop_back();
                    hilo.detach();
                }
            }
            }
        }
    }
}
int main(){
    std::vector<std::thread> clients;

    for(int i = 0; i < CLIENTS; i++){
        int n_random = 1 + rand() % 3;
        if (n_random==1){
            clients.push_back(std::thread (create_client_free,i));
        }
        else if(n_random==2){
            clients.push_back(std::thread (create_client_limited,i));
        }
        else{
            clients.push_back(std::thread (create_client_premium,i));
        }

    }

    std::for_each(clients.begin(), clients.end(), std::mem_fn(&std::thread::join));
    std::thread searcher(initialize_search);
    searcher.join();

    create_objects();


}