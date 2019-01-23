
n = io.read()

while (n > 1 )do

    if(n % 2 == 0)then
        n = n / 2
    else
        n = 3 * n + 1
    end

    print(n)
end


