std::continuation newcontext = std::callcc_deferred(entry_function);
newcontext = newcontext.resume();
