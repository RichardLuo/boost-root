//  Copyright (c) 2011 Helge Bahmann
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// Attempt to determine whether the operations on atomic variables
// do in fact behave atomically: Let multiple threads race modifying
// a shared atomic variable and verify that it behaves as expected.
//
// We assume that "observable race condition" events are exponentially
// distributed, with unknown "average time between observable races"
// (which is just the reciprocal of exp distribution parameter lambda).
// Use a non-atomic implementation that intentionally exhibits a
// (hopefully tight) race to compute the maximum-likelihood estimate
// for this time. From this, compute an estimate that covers the
// unknown value with 0.995 confidence (using chi square quantile).
//
// Use this estimate to pick a timeout for the race tests of the
// atomic implementations such that under the assumed distribution
// we get 0.995 probability to detect a race (if there is one).
//
// Overall this yields 0.995 * 0.995 > 0.99 confidence that the
// operations truly behave atomic if this test program does not
// report an error.

// #include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/atomic.hpp>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

boost::atomic_int producer_count(0);
boost::atomic_int consumer_count(0);

boost::lockfree::queue<int> queue(128);

const int iterations = 1000000;
const int producer_thread_count = 10;
const int consumer_thread_count = 20;

static void* producer(void *arg) {
    int index = (int)arg;
    for (int i = 0; i != iterations; ++i) {
        int value = ++producer_count;
        if  (i % 100 == 0) {
            printf("++%d producer_count %d \n", index, value);
        }
        while (!queue.push(value))
            ;
    }
    return NULL;
}

boost::atomic<bool> done (false);

static void* consumer(void *arg) {
    int value;
    int index = (int)arg;
    while (!done) {
        while (queue.pop(value)) {
            consumer_count++;
            if (consumer_count % 100 == 0) {
                printf("--%d consumer_count %d \n", index, (int)consumer_count);
            }
        }
    }

    while (queue.pop(value))
        ++consumer_count;
    return NULL;
}

int main(int argc, char* argv[]) {
    using namespace std;

    pthread_t ptids[producer_thread_count];
    pthread_t ctids[consumer_thread_count];

    printf("boost::lockfree::queue is ");
    if (!queue.is_lock_free())
        printf("not ");
    printf("lockfree \n");

    for (int i = 0; i < producer_thread_count; i++ ) {
        if (pthread_create(&ptids[i], NULL, &producer, (void*)i) < 0 ) {
            printf("failed to create producer %d: %s\n", i+1, strerror(errno));
            return -1;
        } else {
            printf("created producer thread %d \n", i);
        }
    }

    for (int i = 0; i < consumer_thread_count; i++ ) {
        if (pthread_create(&ctids[i], NULL, &consumer, (void*)(i)) < 0 ) {
            printf("failed to create consumer %d: %s\n", i+1, strerror(errno));
            return -1;
        } else {
            printf("created consumer thread %d \n", i);
        }
    }

    printf("before join \n");

    for (int i = 0; i < producer_thread_count; i++) {
        pthread_join(ptids[i], NULL);
    }

    done = true;

    for (int i = 0; i < consumer_thread_count; i++) {
        pthread_join(ctids[i], NULL);
    }

    printf("==== producer_count:%d consumer_count:%d ==== \n", (int)producer_count, (int)consumer_count);

    return 0;
}
