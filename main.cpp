#include "application.h"

int main(int argc, char *argv[])
{
    nApplication::Application app(argc, argv);
    app.run();
    return 0;
}