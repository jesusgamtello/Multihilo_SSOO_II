/**************************************************************
 * Project:         Práctica 3
 * 
 * Program name:    main.cpp
 
 * Author:          Jesús Gamero Tello and Pedro Millan Alvarez
 * 
 * Date created:    13/5/2021
 * 
 * Purpose:         some clients make petitions of search in the books that we have in
 *                  the directory utils/. The clients are generated randomly, and there are
 *                  types of clients, type "l" who is premium limited, client "p" who is premium
 *                  and clients "f" who are clients of type free. Clients of type free and premium 
 *                  limited have a number of tokens or words to search. 
 * 
 ****************************************************************/
#include <queue>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <filesystem>
#include "../include/colors.h"

#include "users.cpp"

#define CLIENTS 50
#define TOKENS 500
#define WORDS_FREE 100
#define N 4

//std::queue<User> queue_users;
std::vector<Petition>           v_petition;
std::queue<final_result>        result;
std::vector<Petition>           v_attending;
std::vector<User>               v_users;
std::queue<int>                 v_payments;
int                             buffer                  =   0;
std::mutex                      m;
std::mutex                      sem_cv;
std::condition_variable         cv;
//bank
std::mutex                      bank;
std::condition_variable         y;

//globals ssooiigle
std::queue<final_result>        final_queue;
std::queue<final_result>        aux_queue;
std::mutex                      sem;

//methods ssooiigle
void                            start_message();
int                             count_total_lines(std::string book);
void                            read_file(std::string book, std::string word_argv, int id, int start, int end, int t_id);
void                            find_word(std::string word_argv, int number_of_lines, std::string line, int id, int start, int end, int t_id);
void                            divide_in_threads(std::string book, std::string word_argv, int num_threads, int number_of_lines, int t_id);
void                            order_queue(int id);
void                            print(std::queue<final_result> q);
std::string                     clean_word(std::string word_read);
void                            read_dir(Petition p);

//methods multi_thread

std::string                     select_random_word();
void                            generate_petition(User u, std::string word);
User                            random_type(int id);
void                            create_client(int id);
void                            attend(Petition p);
int                             search_type(std::string type);
void                            initialize_search();
int                             find_position(int t_id);
int                             search_user(Petition p);
void                            add_cash();
void                            write_results(int id, std::string text);

int main()
{
    std::vector<std::thread>    clients;
    std::thread                 searcher(initialize_search);
    std::thread                 bank(add_cash);
    searcher.detach();
    bank.detach();

    for (int i = 0; i < CLIENTS; i++)
    {
        clients.push_back(std::thread(create_client, i));
    }
    std::for_each(clients.begin(), clients.end(), std::mem_fn(&std::thread::join));

    return 0;

    
}
int find_position(int t_id)
{
    for (int i = 0; i < v_users.size(); i++)
    {
        if (v_users[i].get_id() == t_id)
        {
            return i;
        }
    }
    return -1;
}
void start_message()
{
    std::cout << BOLDMAGENTA << "WELCOME TO THE SEARCHER :: " << BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "II" << BOLDBLUE << "GL" << BOLDGREEN << "E" << BOLDRED << RESET << std::endl;
    std::cout << std::endl;
}

//code from ssooiigle

/******************************************************
 * Function:    count_total_lines
 * Date:     14/4/2021
 * Input arguments:  book book's path
 * Purpose:          Count the number of the specified file
 ******************************************************/
int count_total_lines(std::string book)
{
    std::string line;
    int number_of_lines = 0;
    //std::string     path                =   "./utils/"+book;
    std::ifstream file(book);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            number_of_lines++;
        }
        file.close();
    }
    else
        std::cout << "Unable to open file or file doesn't exist" << std::endl;
    return number_of_lines;
}
/******************************************************
 * Function:    clean_word
 * Date:     14/4/2021
 * Input arguments:  word_read word read in each line
 * Purpose:          Clean the words of strange characters
 ******************************************************/
