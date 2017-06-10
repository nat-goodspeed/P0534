class continuation {
private:
    void    *   vp;

    explicit continuation( void * ptr) :
        vp{ ptr } {
    }

public:
    ~continuation() {
        if ( nullptr != vp) {
            // resume context by calling resume_with().
            // apply a special function to resume_with() 
            // that throws a std::unwind_exception.
            // this exception is caught at the last stack-frame,
            // i.e. the stack-frame originally prepared by callcc().
            // from that stack frame switch back to the context that
            // invoked ~continuation().
            // deallocate the stack.
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
        // `fn` is loaded into instruction-pointer: `fn()` is executed by
        // the resumed execution context
        // stack-pointer of caller passed as std::continuation to `fn()`
    }
};

template< typename StackAlloc, typename Fn >
continuation callcc( std::allocator_arg_t, StackAlloc salloc, Fn && fn) {
    // allocate memory for stack `vp`
    // prepare stack (generate special stack-frame)
    // construct std::continuation from stack `vp` and resume it
    return continuation{ vp }.resume();
}
