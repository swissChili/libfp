#include <fp/fp.hh>
#include <fp/math.hh>
#include <fp/io.hh>

int main(int argc, char *argv[]) {
    fp::list<int> list{};

    list << 123412 << 432 << 342;

    int sum = list.each(fp::println<int>).fold<int>(fp::sum, 0);

    std::cout << "Sum of list is " << sum << std::endl;
}
