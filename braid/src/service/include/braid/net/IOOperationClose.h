#pragma once
#include <braid/net/IOOperation.h>

struct io_uring;

namespace braid {
    class IOOperationClose : public IOOperation {
    public:
        IOOperationClose(std::shared_ptr<IOUringObject>&& io_object);
        virtual ~IOOperationClose() = default;


    public:
        virtual void request_io(io_uring* ring) override;
        virtual void handle_io_completion(int result) override;
        virtual void on_zero_ref() override;
    };
}