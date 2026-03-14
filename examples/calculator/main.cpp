#include <iostream>
#include <kito/core/application.h>

int main() {
    kito::Application app;
    app.Init("config.yaml");
    app.start();    
    return 0;  
}          