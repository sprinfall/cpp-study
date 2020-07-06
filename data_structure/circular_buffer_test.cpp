#include "circular_buffer.hpp"

#include <cassert>

int main() {
  circular_buffer<int> cb{ 3 };
  // head: 0
  // tail: 0

  cb.put(1);
  // [ 1 | x | x ]
  // head: 1
  // tail: 0

  cb.put(2);
  // [ 1 | 2 | x ]
  // head: 2
  // tail: 0

  cb.put(3);
  // [ 1 | 2 | 3 ]
  // head: 0 <- (2 + 1) % 3
  // tail: 0

  assert(cb.full());

  assert(cb.pop() == 1);
  // [ x | 2 | 3 ]
  // head: 0
  // tail: 1

  assert(cb.pop() == 2);
  // [ x | x | 3 ]
  // head: 0
  // tail: 2
  // size: capacity + head - tail = 3 + 0 - 2 = 1

  assert(cb.pop() == 3);
  // [ x | x | x ]
  // head: 0
  // tail: 0 <- (2 + 1) % 3

  assert(!cb.full());
  assert(cb.empty());

  cb.put(1);
  cb.put(2);
  cb.put(3);
  cb.put(4);
  cb.put(5);

  assert(cb.pop() == 3);
  assert(cb.pop() == 4);
  assert(cb.pop() == 5);

  assert(cb.empty());

  return 0;
}
