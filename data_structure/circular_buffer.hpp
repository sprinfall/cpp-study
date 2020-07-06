#ifndef CIRCULAR_BUFFER_HPP_
#define CIRCULAR_BUFFER_HPP_

#include <memory>

template <class T>
class circular_buffer {
public:
  explicit circular_buffer(std::size_t capacity)
      : buf_(std::unique_ptr<T[]>(new T[capacity])), capacity_(capacity) {
  }

  void put(const T& item) {
    buf_[head_] = item;

    if (full_) {
      tail_ = (tail_ + 1) % capacity_;
    }

    head_ = (head_ + 1) % capacity_;

    full_ = (head_ == tail_);
  }

  T pop() {
    if (empty()) {
      return T{};
    }

    T item = buf_[tail_];
    full_ = false;
    tail_ = (tail_ + 1) % capacity_;

    return item;
  }

  void reset() {
    head_ = tail_;
    full_ = false;
  }

  bool empty() const {
    return (!full_ && (head_ == tail_));
  }

  bool full() const {
    return full_;
  }

  std::size_t capacity() const {
    return capacity_;
  }

  std::size_t size() const {
    std::size_t size = capacity_;

    if (!full_) {
      if (head_ >= tail_) {
        size = head_ - tail_;
      } else {
        size = capacity_ + head_ - tail_;
      }
    }

    return size;
  }

private:
  // See: https://stackoverflow.com/q/16711697 for `unique_ptr<T[]>`.
  std::unique_ptr<T[]> buf_;
  const std::size_t capacity_;
  std::size_t head_ = 0;
  std::size_t tail_ = 0;
  bool full_ = false;
};

#endif  // CIRCULAR_BUFFER_HPP_
