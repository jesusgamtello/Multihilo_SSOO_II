#include <iostream>

class User{

    private:
        int id;
        std::string random_word;

    public:
        User(int id, std::string random_word){
            this -> id = id;
            this -> random_word = random_word;
        }
        int get_id(){return id;}
        std::string get_random_word(){return random_word;}
        void set_id(int id){
            this->id = id;
        }
        void set_random_word(std::string random_word){
            this->random_word = random_word;
        }

        
};

class Ilimited : public User{
    public:
        Ilimited(int id, std::string random_word):User(id,random_word){
           
        }
};

class Free : public User{
    private:
        int number_of_words;
    public:
        Free(int id, std::string random_word, int number_of_words):User(id,random_word){
            this -> number_of_words = number_of_words;
        }
        int get_number_of_words(){return number_of_words;}
        void set_number_of_words(int number_of_words){
            this -> number_of_words = number_of_words;
        }
        
};

class Premium_credits : public User{
    private:
        int credits;
    public:
        Premium_credits(int id, std::string random_word, int credits):User(id,random_word){
            this->credits = credits;
        }
        int get_credits(){return credits;}
        void set_credis(int credits){
            this -> credits = credits;
        }
        
};