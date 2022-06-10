import functools


#a = fopen ('alice_copy.txt', 'r')
b = open ('result.txt', 'w')
with open('alice_copy.txt') as f:
    f_read_ch = functools.partial(f.read, 1)
    a = repr(f_read_ch)
    #b.write(a)
    for ch in iter(f_read_ch,'' ):
        b.write(ch + "\n")
        print '', repr(ch)
