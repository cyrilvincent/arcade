import sys
d = open(sys.argv[1], 'rb').read()
S = lambda t, s: (t*16 + s-1)*256          # offset piste/secteur (secteur 1..16)
fat = d[S(20,2):S(20,2)+256]

def read_file(first, last_bytes):
    out, b = b'', first
    while True:
        v = fat[1+b]
        n = 8 if v < 0xC0 else v - 0xC0
        for i in range(n):
            out += d[S(b//2, (b%2)*8 + 1 + i):][:256]
        if v >= 0xC0: break
        b = v
    return out[:len(out) - 256 + last_bytes] if last_bytes else out

for s in range(3, 17):                      # directory
    for e in range(8):
        o = S(20, s) + e*32
        ent = d[o:o+32]
        if ent[0] in (0x00, 0xFF) or ent[11] != 2: continue   # type 2 = BIN
        name = ent[:8].decode('ascii','replace').strip() + '.' + ent[8:11].decode('ascii','replace').strip()
        data = read_file(ent[13], int.from_bytes(ent[14:16], 'big'))
        p = 0
        print(name)
        while p < len(data):
            if data[p] == 0:
                l = int.from_bytes(data[p+1:p+3], 'big'); a = int.from_bytes(data[p+3:p+5], 'big')
                print(f'  charge ${a:04X}-${a+l-1:04X} ({l} octets)'); p += 5 + l
            else:
                print(f'  exec   ${int.from_bytes(data[p+3:p+5], "big"):04X}'); break