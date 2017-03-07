class continuation {
private:
    void    *   vp;

    explicit continuation( void * ptr) :
        vp{ ptr } {
    }

public:
    ~continuation() {
        if ( nullptr != vp) {
            // resume context by calling resume_with()
            // apply a special function to resume_with() 
            // that throws a std::unwind_exception
            // this exception is catched at the last stack-frame,
            // e.g. the stack-frame that was prepared by callcc() before
            // from this stack frame switch back to the context that has
            // invoked ~continuation()
            // deallocate the stack
        }
    }

    continuation resume() {
        // PROLOGUE (+ store instruction-pointer)
        // exchange current stack with `vp` (becomes current stack)
        // EPILOGUE (+ restore instruction-pointer)
        // stack-pointer of caller passed as std::continuation
    }

    template< typename Fn >
    continuation resume_with( Fn && fn) {
        // PROLOGUE (+ store instruction-pointer)
        // exchange current stack with `vp` (becomes current stack)
        // EPILOGUE (+ restore instruction-pointer)
        // `fn` is loaded into instruction-pointer == `fn()` is executed by
        // the resumed execution context
        // stack-pointer of caller passed as std::continuation to `fn()`
    }
};

template< typename StackAlloc, typename Fn >
continuation callcc( std::allocator_arg_t, StackAlloc salloc, Fn && fn) {
    // allocated memory for stack `vp`
    // prepare stack (generate special stack-frame)
    // construct std::continuation from stack `vp` and resume it
    return continuation{ vp }.resume();
}
