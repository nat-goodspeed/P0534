int i=1;
std::continuation lambda=
    std::callcc( // (a)
        [](std::continuation && caller){
            int j=std::get_data<int>(caller); // (b)
            std::cout << "inside lambda,j==" << j << std::endl;
            caller=caller(j+1); // (c)
            return std::move(caller); // (f)
        },
        i);
i=std::get_data<int>(lambda); // (d)
std::cout << "i==" << i << std::endl;
lambda=lambda(); // (e)

output:
    inside lambda,j==1
    i==2
