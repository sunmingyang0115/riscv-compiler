(export main)

#| computes the 27th prime |#

(int (isPrime [int a])
    (int ret)
    (cond
        [(= a 1) (set ret 0)]
        [1
            (int i)
            (set ret 1)
            (set i 2)
                (while (and ret (<= (* i i) a))
                    (cond
                        [(= (% a i) 0)
                            (set ret 0)])
                            (set i (+ i 1)))])
    ret)

(int (getNPrime [int n])
    (int ret)
    (int c)
    (int i)
    (set ret -1)
    (set c 0)
    (set i 1)
    (while (< c n)
        (cond
            [(isPrime i)
                
                (set c (+ c 1)) 
                (set ret i)])
        (set i (+ i 1)))
    ret)

(int (main)
    (print (getNPrime 27))
    0)

