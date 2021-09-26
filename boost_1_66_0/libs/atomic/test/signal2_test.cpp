#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <boost/bind.hpp>

#include <boost/signals2/signal.hpp>

struct Hello {
    void operator()() const {
        printf("Hello,");
    }

    void PrintHello() {
        printf("HELLO,");
    }
};


struct World {
    void operator()() const {
        printf(" World! \n");
    }
    void PrintWorld(int i) {
        printf(" WORLD! %d \n", i);
    }
};

struct ClassA {
    boost::signals2::signal<void ()>    SigHello;
    boost::signals2::signal<void (int)> SigWorld;
};


int main() {
    // Signal with no arguments and a void return value
    boost::signals2::signal<void ()> sig;

    // Connect a HelloWorld slot
    Hello hello;
    World world;

    ClassA a;
    a.SigHello.connect(boost::bind(&Hello::PrintHello, &hello));
    a.SigWorld.connect(boost::bind(&World::PrintWorld, &world, _1));
    a.SigHello();
    a.SigWorld(88);

    sig.connect(1, hello);
    sig.connect(0, world);

    // Call all of the slots
    sig();
}
