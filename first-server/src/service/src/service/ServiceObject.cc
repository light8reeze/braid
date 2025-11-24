#include <service/ServiceObject.h>

namespace first {
	ServiceObject::ServiceObject(std::shared_ptr<Service>& service_instance) 
		: service_instance_(service_instance) {
		
		assert(nullptr != service_instance);
	}


}