bool data_available( continuation const& c) noexcept;

template< typename Arg >
typename Arg get_data( continuation & c);

template< typename ... Arg >
typename std::tuple< Arg ... > get_data( continuation & c);

template< typename Fn, typename ... Arg >
continuation callcc( Fn && fn, Arg ... arg);

template< typename StackAlloc, typename Fn, typename ... Arg >
continuation callcc( std::allocator_arg_t, StackAlloc salloc, Fn && fn, Arg ... arg);

template< typename StackAlloc, typename Fn, typename ... Arg >
continuation callcc( std::allocator_arg_t, preallocated palloc, StackAlloc salloc, Fn && fn, Arg ... arg);

void swap( continuation & l, continuation & r) noexcept;
