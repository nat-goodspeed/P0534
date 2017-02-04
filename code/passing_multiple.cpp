int i=1,j=2;
std::continuation lambda=
    std::callcc( // (0)
        [](std::continuation && caller){
            auto [i,j]=std::get_data<int,int>(caller); // (1)
            std::cout << "inside lambda,i==" << i << ",j==" << j << std::endl;
            caller=caller(i+j); // (2)
            return std::move(caller); // (5)
        },
        i,
        j);
int k=std::get_data<int>(lambda); // (3)
std::cout << "k==" << k << std::endl;
lambda=lambda(); // (4)

output:
    inside lambda,i==1,j==2
    k==3
