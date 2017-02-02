std::continuation c2=
    std::callcc(  // (a)
        [](std::continuation && c1){
            int a=0;
            int b=1;
            for(;;){
                c1=c1(a); // (b)
                int next=a+b;
                a=b;
                b=next;
            }
            return std::move(c1);
        });
for (int j=0;j<10;++j) {
    int i=std::transfer_data<int>(c2); // (c)
    std::cout << i << " ";
    c2=c2(); // (d)
}

output:
    0 1 1 2 3 5 8 13 21 34 55
