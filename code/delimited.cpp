reset=[]{
    std::cout << "1\n"; // (0)
    shift=[](auto cont){ // (1)
        cont();
        cont();
        std::cout << "2\n"; // (3)
    };
    std::cout << "3\n"; // (2)
};

output:
    1 3 3 2
