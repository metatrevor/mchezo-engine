#include "StateManager.h"

int main(int argc, char *argv[])
{
    StateMachine::instance().run(argc, argv);
    return 0;
}
