fun minbases lst =
    let
        fun sumOfPowers b k = (b - 1) div ((Int.pow(b, k + 1) - 1) div (b - 1))
        fun checkBase n b =
            if b > n then b - 1
            else if n mod (b - 1) = 0 andalso n div (b - 1) >= 1 andalso n div (b - 1) <= 9 then b
            else checkBase n (b + 1)
        fun findBase n = checkBase n 2
    in
        map findBase lst
    end;
