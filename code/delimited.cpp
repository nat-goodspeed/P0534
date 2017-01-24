reset=[]{
    std::cout << "1\n"; // (a)
    shift=[](auto cont){ // (b)
        cont();
        cont();
        std::cout << "2\n"; // (d)
    };
    std::cout << "3\n"; // (c)
};

output:
    1 3 3 2
