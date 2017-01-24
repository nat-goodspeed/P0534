using channel_t=boost::fibers::buffered_channel<std::string>;
channel_t chan1{1},chan2{1};
boost::fibers::fiber fping(
    [&chan1,&chan2]{
        chan1.push("ping");
        std::cout << chan2.value_pop() << "\n";
        chan1.push("ping");
        std::cout << chan2.value_pop() << "\n";
        chan1.push("ping");
        std::cout << chan2.value_pop() << "\n";
    });
boost::fibers::fiber fpong(
    [&chan1,&chan2]{
        std::cout << chan1.value_pop() << "\n";
        chan2.push("pong");
        std::cout << chan1.value_pop() << "\n";
        chan2.push("pong");
        std::cout << chan1.value_pop() << "\n";
        chan2.push("pong");
    });
fping.join();
fpong.join();

output:
    ping
    pong
    ping
    pong
    ping
    pong
