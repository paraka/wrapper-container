#ifndef _WRAPPER_CONTAINER_H_
#define _WRAPPER_CONTAINER_H_
 
#include <vector>
#include <initializer_list>

namespace Container
{

template <typename T, template<typename... > class U=std::vector>
class WrapperContainer
{
    using ContainerType = U<T>;
    using size_type = typename ContainerType::size_type;
    ContainerType theContainer {};

public:
    WrapperContainer() = default;
    ~WrapperContainer() = default;
    WrapperContainer(const WrapperContainer &) = default;
    WrapperContainer(WrapperContainer &&) = default;
    WrapperContainer& operator=(const WrapperContainer &) = default;

    WrapperContainer(std::initializer_list<T> il) : theContainer(il) {}

    bool empty() const 
    { 
        return theContainer.empty() ; 
    }

    size_type size() const 
    { 
        return theContainer.size(); 
    }

    void push(const T& item)
    {
        theContainer.insert(theContainer.end(), item);
    }

    void push(T&& item)
    {
        theContainer.insert(theContainer.end(), std::move(item));
    }

    T pop()
    {
        if (empty()) throw std::logic_error("Container Empty");
        auto iter = theContainer.begin();
        std::advance(iter,static_cast<size_type>(0));
        T retval{*iter};
        theContainer.erase(iter);

        return retval;
    }

    void pop(T& item)
    {
        if (empty()) throw std::logic_error("Container Empty");
        auto iter = theContainer.begin();
        std::advance(iter,static_cast<size_type>(0));
        T retval{*iter};
        item = retval;
        theContainer.erase(iter);
    }

    // Iterator stuff
    using iterator = typename ContainerType::iterator;
    using const_iterator = typename ContainerType::const_iterator;
    iterator begin() { return theContainer.begin(); }
    iterator end() { return theContainer.end(); }
    const_iterator begin() const { return theContainer.begin(); }
    const_iterator end() const { return theContainer.end(); }
    const_iterator cbegin() const { return theContainer.cbegin(); }
    const_iterator cend() const { return theContainer.cend(); }
};

template <typename T>
WrapperContainer<T> makeWrapperContainer(std::initializer_list<T> list)
{
    return WrapperContainer<T>{list};
}

template <template<typename...> class U,typename T>
WrapperContainer<T,U> makeWrapperContainer(std::initializer_list<T> list)
{
    return WrapperContainer<T,U>{list};
}

} // namespace Container

#endif // _WRAPPER_CONTAINER_H_
