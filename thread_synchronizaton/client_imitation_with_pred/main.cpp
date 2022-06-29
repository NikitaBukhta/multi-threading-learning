#include "client.h"

#include <iostream>
#include <thread>

int main(int argc, char **argv){
    imitation::Client client;
    std::thread(&imitation::Client::get_data, &client).join();

    return EXIT_SUCCESS;
}