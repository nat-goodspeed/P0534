std::continuation entry_function(std::continuation&& caller) {
    caller = caller.resume();
    // ...
}
