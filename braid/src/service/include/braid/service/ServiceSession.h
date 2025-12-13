#pragma once
#include <braid/net/IOUringObject.h>
#include <braid/service/Actor.h>
#include <braid/message/SendBuffer.h>
#include <memory>

namespace braid {

	class Service;
	// 서비스 레이어에서 사용하는 기본 오브젝트
	class ServiceSession : public IOUringObject {

	public:
		ServiceSession(std::shared_ptr<Service>& service_instance);
		virtual ~ServiceSession() = default;


	public:
		void request_receive();
		void request_send(ObjectPtr<SendBuffer> send_buffer);
		void request_accept(int accept_fd_);
		void request_close();


	public:
		virtual void on_accepted() override;
		virtual void on_received(int bytes_received) override;
		virtual void on_closed() override;

		virtual void on_receive_failed(int error_code) override;
		virtual void on_send_failed(int error_code) override;


	protected:
		const std::weak_ptr<Service> service_instance_;

		ObjectPtr<Actor> main_actor_;
	};
}