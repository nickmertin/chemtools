state_map = {
    '': 'MS_NONE',
    'solid': 'MS_SOLID',
    'liquid': 'MS_LIQUID',
    'gas': 'MS_GAS'
}

bonding_map = {
    '': 'BT_NONE',
    'atomic': 'BT_ATOMIC',
    'diatomic': 'BT_DIATOMIC',
    'metallic': 'BT_METALLIC',
    'covalent network': 'BT_COVALENT'
}

block_map = {
    'alkali metal': 'GB_ALKALI',
    'alkaline earth metal': 'GB_ALKALINE',
    'transition metal': 'GB_TRANSITION',
    'metal': 'GB_METAL',
    'post-transition metal': 'GB_METAL',
    'metalloid': 'GB_METALLOID',
    'nonmetal': 'GB_NONMETAL',
    'halogen': 'GB_HALOGEN',
    'noble gas': 'GB_NOBLE',
    'lanthanoid': 'GB_LANTHANOID',
    'actinoid': 'GB_ACTINOID'
}

def csv(line):
    i = 0
    s = 0
    ignore = False
    while i < len(line):
        if line[i] == '"':
            ignore = not ignore
        if not ignore and line[i] == ',':
            yield line[s:i]
            i += 1
            s = i
        else:
            i += 1

def f(s):
    try:
        return repr(float(s))
    except:
        return 'NAN'

with open('../base/table.inc', 'w') as out:
    for line in ([c for c in csv(s)] for s in open('../lib/periodic-table/data.csv')):
        if line[0] == 'atomicNumber':
            print('{},', file=out)
        else:
            print('{"%s", "%s", %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, base::%s, base::%s, base::%s},' % (line[1].strip(), line[2].strip().lower(), f(line[3][0:line[3].index('(')] if '(' in line[3] else line[3]), f(line[6]), f(line[7]), f(line[8]), f(line[9]), f(line[10]), f(line[11]), f(line[15]), f(line[16]), f(line[17]), state_map[line[13].strip()], bonding_map[line[14].strip()], block_map[line[18].strip()]), file=out)
