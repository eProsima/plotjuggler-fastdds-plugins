# Fast DDS Visualizer Plugin

> :warning: **TODO**

## Existing Plugins

- Fast DDS Visualizer Plugin DataStream.

## Install from source using Colcon

### Qt dependencies

Download Qt dependencies for PlotJuggler:

```sh
sudo apt -y install qtbase5-dev libqt5svg5-dev libqt5websockets5-dev libqt5opengl5-dev libqt5x11extras5-dev libprotoc-dev
```

### Fast DDS dependencies

Download Fast DDS dependencies as specified in the following [link](https://fast-dds.docs.eprosima.com/en/latest/installation/sources/sources_linux.html#requirements).
It is not needed to install Fast DDS, as it will be installed within this workspace.

### Download required projects

Create a colcon workspace and clone the repositories:

```bash
mkdir -p ~/fastdds_visualizer_plugin/src
cd ~/fastdds_visualizer_plugin
wget https://raw.githubusercontent.com/eProsima/fastdds-visualizer-plugin/main/fastdds_visualizer_plugin.repos
vcs import src < fastdds_visualizer_plugin.repos
```

### Compile using colcon

```bash
colcon build
```

## Use Fast DDS Plugin

In order to use this plugin, execute the PlotJuggler application (`./install/plotjuggler/bin/plotjuggler/`).
Once in the application, go to the menu _App -> Preferences -> Plugins_ and add the location of the library
`fastdds_visualizer_plugin`, installed by this project in `INSTALL_PREFIX_PATH/bin`.
In case of colcon built, the path is `./install/fastdds_visualizer_plugin/bin/`.

### Dynamic Types

In order to use the Fast DDS Plugin of PlotJuggler, it is necessary to use Dynamic Types.
There are several ways to configure this:

1. Configure Fast DDS entities to share the data type information. This is done by:
    1. Have Data Type descriptor:
        1. Use Fast DDS Gen with `-objectype` option to generate Data Type description info from `.idl` file.
        1. Register Data Type from `.xml` file.
    1. Configure QoS to share Data Type Information.
        1. `auto_fill_type_information(true)`
        1. `auto_fill_type_object(true)`
1. Add the `.xml` file with the data types required.
