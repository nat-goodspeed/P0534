int i=1,j=2;
std::continuation lambda=
    std::callcc( // (a)
        [](std::continuation && caller){
            auto [i,j]=std::get_data<int,int>(caller); // (b)
            std::cout << "inside lambda,i==" << i << ",j==" << j << std::endl;
            caller=caller(i+j); // (c)
            return std::move(caller); // (f)
        },
        i,
        j);
int k=std::get_data<int>(lambda); // (d)
std::cout << "k==" << k << std::endl;
lambda=lambda(); // (e)

output:
    inside lambda,i==1,j==2
    k==3
