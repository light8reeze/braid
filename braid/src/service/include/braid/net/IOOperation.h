#pragma once
#include <braid/memory/PooledObject.h>

#include <liburing.h>
#include <memory>

namespace braid {
    class IOUringObject;
    class IOOperation : public PooledObject {
    public:
        IOOperation(std::shared_ptr<IOUringObject>&& io_object)
            : io_object_(std::move(io_object)) {
        }
        virtual ~IOOperation() = default;


    public:
        virtual void request_io(io_uring* ring) = 0;
        virtual void handle_io_completion(int result) = 0;


    protected:
        std::shared_ptr<IOUringObject> io_object_;
    };
}