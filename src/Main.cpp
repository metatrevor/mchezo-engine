#include "StateManager.h"

int main(int argc, char *argv[])
{
    StateManager::instance().run(argc, argv);
    return 0;
}
