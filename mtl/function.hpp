#pragma once

#include <functional>
#include <memory>

// Initial implementation based on Sean Parent's ligthting talk "Polymorphic Task Template in Ten Minutes" at Meeting C++ 2017
// std::function like object to execute and hold a generic callable object

namespace mtl
{
    template <class>
    class Function;

    template <class ReturnType, class... Args>
    class Function<ReturnType(Args...)>
    {
        struct Concept;

        template <class T>
        struct Model;

        std::unique_ptr<Concept> data;

    public:
        template <class T>
        Function(T&& obj) :
        data(std::make_unique<Model<std::decay_t<T>>>(std::forward<T>(obj)))
        {}

        ReturnType operator()(Args... args)
        {
            return data->invoke(std::forward<Args>(args)...);
        }
    };

    template <class ReturnType, class... Args>
    struct Function<ReturnType(Args...)>::Concept
    {
        virtual ~Concept() = default;

        virtual ReturnType invoke(Args&&...) = 0;
    };

    template <class ReturnType, class... Args>
    template <class T>
    struct Function<ReturnType(Args...)>::Model final : Concept
    {
        template <class F>
        Model(F&& f) :
        func(std::forward<F>(f)) 
        {}

        ReturnType invoke(Args&&... args) override
        {
            return std::invoke(func, std::forward<Args>(args)...);
        }

        T func;
    };
}
