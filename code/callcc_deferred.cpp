template<typename Fn>
std::continuation callcc_deferred(Fn&& fn) {
    return std::callcc([auto fn=std::forward<Fn>(fn)](std::continuation&& caller){
        return fn(caller.resume());
    });
}
