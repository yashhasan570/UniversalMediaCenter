// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2026 Team Universal Media Center
//
// Main-thread setup for Universal Media Center's WASM build: profile persistence, canvas focus
// and clipboard paste. Rendering goes through a WebGL context Emscripten
// creates on <canvas id="canvas"> and proxies to the Universal Media Center pthread.

// Persist Universal Media Center's user profile ($HOME/.Universal Media Center) to IndexedDB via IDBFS so that
// sources.xml, guisettings.xml, the databases, etc. survive a page refresh.
// Mount and populate run inside Module.preRun, and addRunDependency blocks
// main() until IDBFS has finished loading from IndexedDB.
(function installIdbfsPersistence() {
  var Module = globalThis.Module = globalThis.Module || {};
  var Universal Media Center = (Module.Universal Media Center = Module.Universal Media Center || {});
  var PROFILE_PATH = '/home/web_user/.Universal Media Center';

  Module.preRun = Module.preRun || [];
  Module.preRun.push(function mountUniversalMediaCenter*rofile() {
    try {
      FS.mkdirTree(PROFILE_PATH);
    } catch (e) {
      console.warn('[Universal Media Center] mkdirTree ' + PROFILE_PATH + ':', e);
    }

    try {
      FS.mount(IDBFS, {}, PROFILE_PATH);
    } catch (e) {
      console.warn('[Universal Media Center] IDBFS mount failed, profile will not persist:', e);
      return;
    }

    // Debounced background flush to IndexedDB. A callback runs once a flush
    // that started after it was queued has finished.
    var syncing = false;
    var pending = false;
    var waiting = [];
    function flushToIdb(done) {
      if (typeof done === 'function') { waiting.push(done); }
      if (syncing) { pending = true; return; }
      syncing = true;
      var callbacks = waiting;
      waiting = [];
      FS.syncfs(false, function (err) {
        syncing = false;
        if (err) { console.warn('[Universal Media Center] IDBFS persist:', err); }
        callbacks.forEach(function (cb) { cb(); });
        if (pending) { pending = false; flushToIdb(); }
      });
    }

    // Block main() until the profile has been loaded from IndexedDB. A flush
    // before then would delete whatever has not been loaded yet.
    addRunDependency('Universal Media Center-idbfs-populate');
    FS.syncfs(true, function (err) {
      removeRunDependency('Universal Media Center-idbfs-populate');
      if (err) {
        console.warn('[Universal Media Center] IDBFS populate failed, profile will not persist:', err);
        return;
      }

      Universal Media Center.flushProfile = flushToIdb;
      setInterval(flushToIdb, 5000);

      if (typeof window !== 'undefined') {
        window.addEventListener('pagehide', flushToIdb, { capture: true });
        window.addEventListener('beforeunload', flushToIdb, { capture: true });
        // A TV can stop a hidden app without either of the above firing.
        document.addEventListener('visibilitychange', function () {
          if (document.visibilityState === 'hidden') { flushToIdb(); }
        });
      }
    });
  });
})();

(function () {
  if (typeof document === 'undefined') {
    return; // pthread worker
  }

  var Module = globalThis.Module = globalThis.Module || {};
  var Universal Media Center = (Module.Universal Media Center = Module.Universal Media Center || {});

  // Called once Universal Media Center has shut down. A Tizen app has to close itself, after the
  // last profile changes are saved.
  Universal Media Center.onExit = function () {
    function close() {
      try {
        if (typeof tizen !== 'undefined' && tizen.application) {
          tizen.application.getCurrentApplication().exit();
        }
      } catch (e) {
        console.warn('[Universal Media Center] closing the app:', e);
      }
    }
    if (typeof Universal Media Center.flushProfile === 'function') { Universal Media Center.flushProfile(close); } else { close(); }
  };

  var canvas = document.getElementById('canvas');
  if (!canvas) {
    console.warn('[Universal Media Center] No <canvas id="canvas"> found; rendering disabled.');
    return;
  }
  // tabindex=0 allows the canvas to receive focus so paste and keyboard reach Universal Media Center.
  if (canvas.getAttribute('tabindex') === '-1' || canvas.getAttribute('tabindex') === null) {
    canvas.setAttribute('tabindex', '0');
  }

  // The WebGL context is created on this canvas by Emscripten (proxied from the
  // Universal Media Center pthread); nothing else may take a rendering context on it.
  Universal Media Center.canvas = canvas;

  var prevOnRuntime = Module.onRuntimeInitialized;
  Module.onRuntimeInitialized = function () {
    // Must run on the browser main thread (document is undefined on pthread workers).
    document.addEventListener(
        'paste',
        function (e) {
          // A paste into a DOM field (the native keyboard's input) is the browser's.
          var t = e.target;
          if (t && (t.tagName === 'INPUT' || t.tagName === 'TEXTAREA' || t.isContentEditable)) {
            return;
          }
          try {
            var text = (e.clipboardData && e.clipboardData.getData)
                ? e.clipboardData.getData('text/plain')
                : String();
            if (text === undefined || text === null) {
              text = String();
            }
            e.preventDefault();
            if (typeof Module.ccall === 'function') {
              Module.ccall('Universal Media Center_wasm_dispatch_paste', null, ['string'], [text]);
            }
          } catch (err) {
            console.error('[Universal Media Center] paste handler:', err);
          }
        },
        true);
    try { canvas.focus(); } catch (_) {}
    if (typeof prevOnRuntime === 'function') {
      try { prevOnRuntime(); } catch (e) { console.error(e); }
    }
  };
})();
