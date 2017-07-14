## BSD - SKT Core 1.2.7.1
----------------
![alt tag](https://dl.dropboxusercontent.com/u/21000833/SKT/Website/Splash.png)

 http://www.skt.info 
 Bitcointalk https://bitcointalk.org/index.php?topic=1370307
 
 


What is SKT?
----------------

SKT is an experimental and new digital currency that enables anonymous, instant
payments to anyone, anywhere in the world. SKT uses peer-to-peer technology
to operate without a central authority: transaction management and money subsidy
are carried out collectively by the network. SKT Core is the name of open
source software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the SKT Core software, see http://www.skt.info

License
-------

SKT Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is normally done in separate branches.
[Tags](https://github.com/LIMXTEC/SKT/tags) are created to indicate new official,
stable release versions of SKT Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).


Building process
-----------------

**compiling SKT from git**

Use the autogen script to prepare the build environment.

    ./autogen.sh
    ./configure
    make

**precompiled binaries**

Precompiled binaries are available at GitHub, see
http://sourceforge.net/projects/skt/files/?source=navbar

Always verify the signatures and checksums.


Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging message are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play skts" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regtest mode.

**DEBUG_LOCKORDER**

SKT Core is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of what locks
are held, and adds warning to the debug.log file if inconsistencies are detected.
