// Launch this context early in the thread as a service
// used by deep_call()
std::continuation deep_stack(std::continuation&& client)
{
    for (;;)
    {
        // In effect, this context is a little server, running resume_with()
        // functions that need a deep stack and then context-switching back to
        // whatever invoked them. Because of this infinite loop, it won't
        // terminate voluntarily: we'll destroy it while it's suspended.
        client = client();
    }
    return std::move(client);
}

// deep_call() continually updates this continuation as the way to run code in
// the context of deep_stack()
std::continuation deep_stack_cont;

// This resume_with() function expects a single argument: a nullary callable
// to be run in the context of deep_stack(). A resume_with() function must
// return the same type as the parameter passed to it.
template <typename FUNC>
auto deep_thunk(std::continuation&& caller)
{
    // retrieve the function passed to deep_thunk() by deep_call()
    FUNC func(std::get_data<FUNC>(caller));
    // then call it
    func();
    // returning from this function should return from the client() call in
    // deep_stack()
    return std::move(func);
}

// this function can be called from a context with a shallow stack to run some
// non-suspending function in the context of deep_stack()
template <typename FUNC>
void deep_call(FUNC&& func)
{
    deep_stack_cont = deep_stack_cont(std::exec_ontop_arg,
                                      deep_thunk<FUNC>,
                                      std::forward<FUNC>(func));
}

// this is an example of a context with a shallow stack...
// we don't actually give it a shallow stack because we do
std::continuation shallow_stack(std::continuation&& caller)
{
    return std::move(caller);
}

// main() simply launches the deep_stack() resource context, then runs
// shallow_stack() as an example of a consumer
int main(int argc, char *argv[])
{
    // Because deep_stack() simply loops on switching back
    // to its most recent invoker, this call should bounce
    // right back here.
    deep_stack_cont = std::callcc(deep_stack);
    std::callcc(shallow_stack);
    return 0;
}
