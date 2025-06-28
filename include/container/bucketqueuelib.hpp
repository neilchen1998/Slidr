#ifndef INCLUDE_CONTAINER_BUCKETQUEUE_H_
#define INCLUDE_CONTAINER_BUCKETQUEUE_H_

#include <vector>   // std::vector
#include <list>   // std::list
#include <cstddef>  // std::size_t
#include <tuple>    // std::tuple
#include <memory>   // std::shared_ptr
#include <iostream>

template<typename T, typename PriorityType = std::size_t>
class BucketQueue
{
public:
    explicit BucketQueue(std::size_t maxPriority) :
        buckets_(maxPriority + 1),
        size_(0),
        maxPriority_(maxPriority),
        hightPriority_(0)
    {

    }

    /// @brief Returns the number of elements
    /// @return The number of elements
    inline std::size_t size() const noexcept
    {
        return size_;
    }

    /// @brief Checks whether the container adaptor is empty
    /// @return True if the container adaptor is empty
    inline bool empty() const noexcept
    {
        return (size_ == 0);
    }

    /// @brief Accesses the highest priority element
    /// @return A const reference to the top element
    const T& top()
    {
        if (empty())
        {
            throw std::runtime_error("Cannot call top() on an empty bucket queue.");
        }

        return buckets_[hightPriority_].front();
    }

    /// @brief Removes the hightest priority element
    void pop()
    {
        if (empty())
        {
            throw std::runtime_error("Cannot call top() on an empty bucket queue.");
        }

        buckets_[hightPriority_].pop_front();
        --size_;

        if (buckets_[hightPriority_].empty())
        {
            UpdateHigestPriority();
        }
    }

    void push(const T& ele, PriorityType priority)
    {
        if (priority > maxPriority_)
        {
            throw std::out_of_range("Priority exceeds the max limit.");
        }

        buckets_[priority].push_back(ele);
        ++size_;

        hightPriority_ = (priority > hightPriority_) ? priority : hightPriority_;
    }

    void push(T&& ele, PriorityType priority)
    {
        if (priority > maxPriority_)
        {
            throw std::out_of_range("Priority exceeds the max limit.");
        }

        buckets_[priority].push_back(std::move(ele));
        ++size_;

        hightPriority_ = (priority >= hightPriority_) ? priority : hightPriority_;
    }

private:
    void UpdateHigestPriority()
    {
        for (PriorityType i = hightPriority_; i > 0; --i)
        {
            if (!buckets_[i].empty())
            {
                hightPriority_ = i;
                return;
            }
        }

        // If we reach here, that means the hightest priority is 0
        // no matter if the 0th bucket is empty or not
        hightPriority_ = 0;
    }

private:

    std::vector<std::list<T>> buckets_;

    /// @brief The number of elements in the queue
    std::size_t size_;

    const PriorityType maxPriority_;

    PriorityType hightPriority_;
};

#endif // INCLUDE_CONTAINER_BUCKETQUEUE_H_
