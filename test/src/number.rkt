(export number_new number_del number_get number_set)

(int (_number_key) 932013)
(int (_number_error) (println 404) 0)

(long (number_new [int num])
    (long n)
    (set n (malloc 12))
    (set long^n (_number_key))
    (set int^(+ n 8) num)
    n)

(int (number_del [long n])
    (cond
        [(= long^n (_number_key))
            (free n)]
        [1 (_number_error)])
    0)

(int (number_get [long n])
    (int res)
    (cond
        [(= long^n (_number_key))
            (set res int^(+ n 8))]
        [1 (_number_error)])
    res)

(int (number_set [long n] [int num])
    (cond
        [(= long^n (_number_key))
            (set int^(+ n 8) num)]
        [1 (_number_error)])
    0)