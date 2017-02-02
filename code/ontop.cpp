std::continuation f1(std::continuation && c) {
    int data=std::transfer_data<int>(c); // (b)
    std::cout << "f1: entered first time: " << data << std::endl;
    c = // (f)
       c(data+1); // (c)
    data=std::transfer_data<int>(c);
    std::cout << "f1: entered second time: " << data << std::endl;
    c = // (k)
       c(data+1); // (g)
    data=std::transfer_data<int>(c); // (l)
    std::cout << "f1: entered third time: " << data << std::endl;
    return std::move(c); // (m)
}

int f2(std::continuation & c) {
    int data=std::transfer_data<int>(c);
    std::cout << "f2: entered: " << data << std::endl;
    return -1; // (j)
}

int data=0;
std::continuation c= // (d)
    std::callcc(f1,data); // (a)
data=std::transfer_data<int>(c);
std::cout << "f1: returned first time: " << data << std::endl;
c = // (h)
    c(data+1); // (e)
data=std::transfer_data<int>(c);
std::cout << "f1: returned second time: " << data << std::endl;
c = // (n)
    c(std::invoke_ontop_arg,f2,data+1); // (i)
data=std::transfer_data<int>(c);
std::cout << "f1: returned third time: " << data << std::endl;

output:
    f1: entered first time: 1
    f1: returned first time: 2
    f1: entered second time: 3
    f1: returned second time: 4
    f2: entered: 5
    f1: entered third time: -1
