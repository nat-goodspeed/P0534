class continuation {
public:
    continuation() noexcept:

    ~continuation():

    continuation( continuation && other) noexcept;

    continuation & operator=( continuation && other) noexcept;

    continuation( continuation const& other) noexcept = delete;
    continuation & operator=( continuation const& other) noexcept = delete;

    template< typename ... Arg >
    continuation operator()( Arg ... arg);

    template< typename Fn, typename ... Arg >
    continuation operator()( invoke_ontop_arg_t, Fn && fn, Arg ... arg);

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;

    bool operator==( continuation const& other) const noexcept;
    bool operator!=( continuation const& other) const noexcept;
    bool operator<( continuation const& other) const noexcept;
    bool operator>( continuation const& other) const noexcept;
    bool operator<=( continuation const& other) const noexcept;
    bool operator>=( continuation const& other) const noexcept;

    void swap( continuation & other) noexcept;
};
