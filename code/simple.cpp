int main() {
    std::continuation c1=
        std::callcc( // (a)
            [](std::continuation && c2){ // (b)
                return std::move(c2); // (c)
            });
    return 0;
}
