// launch this context early in the thread as a service used by deep_call()
std::continuation deep_stack(std::continuation&& client) {
    for (;;) {
        // In effect, this context is a little server, running a function that
        // needs a deep stack and then context-switching back to whatever
        // invoked it. Because of this infinite loop, it won't terminate
        // voluntarily: we'll destroy it while it's suspended.
        client = client.resume();
    }
    return std::move(client);
}

// deep_call() continually updates this continuation as the way to run code in
// the context of deep_stack()
std::continuation deep_stack_cont;

// this function can be called from a context with a shallow stack to run some
// non-suspending function in the context of deep_stack()
template <typename Fn>
void deep_call(Fn&& fn) {
    // This resume_with() call runs the lambda on the deep_stack() context.
    // The lambda simply calls the passed fn, then returns to the loop in
    // deep_stack(), which context-switches back to return from resume_with().
    // Finally we update the canonical deep_stack_cont for the next usage.
    deep_stack_cont = deep_stack_cont.resume_with(
        [auto fn=std::forward<Fn>(fn)](std::continuation&& caller){
            fn();
            return std::move(caller);
        });
}

// this is an example of a context with a shallow stack
std::continuation shallow_stack(std::continuation&& caller) {
    // pretend that emitting std::cout requires arbitrary stack depth
    deep_call([](){ std::cout << "Hello from deep_stack!" << std::endl; });
    deep_call([](){ std::cout << "Another visit to deep_stack" << std::endl; });
    return std::move(caller);
}

// main() simply launches the deep_stack() resource context, then runs
// shallow_stack() as an example of a consumer
int main() {
    // Launch the deep_stack() context. Pretend we're passing a StackAllocator
    // with a size "big enough for whatever." Since the first thing
    // deep_stack() does is to switch back to its invoker, this call should
    // bounce right back here.
    deep_stack_cont = std::callcc(deep_stack);
    // pretend we're passing a StackAllocator with a very small stack size
    std::callcc(shallow_stack);
    return 0;
}
