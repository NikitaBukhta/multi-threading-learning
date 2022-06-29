#include "client.h"
 
using namespace imitation;
using namespace std::literals;
 
Client::Client(void){
    // try to connect to the server;
    std::cout << "Connecting to the server..." << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "Connected!" << std::endl;
}
 
std::string Client::get_data(void){
    // random msg size from 1 to 1024 bytes;
    const size_t msg_size_to_read = random_number(1, 1024);
 
    size_t random_bytes_count;  // count bytes we read by 1 it;
    size_t current_data_size;   // count bytes we read at all;
 
    // separate thread, that output the status bar of downloaded resources;
    std::thread status_bar_th(&Client::show_progress_bar, this, msg_size_to_read);
 
    std::unique_lock guard(_read_data_mut);
    while((current_data_size = _data.size()) < msg_size_to_read){
        random_bytes_count = random_number(0, msg_size_to_read - current_data_size);
        
        /* I do not know why, but std::unique_lock::try_lock method throw the next
         * exception:
         *  << unique_lock::try_lock: already locked: Resource deadlock avoided >>
         * 
         * So I decided to check if mutex is locked;
         */
        if (!guard.owns_lock()){
            guard.lock();
        }
 
        // Allocate new memory space to push new data;
        _data.resize(random_bytes_count + current_data_size);
        
        /* We use lambda expression there because function needs pointer
         * to the funciton, but we put the args;
         */
        std::generate(std::begin(_data) + current_data_size, std::end(_data), 
            [this] (void) { 
                char rand_char;
                // I do not want to get enter in random chars :D;
                while ((rand_char = random_number(0, CHAR_MAX)) == '\n');
                return rand_char; 
            });
 
        guard.unlock();
 
        _some_data_read = true;
        // Allow to display progress bar;
        _read_cond_var.notify_one();
 
        std::thread transcription_thread (&Client::transcription, this);
 
        if (_data.size() < msg_size_to_read){
            transcription_thread.detach();
        }
        else{
            transcription_thread.join();
        }
 
        std::this_thread::sleep_for(1s);
    }
 
    status_bar_th.join();
 
    return _data;
}
 
void Client::show_progress_bar(size_t bytes_needed){
    float current_download_status = 0;
    size_t current_data_size;
 
    std::unique_lock guard(_read_data_mut);
    do{
        // waiting for new data;
        _read_cond_var.wait(guard, [this](void)->bool { return _some_data_read; });
 
        current_data_size = _data.size();
 
        current_download_status = static_cast<float>(current_data_size) / bytes_needed * 100.0f;
        std::cout << "\nDownloaded: " << current_download_status
                  << "%\n\n";
 
        _some_data_read = false;
    } while(current_data_size < bytes_needed);
}
 
size_t Client::random_number(size_t min, size_t max){
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> generator(min, max);
 
    return generator(mt);
}
 
void Client::transcription(void){
    std::unique_lock guard(_read_data_mut);
    std::cout << "Make transcription..." << std::endl;
    guard.unlock();
 
    std::this_thread::sleep_for(1s);
 
    guard.lock();
    std::cout << "Transcription made" << std::endl;
    guard.unlock();
}