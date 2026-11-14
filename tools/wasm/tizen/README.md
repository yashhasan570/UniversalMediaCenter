# Tizen web packaging template for Universal Media Center WASM

Source-controlled template files used to stage a Tizen web app from a WASM Universal Media Center
build.

The build, packaging and install workflow is documented in
[`docs/README.WASM.md`](../../../docs/README.WASM.md); SDK, device pairing and
certificate setup in [`docs/README.Tizen.md`](../../../docs/README.Tizen.md).
This file only describes what is in this directory and how it is staged.

## Files

- `icon.png`: application icon shown in the TV's Apps panel; 512x423 24-bit RGB PNG as Samsung requires, rendered from `tools/Linux/packaging/media/iconScalable.svg`.
- `config.xml.in`: CMake-configured Tizen widget metadata. Holds the
  application and package IDs (`kodiplayer.Universal Media Center` / `kodiplayer`), the
  `tv-samsung` profile, the widget version (Universal Media Center's `VERSION_CODE` from
  `version.txt`) and the privileges Universal Media Center needs: `internet`, and the public-level
  Samsung `network.public` and `productinfo` privileges that let the System
  Information window show the TV's network configuration, model and firmware.
  `required_version` is 6.5, the first Tizen TV release on Chromium 85, the
  oldest browser Emscripten targets by default.
- `tizen_web_project.yaml.in`: CMake-configured Tizen web project config. Its
  `signing_profile` is intentionally empty, which makes `tz` sign with whichever
  security profile is active.

The staged `index.html` is copied from the shared browser shell at
`tools/wasm/kodi.html` so browser and Tizen builds use the same entry page.

## Staging

`cmake --build <build-dir> --target package_tizen` assembles a complete Tizen
web project in `<build-dir>/tizen_packaging/Universal Media Center`:

- the template files from this directory
- `config.xml` and `tizen_web_project.yaml`, generated from their CMake
  templates
- `index.html`, the shared web entry page
- `media/splash.jpg`, the splash picture `index.html` shows while Universal Media Center loads
- the build artifacts `kodi.js`, `kodi.wasm` and `kodi.data`

`package_tizen_wgt` then packs and signs that directory into
`<build-dir>/tizen_packaging/Universal Media Center/Release/Universal Media Center.wgt` (`Debug/` for a Debug
CMake build), and `install_tizen_wgt` pushes it to a connected device. Both require the `tz` CLI to have been found
when CMake configured the build; the values that name the staging directory,
output name, profile and API version live in
`cmake/scripts/wasm/TizenTargets.cmake`.

## Profiling

Configure the build with `-DENABLE_WASM_PROFILING=ON` to preserve wasm function
names, then build and install with
`cmake --build <build-dir> --target install_tizen_wgt`.
Close Universal Media Center before running `tools/wasm/tizen/inspect.sh`, then attach DevTools
as described in [`docs/README.WASM.md`](../../../docs/README.WASM.md#74-launch-debug-and-remove).
