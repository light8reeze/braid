#include "WorkerThread.h"
#include <iostream>

namespace first {

    WorkerThread::WorkerThread(int queue_depth /* = 1024 */) 
        : IOURingThread(queue_depth) {
    }

    WorkerThread::~WorkerThread() {
        io_uring_queue_exit(&ring_);
    }

    void WorkerThread::initialize() {
        IOURingThread::initialize();
    }

    int WorkerThread::routine() {
        io_uring_cqe* cqe = nullptr;

        int ret = io_uring_wait_cqe(&ring_, &cqe);
        if (ret < 0) {
            std::cout << "WorkerThread : io_uring_wait_cqe" << std::endl;
            return ret;
        }

        // TODO: IO Event

        io_uring_cqe_seen(&ring_, cqe);

        return 0;
    }
}