# C++ 的聚合对象及其初始化

首先，什么叫聚合 (aggregate)？

对 C 来说，数组和结构是聚合。

对 C++ 来说，除了数组外，满足以下条件的类（或结构）也是聚合：
- 没有用户声明的构造函数
- 没有 `private` 或 `protected` 非静态数据成员
- 没有基类
- 没有虚函数

所以，下面几个类型都是聚合：

```cpp
int[5];

struct Person {
  std::string name;
  int age;
};

std::array;
```

## 初始化聚合对象

聚合对象可以用“初始化列表”，这种初始化方式非常方便。

```cpp
typedef int Array[5];

Array a1{};  // or Array a1 = {}
// { 0, 0, 0, 0, 0 }
Array a2{ 0, 1, 2 };
// { 0, 1, 2, 0, 0 }
Array a3{ 0, 1, 2, 3, 4 };
// { 0, 1, 2, 3, 4 }
```

```cpp
struct Person {
  std::string name;
  int age;
};

Person p1{};
// { "",  0 }
Person p2{ "john" };
// { "john", 0 }
Person p3{ "john", 26 };
// { "john", 26 }
```

```cpp
std::array<int, 3> a{ 0, 1, 2 };
```

对聚合对象来说，缺省初始化（default-initalization）就是指零值初始化（zero-initialization）。

如果不指定初始化列表的话，对象各元素的初始值就不确定了。

```cpp
std::array<int, 3> a;  // 三个元素的初始值不确定
```

## 成员聚合对象的零值初始化

- 成员名字后面加 `{}` 或 `()` 就缺省初始化了这个成员；
- 对于聚合成员来说，缺省初始化就是指零值初始化；
- 如果成员有一个 non-trivial 的构造函数，那么缺省初始化就意味着调用它的缺省构造函数。

如何实现下面这个类的缺省构造函数？

```cpp
class C {
public:
  C();  // 如何实现这个？
private:
  struct S {
    int x;
    int* p;
    bool b;
  };
  S s;
  int d[5];
};
```

由 C 转过来的 C++ 程序员可能会这样实现：

```cpp
C::C() {
  memset(&s, 0, sizeof(S));
  memset(d, 0, sizeof(d));  // 或者甚至用 for (int i = 0; i < 5; ++i) d[i] = 0;
}
```

更简单更 C++ 的方式是：

```cpp
C::C() : s{}, d{} {
}
```
因为 `s` 和 `d` 这两个成员都是聚合对象，使用 `{}` 或 `()` 就可以初始化为零值。

成员聚合对象的非零值初始化也是一个道理，就不赘述了。
