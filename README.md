# PancakeStudio_CaseStudy or VehicleStreamer Plugin for Unreal Engine 5

Real-time UDP data streaming for physical vehicle simulation. Sends actor's location and rotation to a client at game FPS rate.

---

## Plugin Installation

1. Clone or copy the plugin folder into your project under:
 YourProjectName/Plugins/VehicleStreamer/

2. Right-click on the `.uproject` file and choose **"Generate Visual Studio project files"** (or regenerate project files on Mac).

3. Open your project and enable the plugin if not already active.

---

## Add Simulated Vehicle to the Scene

1. From the Content Browser, locate the `BP_TestVehicle` Blueprint.
2. Drag it into your level.
3. Press *Play* — the cube will move randomly and start sending its transform data over UDP.

---

## Using the UDP Client

This plugin streams the vehicle’s transform (location and rotation) via UDP to the IP and port specified in the settings (`127.0.0.1:8888` by default).

To receive and view this data in real time, a Python script named `udp_listener.py` is included in the project directory.

This script listens on the specified port and prints all incoming messages sent by Unreal Engine.

### How to Run the UDP Listener

#### On **Windows**:

```bash
python udp_listener.py
```
---

## Configurable Settings (Optional)

To change target IP and port:

1. Go to `Project Settings > Plugins > Vehicle Streamer`  in VehicleStreamerSettings.h
2. Edit the following:

- **UDP Server IP**
- **UDP Server Port**

Or edit directly in `DefaultGame.ini`:

```ini
[/Script/VehicleStreamer.VehicleStreamerSettings]
UDPServerIP=127.0.0.1
UDPServerPort=8888
```
#### On **MacOS**:

```bash
python3 udp_listener.py
```

Make sure Python is installed. You can verify it by running:

```bash
python --version (Windows)
```

```bash
python3 --version (macOS/Linux)
```
---

## Using in Other Projects

1. Copy `Plugins/VehicleStreamer` into the `Plugins` folder of your new project.
2. Regenerate project files.
3. Compile and use `BP_TestVehicle` or create your own vehicle class based on `ATestVehicle`.
4. Please don't forget the chamge cube mesh in CPP files for TestVehicle. 

---

## Development Notes

- Built in C++ with no Blueprint dependencies
- Uses `AsyncTask` for low-latency data sending
- Fully modular plugin
- Cross-platform UDP support via Unreal's socket API

---

Made with ❤️ by [Ibrahim Eren Kilisli](https://github.com/erenkilisli) for Pancake Studios as a Case Study