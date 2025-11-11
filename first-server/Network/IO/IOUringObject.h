#pragma once
#include "FirstServerPCH.h"
#include <netinet/in.h>

namespace first {

	enum IOEventType
	{
		IO_EVENT_NONE = 0,
		IO_EVENT_ACCEPT,
		IO_EVENT_READ,
		IO_EVENT_WRITE,
		IO_EVENT_DISCONNECT,
	};
	
	// io_uring 이벤트 객체 기본 클래스
	class IOUringObject
	{
		NON_COPYABLE(IOUringObject);

	public:
		IOUringObject() = default;
		virtual ~IOUringObject() = default;


	public:
		void set_request_type(IOEventType type) { request_type_ = type; }
		void set_socket_fd(socket_fd fd) { socket_fd_ = fd; }
		void set_address(const struct sockaddr_in& addr) { address_ = addr; }

		IOEventType			get_request_type() const { return request_type_; }
		char*				get_buffer() { return buffer_; }
		int					get_buffer_size() const { return 4096; }
		socket_fd			get_socket_fd() const { return socket_fd_; }
		struct sockaddr_in& get_address() { return address_; }


	private:
		IOEventType request_type_ = IO_EVENT_NONE;

		// TODO: 추후 버퍼 분리
		char				buffer_[4096] = { 0 };

		socket_fd			socket_fd_ = -1;
		struct sockaddr_in	address_ = { 0 }
	};
}