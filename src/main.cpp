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
std::vector<User> v_users;

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
}*/ // User(int id, std::string random_word,std::string type,int limit_words,int credits)
User random_type(int id){
    
    int n_random = 1 + rand() % 3;
    if (n_random==1){
        User u(id, "", "f", WORDS_FREE, -1);
        return u;
    }
    else if(n_random==2){
        User u(id, "", "l", -1, TOKENS);
        return u;
    }
    else{
        User u(id,"","p",-1,-1); 
        return u;
    }

}
void create_client(int id){
    User u = random_type(id);
    v_users.push_back(u);
}
void attend(int id){
    std::cout<<"ATENDIENDO..."<< id<< std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(4000));
    m.lock();
    std::cout<<"termino..."<< id<< std::endl;
    buffer=buffer-1;
    m.unlock();
}
int search_type(std::string type){
 
    for (int i = 0; i < v_users.size(); i++)
    {
        if (v_users[i].get_type() == type)
        {
            return  v_users[i].get_id();
        }
    }
    return -1;
}
void initialize_search(){
    int id;

    while(1){
        int n_random = 1 + rand() % (11 - 1);
        if (n_random <= 2)
        {
            id=search_type("f");
        }
        else if (n_random > 2)
        {
            if (n_random % 2 == 0)
            {
            }
            else
            {
            }
        }
    }
}
int main(){
    std::vector<std::thread> clients;

    for(int i = 0; i < CLIENTS; i++){
            clients.push_back(std::thread (create_client,i));
    }

    std::for_each(clients.begin(), clients.end(), std::mem_fn(&std::thread::join));
    std::thread searcher(initialize_search);
    searcher.join();

    create_objects();


}