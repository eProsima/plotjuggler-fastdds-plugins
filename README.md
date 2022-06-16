# Fast DDS plugins for PlotJuggler

PlotJuggler works great with ROS, but it is not itself a "ROS" application.

ROS is supported through external plugins that can be found in this [repository](https://github.com/PlotJuggler/plotjuggler-ros-plugins/).

## Existing Plugins

- DataStream for Dynamic Types.

## Install with Debians (TODO)

> :warning: **TODO**

## Install from source using Colcon

### Qt dependencies

Download Qt dependencies for PlotJuggler:

```sh
sudo apt -y install qtbase5-dev libqt5svg5-dev libqt5websockets5-dev libqt5opengl5-dev libqt5x11extras5-dev libprotoc-dev
```

### Qt dependencies

Download Fast DDS dependencies as specified in the following [link](https://fast-dds.docs.eprosima.com/en/latest/installation/sources/sources_linux.html#requirements).
It is not needed to install Fast DDS, as it will be installed within this workspace.

### Download required projects

Create a colcon workspace and clone the repositories:

```bash
mkdir -p ~/plotjuggler_fastdds/src
cd ~/plotjuggler_fastdds
wget https://raw.githubusercontent.com/eProsima/plotjuggler-fastdds-plugins/main/plotjuggler_fastdds.repos
vcs import src < plotjuggler_fastdds.repos
```

### Compile using colcon

```bash
colcon build
```

## Use of Fast DDS Plugin

In order to use this plugin, execute the PlotJuggler application (`./install/plotjuggler/bin/plotjuggler/`).
Once in the application, go to the menu _App -> Preferences -> Plugins_ and add the location of the library
`plotjuggler_fastdds`, installed by this project in `INSTALL_PREFIX_PATH/bin`.
In case of colcon built, the path is `./install/plotjuggler_fastdds/bin/`.
