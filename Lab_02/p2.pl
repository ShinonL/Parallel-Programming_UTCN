gen_random_bytes(L, Len) :- length(L, Len), maplist(random(0, 2), L).

count(_, [], 0).
count(X, [X|T], N) :- !, count(X, T, N1), N is N1 + 1.
count(X, [_|T], N) :- count(X, T, N).

log_2(X, R) :- L1 is log10(X), L2 is log10(2), R is L1 / L2.

entropy(E, Len) :- 
    gen_random_bytes(L, Len), 
    count(1, L, NoOnes), 
    NoZeros is Len - NoOnes,
    OnesRatio is NoOnes / Len,
    ZerosRatio is NoZeros / Len,
    log_2(OnesRatio, Log1),
    log_2(ZerosRatio, Log2),
    E is 0 - OnesRatio * Log1 - ZerosRatio * Log2.

/*
 * ?- entropy(E, 1000000)
 * E = 0.9999999984736287
 * 
 * ?- entropy(E, 10)
 * E = 0.8812908992306927
 * 
 * ?- get_time(T0), entropy(E, 1000000), get_time(T1), Time is T1 - T0
 * E = 0.9999992844115998,
 * T0 = 1678641065.9152,
 * T1 = 1678641071.27598,
 * Time = 5.3607800006866455
 * */