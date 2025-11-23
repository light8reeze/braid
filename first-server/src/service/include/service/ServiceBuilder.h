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
        ServiceBuilder();
        virtual ~ServiceBuilder();


    public:
        std::shared_ptr<ServiceType> build() {
            service_instance_ = new ServiceType(*this);
            return service_instance_;
        }

        ServiceBuilder<ServiceType>& set_address(std::string address, int port) {
            if(nullptr == acceptor_object_)
                acceptor_object_ = new IOUringObject();

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

            acceptor_object_->set_socket_fd(sock_fd);
            acceptor_object_->set_address(addr);

            return (*this);
        }


    public:
        


    protected:
        std::shared_ptr<ServiceType> service_instance_;
        std::shared_ptr<IOUringObject> acceptor_object_;

        int session_count_;
        
    };
}