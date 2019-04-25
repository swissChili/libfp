# libfp

libfp is a header-only library for functional programming in c++. You should use cmake to build your project and use
libfp, but if you don't want to, just pass `-I libfp` to your compiler and it will do the same thing. It is header
only after all.

libfp's `list<T>` type is a linked list which supports various functional and immutable features. It is automatically
garbage collected by `std::shared_ptr`, and supports O(1) insertions, O(n) mapping, folding, and iterating. Indexing
is also O(n) unfortunately. There should be a vector type implemented later that will have O(1) indexing and O(n)
insertions.

## example

```cpp
// main.cpp
#include <fp/fp.hh>
#include <fp/math.hh>
#include <fp/io.hh>

int main(int argc, char *argv[]) {
    fp::list<int> list{};

    list << 123412 << 432 << 342;

    int sum = list.each(fp::println<int>).fold<int>(fp::sum, 0);

    std::cout << "Sum of list is " << sum << std::endl;
}
```
