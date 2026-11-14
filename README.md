# Universal Media Center

A free, open media player and hub: play local and network media, live TV, addons, and more on Windows, Linux, macOS, Android and more.

## Contact

Questions or feedback? Reach us on Telegram: [@johnconstantine570](https://t.me/johnconstantine570)

## Building

See `docs/README.*.md` for your platform, then:

```
cmake -DCMAKE_BUILD_TYPE=Release -DAPP_PACKAGE=com.universalmediacenter.app ..
make -j$(nproc)
```

## Sync

`.github/workflows/sync.yml` pulls upstream changes daily, re-applies the Universal Media Center branding via `scripts/migrate.py`, and pushes.
