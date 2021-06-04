# Mondradiko Project Repository Layout
This document describes the high-level organization of the Mondradiko engine,
which encompasses several repositories, providing subsystems and libraries for
the engine as a whole.

# Utility Repositories
Utility repositories contain Mondradiko's various low-level subsystems.

Utility repos must be:
- lightweight
- easy to understand
- well-documented
- written in C (when appropriate)
- low-overhead (simple C APIs when possible)
- fully tested (coverage requirements will vary)

The main priority with these design rules is to make development efficient and
distributable. With minimal knowledge prerequisites for each repository, new
contributors can easily get on board, make their changes, then get their
contributions tested and merged. Longer-term contributors can also get their
changes merged quickly, as well as educate new contributors or third parties on
the design of that subsystem, leading to even more contribution and even more
integration with other projects.

Simplicity is key! Game engines are packed full of incredibly complex
engineering problems, and not preparing for that complexity ahead of time will
lead to the entire engine seizing up, both in terms of development efficiency
AND runtime performance.

Any subsystem implemented by a higher-level repository should be made a utility
repository, or moved into an existing utility repository, if possible. This way,
every single subsystem can stay distinct from the other subsystems, easy to
outsource work for, and easy to write tests for.

## `mdo-utils`

### Dependencies
- [libuv](https://libuv.org)
- [cmocka](https://cmocka.org/)
- [tomlc99](https://github.com/cktan/tomlc99)
- [Tracy](https://github.com/wolfpld/tracy)

### Services
- memory allocators
- data container structures
- testing framework (aided by cmocka)
- job scheduler (queues, workers, jobs, semaphores)
- frame profiling
- logging
- results
- cvars
- vector/matrix math?

## `mdo-assets`

### Dependencies
- [libuv](https://libuv.org)
- [lz4](https://lz4.github.io/lz4/)
- [xxHash](https://cyan4973.github.io/xxHash/)

### Services
- asynchronous file reading
- LZ4 de/compression
- xxHash checksum calculation
- asset indexing
- asset loader callbacks

## `mdo-renderer`

### Dependencies
- `mdo-utils`
- [Vulkan](https://www.vulkan.org/)
- [shaderc](https://github.com/Google/shaderc)

## `mdo-wasm` (needs renaming?)

### Dependencies
Project dependencies:
- `mdo-utils`

Runtimes:
- default: [Wasmtime](https://wasmtime.dev/)
- alternative: [Wasmer](https://wasmer.io/)
- embedded (Wasm within Wasm): [Wasm3](https://github.com/wasm3/wasm3)

### Services
- type conversion (host-to-Wasm, Wasm-to-host)
- binding functions for object-oriented methods
- abstract environment interfaces (AssemblyScript, Rust, C++, etc.)
- support for multiple Wasm runtimes
- stack sampling at regular intervals for performance profiling?
- GPU mapped buffer support (for real-time canvases)?

## `asc-cpp` (can be retargeted to C and renamed?)

### Dependencies
- `mdo-wasm`
- [AssemblyScript](https://www.assemblyscript.org/) compiler; built for Wasm
- [Binaryen](https://github.com/WebAssembly/binaryen)

### Services
- embeddable AssemblyScript compilation to Wasm
- reflection of exported classes?

## `mdo-ik` (needs renaming)

### Dependencies
- `mdo-utils`
- `mdo-wasm`

### Services
- built-in "standard" humanoid IK rig
- WebAssembly for custom IK rigs
- de/serialization of rig state
- concept of "avatars?"

## `mdo-ui` (needs renaming)

### Dependencies
- `mdo-utils`
- `mdo-wasm`
- protocol definition: [FlatBuffers](https://google.github.io/flatbuffers/)

### Services
- WebAssembly UI scripting
- FlatBuffers protocol definitions (can be used by any environment/language)
- binary source/sink data
- drawing API interface
- input event handlers (in 2D, per panel)
- panel geometry helpers (3D to 2D)
- standard widget classes
- native SDL-based test/demo rig
- browser-based test/demo rig

# Content Repositories
Content repositories are built on top of the
[utility repositories](utility-repositories) and define and operate on the data
that the Mondradiko engine uses at runtime.

These repositories are not meant to be usable outside of Mondradiko, and so we
can prioritize needs like performance, rapid development, and quick iteration
over needs like abstraction or minimum-prerequisite readability.

## mdo-asset-format (definitely needs renaming)

### Dependencies
- asset definitions: [FlatBuffers](https://google.github.io/flatbuffers/)

### Services
- asset format definitions
- C helper functions to convert vector types for example?

## mdo-converter (needs renaming)

### Dependencies
Project dependencies:
- `mdo-asset-format`
- `mdo-assets`

Third-party dependencies:
- manifest parsing: [tomlc99](https://github.com/cktan/tomlc99)
- glTF loading: [cgltf](https://github.com/jkuhlmann/cgltf)
- ...more libraries as needed...

### Services
- bundler manifest loading
- conversion to internal asset format from various supported external formats
- converted asset caching
- bundle dependency graph
- multithreaded conversion
- asset bundling

## mdo-core

### Dependencies
Project dependencies:
- `mdo-utils`
- `mdo-assets`
- `mdo-asset-format`
- `mdo-converter`
- `mdo-renderer`
- `mdo-ik`

Third-party dependencies:
- ECS: [EnTT](https://github.com/skypjack/entt)
- audio: [OpenAL Soft](https://openal-soft.org/)
- network protocol: [FlatBuffers](https://google.github.io/flatbuffers/)
- physics: [Bullet](https://pybullet.org/wordpress/)
- game networking: [libuv](https://libuv.org)
- IPC: [ZeroMQ](https://zeromq.org/)
- script sockets: WebSockets (?)

Display dependencies:
- desktop: [SDL2](https://www.libsdl.org/)
- universal XR: [OpenXR](https://www.khronos.org/OpenXR/)
- North Star: [Project Esky](https://docs.projectnorthstar.org/software/esky)

[ILLIXR](https://illixr.github.io/) can also be used as the OpenXR runtime
for rapidly developing drivers for XR hardware that does not yet have official
support in a heavier runtime like Monado or SteamVR.

### Services
- asset sources
  * from asset bundle
  * external format conversion from disk/cloud
  * asset transfer from server to client
- asset types
  * asset loader implementations for `mdo-assets`
  * asset garbage collection and refcounting
  * GPU asset transfer with `mdo-renderer`
- component definitions
  * scripting API
  * de/serialization functions
- component script runtime
  (can be made a utility repo and/or enhanced with Lunatic?)
  * message queue
  * message synchronization
  * message callback API
  * Wasm memory synchronization?
- physics with Bullet
- audio with OpenAL
- world simulation
  * entity hierarchy (aka. scene graph)
  * client visibility testing
  * client LOD?
- avatars (todo: details)
- network server (todo: details)
- network client (todo: details)
- voice chat (todo: details)
- world script runtime
  * send messages to component scripts
  * receive messages from component scripts
  * callbacks for world events (client join/leave, etc.)
  * world UI panel API
- IPC server for out-of-process plugins
  * UI clients
  * world queries
  * WebSockets for world scripts?
  * WebSockets for avatar/IK scripts?
- display implementations for various APIs
  * create renderer cameras
  * create avatars
  * process input
  * drive main event loop

# User Repositories
User repositories provide user-friendly front-ends to the content repositories.
These are directly coupled to the engine API itself, and can only be used for
Mondradiko and its subprojects. User repositories are reponsible for making
Mondradiko an accessible tool for game development and VR research.

## mdo-launcher

### Dependencies
- `mdo-core`
- [node.js](https://nodejs.org/)
- [Electron](https://www.electronjs.org/)
- whatever other node libraries we end up needing

### Services
- server management
- runtime version management
- core configuration
- stdout/stderr log capturing and recording
- automatic asset bundle downloading, extracting, and caching?

## mdo-editor

### Dependencies
- `mdo-core`
- `mdo-converter`
- `mdo-renderer`
- UX: [Qt](https://www.qt.io/)

### Services
- native Vulkan viewports into game world
- prefab editing
- project files
- direct playtesting and launching
- asset bundling
