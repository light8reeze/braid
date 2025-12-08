#include <task/TaskSerializer.h>
#include <task/Task.h>

namespace first {
    void TaskSerializer::push(ITask* task) {
        task_queue_.push(task);
    }

    std::shared_ptr<ITask> TaskSerializer::pop() {
        ITask* task;
        task_queue_.pop(task);
        return std::shared_ptr<ITask>(task);
    }
    
}