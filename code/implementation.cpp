class continuation {
private:
    void    *   fctx;

    explicit continuation( void * ptr) :
        fctx{ ptr } {
    }

public:
    ~continuation() {
        if ( nullptr != sptr_) {
            detail::ontop_fcontext( std::exchange( fctx, nullptr), nullptr, detail::unwind_stack);
        }
    }

    continuation resume() {
        return continuation{ detail::jump_fcontext( std::exchange( fctx, nullptr), nullptr) };
    }

    template< typename Fn, typename ... Arg >
    continuation resume_with( Fn && fn, Arg ... arg) {
        auto tpl = std::make_tuple( std::forward< Fn >( fn), std::forward< Arg >( arg) ... );
        return continuation{ detail::ontop_fcontext( std::exchange( fctx, nullptr), & tpl, detail::resume_with) };
    }
};

template< typename StackAlloc, typename Fn, typename ...Arg >
continuation callcc( std::allocator_arg_t, StackAlloc salloc, Fn && fn, Arg ... arg) {
    void * sp = salloc.allocate();
    return continuation{ make_fcontext( sp, std::forward< Fn >( fn) ) }.resume();
}
