#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <type_traits>
#include <iosfwd>

template <typename T, typename = std::enable_if_t< std::is_arithmetic<T>::value >>
class primitive final {
    T m_value;

public:
    using value_type = T;

    constexpr primitive() noexcept: m_value() {}
    constexpr primitive(T const& value) noexcept: m_value(value) {}

    primitive(primitive const&) noexcept = default;
    primitive(primitive &&) noexcept = default;

    primitive& operator=(primitive const&) noexcept = default;
    primitive& operator=(primitive &&) noexcept = default;

    constexpr T const& get() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t<!std::is_same<U, bool>::value  >>
    constexpr primitive const& operator+() const noexcept { return *this; }
    template <typename U = T, typename = std::enable_if_t<!std::is_same<U, bool>::value  >>
    constexpr primitive operator-() const noexcept { return -this->get(); }

    template <typename U = T, typename = std::enable_if_t< std::is_integral<U>::value && !std::is_same<U, bool>::value >>
    constexpr primitive operator~() const noexcept { return ~this->get(); }

    constexpr primitive<bool> operator!() const noexcept { return !this->get(); }

    primitive& operator++() noexcept { 
        ++m_value; 
        return *this; 
    }
    primitive operator++(int) noexcept { 
        return m_value++;
    }

    primitive& operator--() noexcept { 
        --m_value; 
        return *this; 
    }
    primitive operator--(int) noexcept { 
        return m_value--;
    }

    template <typename U>
    primitive& operator+=(U const& other) noexcept {
        m_value += other;
        return *this;
    }
    template <typename U>
    primitive& operator+=(primitive<U> const& other) noexcept {
        m_value += other.get();
        return *this;
    }

    template <typename U>
    primitive& operator-=(U const& other) noexcept {
        m_value -= other;
        return *this;
    }
    template <typename U>
    primitive& operator-=(primitive<U> const& other) noexcept {
        m_value -= other.get();
        return *this;
    }

    template <typename U>
    primitive& operator*=(U const& other) noexcept {
        m_value *= other;
        return *this;
    }
    template <typename U>
    primitive& operator*=(primitive<U> const& other) noexcept {
        m_value *= other.get();
        return *this;
    }

    template <typename U>
    primitive& operator/=(U const& other) noexcept {
        m_value /= other;
        return *this;
    }
    template <typename U>
    primitive& operator/=(primitive<U> const& other) noexcept {
        m_value /= other.get();
        return *this;
    }

    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator%=(U const& other) noexcept {
        m_value %= other;
        return *this;
    }
    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator%=(primitive<U> const& other) noexcept {
        m_value %= other.get();
        return *this;
    }

    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator<<=(U const& other) noexcept {
        m_value <<= other;
        return *this;
    }
    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator<<=(primitive<U> const& other) noexcept {
        m_value <<= other.get();
        return *this;
    }

    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator>>=(U const& other) noexcept {
        m_value >>= other;
        return *this;
    }
    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator>>=(primitive<U> const& other) noexcept {
        m_value >>= other.get();
        return *this;
    }

    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator&=(U const& other) noexcept {
        m_value &= other;
        return *this;
    }
    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator&=(primitive<U> const& other) noexcept {
        m_value &= other.get();
        return *this;
    }

    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator|=(U const& other) noexcept {
        m_value |= other;
        return *this;
    }
    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator|=(primitive<U> const& other) noexcept {
        m_value |= other.get();
        return *this;
    }

    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator^=(U const& other) noexcept {
        m_value ^= other;
        return *this;
    }
    template <typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator^=(primitive<U> const& other) noexcept {
        m_value ^= other.get();
        return *this;
    }

