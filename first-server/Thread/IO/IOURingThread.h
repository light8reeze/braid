#include "Thread.h"
#include <IOUring.h>

namespace first {

    class IOURingThread : public Thread {

    public:
        IOURingThread(int queue_depth = 1024);
        virtual ~IOURingThread();


    public:
        IOUring* getRing();


    protected:
		IOUring ring_;
    };
}