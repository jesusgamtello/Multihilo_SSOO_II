#include <iostream>

class final_result{

    private:
        int id;
        int line;
        int start_thread_line;
        int end_thread_line;
        std::string behind_word;
        std::string after_word;
        std::string exact_word;

    public:
        final_result(int id, int line, int start_thread_line, int end_thread_line, std::string behind_word, std::string exact_word, std::string after_word){
            this -> id = id;
            this -> line = line;
            this -> start_thread_line = start_thread_line;
            this -> end_thread_line = end_thread_line;
            this -> behind_word = behind_word;
            this -> exact_word = exact_word;
            this -> after_word = after_word;
        }
        int get_id(){return id;}
        int get_line(){return line;}
        int get_start_thread_line(){return start_thread_line;}
        int get_end_thread_line(){return end_thread_line;}
        std::string get_behind_word(){return behind_word;}
        std::string get_after_word(){return after_word;}
        std::string get_exact_word(){return exact_word;}

        
};