    template <typename U = T, typename = std::enable_if_t< std::is_same<U, signed char>::value >>
    constexpr operator primitive<short>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t< std::is_same<U, unsigned char>::value >>
    constexpr operator primitive<unsigned short>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t< std::is_same<U, signed char>::value || std::is_same<U, short>::value >>
    constexpr operator primitive<int>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t< std::is_same<U, unsigned char>::value || std::is_same<U, unsigned short>::value >>
    constexpr operator primitive<unsigned int>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t< 
        std::is_same<U, signed char>::value
        || std::is_same<U, short>::value 
        || std::is_same<U, int>::value
    >>
    constexpr operator primitive<long>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t< 
        std::is_same<U, unsigned char>::value 
        || std::is_same<U, unsigned short>::value
        || std::is_same<U, unsigned int>::value
    >>
    constexpr operator primitive<unsigned long>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t< 
        std::is_same<U, signed char>::value
        || std::is_same<U, short>::value 
        || std::is_same<U, int>::value
        || std::is_same<U, long>::value
    >>
    constexpr operator primitive<long long>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t< 
        std::is_same<U, unsigned char>::value 
        || std::is_same<U, unsigned short>::value
        || std::is_same<U, unsigned int>::value
        || std::is_same<U, unsigned long>::value
    >>
    constexpr operator primitive<unsigned long long>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t<
        std::is_same<U, signed char>::value 
        || std::is_same<U, unsigned char>::value
        || std::is_same<U, short>::value 
        || std::is_same<U, unsigned short>::value
        || std::is_same<U, int>::value
        || std::is_same<U, unsigned int>::value
        || std::is_same<U, long>::value
        || std::is_same<U, unsigned long>::value
        || std::is_same<U, float>::value
    >>
    constexpr operator primitive<double>() const noexcept { return m_value; }

    template <typename U = T, typename = std::enable_if_t<
        std::is_same<U, signed char>::value 
        || std::is_same<U, unsigned char>::value
        || std::is_same<U, short>::value 
        || std::is_same<U, unsigned short>::value
        || std::is_same<U, int>::value
        || std::is_same<U, unsigned int>::value
        || std::is_same<U, long>::value
        || std::is_same<U, unsigned long>::value
        || std::is_same<U, float>::value
        || std::is_same<U, double>::value
    >>
    constexpr operator primitive<long double>() const noexcept { return m_value; }

    template <typename U>
    constexpr explicit operator primitive<U>() const noexcept { return static_cast<U>(m_value); }

    friend std::istream& operator>>(std::istream& lhs, primitive<T> & rhs) { return lhs >> rhs.m_value; }
};

template <typename T>
constexpr primitive<T> operator+(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() + rhs; }
template <typename T>
constexpr primitive<T> operator+(T const& lhs, primitive<T> const& rhs) noexcept { return lhs + rhs.get(); }
template <typename T1, typename T2>
constexpr auto operator+(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() + rhs.get())> {
    return lhs.get() + rhs.get();
}

template <typename T>
constexpr primitive<T> operator-(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() - rhs; }
template <typename T>
constexpr primitive<T> operator-(T const& lhs, primitive<T> const& rhs) noexcept { return lhs - rhs.get(); }
template <typename T1, typename T2>
constexpr auto operator-(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() - rhs.get())> {
    return lhs.get() - rhs.get();
}

template <typename T>
constexpr primitive<T> operator*(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() * rhs; }
template <typename T>
constexpr primitive<T> operator*(T const& lhs, primitive<T> const& rhs) noexcept { return lhs * rhs.get(); }
template <typename T1, typename T2>
constexpr auto operator*(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() * rhs.get())> {
    return lhs.get() * rhs.get();
}

template <typename T>
constexpr primitive<T> operator/(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() / rhs; }
template <typename T>
constexpr primitive<T> operator/(T const& lhs, primitive<T> const& rhs) noexcept { return lhs / rhs.get(); }
template <typename T1, typename T2>
constexpr auto operator/(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() / rhs.get())> {
    return lhs.get() / rhs.get();
}

template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator%(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() % rhs; }
template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator%(T const& lhs, primitive<T> const& rhs) noexcept { return lhs % rhs.get(); }
template <typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator%(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() % rhs.get())> {
    return lhs.get() % rhs.get();
}

