#include <liburing.h>
#include "IOCompletion.h"

class IOUring
{
public:
	IOUring(int queue_depth = 1024);
	~IOUring();


public:
	IOCompletion	wait();
	void			submit();


public:
	io_uring* get_ring() { return &ring_; }


private:
	io_uring ring_;
};