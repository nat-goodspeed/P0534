int i=1;
std::continuation lambda=
    std::callcc( // (0)
        [](std::continuation && caller){
            int j=std::get_data<int>(caller); // (1)
            std::cout << "inside lambda,j==" << j << std::endl;
            caller=caller(j+1); // (2)
            return std::move(caller); // (5)
        },
        i);
i=std::get_data<int>(lambda); // (3)
std::cout << "i==" << i << std::endl;
lambda=lambda(); // (4)

output:
    inside lambda,j==1
    i==2
