int a;
std::continuation lambda=
    std::callcc(  // (0)
        [&a](std::continuation && c){
            a=0;
            int b=1;
            for(;;){
                caller=caller.resume();  // (1)
                int next=a+b;
                a=b;
                b=next;
            }
            return std::move(caller);
        });
for (int j=0;j<10;++j) {
    std::cout << a << " ";  // (2)
    lambda=lambda.resume(); // (3)
}

output:
    0 1 1 2 3 5 8 13 21 34
