std::continuation f(std::continuation && mc) {
    int data=std::get_data<int>(mc); // (b)
    std::cout << "f: entered first time: " << data << std::endl;
    mc = // (f)
       mc(data+1); // (c)
    data=std::get_data<int>(mc);
    std::cout << "f: entered second time: " << data << std::endl;
    mc = // (k)
       mc(data+1); // (g)
    data=std::get_data<int>(mc); // (l)
    std::cout << "f: entered third time: " << data << std::endl;
    return std::move(mc); // (m)
}

int g(std::continuation && mc) {
    int data=std::get_data<int>(mc);
    std::cout << "g: entered: " << data << std::endl;
    return -1; // (j)
}

int data=1;
std::continuation f_ct= // (d)
    std::callcc(f,data); // (a)
data=std::get_data<int>(f_ct);
std::cout << "f: returned first time: " << data << std::endl;
f_ct = // (h)
    f_ct(data+1); // (e)
data=std::get_data<int>(f_ct);
std::cout << "f: returned second time: " << data << std::endl;
f_ct = // (n)
    f_ct(std::invoke_ontop_arg,g,data+1); // (i)
data=std::get_data<int>(f_ct);
std::cout << "f: returned third time: " << data << std::endl;

output:
    f: entered first time: 1
    f: returned first time: 2
    f: entered second time: 3
    f: returned second time: 4
    g: entered: 5
    f: entered third time: -1
