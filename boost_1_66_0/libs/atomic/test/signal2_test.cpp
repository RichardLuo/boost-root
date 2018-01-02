#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include <boost/signals2/signal.hpp>

struct HelloWorld {
    void operator()() const {
        printf("Hello, World! \n");
    }
};


struct Shoe {
    ~Shoe() {
        printf("Buckle my shoe\n");
    }
};

class MyClass {
    boost::scoped_ptr<int> ptr;
  public:
    MyClass() : ptr(new int) { *ptr = 0; }
    int add_one() { return ++*ptr; }
};

int main() {
    boost::scoped_ptr<Shoe> x(new Shoe);
    MyClass my_instance;

    // Signal with no arguments and a void return value
    boost::signals2::signal<void ()> sig;

    // Connect a HelloWorld slot
    HelloWorld hello;
    sig.connect(hello);

    // Call all of the slots
    sig();
}
