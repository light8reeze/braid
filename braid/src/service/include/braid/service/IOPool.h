#pragma once
#include <braid/memory/ObjectPool.h>
#include <braid/net/IOOperation.h>

namespace braid {
    class IOOperationRecv;
    class IOOperationSendBuffer;
    class IOOperationAccept;
    class IOOperationClose;
    class IOPool final {
    public:
        IOPool() = default;
        ~IOPool() = default;

    public:
        template<typename T, typename... Args>
        T* acquire(Args&&... args) noexcept {
            return get_io_pool<T>().acquire(std::forward<Args>(args)...);
        }

        template<typename T>
        void release(T* object) noexcept {
            get_io_pool<T>().release(object);
        }

        template<typename T>
        requires std::is_base_of_v<IOOperation, T> && (!std::is_same_v<IOOperation, T>)
        ObjectPool<T>& get_io_pool() noexcept {
            static ObjectPool<T> pool;
            return pool;
        }
    };

    static IOPool g_io_pool;
}