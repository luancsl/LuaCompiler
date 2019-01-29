
n = io.read()

function fac(n)
    p = 0

    if(n >= 1)then

        p = n * fac(n-1)

    else
        p = 1
    end

    return p

end

print(fac(n))