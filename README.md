
Chat over SCTP
==============

[![Build Status](https://travis-ci.org/azat/twosome.png)](https://travis-ci.org/azat/twosome)

- For more comfortable using of chat client see [rlwrap](http://linux.die.net/man/1/rlwrap) util.

Used libraries
---------------

- [boost tcp asio](http://www.boost.org/libs/intrusive)
- [boost::asio_sctp](http://code.halssoftware.com/p/boostasiosctp)
  - [with some minor patches](https://github.com/azat/boostasiosctp)
- [cmake for builds](http://cmake.org/)
- [boost log (proposal)](http://boost-log.sourceforge.net/)

See also
----------

- Based on [boost_asio chat example](http://www.boost.org/doc/libs/1_45_0/doc/html/boost_asio/example/chat)

Building
========

Please look at [.travis.yml](.travis.yml) for this,
but in short you can run next commands on debian like distribution:

```shell
sudo add-apt-repository -y ppa:azat/boost-unofficial
sudo apt-get update
sudo apt-get install libboost1.53-all-dev libsctp-dev

mkdir .cmake
cd .cmake
cmake ..
make

./twosomed &
./twosome
Go ahead!
```
