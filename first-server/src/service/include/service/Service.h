#pragma once
#include <service/ServiceBuilder.h>

namespace first {
    class Service {
    public:
        Service(ServiceBuilder& builder);
        virtual ~Service();
    };
}