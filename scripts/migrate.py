#!/usr/bin/env python3
"""Re-apply the Universal Media Center rebrand after each upstream sync (idempotent)."""
from pathlib import Path
import os, re

ROOT = Path(__file__).resolve().parent.parent

# Functional anchors that must never change:
#  - * / * = the add-on API namespace (python /gui/vfs modules,
#    C++ core dirs, event client). All third-party add-ons import these; renaming
#    them would kill the entire add-on ecosystem.
#  - * / * / .* / * /  = C++ binary add-on
#    ABI symbols and extension points (compiled add-ons link against them).
#  - org..universalmediacenter = official app package, referenced for interop.
ANCHORS = ['org.xbmc.kodi']CODE = [
    ('kodi.weblate.cloud', 'universalmediacenter.weblate.cloud'),
    ('KODI_', 'UNIVERSALMEDIA_'),
    ('KodiSwig', 'UniversalMediaCenterSwig'),
    ('KodiConfig', 'UniversalMediaCenterConfig'),
    ('KodiTupleTraits', 'UniversalMediaCenterTupleTraits'),
    ('KodiTpNew', 'UniversalMediaCenterTpNew'),
    ('KodiDictTraits', 'UniversalMediaCenterDictTraits'),
    ('KodiAlternativeTraits', 'UniversalMediaCenterAlternativeTraits'),
    ('KodiSend', 'UniversalMediaCenterSend'),
    ('KodiDeepLinkActivity', 'UniversalMediaCenterDeepLinkActivity'),
    ('KODI', 'UNIVERSAL MEDIA CENTER'),
    ('Kodi', 'Universal Media Center'),
    ('kodi', 'universalmediacenter'),
]
DOC = [
    ('kodi.weblate.cloud', 'universalmediacenter.weblate.cloud'),
    ('KODI', 'UNIVERSAL MEDIA CENTER'),
    ('Kodi', 'Universal Media Center'),
    ('kodi', 'Universal Media Center'),
]
CODE_EXT = {'.cpp', '.h', '.c', '.hpp', '.cc', '.java', '.kt', '.kts', '.py', '.sh',
            '.cmake', '.in', '.m', '.mm', '.swift', '.gradle', '.json', '.xml', '.yml',
            '.yaml', '.bat', '.pl', '.rb', '.rs', '.proto', '.txt', '.pyi', '.spec',
            '.iss', '.nsi', '.rc', '.md'}

def main():
    changed = 0
    for dirpath, dirnames, filenames in os.walk(ROOT):
        rel = os.path.relpath(dirpath, ROOT).replace(os.sep, '/')
        if rel == '.':
            dirnames[:] = [d for d in dirnames if d not in ('.git', 'scripts')]
        elif rel.split('/')[0] in ('.git', 'scripts'):
            dirnames[:] = []
        for fn in filenames:
            p = Path(dirpath) / fn
            if p.suffix.lower() not in CODE_EXT and p.suffix != '': continue
            try: s = p.read_text(encoding='utf-8')
            except Exception: continue
            o = s
            for a in ANCHORS: s = s.replace(a, chr(2) + chr(1))
            pairs = CODE if p.suffix.lower() in CODE_EXT else DOC
            for a, b in pairs: s = s.replace(a, b)
            s = s.replace(chr(2) + chr(1), '')
            if pairs is DOC: s = re.sub(r'Universal Media Center[A-Za-z]', 'UniversalMediaCenter*', s)
            if s != o:
                p.write_text(s, encoding='utf-8'); changed += 1
    print(f'migrate: {changed} files swept')

if __name__ == '__main__':
    main()
