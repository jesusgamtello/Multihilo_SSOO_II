#include<iostream>
#include"result.cpp"
class User{

    private:
        int id;
        std::string type;
        int limit_words;
        int credits;
        std::queue<final_result> result;
        bool confirmated;
        

    public:
        User(int id, std::string type,int limit_words,int credits,bool confirmated ){
            this -> id = id;
            this -> type = type;
            this -> limit_words = limit_words;
            this -> credits = credits;
            //this -> result = result;
            this -> confirmated = confirmated;
        }
        //getters
        int get_id(){return id;}
        std::string get_type(){return type;}
        int get_limit_words(){return limit_words;}
        int get_credits(){return credits;}
        std::queue<final_result> get_result(){return result;}
        bool is_confirmated(){return confirmated;}
        //setters
        void set_id(int id){
            this->id = id;
        }
        void set_type(std::string type){
            this->type = type;
        }
        void set_limit_words(int limit_words){
            this->limit_words = limit_words;
        }
        void set_credits(int credits){
            this->credits = credits;
        }
        void introduce(final_result f){
            result.push(f);
        }
        void set_confirmated(bool confirmated){
            this->confirmated=confirmated;
        }
        void print_q(){
            while(!result.empty()){
                std::cout<<result.front().get_after_word()<<std::endl;
                result.pop();
            }
        }
    

        
};
/*class Petition{

    private:
        User user;
        std::string random_word;
        
       
        

    public:
        Petition(User user, std::string random_word):user(user),random_word(random_word){}
          
        //getters
        User get_user(){return user;}
        std::string get_random_word(){return random_word;}
        //setters
        void set_user(User user){
            this->user = user;
        }
        void set_random_word(std::string random_word){
            this->random_word = random_word;
        }
        

        
};*/
class Petition{

    private:
        int id;
        std::string random_word;
        
       
        

    public:
        Petition(int id, std::string random_word):id(id),random_word(random_word){}
          
        //getters
        int get_id(){return id;}
        std::string get_random_word(){return random_word;}
        //setters
        void set_id(int id){
            this->id = id;
        }
        void set_random_word(std::string random_word){
            this->random_word = random_word;
        }
        

        
};

