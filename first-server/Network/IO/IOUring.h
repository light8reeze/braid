#pragma once
#include <liburing.h>
#include "IOCompletion.h"

namespace first {

	class IOUringObject;
	class IOUring
	{
	public:
		IOUring(int queue_depth = 1024);
		~IOUring();


	public:
		void			set_accept(IOUringObject* acceptor, IOUringObject* io_object);
		void			set_receive(IOUringObject* io_object);
		void			set_send(IOUringObject* io_object);

		IOCompletion	wait();
		void			submit();


	public:
		io_uring* get_ring() { return &ring_; }


	private:
		io_uring ring_;
	};

}