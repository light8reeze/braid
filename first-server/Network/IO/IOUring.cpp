#include "IOURing.h"

namespace first {

	IOUring::IOUring(int queue_depth /*= 1024*/) {
		::io_uring_queue_init(queue_depth, &ring_, 0);
	}

	IOUring::~IOUring() {
		::io_uring_queue_exit(&ring_);
	}

	void IOUring::set_accept(IOUringObject* acceptor, IOUringObject* io_object) {
		io_uring_sqe* sqe = io_uring_get_sqe(&ring_);
		
		socklen_t addrlen = sizeof(io_object->get_address());
		struct sockaddr* addr = reinterpret_cast<struct sockaddr*>(&io_object->get_address());

		io_object->set_request_type(IO_EVENT_ACCEPT);
		::io_uring_prep_accept(sqe, acceptor->get_socket_fd(), addr, &addrlen, 0);
		::io_uring_sqe_set_data(sqe, io_object);
	}

	void IOUring::set_receive(IOUringObject* io_object) {
		io_uring_sqe* sqe = io_uring_get_sqe(&ring_);

		io_object->set_request_type(IO_EVENT_READ);
		::io_uring_prep_recv(sqe, io_object->get_socket_fd(), io_object->get_buffer(), io_object->get_buffer_size(), 0);
		::io_uring_sqe_set_data(sqe, io_object);
	}

	void IOUring::set_send(IOUringObject* io_object) {
		io_uring_sqe* sqe = io_uring_get_sqe(&ring_);

		io_object->set_request_type(IO_EVENT_WRITE);
		::io_uring_prep_send(sqe, io_object->get_socket_fd(), io_object->get_buffer(), io_object->get_buffer_size(), 0);
		::io_uring_sqe_set_data(sqe, io_object);
	}

	IOCompletion IOUring::wait() {
		io_uring_cqe* cqe;

		int ret = ::io_uring_wait_cqe(&ring_, &cqe);
		if (ret < 0) {
			// TODO: 예외처리 추가
			perror("io_uring_wait_cqe");
			return IOCompletion(nullptr, nullptr);
		}

		return IOCompletion(&ring_, cqe);
	}

	void IOUring::submit() {
		::io_uring_submit(&ring_);
	}
}