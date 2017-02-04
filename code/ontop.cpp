std::continuation f(std::continuation && mc) {
    int data=std::get_data<int>(mc); // (1)
    std::cout << "f: entered first time: " << data << std::endl;
    mc = // (5)
       mc(data+1); // (2)
    data=std::get_data<int>(mc);
    std::cout << "f: entered second time: " << data << std::endl;
    mc = // (10)
       mc(data+1); // (6)
    data=std::get_data<int>(mc); // (11)
    std::cout << "f: entered third time: " << data << std::endl;
    return std::move(mc); // (12)
}

int g(std::continuation && mc) {
    int data=std::get_data<int>(mc);
    std::cout << "g: entered: " << data << std::endl;
    return -1; // (9)
}

int data=1;
std::continuation f_ct= // (3)
    std::callcc(f,data); // (0)
data=std::get_data<int>(f_ct);
std::cout << "f: returned first time: " << data << std::endl;
f_ct = // (7)
    f_ct(data+1); // (4)
data=std::get_data<int>(f_ct);
std::cout << "f: returned second time: " << data << std::endl;
f_ct = // (13)
    f_ct(std::invoke_ontop_arg,g,data+1); // (8)
data=std::get_data<int>(f_ct);
std::cout << "f: returned third time: " << data << std::endl;

output:
    f: entered first time: 1
    f: returned first time: 2
    f: entered second time: 3
    f: returned second time: 4
    g: entered: 5
    f: entered third time: -1
