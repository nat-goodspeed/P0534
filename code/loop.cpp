std::continuation foo( std::continuation && c1) {
    while ( c1) {
        std::cout << "foo\n"; // (b)
        c1 = // (f)
            std::resume( std::move( c1) ); // (c)
    }
    return std::move( c1);
}

int main() {
    std::continuation c2 = // (d)
        std::callcc( foo); // (a)
    while ( c2) {
        std::cout << "bar\n";
        c2 = // (g)
            std::resume( std::move( c2) ); // (e)
    }
    std::cout << "main: done" << std::endl;
    return 0;
}

output:
    foo
    bar
    foo
    ...
