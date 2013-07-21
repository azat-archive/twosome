
Chat over SCTP
==============

- For more comfortable using of chat client see [rlwrap](http://linux.die.net/man/1/rlwrap) util.

Used libraries
---------------

- [boost tcp asio](http://www.boost.org/libs/intrusive)
- [boost::asio_sctp](http://code.halssoftware.com/p/boostasiosctp)
  - [with some minor patches](https://github.com/azat/boostasiosctp)
- [cmake for builds](http://cmake.org/)
- [boost log](http://www.boost.org/libs/log)

See also
----------

- Based on [boost_asio chat example](http://www.boost.org/doc/libs/1_45_0/doc/html/boost_asio/example/chat)

Building
========

Please look at [.travis.yml](.travis.yml) for this,
but in short you can run next commands on debian like distribution:

```shell
sudo apt-get install libboost1.54-all-dev

mkdir .cmake
cd .cmake
cmake ..
make

./twosomed &
./twosome
Go ahead!
```
