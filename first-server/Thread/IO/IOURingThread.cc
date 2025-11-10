#include "IORingThread.h"
#include <liburing.h>

namespace first {

    IOURingThread::IOURingThread(int queue_depth /* = 1024 */) {
        io_uring_queue_init(queue_depth, &ring_, 0);
    }

    IOURingThread::~IOURingThread() {
        io_uring_queue_exit(&ring_);
    }

    io_uring* IOURingThread::getRing() {
        return &ring_;
    }
}