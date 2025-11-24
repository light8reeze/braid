#pragma once
#include <type_traits>
#include <util/FirstServerPCH.h>
#include <memory>

namespace first {
    class Service;
    class IOUringObject;

    template<typename ServiceType = Service>
    requires std::is_base_of_v<Service, ServiceType>
    class ServiceBuilder {
    public:
        ServiceBuilder() {
            service_instance_ = std::make_shared<ServiceType>();
        }

        virtual ~ServiceBuilder() = default;


    public:
		static ServiceBuilder<ServiceType> create_builder() {
			ServiceBuilder<ServiceType> builder;
			return builder;
		}


    public:
        virtual bool validate() {
            if (nullptr == acceptor_object_)
                return false;

            return true;
        }

		std::shared_ptr<ServiceType> build() {
			assert(nullptr == service_instance_);

            if (!validate())
                return nullptr;

            return service_instance_;
        }

        ServiceBuilder<ServiceType>& set_address(std::string address, int port) {
            std::shared_ptr<IOUringObject> acceptor = service_instance_->acceptor_object_;
            if(nullptr == acceptor)
                acceptor = std::make_shared<IOUringObject>();

            socket_fd listen_fd = socket(AF_INET, SOCK_STREAM, 0);
            int enable = 1;
            setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
            
            struct sockaddr_in addr = { 0 };
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);

            if (address.empty())
                addr.sin_addr.s_addr = INADDR_ANY;
            else 
                inet_pton(AF_INET, address.c_str(), &(addr.sin_addr));

            bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
            listen(sock_fd, 128);

            acceptor->set_socket_fd(sock_fd);
            acceptor->set_address(addr);

            return (*this);
        }

        ServiceBuilder<ServiceType>& set_thread_count(int thread_count) {
            service_instance_->thread_count_ = thread_count;
			return (*this);
        }

		ServiceBuilder<ServiceType>& set_session_count(int session_count) {
            service_instance_->session_count_ = session_count;
			return (*this);
		}

		ServiceBuilder<ServiceType>& set_queue_depth_per_thread(int queue_depth) {
            service_instance_->queue_depth_per_thread_ = queue_depth;
			return (*this);
		}


    protected:
        std::shared_ptr<ServiceType> service_instance_ = nullptr;
    };
}