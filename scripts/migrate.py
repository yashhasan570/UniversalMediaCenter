#!/usr/bin/env python3
"""Re-apply the Universal Media Center rebrand after each upstream sync (idempotent)."""
from pathlib import Path
import os, re
from PIL import Image

ROOT = Path(__file__).resolve().parent.parent

def main():
    REPL = [
        ('XBMC Foundation','Universal Media Center project'),
        ('forum.kodi.tv','github.com/yashhasan570/UniversalMediaCenter'),
        ('kodi.wiki','github.com/yashhasan570/UniversalMediaCenter/wiki'),
        ('kodi.tv','github.com/yashhasan570/UniversalMediaCenter'),
        ('xbmc.org','github.com/yashhasan570/UniversalMediaCenter'),
        ('org.xbmc.kodi','com.universalmediacenter.app'),
        ('Kodi','Universal Media Center'),
    ]
    TEXT_EXTS = {'.cpp','.h','.hpp','.c','.m','.mm','.py','.xml','.md','.txt','.cmake','.in','.json','.yml','.yaml','.po','.pot','.ini','.cfg','.lua','.rss','.html','.js','.java','.gradle','.kts','.plist','.sh','.rb','.svg','.glsl','.frag','.vert','.info','.desktop','.spec','.nsi','.rc','.inc','.dox','.php','.xsd','.xsl','.sln','.vcxproj','.props','.targets','.ts','.tsx','.css','.rst','.tex'}
    SKIP = {'.git','node_modules','scripts'}
    changed = 0
    for dirpath, dirnames, filenames in os.walk(ROOT):
        dirnames[:] = [d for d in dirnames if d not in SKIP]
        for fn in filenames:
            p = Path(dirpath)/fn
            if p.suffix.lower() not in TEXT_EXTS: continue
            try: s = p.read_text(encoding='utf-8')
            except Exception: continue
            o = s
            for a,b in REPL: s = s.replace(a,b)
            if s != o:
                p.write_text(s, encoding='utf-8'); changed += 1
    badge = ROOT/'scripts/icons/badge.png'
    n = 0
    if badge.exists():
        img = Image.open(badge).convert('RGBA')
        for p in (ROOT/'media').glob('*.png'):
            m = re.match(r'(?i)icon(\d+)x(\d+)\.png', p.name)
            if m:
                w,h = int(m.group(1)), int(m.group(2))
            elif p.name == 'vendor_icon.png':
                w,h = 256,256
            else:
                continue
            canvas = Image.new('RGBA',(w,h),(0,0,0,0))
            inner = img.resize((w,h), Image.LANCZOS)
            canvas.paste(inner,(0,0),inner)
            canvas.save(p); n += 1
    print(f'migrate: {changed} files swept, {n} icon files updated')

if __name__ == '__main__':
    main()
