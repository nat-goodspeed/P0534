std::continuation foo(std::continuation && caller) {
    while (caller) {
        std::cout << "foo\n";
        caller= // (4)
           caller.resume(); // (1)
    }
    return std::move(caller);
}

std::continuation foo_ct= // (2)
                     std::callcc(foo); // (0)
while (foo_ct) {
    std::cout << "bar\n";
    foo_ct= // (5)
       foo_ct.resume(); // (3)
}

output:
    foo
    bar
    ...
