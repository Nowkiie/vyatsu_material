def index_of_coincidence(text, period, pos):
    total_count = len(text)
    letter_count = {}
    test =""
    for i in range(pos, total_count, period):
        letter = text[i]
        if not letter.isspace():
            test = test + letter
            if letter.lower() in letter_count:
                letter_count[letter.lower()] += 1
            else:
                letter_count[letter.lower()] = 1
    
    ic = 0
    for letter, count in letter_count.items():
        ic += count * (count - 1)
    
    ic = ic / (total_count * (total_count - 1) / period)
    print(test)
    return ic


#text = "8№!@#|!@|'№'3№&~!>#№;"
text = "<~-,3&(№83|#(№-=:3~=(-'?!;~;33^.3;%(,~')"
for i in range(1, 6):
    print(i)
    period = i
    for j in range(0, i):
        ic = index_of_coincidence(text, period, j)
        print(ic)
