int i=1,j=2;
std::continuation c1=
    std::callcc( // (a)
        [](std::continuation && c2){
            auto [i,j]=std::transfer_data<int,int>(c2); // (b)
            std::cout << "inside ctx1,i==" << i << ",j==" << j << std::endl;
            c2=c2(i+j); // (c)
            return std::move(c2); // (f)
        },
        i,
        j);
int k=std::transfer_data<int>(c1); // (d)
std::cout << "k==" << k << std::endl;
c1=c1(); // (e)

output:
    inside c1,i==1,j==2
    k==3
