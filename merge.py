import os
import sys
import shutil 


def listdir(root):
    ret = []
    for ln in open(root + '/(listfile)').readlines():
        ret.append(ln.strip('\n'))
    return ret





def stat(name, fs):
    print(name, len(fs))
    return

    postfix = {}
    for f in fs:
        assert '.' in f
        pfx = f.split('.')[-1]
        postfix.setdefault(pfx, []).append(f)
    for pfx, fs2 in postfix.items():
        if pfx.lower() in ('mdx', 'blp', 'txt', 'html', 'wav', 'mp3', 'w3m', 'mid', 'jpg', 'ttf', 'tga', 'ai', 'pld'):
            #print('    ', pfx, len(fs2))
            pass
        else:
            print('    ', pfx)
            for f in fs2:
                print('       ', f)

def main(root = '../mpq'):

    roc = sorted(listdir(root + '/war3'))
    tft = sorted(listdir(root + '/war3x') + listdir(root + '/war3xlocal'))
    join = sorted(list(set(roc) & set(tft)))

    stat('roc', roc)
    stat('tft', tft)
    stat('roc & tft', join)

    shutil.rmtree(root + '/merge', ignore_errors=True)

    for d in ['war3', 'war3x', 'war3xlocal']:
        for f in listdir(root + '/' + d):
            f = f.replace('\\', '/')
            sf = root + '/' + d + '/' + f
            df = (root + '/merge/' + f).lower()
            os.makedirs(os.path.dirname(df), exist_ok=True)
            shutil.copyfile(sf, df)

if __name__ == '__main__':
    main()