std::string clean_word(std::string word_read)
{
    for (int i = 0, len = word_read.size(); i < len; i++)
    {
        if (ispunct(word_read[i]) && i != 0)
        {
            word_read.erase(i--, 1);

            len = word_read.size();
        }
        if (!isalpha(word_read[i]) && i == 0)
        {
            word_read.erase(i--, 1);

            len = word_read.size();
        }
    }

    return word_read;
}
/******************************************************
 * Function:    find_word
 * Date:     14/4/2021
 * Input arguments:  word_argv word specified, number_of_lines book's number of line,
 *                   id thread id, start where the thread start,
 *                   end where the thread end  
 * Purpose:          find the word who we are looking for 
 ******************************************************/
void find_word(std::string word_argv, int number_of_lines, std::string line, int id, int start, int end, int t_id)
{
    std::istringstream          entire_line(line);
    std::string                 word_read;
    std::vector<std::string>    vect;
    int                         position    =   find_position(t_id);

    vect.push_back(" ");
    while (entire_line >> word_read)
    {
        vect.push_back(word_read);
    }
    vect.push_back(" ");

    for (int i = 0; i < vect.size(); i++)
    {
                        word_read       = vect[i];
        std::string     word_to_print   = vect[i];
        std::transform(word_read.begin(), word_read.end(), word_read.begin(), ::tolower);

        word_read = clean_word(word_read);

        if ((word_argv.compare(word_read)) == 0)
        {
            if ((vect[i].compare(word_to_print)) == 0)
            {
                if (v_users[position].get_limit_words() == -1)
                {
                    //case ilimitado
                    final_result result(id, number_of_lines, start, end, vect[i - 1], vect[i], vect[i + 1]); /********************* CREACION DE OBJETO!!!!!!!! *********************/

                    sem.lock();
                    v_users[position].introduce(result);
                    sem.unlock();
                }
                else if (v_users[position].get_limit_words() > 0)
                {
                    //case free
                    final_result result(id, number_of_lines, start, end, vect[i - 1], vect[i], vect[i + 1]); /********************* CREACION DE OBJETO!!!!!!!! *********************/

                    sem.lock();
                    v_users[position].introduce(result);
                    int words = v_users[position].get_limit_words() - 1;
                    v_users.at(position).set_limit_words(words);
                    sem.unlock();
                }
                else if (v_users[position].get_limit_words() == 0)
                {

                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                else if (v_users[position].get_credits() > 0)
                {
                    //case premium limite
                    final_result result(id, number_of_lines, start, end, vect[i - 1], vect[i], vect[i + 1]); /********************* CREACION DE OBJETO!!!!!!!! *********************/
                    sem.lock();
                    v_users[position].introduce(result);
                    int credits = v_users[position].get_credits() - 1;
                    v_users[position].set_credits(credits);
                    sem.unlock();
                }
                else if (v_users[position].get_credits() == 0)
                {
                    std::cout << BOLDYELLOW << "[Client : " << v_users[position].get_id() <<"]"<< RESET <<" Need credits " << std::endl;
                    v_payments.push(v_users[position].get_id());
                    y.notify_one();
                    while (v_users[position].get_credits() == 0)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    }

                    final_result result(id, number_of_lines, start, end, vect[i - 1], vect[i], vect[i + 1]);
                    sem.lock();
                    v_users[position].introduce(result);
                    int credits = v_users[position].get_credits() - 1;
                    v_users[position].set_credits(credits);
                    sem.unlock();
                }
            }
        }
    }
}
/******************************************************
 * Function:    read_file
 * Date:     14/4/2021
 * Input arguments:  book name, word_argv word specified, id thread id, start where the thread start,
 *                   en where the thread end
 * Purpose:          read the file and try to find the word
 ******************************************************/
