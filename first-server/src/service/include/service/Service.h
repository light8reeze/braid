#pragma once
#include <service/ServiceBuilder.h>

namespace first {
    class IOOperation;
    class Service : std::enable_shared_from_this<Service> {
    private:
        // ServiceBuilder를 통해서만 생성하도록 한다.
        friend class ServiceBuilder<Service>;
		Service();


	public:
        virtual ~Service();


    public:
        virtual bool initialize();


    public:
        bool run();

		void request_io(IOOperation* operation);
		void request_io(int thread_index, IOOperation* operation);


    private:
        virtual void initialize_threads();


	protected:
        std::vector<std::unique_ptr<WorkerThread>>  worker_threads_{};

		std::shared_ptr<IOUringObject> acceptor_object_ = nullptr;

		int session_count_          = 1000;
		int thread_count_           = 4;
		int queue_depth_per_thread_ = 1024;
    };
}