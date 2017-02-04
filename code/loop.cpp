std::continuation foo(std::continuation && caller) {
    while (caller) {
        std::cout << "foo\n";
        caller= // (e)
           caller(); // (b)
    }
    return std::move(caller);
}

std::continuation foo_ct= // (c)
                     std::callcc(foo); // (a)
while (foo_ct) {
    std::cout << "bar\n";
    foo_ct= // (f)
       foo_ct(); // (d)
}

output:
    foo
    bar
    ...
