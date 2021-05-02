#include <iostream>
#include "users.cpp"
#include <vector>
#include <thread>
#include <mutex>
#include <thread>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <fstream>
#include <string>
#include <chrono>
#include <queue>
#include "result.cpp"

#define TOKENS 500
#define WORDS_FREE 500

std::vector<Petition> v_petition;
std::queue<final_result> result; 
int id_result = -1;
int contador = 0;
int buffer=0;
std::mutex m;

std::string  select_random_word()
    {
        std::vector<std::string> v = {"actitud", "velocidad", "oro", "Cuál", "perdón", "Qué", "hola", "Cuando"};
        srand(time(NULL));
        int n_random = rand() % (v.size());

       return v[n_random];
    }

void generate_petition(User u, std::string word){
    Petition p(u,word);

    m.lock();
    v_petition.push_back(p);
    m.unlock();

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
    std::queue<final_result> cola;
    std::string word = select_random_word();
    User u = random_type(id);

    std::vector<User> v_user;
    generate_petition(u,word);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<< u.get_credits()<<std::endl;
    
    while(1){
        if(id_result == u.get_id()){
            cola = result;
            break;
            
        }
    }
    //llamar metodo print y limpiar cola y notify





}
void attend(Petition p){

//buscador y almacenar en cola result y condition variables cambiar id_result global con mutex 
//if cliente ilimitado buscar 
//else soy otro cliente
   


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
        if (buffer < 4){
            if (v_petition.size() != 0)
            {
                int n_random = 1 + rand() % (11 - 1);
                if (n_random <= 2)
                {
                    position = search_type("f");
                    if (position != -1)
                    {
                        Petition p = v_petition[position];
                        std::thread hilo(attend,p);
                        buffer++;
                        hilo.detach();
                        v_petition.erase(v_petition.begin() + position);
                    }
                }
                else if (n_random > 2)
                {
                    if (n_random % 2 == 0)
                    {
                        position = search_type("l");
                        if (position != -1)
                        {
                            Petition p = v_petition[position];
                            std::thread hilo(attend, p);
                            buffer++;
                            hilo.detach();
                            v_petition.erase(v_petition.begin() + position);
                            
                        }
                    }
                    else
                    {
                        position = search_type("p");
                        if (position != -1)
                        {
                            Petition p = v_petition[position];
                            std::thread hilo(attend, p);
                            buffer++;
                            hilo.detach();
                            v_petition.erase(v_petition.begin() + position);
                    
                        }
                    }
                }
            }
        }
    }
}

int main(){
    std::vector<std::thread> clients;

    for(int i = 0; i < 10; i++){
            clients.push_back(std::thread (create_client,i));
    }

    std::for_each(clients.begin(), clients.end(), std::mem_fn(&std::thread::join));
    std::thread searcher(initialize_search);
    searcher.join();

    //for(int i = 0; i < v_petition.size(); i++){
   //     std::cout << v_petition[i].get_user().get_id() << std::endl;
    //}



}
    