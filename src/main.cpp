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

#define CLIENTS 5
#define TOKENS 500
#define WORDS_FREE 500

//std::queue<User> queue_users;
std::vector<Petition> v_petition;

int contador = 0;
int buffer=0;
std::mutex m;
void select_random_word()
    {
        std::vector<std::string> v = {"actitud", "velocidad", "oro", "Cuál", "perdón", "Qué", "hola", "Cuando"};
        srand(time(NULL));
        int n_random = rand() % (v.size());

        std::cout << v[n_random] << std::endl;
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
        User u(id, "f", WORDS_FREE, -1);
        return u;
    }
    else if(n_random==2){
        User u(id, "l", -1, TOKENS);
        return u;
    }
    else{
        User u(id,"p",-1,-1); 
        return u;
    }

}
void create_client(int id){
    User u = random_type(id);
    Petition p(u,"hola");

    m.lock();
    v_petition.push_back(p);
    m.unlock();

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
 
    for (int i = 0; i < v_petition.size(); i++)
    {
        if (v_petition[i].get_user().get_type() == type)
        {
            return  i;
        }
    }
    return -1;
}
void initialize_search()
{
    int position;

    while (1)
    {
        if (v_petition.size() != 0)
        {
            int n_random = 1 + rand() % (11 - 1);
            if (n_random <= 2)
            {
                    position = search_type("f");
                if(position!=-1){
                    Petition p = v_petition[position];
                    std::cout << v_petition.size() << std::endl;
                    std::cout << "SOY CLIENTE FREE ID: " << p.get_user().get_id() << std::endl;
                    v_petition.erase(v_petition.begin()+position);
                    std::cout << v_petition.size() << std::endl;
                }
            }
            else if (n_random > 2)
            {
                if (n_random % 2 == 0)
                {
                        position = search_type("l");
                    if (position!=-1){
                        Petition p = v_petition[position];
                        std::cout << v_petition.size() << std::endl;
                        std::cout << "SOY CLIENTE LIMITADO ID: " << p.get_user().get_id() << std::endl;
                        v_petition.erase(v_petition.begin()+position);
                        std::cout << v_petition.size() << std::endl;

                    }
                }
                else
                {
                        position = search_type("p");
                    if(position!=-1){
                        Petition p = v_petition[position];
                        std::cout << v_petition.size() << std::endl;
                        std::cout << "SOY CLIENTE ILIMITADO PREMIUM ID: " << p.get_user().get_id() << std::endl;
                        v_petition.erase(v_petition.begin()+position);
                        std::cout << v_petition.size() << std::endl;

                    }
                }
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

    //for(int i = 0; i < v_petition.size(); i++){
   //     std::cout << v_petition[i].get_user().get_id() << std::endl;
    //}



}