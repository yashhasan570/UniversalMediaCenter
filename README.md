# Universal Media Center

A free, open media player and hub: play local and network media, live TV, addons, and more on Windows, Linux, macOS, Android and more.

Universal Media Center is a fork of the Kodi codebase, maintained as a private build. The addon ecosystem is unchanged (Kodi addons keep working).

## Contact

Questions or feedback? Reach us on Telegram: [@johnconstantine570](https://t.me/johnconstantine570)

## Building

See `docs/README.*.md` for your platform, then:

```
cmake -DCMAKE_BUILD_TYPE=Release -DAPP_PACKAGE=com.universalmediacenter.app ..
make -j$(nproc)
```

## Sync

`.github/workflows/sync.yml` pulls upstream changes from the Kodi project daily, re-applies the Universal Media Center branding via `scripts/migrate.py`, and pushes.
