#include <cstdint>

namespace resolvers {

    static constexpr std::uint32_t m_min{ 0x9000000 };
    static constexpr std::uint32_t m_max{ 0x10000000 };

    class fname_c
    {
    public:
        bool initialize();
        std::array<char, 64> resolve(const std::uint32_t index);

    private:
        std::uintptr_t pool_offset();
        std::uint32_t recover_key() const;

    private:
        bool m_initialized{ false };
        std::uintptr_t m_pool{ 0 };
        std::uint32_t m_key{ 0 };
    }; // fname_c

    inline bool valid(const std::uintptr_t v) noexcept
    {
        if (!v) {
            return false;
        }

        if (v < 0x10000ull or v > 0x00007fffffffffffull) {
            return false;
        }

        if (v & 0xfull) {
            return false;
        }

        if (((v >> 36) & 0xfff) == 0x7ff) {
            return false;
        }

        if (v <= 0xffffffffull) {
            return false;
        }

        if (v < 0x10000000000ull) {
            return false;
        }

        return true;
    }

    template< typename t, std::size_t step = sizeof(t), std::size_t page_size = 0x1000u >
    std::vector< std::pair< t, std::uint32_t > > batch_read(const std::uintptr_t base, const std::uint32_t start, const std::uint32_t end);

} // namespace resolvers

namespace check {
    uintptr_t guard;

    bool zero_check(uintptr_t pointer)
    {
        constexpr uintptr_t filter = 0xFFFF0000FFFFFF00;
        uintptr_t result = pointer & filter;
        return result == 0x0000000000000000;
    }

    bool extras_check(uintptr_t pointer)
    {
        constexpr uintptr_t filter = 0xFFFF000000000000;
        uintptr_t result = pointer & filter;
        return result == 0x0000000000000000;
    }

    bool is_valid(uintptr_t pointer)
    {
        if (!pointer)
            return false;

        if (zero_check(pointer))
            return false;

        if (!extras_check(pointer))
            return false;

        return true;
    }

    bool is_guarded_2(uintptr_t pointer)
    {

        if (zero_check(pointer))
        {
            return false;
        }

        constexpr uintptr_t filter = 0xFFFFFFFFFF000000;
        uintptr_t result = pointer & filter;
        return result == 0x0000000000000000;
    }

    bool is_guarded(uintptr_t pointer)
    {
        constexpr uintptr_t filter = 0xFFFFFFFF00000000;
        uintptr_t result = pointer & filter;
        return result == 0x8000000000 || result == 0x10000000000;
    }

    uint64_t validate_pointer(uint64_t address)
    {
        if (guard != 0 && is_guarded(address))
            return guard + (address & 0xFFFFFF);
        else
            return address;
    }
}