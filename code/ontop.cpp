int data = 0;
std::continuation f_ct=  // (3)
    std::callcc([&data](std::continuation && mc) {  // (0)
                std::cout << "f1: entered first time: " << data  << std::endl; // (1)
                data+=1;
                mc=  // (5)
                    mc.resume();  // (2)
                std::cout << "f1: entered second time: " << data  << std::endl;
                data+=1;
                mc=  // (10)
                    mc.resume();  // (6)
                std::cout << "f1: entered third time: " << data << std::endl; // (11)
                return std::move(mc);  // (12)
            });
std::cout << "f1: returned first time: " << data << std::endl;
data+=1;
f_ct=  // (7)
    f_ct.resume();  // (4)
std::cout << "f1: returned second time: " << data << std::endl;
data+=1;
f_ct=  // (13)
    f_ct.resume_with([&data](std::continuation && mc){  // (8)
                        std::cout << "f2: entered: " << data << std::endl;
                        data=-1;  // (9)
                        return std::move( c);
                });
std::cout << "f1: returned third time" << std::endl;

output:
    f: entered first time: 1
    f: returned first time: 2
    f: entered second time: 3
    f: returned second time: 4
    g: entered: 5
    f: entered third time: -1
