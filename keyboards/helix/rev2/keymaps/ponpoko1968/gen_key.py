
templ='''
    /* {key} */
    {{.key_combo = {{NN_{key}, NN_LSFT, NN_NO}}, .key_sequence = KS_}},
    {{.key_combo = {{NN_{key}, NN_RSFT, NN_NO}}, .key_sequence = KS_}},
    {{.key_combo = {{NN_{key}, NN_NO, NN_NO}}, .key_sequence = KS_}},'''

for c in ['D','F','G',\
          'Z','X','C','V','B',\
          'Y','U','I','O','P',\
          'H','J','K','L','SCOLON','ENT',\
          'N','M','COMMA','DOT','SLASH']:
    a=templ.format(key=c)
    print(a)


