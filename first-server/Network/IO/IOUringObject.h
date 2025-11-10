#include "FirstServerPCH.h"

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
	class IOURingObject
	{
		NON_COPYABLE(IOURingObject);

	public:
		IOURingObject() = default;
		virtual ~IOURingObject() = default;


	private:
		IOEventType request_type_ = IO_EVENT_NONE;

		// TODO: 추후 버퍼 분리
		char		buffer_[4096] = { 0 };
		socket_fd	socket_fd_ = -1;
	};
}