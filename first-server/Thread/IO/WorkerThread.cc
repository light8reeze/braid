#include "WorkerThread.h"
#include <iostream>

namespace first {

    WorkerThread::WorkerThread(int queue_depth /* = 1024 */) 
        : IOURingThread(queue_depth) {
    }

    WorkerThread::~WorkerThread() {
    }

    void WorkerThread::initialize() {
        IOURingThread::initialize();
    }

    int WorkerThread::routine() {
		IOCompletion completion = ring_.wait_completion();

        // TODO: IO Event

        return 0;
    }
}