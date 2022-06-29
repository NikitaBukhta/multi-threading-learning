#ifndef Client_H
#define Client_H

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <random>

namespace imitation{
    class Client{
    private:
        std::string _data;
        std::mutex _read_data_mut;

        std::condition_variable _read_cond_var;
        bool _some_data_read;
    public:
        Client(void);

        /* Description:
         *      Return new data from the server and display the bar in order to
         *  display how many bytes left to download in %;
         * 
         * Return values:
         *  return new data msg from the server;
         */
        std::string get_data(void);

    private:

        /* Desciption:
         *      Show progress bar of downloading data from the server;
         * Args:
         *  bytes_needed - count of bytes we need to read;
         */
        void show_progress_bar(size_t bytes_needed);

        /* Description:
         *      Return random integer number from min to max;
         *
         * Args:
         *  min - min value;
         *  max - max value;
         * 
         * return random [min, max];
         */
        size_t random_number(size_t min, size_t max);

        void transcription(void);
    };
}

#endif // !Client_H