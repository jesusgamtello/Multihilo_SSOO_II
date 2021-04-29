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
std::vector<Petition> v_petition;
std::vector<std::string> result; 
int id_result;
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
    std::string word = select_random_word();
    User u = random_type(id);

    generate_petition(u,word);
    //bloquear

    // se desbloquea que es el id, coge el reulstado y se lo queda, que si no lo es tiene que seguir bloqueado por tanto el while() 

    // que cuaando coja el resultado si es suyo notifica a los demás que están eseprando para guaradar el resultado y break del while y termina 



}
void attend(Petition p){

    if(p.get_user().get_type()=="p"){

        //buscar palabras

        // guardar resultado en variable result, y bloquear demás objetos que quieran entrar por ejemplo diciendo que sea distinto de 0 el size()

        // notificaría a los clientes de que hay un resultado
        
    }else{
        std::cout << "SOy otro tipo de cliente"<< std::endl;
    }


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