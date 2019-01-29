
n = io.read()

function fac(n)

    if(n >= 1)then

        return n * fac(n - 1)

    else
        return 1
    end

end

print(fac(n))