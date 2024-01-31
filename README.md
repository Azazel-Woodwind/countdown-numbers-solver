# Countdown Numbers Game Solver

I present 2 algorithms for solving the numbers game from the popular British Game Show, [Countdown](<https://en.wikipedia.org/wiki/Countdown_(game_show)>). One is based on a Brute Force method, the other is based on a Divide and Conquer strategy. From my testing, the Brute Force method has a better average time complexity, but can be very slow in the worst case. The Divide and Conquer strategy, while being a bit slower on average, has a more consistent run time for all inputs.

Running `Solver::solve` on the brute force or divide-and-conquer class yields a solution object containing the solution expressed in [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation).
