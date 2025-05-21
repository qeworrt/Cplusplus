#include <type_traits>

namespace tlist {

template<typename... types>
struct typeList {};


template<typename TList>
struct size;

template<typename... types>
struct size<typeList<types...>> : std::integral_constant<std::size_t, sizeof...(types)> {};


template<std::size_t index, typename TList>
struct typeAt;

template<std::size_t index, typename head, typename... tail>
struct typeAt<index, typeList<head, tail...>> : typeAt<index - 1, typeList<tail...>> {};

template<typename head, typename... tail>
struct typeAt<0, typeList<head, tail...>> {
    using type = head;
};


template<typename T, typename TList>
struct contains;

template<typename T>
struct contains<T, typeList<>> : std::false_type {};

template<typename T, typename head, typename... tail>
struct contains<T, typeList<head, tail...>> : std::conditional_t<
    std::is_same_v<T, head>,
    std::true_type,
    contains<T, typeList<tail...>>
> {};


template<typename T, typename TList>
struct indexOf;

template<typename T>
struct indexOf<T, typeList<>> {
    static_assert(sizeof(T) == 0, "тип не найден");
};

template<typename T, typename head, typename... tail>
struct indexOf<T, typeList<head, tail...>> {
private:
    static constexpr std::size_t next = indexOf<T, typeList<tail...>>::value;
public:
    static constexpr std::size_t value = std::is_same_v<T, head> ? 0 : 1 + next;
};

template<typename T, typename... tail>
struct indexOf<T, typeList<T, tail...>> : std::integral_constant<std::size_t, 0> {};


template<typename T, typename TList>
struct pushFront;

template<typename T, typename... types>
struct pushFront<T, typeList<types...>> {
    using type = typeList<T, types...>;
};


template<typename T, typename TList>
struct pushBack;

template<typename T, typename... types>
struct pushBack<T, typeList<types...>> {
    using type = typeList<types..., T>;
};

}
