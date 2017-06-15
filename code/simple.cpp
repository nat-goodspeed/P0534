int main() {
    std::continuation lambda=
        std::callcc( // (a)
            [](std::continuation && caller){ // (b)
                return std::move(caller); // (c)
            });
    return 0;
}
