#include "Thread.h"
#include <liburing.h>

namespace first {

    class IOURingThread : public Thread {

    public:
        IOURingThread(int queue_depth = 1024);
        virtual ~IOURingThread();


    public:
        io_uring* getRing();


    protected:
        io_uring ring_;
    };
}