#ifndef LIBFP_FP_HH
#define LIBFP_FP_HH

#include <string>
#include <iostream>
#include <memory>
#include <functional>


namespace fp {

    template<class T>
    class option {
    protected:
        T val;
        bool should_unwrap;
        std::string err = "Failed to unwrap a `none` value on an option.";

    public:
        option(T s) : val(s), should_unwrap(true) {}

        option() : val((T) 0), should_unwrap(false) {}

        bool is_just() { return should_unwrap; }

        T unwrap() {
            if (should_unwrap) return val;
            else {
                std::cerr << err;
                std::exit(1);
            }
        }

        T expect(std::string error) {
            if (should_unwrap) return val;
            else {
                std::cerr << error;
                std::exit(1);
            }
        }
    };


    template<class T>
    class node {
    public:
        option<T> value;
        option<std::shared_ptr<node<T>>> next;

        node(T val) : value(option<T>(val)), next(option<std::shared_ptr<node<T>>>()) {}

        void set_next(std::shared_ptr<node<T>> shared) {
            next = option<std::shared_ptr<node<T>>>(shared);
        }
    };

    template<class T>
    class list {
    public:
        option<std::shared_ptr<node<T>>> first;
        option<std::shared_ptr<node<T>>> last;

        unsigned int length;

        list() :
                first(option<std::shared_ptr<node<T>>>()),
                last(option<std::shared_ptr<node<T>>>()),
                length(0) {}

        explicit list(std::initializer_list<T> items): length(0) {
            for (T i : items) {
                length++;
                operator<<(i);
            }
        }

        list<T> operator<<(T val) {
            std::shared_ptr<node<T>> shared(new node<T>(val));
            option<std::shared_ptr<node<T>>> opt(shared);

            if (!first.is_just() || !last.is_just()) {
                // praise be verbosity
                first = opt;
            } else {
                last.unwrap()->set_next(shared);
            }
            last = opt;
            length++;

            return *this;
        }

        option<T> get_last() {
            return last.unwrap()->value;
        }

        option<T> operator[](int index) {
            if (index >= length) return option<T>();

            std::shared_ptr<node<T>> current = first.unwrap();
            for (int i = 0; i < index; ++i) {
                current = current->next.unwrap();
            }

            return current->value;
        }

        template <typename U>
        list<U> map(std::function<U(T)> f) {
            auto newlist = new list<U>();
            for (int i = 0; i < length; ++i) {
                newlist->operator<<(f(operator[](i).unwrap()));
            }

            return *newlist;
        }

        list<T> each(std::function<void(T)> f) {
            for (int i = 0; i < length; ++i) {
                f(operator[](i).unwrap());
            }

            return *this;
        }

        template <typename U>
        U fold(std::function<U(U, T)> f, U initial) {
            U acc = initial;

            for (int i = 0; i < length; ++i) {
                acc = f(acc, operator[](i).unwrap());
            }

            return acc;
        }
    };
}


#endif //LIBFP_FP_HH
