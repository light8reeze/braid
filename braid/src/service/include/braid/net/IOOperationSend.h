#pragma once
#include <braid/net/IOOperation.h>
#include <span>

struct io_uring;

namespace braid {
    class IOOperationSend : public IOOperation {
    public:
        IOOperationSend(std::shared_ptr<IOUringObject>&& io_object, std::span<char>& buffer);
        virtual ~IOOperationSend() = default;

        
    public:
        virtual void request_io(io_uring* ring) override;
        virtual void handle_io_completion(int result) override;
        virtual void on_zero_ref() override;


    private:
        std::span<char> buffer_;
    };
}