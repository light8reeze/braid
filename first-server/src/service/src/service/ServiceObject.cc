#include <service/ServiceObject.h>
#include <service/Service.h>

#include <net/IOOperationRecv.h>
#include <net/IOOperationSend.h>
#include <net/IOOperationAccept.h>

namespace first {
	ServiceObject::ServiceObject(std::shared_ptr<Service>& service_instance) 
		: service_instance_(service_instance) {
		
		assert(nullptr != service_instance);
	}

	void ServiceObject::request_receive() {
		IOOperationRecv* io_recv = new IOOperationRecv(shared_from_this());

		if (auto service_ptr_ = service_instance_.lock())
			service_ptr_->request_io(io_recv);
	}

	void ServiceObject::request_send() {
		IOOperationSend* io_send = new IOOperationSend(shared_from_this());

		if (auto service_ptr_ = service_instance_.lock())
			service_ptr_->request_io(io_send);
	}

	void ServiceObject::request_accept(int accept_fd_) {
		IOOperationAccept* io_accept = new IOOperationAccept(shared_from_this(), accept_fd_);

		if (auto service_ptr_ = service_instance_.lock())
			service_ptr_->request_io(io_accept);
	}

	void ServiceObject::on_accepted() {
		request_receive();
	}
}