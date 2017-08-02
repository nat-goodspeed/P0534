int i=1;
std::continuation lambda=
    std::callcc(  // (0)
        [&i](std::continuation && caller){
            std::cout << "inside lambda,i==" << i << std::endl;
            i+=1;  // (1)
            caller=caller.resume();  // (2)
            return std::move(caller);  // (4)
        });
std::cout << "i==" << i << std::endl;
lambda=lambda.resume();  // (3)

output:
    inside lambda,i==1
    i==2
