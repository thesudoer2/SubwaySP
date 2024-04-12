What does Subwaysp do?
--------------

Subwaysp (stands for Subway Short Path) calculates the shortest path between two subway stations in any subway system based on number of stations.

Building Subwaysp
--------------

It's really simple. configure project by the following command:

    $ ./configure

Then run make command:

    $ make -j

To build project with debug information, you should export "BUILD_TYPE=Debug" variable and then run make command:

    $ export BUILD_TYPE=Debug ; make -j

_Note_: If you have build project in Release mode and now you want to build it in Debug mode, you should run `make clean` command at first and then run the above command.

_Note_: If you have build project in Debug mode and now you want to build it in Release mode, you should unset BUILD_TYPE variable by `unset BUILD_TYPE` command and then clean the project by `make clean` command and finally you can run `make -j` to build it in Release mode.

Running Subwaysp
-------------

To run subwaysp, just type:

    $ build/sybwaysp <start_subway_station> <end_subway_station>

Installing Subwaysp
--------------

To install project, after building project, you should run the following command:

    $ sudo make install

After installing the project, run `exec bash` on your Bash.

Uninstalling Subwaysp
--------------

To uninstall subwaysp, after building the project, you should run the following command:

    $ sudo make uninstall

Adapt With Any Subway System
-------------

If you want to use subwaysp prgoram to calculate the shortest path of your arbitrary subway system, you must delete res/stations.json and use your json of stations instead.

_Note_: Structure of Json file (for stations) must be as follows (it's just a sample don't rely on :) ):

```json
{
    "station1": {
        "relations": [
            {
                "name": "station3"
            }
        ]
    },
    "station2": {
        "relations": [
            {
                "name": "station3",
            }
        ]
    },
    "station3": {
        "relations": [
            {
                "name": "station1",
            },
            {
                "name": "station2",
            }
        ]
    }
}
```
