#include <service/Service.h>
#include <thread/WorkerThread.h>
#include <net/IOOperation.h>

namespace first {
	Service::Service() 
		: worker_threads_(){
		acceptor_object_ = std::make_shared<IOUringObject>();
	}

	Service::~Service() {
		worker_threads_.clear();
	}

	bool Service::initialize() {
		initialize_threads();

		// session List를 생성 후 accept 시킨다.

		return true;
	}

	bool Service::run() {

		for (auto& thread : worker_threads_)
			thread->start();

		for (auto& thread : worker_threads_)
			thread->wait();

		return true;
	}

	void Service::request_io(IOOperation* operation) {
		static std::atomic<int> request_index = 0;
		int thread_index = request_index++ % num_threads_;

		request_io(thread_index, operation);
	}

	void Service::request_io(int thread_index, IOOperation* operation) {
		if (thread_index < 0 || thread_index >= num_threads_)
			return;

		worker_threads_[thread_index]->request_io(operation);
	}

	void Service::initialize_threads() {
		for (int i = 0; i < thread_count_; ++i) {
			worker_threads_.emplace_back(std::make_unique<WorkerThread>(queue_depth_per_thread_));
			worker_threads_.back()->set_thread_id(i);
			worker_threads_.back()->initialize();
		}
	}
}