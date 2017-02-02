int i=1;
std::continuation c1=
    std::callcc( // (a)
        [](std::continuation && c2){
            int j=std::transfer_data<int>(c2); // (b)
            std::cout << "inside ctx1,j==" << j << std::endl;
            c2=c2(j+1); // (c)
            return std::move(c2); // (f)
        },
        i);
i=std::transfer_data<int>(c1); // (d)
std::cout << "i==" << i << std::endl;
c1=c1(); // (e)

output:
    inside c1,j==1
    i==2
