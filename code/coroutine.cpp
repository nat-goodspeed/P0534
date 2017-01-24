boost::coroutines2::coroutine<int>::pull_type source(
    [](boost::coroutines2::coroutine<int>::push_type & sink){
        int first=1,second=1;
        sink(first);
        sink(second);
        for(int i=0;i<10;++i){
            int third=first+second;
            first=second;
            second=third;
            sink(third);
        }
    });
for(auto i: source){
    std::cout << i <<  " ";
}

output:
    0 1 1 2 3 5 8 13 21 34 55
