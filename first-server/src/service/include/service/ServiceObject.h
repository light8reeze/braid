#pragma once
#include <net/IOUringObject.h>
#include <memory>

namespace first {

	class Service;
	// 서비스에 사용되는 기본 오브젝트
	class ServiceObject : public IOUringObject {

	public:
		ServiceObject(std::shared_ptr<Service>& service_instance);
		virtual ~ServiceObject() = default;


	public:
		void request_receive();
		void request_send();


	private:
		const std::weak_ptr<Service> service_instance_;
	};
}