template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator&(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() & rhs; }
template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator&(T const& lhs, primitive<T> const& rhs) noexcept { return lhs & rhs.get(); }
template <typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator&(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() & rhs.get())> {
    return lhs.get() & rhs.get();
}

template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator|(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() | rhs; }
template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator|(T const& lhs, primitive<T> const& rhs) noexcept { return lhs | rhs.get(); }
template <typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator|(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() | rhs.get())> {
    return lhs.get() | rhs.get();
}

template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator^(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() ^ rhs; }
template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator^(T const& lhs, primitive<T> const& rhs) noexcept { return lhs ^ rhs.get(); }
template <typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator^(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() ^ rhs.get())>  {
    return lhs.get() ^ rhs.get();
}

template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator<<(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() << rhs; }
template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator<<(T const& lhs, primitive<T> const& rhs) noexcept { return lhs << rhs.get(); }
template <typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator<<(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() << rhs.get())> {
    return lhs.get() << rhs.get();
}

template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator>>(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() >> rhs; }
template <typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator>>(T const& lhs, primitive<T> const& rhs) noexcept { return lhs >> rhs.get(); }
template <typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator>>(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() >> rhs.get())> {
    return lhs.get() >> rhs.get();
}

constexpr primitive<bool> operator&&(primitive<bool> const& lhs, bool const& rhs) noexcept { return lhs.get() && rhs; }
constexpr primitive<bool> operator&&(bool const& lhs, primitive<bool> const& rhs) noexcept { return lhs && rhs.get(); }
constexpr primitive<bool> operator&&(primitive<bool> const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs.get() && rhs.get();
}

constexpr primitive<bool> operator||(primitive<bool> const& lhs, bool const& rhs) noexcept { return lhs.get() || rhs; }
constexpr primitive<bool> operator||(bool const& lhs, primitive<bool> const& rhs) noexcept { return lhs || rhs.get(); }
constexpr primitive<bool> operator||(primitive<bool> const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs.get() || rhs.get();
}

template <typename T>
constexpr bool operator==(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() == rhs; }
template <typename T>
constexpr bool operator==(T const& lhs, primitive<T> const& rhs) noexcept { return lhs == rhs.get(); }
template <typename T1, typename T2>
constexpr bool operator==(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() == rhs.get();
}

template <typename T>
constexpr bool operator!=(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() != rhs; }
template <typename T>
constexpr bool operator!=(T const& lhs, primitive<T> const& rhs) noexcept { return lhs != rhs.get(); }
template <typename T1, typename T2>
constexpr bool operator!=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() != rhs.get();
}

template <typename T>
constexpr bool operator<(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() < rhs; }
template <typename T>
constexpr bool operator<(T const& lhs, primitive<T> const& rhs) noexcept { return lhs < rhs.get(); }
template <typename T1, typename T2>
constexpr bool operator<(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() < rhs.get();
}

template <typename T>
constexpr bool operator<=(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() <= rhs; }
template <typename T>
constexpr bool operator<=(T const& lhs, primitive<T> const& rhs) noexcept { return lhs <= rhs.get(); }
template <typename T1, typename T2>
constexpr bool operator<=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() <= rhs.get();
}

template <typename T>
constexpr bool operator>(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() > rhs; }
template <typename T>
constexpr bool operator>(T const& lhs, primitive<T> const& rhs) noexcept { return lhs > rhs.get(); }
template <typename T1, typename T2>
constexpr bool operator>(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() > rhs.get();
}

template <typename T>
constexpr bool operator>=(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() >= rhs; }
template <typename T>
constexpr bool operator>=(T const& lhs, primitive<T> const& rhs) noexcept { return lhs >= rhs.get(); }
template <typename T1, typename T2>
constexpr bool operator>=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() >= rhs.get();
}

template <typename T>
std::ostream& operator<<(std::ostream& lhs, primitive<T> const& rhs) { return lhs << rhs.get(); }

#endif