void read_file(std::string book, std::string word_argv, int id, int start, int end, int t_id)
{
    std::string                 word_read, line;
    std::vector<std::string>    vector_of_words;
    int                         number_of_lines     =   1;
    //std::string                 path                    =   "./utils/"+book;
    std::ifstream file(book);
    if (file.is_open())
    {
        while (number_of_lines <= end)
        {
            std::getline(file, line, '\n');
            if (number_of_lines >= start)
            {

                find_word(word_argv, number_of_lines, line, id, start, end, t_id);
            }

            number_of_lines++;
        }
        file.close();
    }

    else
        std::cout << "Unable to open file or file doesn't exist" << std::endl;
}
/******************************************************
 * Function:    divide_in_threads
 * Date:     14/4/2021
 * Input arguments:  the book to read, the word specified in the makefile, num_threads num of threads specified,
 *                   number_of_lines book's number of lines
 * Purpose:          divide the file in threads to search simultaneous results
 ******************************************************/
void divide_in_threads(std::string book, std::string word_argv, int num_threads, int number_of_lines, int t_id)
{
    int     start       =   0;
    int     end         =   0;
    int     size_task   =   number_of_lines / num_threads;
    int     id          =   0;
    std::vector<std::thread> vthreads;
    for (int i = 0; i < num_threads; i++)
    {
        start = (i * size_task) + 1;
        end = (start + size_task) - 1;
        if (i == num_threads - 1)
            end = number_of_lines;
        id++;

        vthreads.push_back(std::thread(read_file, book, word_argv, id, start, end, t_id));
    }
    std::for_each(vthreads.begin(), vthreads.end(), std::mem_fn(&std::thread::join));
   
}
/******************************************************
 * Function:    order_queue
 * Date:     14/4/2021
 * Input arguments:  id, the thread_id to store in the queue 
 * Purpose:          Order the queue to print it later
 ******************************************************/
void order_queue(int id)
{

    std::queue<final_result>    queue           =   aux_queue;
    int                         j               =   0;
    int                         initial_size    =   aux_queue.size();
    while (!queue.empty())
    {

        if (queue.front().get_id() == id)
        {

            final_queue.push(queue.front());
            queue.pop();
        }
        else
            queue.pop();

        j++;
    }
}
/******************************************************
 * Function:    print
 * Date:     14/4/2021  
 * Purpose:          Print the final queue with the results
 ******************************************************/
void print(std::queue<final_result> q, int id)
{
    std::cout << BOLDYELLOW << "[Client : " << id << "]"<< RESET << " Has writed results" << std::endl;
    //int     id  =   1;
    while (!q.empty())
    {
        std::string text;
        text = "Hilo " + std::to_string(q.front().get_id());
        text.append(" inicio: " + std::to_string(q.front().get_start_thread_line()));
        text.append(" - final: " + std::to_string(q.front().get_end_thread_line()));
        text.append(" :: línea " + std::to_string(q.front().get_line()));
        text.append(" :: ... ");
        text.append(q.front().get_behind_word() + " " + q.front().get_exact_word() + " " + q.front().get_after_word());
        m.lock();
        write_results(id, text);
        m.unlock();
        q.pop();
    }

    std::cout << std::endl;
}

void read_dir(Petition p)
{
    std::string                 path    =   "./utils";
    std::vector<std::string>    books;

    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        books.push_back(file.path());
    }
    for (int i = 0; i < books.size(); i++)
    {
        int number_of_lines = count_total_lines(books[i]);

        divide_in_threads(books[i], p.get_random_word(), 1, number_of_lines, p.get_id());
    }
    int position = search_user(p);
    v_users[position].set_confirmated(true);
}

/********************************************************** METHODS OF JOB 3: MULTITHREADING *******************************************************************/

/**
* This function search the position of a petition
*/
int search_user(Petition p)
{
    for (int i = 0; i < v_users.size(); i++)
    {
        if (v_users[i].get_id() == p.get_id())
        {
            return i;
        }
    }
    return -1;
}
/**
* This function select a random word from the dictionary
*/
std::string select_random_word()
{
    std::vector<std::string>    v           =   {"actitud", "velocidad", "oro", "cuál", "perdón", "qué", "cuando"};
    int                         n_random    =   rand() % (v.size());

    return v[n_random];
    //return "es";
}

