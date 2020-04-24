function fizzbuzz(n)
    switch !!(n % 3) | !!(n % 5) << 1
        case 0:
            return "FIZZBUZZ"
        case 1:
            return "FIZZ"
        case 2:
            return "BUZZ"
        default:
            return String(n)


for let i = 0; i < 20; ++i
    console.log(`[${i}] ${fizzbuzz(i)}`)
