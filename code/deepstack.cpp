#include <iostream>
#include <boost/context/continuation.hpp>

// Launch this context early in the thread as a service
// used by deep_call()
boost::context::continuation deep_stack(boost::context::continuation&& client) {
    std::cout << "entering   deep_stack()" << std::endl;
    try {
        for (;;) {
            // In effect, this context is a little server,
            // running invoke_ontop_arg functions that
            // need a deep stack and then context-
            // switching back to whatever invoked them.
            // Because of this infinite loop, it won't
            // terminate voluntarily: we'll destroy it
            // while it's suspended.
            std::cout << "spinning   deep_stack()" << std::endl;
            client = client.resume();
            // if we were passed a std::function object
            if (client.data_available()) {
                // retrieve it
                std::function<void()> func =
                    client.get_data<std::function<void()>>();
                // and call it
                func();
            }
        }
        std::cout << "exiting    deep_stack()" << std::endl;
        return std::move(client);
    } catch (...) {
        std::cout << "destroying deep_stack()" << std::endl;
        throw;
    }
}

// deep_call() continually updates this continuation as
// the way to run code in the context of deep_stack()
boost::context::continuation deep_stack_cont;

// this function can be called from a context with a
// shallow stack to run some non-suspending function in
// the context of deep_stack()
void deep_call(std::function<void()> const& func) {
    std::cout << "entering   deep_call()" << std::endl;
    deep_stack_cont = deep_stack_cont.resume(func);
    std::cout << "exiting    deep_call()" << std::endl;
}

// this is an example of a context with a shallow stack...
// we don't actually give it a shallow stack because we do
// want to see its std::cout output
boost::context::continuation shallow_stack(boost::context::continuation&& caller) {
    std::cout << "entering   shallow_stack()" << std::endl;
    std::cout << "calling    deep_call()" << std::endl;
    deep_call([](){ std::cout << "Hello from deep_stack!" << std::endl; });
    std::cout << "calling    deep_call() again" << std::endl;
    deep_call([](){ std::cout << "Another visit to deep_stack" << std::endl; });
    std::cout << "exiting    shallow_stack()" << std::endl;
    return std::move(caller);
}

// main() simply launches the deep_stack() resource context, then runs
// shallow_stack() as an example of a consumer
int main() {
    std::cout << "launching  deep_stack()" << std::endl;
    // Because deep_stack() simply loops on switching back
    // to its most recent invoker, this call should bounce
    // right back here.
    deep_stack_cont = boost::context::callcc(deep_stack);
    std::cout << "launched   deep_stack()" << std::endl;
    std::cout << "launching  shallow_stack()" << std::endl;
    boost::context::callcc(shallow_stack);
    std::cout << "back from  shallow_stack()" << std::endl;
    return 0;
}
