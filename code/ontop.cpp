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
                        data=-1;
                        return std::move( mc);  // (9)
                });
std::cout << "f1: returned third time" << std::endl;

output:
    f1: entered first time: 0
    f1: returned first time: 1
    f1: entered second time: 2
    f1: returned second time: 3
    f2: entered: 4
    f1: entered third time: -1
    f1: returned third time