/**
* This function generates the amounts of petitions
*/
void generate_petition(User u, std::string word)
{
    Petition p(u.get_id(), word);
    m.lock();
    v_petition.push_back(p);
    m.unlock();
}

/**
* This function select a random type of user
*/
User random_type(int id)
{
    int     n_random    =   1 + rand() % 3;
    if (n_random == 1)
    {
        User u(id, "f", WORDS_FREE, -1, false);
        return u;
    }
    else if (n_random == 2)
    {
        User u(id, "l", -2, TOKENS, false);
        return u;
    }
    else
    {
        User u(id, "p", -1, -1, false);
        return u;
    }
}

/**
* This function creates the clients
*/
void create_client(int id)
{
    std::queue<final_result>    cola;
    std::string                 word        =   select_random_word();
    User                        u           =   random_type(id);
    m.lock();
    v_users.push_back(u);
    int                         position    =   find_position(u.get_id());
    m.unlock();
    std::cout << BOLDYELLOW <<"[Client " << id << "]" << RESET
              << " Generate a petition" << std::endl;
    generate_petition(u, word);

    while (1)
    {
        if (v_users[position].is_confirmated() == 1)
        {

            cola = v_users[position].get_result();

            break;
        }
    }
    

    print(cola, v_users[position].get_id());
}

/**
* select the petition and attend it
*/
void attend(Petition p)
{
        std::cout << BOLDCYAN << "[SERVER]: " << RESET << " Attending petition " << p.get_id()  << std::endl;
        read_dir(p); //word, num_threads
        m.lock();
        buffer--;
        cv.notify_one();
        m.unlock();
}
/**
* search a specific type of client
*/
int search_type(std::string type)
{

    for (int i = 0; i < v_petition.size(); i++)
    {
        for (int j = 0; j < v_users.size(); j++)
        {

            if (v_users[j].get_id() == v_petition[i].get_id() && v_users[j].get_type() == type)
            {
                return i;
            }
        }
    }
    return -1;
}
/**
* this method initialices our search to do the tasks
*/
void initialize_search()
{
    int                             position;
    std::unique_lock<std::mutex>    lk(sem_cv);

    while (1)
    {
        cv.wait(lk, []
                { return buffer < N; });
        if (v_petition.size() != 0)
        {
            int n_random = 1 + rand() % (11 - 1);
            if (n_random <= 2)
            {
                position = search_type("f");
                if (position != -1)
                {
                    
                    v_attending.push_back(v_petition[position]);
                    std::thread hilo(attend, v_petition[position]);
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
                        
                        v_attending.push_back(v_petition[position]);
                        std::thread hilo(attend, v_petition[position]);
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
                        
                        v_attending.push_back(v_petition[position]);
                        std::thread hilo(attend, v_petition[position]);
                        hilo.detach();
                        v_petition.erase(v_petition.begin() + position);
                    }
                }
            }
        }
    }
}
/**
* add money or credits to a premium limited user
*/
void add_cash()
{
    std::unique_lock<std::mutex>    u_bank(bank);

    while (1)
    {
        y.wait(u_bank, []{ return !v_payments.empty(); });
        int     position    =   find_position(v_payments.front());
        v_users[position].set_credits(500);
        std::cout << BOLDRED<< "[Bank]"<< RESET << " Client : " << v_payments.front() << " has been paid" << std::endl;
        m.lock();
        v_payments.pop();
        m.unlock();
    }
}

/**
* here we write the results in the path results/ with 
* a specific name id_(thread id).txt
*/
void write_results(int id, std::string text)
{

    std::string     name    =   "id_" + std::to_string(id);
    std::string     final   =    name + ".txt";
    std::string     path    =   "./results/" + final;
    std::ofstream   outfile;
    outfile.open(path, std::ios_base::app); 
    outfile << text << std::endl;
    outfile.close();
}