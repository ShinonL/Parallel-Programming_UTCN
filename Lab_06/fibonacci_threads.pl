% fork N threads
fork_threads(0, _, _, _, _, _, _, []) :- !.
fork_threads(N, NN, MaxN, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom, [H|T]) :-
    N1 is N-1,
    fork_threads(N1, NN, MaxN, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom, T),
    thread_create(worker(N, NN, MaxN, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom), H, []).

% join N threads
join_threads([]).
join_threads([H|T]) :- thread_join(H, _), join_threads(T).

% fork-join N threads
nt(N, MaxN) :-
    get_time(T0),
    compute_sqrt5(MaxN, Sqrt5Nom, Sqrt5Denom),
    compute_phi(Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom),
    fork_threads(N, N, MaxN, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom, List),
    join_threads(List),
    get_time(T1),
    T is (T1 - T0) * 1000,
    write('Elapsed Time : '),
    write(T),
    nl.

worker(CurrentNumber, NoThreads, MaxN, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom) :-
    CurrentNumber =< MaxN, !,
    compute_fibonacci(CurrentNumber, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom, R),
    assert(fib(CurrentNumber, R)),
    NextNumber is CurrentNumber + NoThreads,
    worker(NextNumber, NoThreads, MaxN, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom).

compute_fibonacci(Number, Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom, R) :-
   	PhiBy5Nom is PhiNom ^ Number * Sqrt5Nom,
    PhiBy5Denom is PhiDenom ^ Number * 5 * Sqrt5Denom,

    RNom is 2 * PhiBy5Nom + PhiBy5Denom,
    RDenom is 2 * PhiBy5Denom,
	R is RNom // RDenom.

compute_sqrt5(MaxN, Sqrt5Nom, Sqrt5Denom) :-
    Precision is 2 * MaxN // 10 + 100,
    Integer is 5 * (10 ^ (2 * Precision)),
    nth_integer_root_and_remainder(2, Integer, Sqrt5Nom, _),
    Sqrt5Denom is 10 ^ Precision.
    
compute_phi(Sqrt5Nom, Sqrt5Denom, PhiNom, PhiDenom) :-
    PhiNom is Sqrt5Denom + Sqrt5Nom,
    PhiDenom is 2 * Sqrt5Denom.
