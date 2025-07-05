#ifndef INCLUDE_CONTAINER_BUCKETQUEUE_H_
#define INCLUDE_CONTAINER_BUCKETQUEUE_H_

#include <vector>   // std::vector
#include <cstddef>  // std::size_t
#include <memory>   // std::shared_ptr
#include <type_traits>  // std::is_same
#include <utility>  // std::forward
#include <bitset>  // std::bitset
#include <concepts>  // std::unsigned_integral

/// @brief The interface (abstract class) of Bucket Queue class
/// @tparam T The element type
/// @tparam PriorityType The priority type
template<typename T, std::unsigned_integral PriorityType = std::size_t>
class BucketQueueBase
{
    virtual std::size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;
    virtual const T& top() const = 0;
    virtual void pop() = 0;
    virtual void push(const T& ele, PriorityType priority) = 0;
    virtual void push(T&& ele, PriorityType priority) = 0;
};

/// @brief The concrete class of Bucket Queue class
/// @tparam T The element type
/// @tparam PriorityType The priority type (default is std::size_t)
/// @tparam Compare The compare struct (default is std::less)
/// @tparam MaxPriorityLimit The number of buckets (default value is 64)
template<typename T, std::unsigned_integral PriorityType = std::size_t, typename Compare = std::less<PriorityType>, std::size_t MaxPriorityLimit = 64>
class BucketQueue : public BucketQueueBase <T, PriorityType>
{
    // Determine if this is a max queue
    static constexpr bool isMaxQueue = std::is_same<Compare, std::less<PriorityType>>::value;

public:
    explicit BucketQueue() :
        buckets_(MaxPriorityLimit),
        size_(0),
        maxPriority_(MaxPriorityLimit)
    {
        // Initialize best priority based on the compare type
        // NOTE: if constexpr enables compile-time conditional branching
        if constexpr (isMaxQueue)
        {
            bestPriority_ = 0;
        }
        else
        {
            bestPriority_ = maxPriority_;
        }
    }

    /// @brief Returns the number of elements
    /// @return The number of elements
    [[nodiscard]] inline std::size_t size() const noexcept
    {
        return size_;
    }

    /// @brief Checks whether the container adaptor is empty
    /// @return True if the container adaptor is empty
    [[nodiscard]] inline bool empty() const noexcept
    {
        return (size_ == 0);
    }

    /// @brief Accesses the highest priority element
    /// if there are multiple elements with the same priority, the top one is the last one (LIFO)
    /// @return A const reference to the top element
    [[nodiscard]] const T& top() const
    {
        if (empty())
        {
            throw std::runtime_error("Cannot call top() on an empty bucket queue.");
        }

        return buckets_[bestPriority_].back();
    }

    /// @brief Removes the hightest priority element
    /// if there are multiple elements with the same priority, the last one will be popped (LIFO)
    void pop()
    {
        if (empty())
        {
            throw std::runtime_error("Cannot call top() on an empty bucket queue.");
        }

        buckets_[bestPriority_].pop_back();
        --size_;

        if (buckets_[bestPriority_].empty())
        {
            mask_[bestPriority_] = false;
            UpdateHighestPriority();
        }
    }

    /// @brief Pushes the element into the heap with specified priority
    /// @param ele The element (const reference)
    /// @param priority The priority
    void push(const T& ele, PriorityType priority)
    {
        emplace(ele, priority);
    }

    /// @brief Pushes the element into the heap with specified priority
    /// @param ele The element (rvalue)
    /// @param priority The priority
    void push(T&& ele, PriorityType priority)
    {
        emplace(std::move(ele), priority);
    }

    /// @brief Empplaces the element into the heap with specified priority
    /// @param ele The element (rvalue)
    /// @param priority The priority
    template<typename U>
    void emplace(U&& ele, PriorityType priority)
    {
        if (priority >= maxPriority_)
        {
            throw std::out_of_range("Priority exceeds the max limit.");
        }

        buckets_[priority].push_back(std::forward<U>(ele));
        ++size_;

        mask_[priority] = true;

        if constexpr (isMaxQueue)
        {
            bestPriority_ = (priority > bestPriority_) ? priority : bestPriority_;
        }
        else
        {
           bestPriority_ = (priority < bestPriority_) ? priority : bestPriority_;
        }
    }

private:

    /// @brief Updates the highest priority
    void UpdateHighestPriority()
    {
        if constexpr (isMaxQueue)
        {
            for (PriorityType i = bestPriority_; i > 0; --i)
            {
                if (mask_[i])
                {
                    bestPriority_ = i;
                    return;
                }
            }

            // Reset best priority to 0 no matter if buckets_[0] is empty or not
            bestPriority_ = 0;
        }
        else
        {
           for (PriorityType i = bestPriority_; i < maxPriority_; ++i)
            {
                if (mask_[i])
                {
                    bestPriority_ = i;
                    return;
                }
            }

            // Reset best priority to max no matter if the last bucket is empty or not
            bestPriority_ = maxPriority_;
        }
    }

private:

    /// @brief The container
    std::vector<std::vector<T>> buckets_;

    /// @brief The number of elements in the queue
    std::size_t size_;

    const PriorityType maxPriority_;

    // The current best priority
    PriorityType bestPriority_;

    /// @brief The bitset that indicates which bucket is not empty (true if the bucket is not empty)
    std::bitset<MaxPriorityLimit> mask_;
};

#endif // INCLUDE_CONTAINER_BUCKETQUEUE_H_
